#pragma once

#include "CoreMinimal.h"
#include "VoxelCellTypes.generated.h"

USTRUCT(BlueprintType)
struct FVoxelCell2D
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntPoint Index = FIntPoint(0,0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D MinXY = FVector2D::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D MaxXY = FVector2D::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D CenterXY = FVector2D::ZeroVector;
};
