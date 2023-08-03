#pragma once

#include "CoreMinimal.h"
#include "PingReturn.generated.h"

USTRUCT(BlueprintType)
struct FPingReturn
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY()
        bool status = false;
    bool customConstructor = false;//used to tell buildresponse whether or not to use a custom constructor OR the unreal one!
    void construct(FJsonObject json_in) {};//dummy construct for templating
    void setup(FJsonObject json_in) {};//dummy method to allow for templating in build response!
};