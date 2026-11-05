#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIInteractableInterface.generated.h"

UINTERFACE(Blueprintable)
class AIINTERACTIONPLUGIN_API UAIInteractableInterface
    : public UInterface
{
    GENERATED_BODY()
};

class AIINTERACTIONPLUGIN_API IAIInteractableInterface
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI Interaction")
    bool CanInteract(AActor* Interactor);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI Interaction")
    void ReceiveInteraction(
        AActor* Interactor,
        FName ActionName
    );
};