#include "AgenticSplineLibrary.h"

#include "AgenticSplineMoverComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"

void UAgenticSplineLibrary::SnapActorToSplineDistance(AActor* const Actor, USplineComponent* const Spline, const float Distance, const bool bAlignRotation, const bool bAlignScale)
{
	if (!Actor || !Spline)
	{
		return;
	}

	Actor->SetActorLocation(Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World));

	if (bAlignRotation)
	{
		Actor->SetActorRotation(Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World));
	}

	if (bAlignScale)
	{
		Actor->SetActorScale3D(Spline->GetScaleAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World));
	}
}

UAgenticSplineMoverComponent* UAgenticSplineLibrary::ConfigureSplineMover(AActor* const Actor, USplineComponent* const Spline, const float StartNormalizedTime, const bool bAutoStart)
{
	if (!Actor || !Spline)
	{
		return nullptr;
	}

	UAgenticSplineMoverComponent* Mover = Actor->FindComponentByClass<UAgenticSplineMoverComponent>();
	if (!Mover)
	{
		Mover = NewObject<UAgenticSplineMoverComponent>(Actor);
		if (!Mover)
		{
			return nullptr;
		}

		Mover->RegisterComponent();
		Actor->AddInstanceComponent(Mover);
	}

	Mover->TargetSpline = Spline;
	Mover->SetNormalizedTime(StartNormalizedTime);
	Mover->bAutoStart = bAutoStart;

	if (bAutoStart)
	{
		Mover->StartMovement();
	}
	else
	{
		Mover->StopMovement();
	}

	return Mover;
}
