// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TerrainCoordinateUtils.generated.h"


class ALandscapeProxy;
/**
 * 
 */
UCLASS()
class ASP_OSWALD_LEANDRO_API UTerrainCoordinateUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Terrain|Units")
	static float CmToMeters(float Cm) { return Cm / 100.0f; }

	UFUNCTION(BlueprintPure, Category="Terrain|Units")
	static float MetersToCm(float Meters) { return Meters * 100.0f; }

	UFUNCTION(BlueprintPure, Category="Terrain|Coords")
	static bool WorldToLandscapeLocal(const ALandscapeProxy* Landscape, const FVector& WorldPos, FVector& OutLocalPos);

	UFUNCTION(BlueprintPure, Category="Terrain|Coords")
	static bool LandscapeLocalToWorld(const ALandscapeProxy* Landscape, const FVector& LocalPos, FVector& OutWorldPos);
};
