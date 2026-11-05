#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

UCLASS(
    ClassGroup = (AIInteraction),
    meta = (BlueprintSpawnableComponent)
)
class AIINTERACTIONPLUGIN_API UInteractableComponent
    : public UActorComponent
{
    GENERATED_BODY()

public:

    UInteractableComponent();

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "AI Interaction"
    )
    bool bCanInteract = false;

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "AI Interaction"
    )
    float InteractionRange = 250.0f;

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "AI Interaction"
    )
    FName InteractionType = TEXT("Default");

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "AI Interaction"
    )
    TArray<FName> AvailableActions;

    UFUNCTION(BlueprintCallable, Category = "AI Interaction")
    void SetInteractionEnabled(bool bEnabled);

    UFUNCTION(BlueprintPure, Category = "AI Interaction")
    bool CanExecuteAction(FName ActionName) const;
};