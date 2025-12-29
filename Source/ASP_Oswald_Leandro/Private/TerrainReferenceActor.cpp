// Fill out your copyright notice in the Description page of Project Settings.
#include "TerrainReferenceActor.h"
#include "Landscape.h"
#include "LandscapeProxy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Was macht dieses Script?
// - Hält eine Referenz auf "ALandscapeProxy"
// - Kann Landscape automatisch finden (optional)
// - Liefert World Bounds (Min/Max) und Transform-Infos

// Sets default values
ATerrainReferenceActor::ATerrainReferenceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Falls Landscape nicht gesetzt ist
void ATerrainReferenceActor::AutoFindLandscape()
{
	if (!GetWorld()) return;

	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscapeProxy::StaticClass(), Found);

	if (Found.Num() > 0)
	{
		Landscape = Cast<ALandscapeProxy>(Found[0]);
	}
}

// World Bounds vom Landscape (AABB)
bool ATerrainReferenceActor::GetLandscapeWorldBounds(FVector& OutMin, FVector& OutMax) const
{
	if (!Landscape) return false;

	// LandscapeProxy hat RootComponent Bounds
	const FBox Bounds = Landscape->GetComponentsBoundingBox(true);
	OutMin = Bounds.Min;
	OutMax = Bounds.Max;
	return true;
}

// True wenn WorldPos innerhalb Bounds liegt
bool ATerrainReferenceActor::IsWorldPosInsideLandscapeBounds(const FVector& WorldPos) const
{
	FVector Min, Max;
	if (!GetLandscapeWorldBounds(Min, Max)) return false;

	return (WorldPos.X >= Min.X && WorldPos.X <= Max.X &&
			WorldPos.Y >= Min.Y && WorldPos.Y <= Max.Y);
}

// For Testing ONLY
void ATerrainReferenceActor::DebugPrintLandscapeBounds()
{
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("World is null"));
		return;
	}

	FVector Min, Max;
	if (!GetLandscapeWorldBounds(Min, Max))
	{
		UE_LOG(LogTemp, Warning, TEXT("Landscape not valid"));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Landscape Bounds Min: %s"), *Min.ToString());
	UE_LOG(LogTemp, Display, TEXT("Landscape Bounds Max: %s"), *Max.ToString());

	// DEBUG BOX IM VIEWPORT
	DrawDebugBox(
		GetWorld(),
		(Min + Max) * 0.5f,     // Center
		(Max - Min) * 0.5f,     // Extent
		FColor::Green,
		false,                  // Not persistent
		10.0f,                  // Lifetime (Sekunden)
		0,
		50.0f                   // Linienstaerke
	);
}

// Called when the game starts or when spawned
void ATerrainReferenceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainReferenceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

