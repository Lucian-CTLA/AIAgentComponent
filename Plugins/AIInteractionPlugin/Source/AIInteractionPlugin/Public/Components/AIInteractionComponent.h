#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIInteractionComponent.generated.h"

UCLASS(
    ClassGroup = (AIInteraction),
    meta = (BlueprintSpawnableComponent)
)
class AIINTERACTIONPLUGIN_API UAIInteractionComponent
    : public UActorComponent
{
    GENERATED_BODY()

public:

    UAIInteractionComponent();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "AI Interaction"
    )
    float DetectRadius = 500.0f;

    UPROPERTY(
        BlueprintReadOnly,
        Category = "AI Interaction"
    )
    TArray<AActor*> DetectedActors;

    UPROPERTY(
        BlueprintReadOnly,
        Category = "AI Interaction"
    )
    AActor* CurrentTarget = nullptr;

    UFUNCTION(
        BlueprintCallable,
        Category = "AI Interaction"
    )
    void ScanInteractableActors();

    UFUNCTION(
        BlueprintCallable,
        Category = "AI Interaction"
    )
    void SetCurrentTarget(AActor* TargetActor);

    UFUNCTION(
        BlueprintCallable,
        Category = "AI Interaction"
    )
    void InteractWithCurrentTarget(FName ActionName);
};