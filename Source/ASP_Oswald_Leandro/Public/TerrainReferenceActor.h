// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainReferenceActor.generated.h"

class ALandscapeProxy;

UCLASS()
class ASP_OSWALD_LEANDRO_API ATerrainReferenceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainReferenceActor();

	UPROPERTY(EditAnywhere, Category="Terrain")
	TObjectPtr<ALandscapeProxy> Landscape;

	// Falls Landscape nicht gesetzt ist
	UFUNCTION(CallInEditor, Category="Terrain")
	void AutoFindLandscape();

	// World Bounds vom Landscape (AABB)
	UFUNCTION(BlueprintCallable, Category="Terrain")
	bool GetLandscapeWorldBounds(FVector& OutMin, FVector& OutMax) const;

	// True wenn WorldPos innerhalb Bounds liegt
	UFUNCTION(BlueprintCallable, Category="Terrain")
	bool IsWorldPosInsideLandscapeBounds(const FVector& WorldPos) const;

	// For Testin ONLY
	UFUNCTION(CallInEditor, Category="Terrain|Debug")
	void DebugPrintLandscapeBounds();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
