// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Authenticator.h"
#include "GameFramework/SpectatorPawn.h"
#include "Sqnc_Spec_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class SEQUENCEPLUGIN_API ASqnc_Spec_Pawn : public ASpectatorPawn
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FCredentials_BE Credentials;
	
	
	UFUNCTION(BlueprintCallable, CATEGORY="FUNCTION")
	void SetupCredentials(FCredentials_BE CredentialsIn);
	
};
