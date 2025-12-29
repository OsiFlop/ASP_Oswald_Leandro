// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightQueryProbeActor.h"
#include "VoxelGridBaker.h"
#include "VoxelHeightCache.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHeightQueryProbeActor::AHeightQueryProbeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AHeightQueryProbeActor::WorldXYToCell(const FVector& WorldPos, int32& OutX, int32& OutY) const
{
	if (!GridBaker || !HeightCache || !HeightCache->IsValid())
		return false;

	const FVector Min = GridBaker->GridMinWorld;
	const float CellSizeCm = GridBaker->CellSizeCm;

	if (CellSizeCm <= 0.0f)
		return false;

	const float LocalX = WorldPos.X - Min.X;
	const float LocalY = WorldPos.Y - Min.Y;

	OutX = FMath::FloorToInt(LocalX / CellSizeCm);
	OutY = FMath::FloorToInt(LocalY / CellSizeCm);

	if (OutX < 0 || OutY < 0 || OutX >= HeightCache->GridSize.X || OutY >= HeightCache->GridSize.Y)
		return false;

	return true;
}

void AHeightQueryProbeActor::QueryHeightAtMyLocation()
{
	if (!GridBaker || !HeightCache)
	{
		UE_LOG(LogTemp, Warning, TEXT("QueryHeightAtMyLocation failed: missing GridBaker or HeightCache ref"));
		return;
	}

	if (!HeightCache->IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("QueryHeightAtMyLocation failed: HeightCache invalid. Bake first."));
		return;
	}

	const FVector P = GetActorLocation();

	int32 X, Y;
	if (!WorldXYToCell(P, X, Y))
	{
		UE_LOG(LogTemp, Warning, TEXT("Query: position not inside grid. World=%s"), *P.ToString());
		return;
	}

	const int32 Idx = HeightCache->ToIndex(X, Y);
	const float MaxZcm = HeightCache->MaxHeightCm[Idx];

	UE_LOG(LogTemp, Display, TEXT("Query @ WorldXY(%.1f, %.1f) -> Cell(%d,%d) -> MaxZ=%.1f cm (%.2f m)"),
		P.X, P.Y, X, Y, MaxZcm, MaxZcm / 100.0f);

	if (bDrawMarker && GetWorld())
	{
		const FVector MarkerLoc(P.X, P.Y, MaxZcm);
		DrawDebugSphere(GetWorld(), MarkerLoc, 200.0f, 12, FColor::Yellow, false, MarkerLifeTime, 0, 4.0f);
		DrawDebugString(GetWorld(), MarkerLoc + FVector(0,0,250.0f),
			FString::Printf(TEXT("Cell(%d,%d)\nZ=%.2fm"), X, Y, MaxZcm/100.0f),
			nullptr, FColor::White, MarkerLifeTime, false);
	}
}

