#include "Components/InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    bCanInteract = false;
    InteractionRange = 250.0f;
    InteractionType = TEXT("Default");

    AvailableActions.Add(TEXT("Interact"));
}

void UInteractableComponent::SetInteractionEnabled(
    bool bEnabled
)
{
    bCanInteract = bEnabled;
}

bool UInteractableComponent::CanExecuteAction(
    FName ActionName
) const
{
    if (!bCanInteract)
    {
        return false;
    }

    return AvailableActions.Contains(ActionName);
}