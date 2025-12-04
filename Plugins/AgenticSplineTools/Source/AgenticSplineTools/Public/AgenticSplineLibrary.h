#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AgenticSplineLibrary.generated.h"

class UAgenticSplineMoverComponent;
class USplineComponent;

/**
 * Blueprint helpers for common spline workflow operations.
 */
UCLASS()
class AGENTICSPLINETOOLS_API UAgenticSplineLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Sets the owning actor transform to the provided distance along the spline. */
	UFUNCTION(BlueprintCallable, Category = "Agentic|Spline")
	static void SnapActorToSplineDistance(AActor* Actor, USplineComponent* Spline, float Distance, bool bAlignRotation = true, bool bAlignScale = false);

	/** Adds or reuses a spline mover on an actor and optionally auto starts it. */
	UFUNCTION(BlueprintCallable, Category = "Agentic|Spline")
	static UAgenticSplineMoverComponent* ConfigureSplineMover(AActor* Actor, USplineComponent* Spline, float StartNormalizedTime = 0.f, bool bAutoStart = true);
};
