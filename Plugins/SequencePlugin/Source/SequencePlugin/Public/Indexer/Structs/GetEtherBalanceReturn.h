// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "EtherBalance.h"
#include "GetEtherBalanceReturn.generated.h"

USTRUCT(BlueprintType)
struct FGetEtherBalanceReturn
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY()
        FEtherBalance balance;
    bool customConstructor = false;//used to tell buildresponse whether or not to use a custom constructor OR the unreal one!
    void construct(FJsonObject json_in) {};//dummy construct for templating

    /*
    * Used to Handle Edge Cases with Unreal's Json parsing
    */
    void setup(FJsonObject json_in) {};//dummy method to allow for templating in build response!
};