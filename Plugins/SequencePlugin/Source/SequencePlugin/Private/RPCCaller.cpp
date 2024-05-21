// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#include "..\Public\RPCCaller.h"
#include "Util/HexUtility.h"
#include "RequestHandler.h"
#include "Templates/SharedPointer.h"
#include "Serialization/JsonReader.h"

TSharedPtr<FJsonObject> URPCCaller::Parse(FString JsonRaw)
{
	TSharedPtr<FJsonObject> JsonParsed;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		return JsonParsed;
	}

	return nullptr;
}

TResult<TSharedPtr<FJsonObject>> URPCCaller::ExtractJsonObjectResult(FString JsonRaw)
{
	TSharedPtr<FJsonObject> Json = Parse(JsonRaw);
	
	if(!Json)
	{
		return MakeError(FSequenceError(EmptyResponse, "Could not extract response"));
	}

	return MakeValue(Json->GetObjectField(TEXT("result")));
}

TResult<FString> URPCCaller::ExtractStringResult(FString JsonRaw)
{
	TSharedPtr<FJsonObject> Json = Parse(JsonRaw);
	
	if(!Json)
	{
		return MakeError(FSequenceError(EmptyResponse, "Could not extract response"));
	}

	return MakeValue(Json->GetStringField(TEXT("result")));
}

TResult<uint64> URPCCaller::ExtractUIntResult(FString JsonRaw)
{
	TResult<FString> Result = ExtractStringResult(JsonRaw);
	if(!Result.HasValue())
	{
		return MakeError(Result.GetError());
	}

	TOptional<uint64> Convert = HexStringToUint64(Result.GetValue());
	if(!Convert.IsSet())
	{
		return MakeError(FSequenceError(ResponseParseError, "Couldn't convert \"" + Result.GetValue() + "\" to a number."));
	}
	return MakeValue(Convert.GetValue());
}

void URPCCaller::SendRPC(FString Url, FString Content, TSuccessCallback<FString> OnSuccess, FFailureCallback OnError)
{
	NewObject<URequestHandler>()
		->PrepareRequest()
		->WithUrl(Url)
		->WithHeader("Content-type", "application/json")
		->WithHeader("Accept", "application/json")
		->WithVerb("POST")
		->WithContentAsString(Content)
		->ProcessAndThen(OnSuccess, OnError);
}

FJsonBuilder URPCCaller::RPCBuilder(const FString MethodName)
{
	return *FJsonBuilder().ToPtr()
		->AddString("jsonrpc", "2.0")
		->AddInt("id", 1)
		->AddString("method", MethodName);
}