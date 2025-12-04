#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AgenticSplineMoverComponent.generated.h"

class USplineComponent;

/**
 * Component that drives an owning actor along a target spline at a configurable speed.
 * Intended to be lightweight and designer-friendly with Blueprint exposure.
 */
UCLASS(ClassGroup = (Agentic), meta = (BlueprintSpawnableComponent))
class AGENTICSPLINETOOLS_API UAgenticSplineMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAgenticSplineMoverComponent();

	/** Spline that the actor will follow. If unset, attempts auto-discovery on BeginPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TObjectPtr<USplineComponent> TargetSpline;

	/** Units per second traversal speed used while moving forward on the spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (ClampMin = "0.0"))
	float ForwardSpeed;

	/** Units per second traversal speed used when reversing direction along the spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (ClampMin = "0.0"))
	float ReverseSpeed;

	/** Starting distance in world units along the spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float StartDistance;

	/** Whether movement should automatically begin on BeginPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bAutoStart;

	/** Looping keeps movement continuous by wrapping the param at the end instead of stopping. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bLoop;

	/** When true, movement reverses direction at the end instead of stopping or looping. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bPingPong;

	/** If true, actor rotation matches the spline rotation using world transform. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bAlignRotationToSpline;

	/** If true, actor's scale is to match the spline scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bAlignScaleToSpline;

	/** Updates spline reference by searching components on the owning actor. */
	UFUNCTION(BlueprintCallable, Category = "Spline Mover")
	void RefreshSplineReference();

	/** Start moving along the spline. */
	UFUNCTION(BlueprintCallable, Category = "Spline Mover")
	void StartMovement();

	/** Stop movement and retain the current spline distance. */
	UFUNCTION(BlueprintCallable, Category = "Spline Mover")
	void StopMovement();

	/** Force the mover to a normalized position on the spline in the range [0, 1]. */
	UFUNCTION(BlueprintCallable, Category = "Spline Mover")
	void SetNormalizedTime(const float NormalizedTime);

	/** Current normalized time on the spline in the range [0, 1]. */
	UFUNCTION(BlueprintPure, Category = "Spline Mover")
	float GetNormalizedTime() const;

	/** Current spline distance along the curve. */
	UFUNCTION(BlueprintPure, Category = "Spline Mover")
	float GetCurrentDistance() const { return CurrentDistance; }

protected:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float GetMaxDistance() const;
	float GetStepSpeed() const;
	void ApplyTransformAtDistance(const float Distance);

	UPROPERTY(Transient)
	float CurrentDistance;

	UPROPERTY(Transient)
	int32 TravelDirection;

	UPROPERTY(Transient)
	bool bIsMoving;
};
