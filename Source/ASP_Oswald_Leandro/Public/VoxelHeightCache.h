// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VoxelHeightCache.generated.h"

/**
 * 
 */
UCLASS()
class ASP_OSWALD_LEANDRO_API UVoxelHeightCache : public UDataAsset
{
	GENERATED_BODY()

public:
	// Grid Parameter zum Re-Konstruieren
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid")
	FVector GridMinWorld = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid")
	FIntPoint GridSize = FIntPoint(0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid")
	float CellSizeCm = 0.0f;

	// Pro Zelle: hoechster Punkt in World-Z (cm)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Data")
	TArray<float> MaxHeightCm;

	// Optional: Sea level in World-Z (cm), damit du "ueber Meer" rechnen kannst
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data")
	float SeaLevelWorldZCm = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Data")
	void Allocate(int32 SizeX, int32 SizeY)
	{
		GridSize = FIntPoint(SizeX, SizeY);
		MaxHeightCm.SetNum(SizeX * SizeY);
		for (float& V : MaxHeightCm) V = -FLT_MAX;
	}

	UFUNCTION(BlueprintCallable, Category="Data")
	bool IsValid() const
	{
		return CellSizeCm > 0.0f && GridSize.X > 0 && GridSize.Y > 0 && MaxHeightCm.Num() == GridSize.X * GridSize.Y;
	}

	UFUNCTION(BlueprintCallable, Category="Data")
	int32 ToIndex(int32 X, int32 Y) const
	{
		return X + Y * GridSize.X;
	}

	UFUNCTION(BlueprintCallable, Category="Data")
	float GetHeightMetersASL(int32 X, int32 Y) const
	{
		const int32 Idx = ToIndex(X, Y);
		if (!MaxHeightCm.IsValidIndex(Idx)) return 0.0f;
		return (MaxHeightCm[Idx] - SeaLevelWorldZCm) / 100.0f;
	}
};
