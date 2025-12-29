// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelCellTypes.h"
#include "VoxelHeightCache.h"
#include "VoxelGridBaker.generated.h"

class ATerrainReferenceActor;
class UVoxelGridConfig;

UCLASS()
class ASP_OSWALD_LEANDRO_API AVoxelGridBaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelGridBaker();
	
	UPROPERTY(EditAnywhere, Category="References")
	TObjectPtr<ATerrainReferenceActor> TerrainRef;

	UPROPERTY(EditAnywhere, Category="Config")
	TObjectPtr<UVoxelGridConfig> GridConfig;

	// Grid Daten (minimal)
	UPROPERTY(VisibleAnywhere, Category="Grid")
	FVector GridMinWorld = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category="Grid")
	FVector GridMaxWorld = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category="Grid")
	FIntPoint GridSize = FIntPoint(0, 0);

	UPROPERTY(VisibleAnywhere, Category="Grid")
	float CellSizeCm = 0.0f;

	UFUNCTION(CallInEditor, Category="Voxel | Grid")
	void BuildGrid();

	UFUNCTION(CallInEditor, Category="Voxel | Grid")
	void DebugDrawGridOutline();

	// Zeichnet nur wenige Zellen, on-the-fly berechnet
	UFUNCTION(CallInEditor, Category="Voxel | Grid")
	void DebugDrawSomeCells(int32 MaxCellsToDraw = 1000);

	UFUNCTION(CallInEditor, Category="Voxel | Grid")
	void DebugDrawSomeCells50();

	UPROPERTY(EditAnywhere, Category="Output")
	TObjectPtr<UVoxelHeightCache> HeightCache;

	UFUNCTION(CallInEditor, Category="Voxel|Bake")
	void BakeMaxHeights();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool IsGridValid() const;

	// Hilfsfunktionen fuer Zellberechnung
	void GetCellMinMaxXY(const int32 X, const int32 Y, FVector2D& OutMin, FVector2D& OutMax) const;
};
