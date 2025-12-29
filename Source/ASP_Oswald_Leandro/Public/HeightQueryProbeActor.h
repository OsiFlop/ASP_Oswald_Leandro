// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectPtr.h"
#include "GameFramework/Actor.h"
#include "HeightQueryProbeActor.generated.h"

class AVoxelGridBaker;
class UVoxelHeightCache;

UCLASS()
class ASP_OSWALD_LEANDRO_API AHeightQueryProbeActor : public AActor
{
	GENERATED_BODY()
	
public:
	AHeightQueryProbeActor();

	UPROPERTY(EditAnywhere, Category="References")
	TObjectPtr<AVoxelGridBaker> GridBaker;

	UPROPERTY(EditAnywhere, Category="References")
	TObjectPtr<UVoxelHeightCache> HeightCache;

	UFUNCTION(CallInEditor, Category="HeightQuery")
	void QueryHeightAtMyLocation();

	UPROPERTY(EditAnywhere, Category="Debug")
	bool bDrawMarker = true;

	UPROPERTY(EditAnywhere, Category="Debug")
	float MarkerLifeTime = 5.0f;

private:
	bool WorldXYToCell(const FVector& WorldPos, int32& OutX, int32& OutY) const;
};
