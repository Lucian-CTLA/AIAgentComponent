#include "Components/AIInteractionComponent.h"
#include "Components/InteractableComponent.h"
#include "Interfaces/AIInteractableInterface.h"

#include "Engine/World.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"

UAIInteractionComponent::UAIInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    DetectRadius = 500.0f;
}

void UAIInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UAIInteractionComponent::ScanInteractableActors()
{
    if (!GetOwner() || !GetWorld())
    {
        return;
    }

    DetectedActors.Empty();

    const FVector Center =
        GetOwner()->GetActorLocation();

    const FCollisionShape Sphere =
        FCollisionShape::MakeSphere(DetectRadius);

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    FCollisionObjectQueryParams ObjectQueryParams;

    ObjectQueryParams.AddObjectTypesToQuery(
        ECC_WorldStatic
    );

    ObjectQueryParams.AddObjectTypesToQuery(
        ECC_WorldDynamic
    );

    TArray<FOverlapResult> OverlapResults;

    const bool bHasResults =
        GetWorld()->OverlapMultiByObjectType(
            OverlapResults,
            Center,
            FQuat::Identity,
            ObjectQueryParams,
            Sphere,
            QueryParams
        );

    if (!bHasResults)
    {
        DrawDebugSphere(
            GetWorld(),
            Center,
            DetectRadius,
            24,
            FColor::Red,
            false,
            1.0f
        );

        return;
    }

    for (const FOverlapResult& Result : OverlapResults)
    {
        AActor* OtherActor =
            Result.GetActor();

        if (!OtherActor)
        {
            continue;
        }

        UInteractableComponent* Interactable =
            OtherActor->FindComponentByClass<
            UInteractableComponent
            >();

        if (!Interactable)
        {
            continue;
        }

        if (!Interactable->bCanInteract)
        {
            continue;
        }

        DetectedActors.AddUnique(OtherActor);
    }

    DrawDebugSphere(
        GetWorld(),
        Center,
        DetectRadius,
        24,
        FColor::Green,
        false,
        1.0f
    );
}

void UAIInteractionComponent::SetCurrentTarget(
    AActor* TargetActor
)
{
    if (!TargetActor)
    {
        CurrentTarget = nullptr;
        return;
    }

    if (!DetectedActors.Contains(TargetActor))
    {
        CurrentTarget = nullptr;
        return;
    }

    CurrentTarget = TargetActor;
}

void UAIInteractionComponent::InteractWithCurrentTarget(
    FName ActionName
)
{
    if (!CurrentTarget)
    {
        return;
    }

    UInteractableComponent* Interactable =
        CurrentTarget->FindComponentByClass<
        UInteractableComponent
        >();

    if (!Interactable)
    {
        return;
    }

    if (!Interactable->CanExecuteAction(ActionName))
    {
        return;
    }

    if (!CurrentTarget->GetClass()->ImplementsInterface(
        UAIInteractableInterface::StaticClass()
    ))
    {
        return;
    }

    IAIInteractableInterface::Execute_ReceiveInteraction(
        CurrentTarget,
        GetOwner(),
        ActionName
    );
}