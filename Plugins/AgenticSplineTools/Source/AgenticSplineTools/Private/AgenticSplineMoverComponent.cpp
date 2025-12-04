#include "AgenticSplineMoverComponent.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"

namespace AgenticSplineMover::Constants
{
	constexpr float KindaSmallDistance = 0.01f;
}

UAgenticSplineMoverComponent::UAgenticSplineMoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	bTickInEditor = true;

	ForwardSpeed = 300.f;
	ReverseSpeed = 300.f;
	StartDistance = 0.f;
	bAutoStart = true;
	bLoop = false;
	bPingPong = true;
	bAlignRotationToSpline = true;
	bAlignScaleToSpline = false;

	CurrentDistance = 0.f;
	TravelDirection = 1;
	bIsMoving = false;
}

void UAgenticSplineMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!TargetSpline)
	{
		RefreshSplineReference();
	}

	CurrentDistance = StartDistance;
	TravelDirection = 1;
	bIsMoving = bAutoStart && TargetSpline != nullptr;

	if (!bIsMoving)
	{
		SetComponentTickEnabled(TargetSpline != nullptr);
	}

	if (TargetSpline)
	{
		ApplyTransformAtDistance(CurrentDistance);
	}
}

void UAgenticSplineMoverComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* const ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving || !TargetSpline || DeltaTime <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	const float MaxDistance = GetMaxDistance();
	if (MaxDistance <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	const float StepSpeed = GetStepSpeed();
	if (StepSpeed <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	CurrentDistance += static_cast<float>(TravelDirection) * StepSpeed * DeltaTime;

	if (bLoop)
	{
		while (CurrentDistance >= MaxDistance)
		{
			CurrentDistance -= MaxDistance;
		}
		while (CurrentDistance < 0.f)
		{
			CurrentDistance += MaxDistance;
		}
	}
	else if (bPingPong)
	{
		if (CurrentDistance >= MaxDistance)
		{
			CurrentDistance = MaxDistance;
			TravelDirection = -1;
		}
		else if (CurrentDistance <= 0.f)
		{
			CurrentDistance = 0.f;
			TravelDirection = 1;
		}
	}
	else
	{
		if (CurrentDistance >= MaxDistance)
		{
			CurrentDistance = MaxDistance;
			StopMovement();
		}
		else if (CurrentDistance <= 0.f)
		{
			CurrentDistance = 0.f;
			StopMovement();
		}
	}

	ApplyTransformAtDistance(CurrentDistance);
}

void UAgenticSplineMoverComponent::RefreshSplineReference()
{
	if (TargetSpline)
	{
		return;
	}

	if (const AActor* Owner = GetOwner())
	{
		TargetSpline = Owner->FindComponentByClass<USplineComponent>();
	}
}

void UAgenticSplineMoverComponent::StartMovement()
{
	if (!TargetSpline)
	{
		RefreshSplineReference();
	}

	if (!TargetSpline)
	{
		return;
	}

	bIsMoving = true;
	SetComponentTickEnabled(true);

	if (bPingPong && (CurrentDistance <= 0.f || CurrentDistance >= GetMaxDistance() - AgenticSplineMover::Constants::KindaSmallDistance))
	{
		TravelDirection = CurrentDistance <= 0.f ? 1 : -1;
	}
}

void UAgenticSplineMoverComponent::StopMovement()
{
	bIsMoving = false;
	SetComponentTickEnabled(false);
}

void UAgenticSplineMoverComponent::SetNormalizedTime(const float NormalizedTime)
{
	const float ClampedAlpha = FMath::Clamp(NormalizedTime, 0.f, 1.f);
	const float MaxDistance = GetMaxDistance();
	if (MaxDistance <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	CurrentDistance = ClampedAlpha * MaxDistance;
	ApplyTransformAtDistance(CurrentDistance);
}

float UAgenticSplineMoverComponent::GetNormalizedTime() const
{
	const float MaxDistance = GetMaxDistance();
	if (MaxDistance <= KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}

	return CurrentDistance / MaxDistance;
}

float UAgenticSplineMoverComponent::GetMaxDistance() const
{
	return TargetSpline ? TargetSpline->GetSplineLength() : 0.f;
}

float UAgenticSplineMoverComponent::GetStepSpeed() const
{
	return TravelDirection >= 0 ? ForwardSpeed : ReverseSpeed;
}

void UAgenticSplineMoverComponent::ApplyTransformAtDistance(const float Distance)
{
	if (!TargetSpline || !GetOwner())
	{
		return;
	}

	const FVector Location = TargetSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	GetOwner()->SetActorLocation(Location);

	if (bAlignRotationToSpline)
	{
		const FRotator Rotation = TargetSpline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		GetOwner()->SetActorRotation(Rotation);
	}

	if (bAlignScaleToSpline)
	{
		const FVector Scale = TargetSpline->GetScaleAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		GetOwner()->SetActorScale3D(Scale);
	}
}
