// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VoxelGridConfig.generated.h"

/**
 * 
 */
UCLASS()
class ASP_OSWALD_LEANDRO_API UVoxelGridConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Voxel/Zellgroesse in Metern (XY)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid")
	float CellSizeMeters = 100.0f;

	// Padding um Landscape Bounds herum in Metern
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid")
	float PaddingMeters = 0.0f;

	// Debug: wie viele Sekunden Debug-Lines sichtbar bleiben
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug")
	float DebugDrawLifetime = 10.0f;

	// Debug: Linienstaerke
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug")
	float DebugLineThickness = 2.0f;

	// Wie viele Samples pro Zelle pro Achse (z.B. 3 => 3x3 = 9)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sampling")
	int32 SamplesPerAxis = 3;

	// Trace Start hoehe ueber Zelle (Meter)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sampling")
	float TraceStartAboveMeters = 3000.0f;

	// Trace End hoehe unter Zelle (Meter)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sampling")
	float TraceEndBelowMeters = 3000.0f;

	// Collision channel fuer Terrain
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sampling")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

};
