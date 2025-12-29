// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelGridBaker.h"
#include "TerrainReferenceActor.h"
#include "VoxelGridConfig.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LandscapeProxy.h"


// Sets default values
AVoxelGridBaker::AVoxelGridBaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AVoxelGridBaker::IsGridValid() const
{
	return (GridSize.X > 0 && GridSize.Y > 0 && CellSizeCm > 0.0f);
}

void AVoxelGridBaker::GetCellMinMaxXY(const int32 X, const int32 Y, FVector2D& OutMin, FVector2D& OutMax) const
{
	const float MinX = GridMinWorld.X + (float)X * CellSizeCm;
	const float MinY = GridMinWorld.Y + (float)Y * CellSizeCm;
	const float MaxX = MinX + CellSizeCm;
	const float MaxY = MinY + CellSizeCm;

	OutMin = FVector2D(MinX, MinY);
	OutMax = FVector2D(MaxX, MaxY);
}

void AVoxelGridBaker::BuildGrid()
{
	if (!TerrainRef || !GridConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildGrid failed: TerrainRef or GridConfig missing"));
		return;
	}

	FVector LMin, LMax;
	if (!TerrainRef->GetLandscapeWorldBounds(LMin, LMax))
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildGrid failed: Landscape bounds not available"));
		return;
	}

	CellSizeCm = GridConfig->CellSizeMeters * 100.0f;
	if (CellSizeCm <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildGrid failed: CellSizeMeters must be > 0"));
		return;
	}

	const float PaddingCm = GridConfig->PaddingMeters * 100.0f;

	GridMinWorld = FVector(LMin.X - PaddingCm, LMin.Y - PaddingCm, 0.0f);
	GridMaxWorld = FVector(LMax.X + PaddingCm, LMax.Y + PaddingCm, 0.0f);

	const float WidthCm  = GridMaxWorld.X - GridMinWorld.X;
	const float HeightCm = GridMaxWorld.Y - GridMinWorld.Y;

	GridSize.X = FMath::Max(1, FMath::CeilToInt(WidthCm  / CellSizeCm));
	GridSize.Y = FMath::Max(1, FMath::CeilToInt(HeightCm / CellSizeCm));

	const int32 TotalCells = GridSize.X * GridSize.Y;

	UE_LOG(LogTemp, Display, TEXT("Grid Built: Size=%d x %d (Cells=%d), CellSize=%.2fm"),
		GridSize.X, GridSize.Y, TotalCells, GridConfig->CellSizeMeters);
}

void AVoxelGridBaker::DebugDrawGridOutline()
{
	if (!GetWorld() || !GridConfig || !IsGridValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("DebugDrawGridOutline failed: grid not built or config missing"));
		return;
	}

	const float Z = 0.0f;
	const FVector A(GridMinWorld.X, GridMinWorld.Y, Z);
	const FVector B(GridMaxWorld.X, GridMinWorld.Y, Z);
	const FVector C(GridMaxWorld.X, GridMaxWorld.Y, Z);
	const FVector D(GridMinWorld.X, GridMaxWorld.Y, Z);

	DrawDebugLine(GetWorld(), A, B, FColor::Cyan, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
	DrawDebugLine(GetWorld(), B, C, FColor::Cyan, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
	DrawDebugLine(GetWorld(), C, D, FColor::Cyan, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
	DrawDebugLine(GetWorld(), D, A, FColor::Cyan, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
}

void AVoxelGridBaker::DebugDrawSomeCells(int32 MaxCellsToDraw)
{
	if (!GetWorld() || !GridConfig || !IsGridValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("DebugDrawSomeCells failed: grid not built or config missing"));
		return;
	}

	MaxCellsToDraw = FMath::Max(0, MaxCellsToDraw);

	const int32 TotalCells = GridSize.X * GridSize.Y;
	const int32 Count = FMath::Min(MaxCellsToDraw, TotalCells);

	const float Z = 0.0f;

	for (int32 i = 0; i < Count; ++i)
	{
		const int32 X = i % GridSize.X;
		const int32 Y = i / GridSize.X;

		FVector2D MinXY, MaxXY;
		GetCellMinMaxXY(X, Y, MinXY, MaxXY);

		const FVector A(MinXY.X, MinXY.Y, Z);
		const FVector B(MaxXY.X, MinXY.Y, Z);
		const FVector C(MaxXY.X, MaxXY.Y, Z);
		const FVector D(MinXY.X, MaxXY.Y, Z);

		DrawDebugLine(GetWorld(), A, B, FColor::Green, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
		DrawDebugLine(GetWorld(), B, C, FColor::Green, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
		DrawDebugLine(GetWorld(), C, D, FColor::Green, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
		DrawDebugLine(GetWorld(), D, A, FColor::Green, false, GridConfig->DebugDrawLifetime, 0, GridConfig->DebugLineThickness);
	}
}

void AVoxelGridBaker::DebugDrawSomeCells50()
{
	DebugDrawSomeCells(1000);
}

void AVoxelGridBaker::BakeMaxHeights()
{
	if (!GetWorld() || !TerrainRef || !GridConfig || !HeightCache)
	{
		UE_LOG(LogTemp, Warning, TEXT("BakeMaxHeights failed: missing references (World/TerrainRef/GridConfig/HeightCache)"));
		return;
	}

	if (!IsGridValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("BakeMaxHeights failed: Grid not built. Click BuildGrid first."));
		return;
	}

	ALandscapeProxy* Landscape = TerrainRef->Landscape;
	if (!Landscape)
	{
		UE_LOG(LogTemp, Warning, TEXT("BakeMaxHeights failed: TerrainRef has no Landscape set."));
		return;
	}

	// Cache initialisieren
	HeightCache->GridMinWorld = GridMinWorld;
	HeightCache->CellSizeCm = CellSizeCm;
	HeightCache->Allocate(GridSize.X, GridSize.Y);

	const int32 SamplesPerAxis = FMath::Max(1, GridConfig->SamplesPerAxis);
	const int32 SamplesTotal = SamplesPerAxis * SamplesPerAxis;

	const float TraceStartCm = GridConfig->TraceStartAboveMeters * 100.0f;
	const float TraceEndCm   = GridConfig->TraceEndBelowMeters * 100.0f;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(VoxelBakeTrace), true);
	Params.bReturnPhysicalMaterial = false;
	Params.AddIgnoredActor(this);

	// Optional: Falls du nur Landscape treffen willst, koennte man hier ObjectQuery machen.
	// Wir bleiben bei Channel, weil es simpel und robust ist.

	int32 HitCount = 0;
	const int32 TotalCells = GridSize.X * GridSize.Y;

	for (int32 Y = 0; Y < GridSize.Y; ++Y)
	{
		for (int32 X = 0; X < GridSize.X; ++X)
		{
			float MaxZ = -FLT_MAX;

			// Zell-Min/Max
			const float CellMinX = GridMinWorld.X + (float)X * CellSizeCm;
			const float CellMinY = GridMinWorld.Y + (float)Y * CellSizeCm;

			// Sampling Schritt innerhalb der Zelle
			// Wir sampeln in der Mitte von Sub-Cells, damit es gleichmaessig verteilt ist.
			for (int32 sy = 0; sy < SamplesPerAxis; ++sy)
			{
				for (int32 sx = 0; sx < SamplesPerAxis; ++sx)
				{
					const float U = ((float)sx + 0.5f) / (float)SamplesPerAxis; // 0..1
					const float V = ((float)sy + 0.5f) / (float)SamplesPerAxis;

					const float SampleX = CellMinX + U * CellSizeCm;
					const float SampleY = CellMinY + V * CellSizeCm;

					// Trace von oben nach unten
					const FVector Start(SampleX, SampleY, Landscape->GetActorLocation().Z + TraceStartCm);
					const FVector End  (SampleX, SampleY, Landscape->GetActorLocation().Z - TraceEndCm);

					FHitResult Hit;
					const bool bHit = GetWorld()->LineTraceSingleByChannel(
						Hit,
						Start,
						End,
						GridConfig->TraceChannel,
						Params
					);

					if (bHit)
					{
						HitCount++;
						MaxZ = FMath::Max(MaxZ, Hit.Location.Z);
					}
				}
			}

			const int32 Idx = HeightCache->ToIndex(X, Y);
			HeightCache->MaxHeightCm[Idx] = MaxZ;
		}
	}

	// Asset dirty machen (damit UE merkt, dass sich DataAsset geaendert hat)
#if WITH_EDITOR
	HeightCache->Modify();
#endif

	UE_LOG(LogTemp, Display, TEXT("Bake complete. Cells=%d, SamplesPerCell=%d, TotalTraces=%d, Hits=%d"),
		TotalCells, SamplesTotal, TotalCells * SamplesTotal, HitCount);
}

// Called when the game starts or when spawned
void AVoxelGridBaker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelGridBaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

