// Fill out your copyright notice in the Description page of Project Settings.


#include "Provider.h"

#include "HexUtility.h"
#include "HttpManager.h"
#include "JsonBuilder.h"
#include "JsonObjectConverter.h"
#include "RequestHandler.h"

FString TagToString(EBlockTag Tag)
{
	switch (Tag)
	{
	case Latest:
		return "latest";
	case Earliest:
		return "earliest";
	case Pending:
		return "pending";
	case Safe:
		return "safe";
	case Finalized:
		return "finalized";
	}

	return "";
}

TResult<TSharedPtr<FJsonObject>> Provider::GetBlockByNumberHelper(FString Number)
{
	const auto Content = FJsonBuilder().ToPtr()
		->AddString("jsonrpc", "2.0")
		->AddInt("id", 1)
		->AddString("method", "eth_getBlockByNumber")
		->AddArray("params").ToPtr()
			->AddValue(Number)
			->AddBool(true)
			->EndArray()
		->ToString();
	return ExtractJsonObjectResult(SendRPC(Content));
}

TSharedPtr<FJsonObject> Provider::Parse(FString JsonRaw)
{
	TSharedPtr<FJsonObject> JsonParsed;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		return JsonParsed;
	}

	return nullptr;
}

TResult<TSharedPtr<FJsonObject>> Provider::ExtractJsonObjectResult(FString JsonRaw)
{
	auto Json = Parse(JsonRaw);
	
	if(!Json)
	{
		return MakeError(SequenceError(EmptyResponse, "Could not extract response"));
	}

	return MakeValue(Json->GetObjectField("result"));
}

TResult<FString> Provider::ExtractStringResult(FString JsonRaw)
{
	auto Json = Parse(JsonRaw);
	
	if(!Json)
	{
		return MakeError(SequenceError(EmptyResponse, "Could not extract response"));
	}

	return MakeValue(Json->GetStringField("result"));
}

TResult<uint32> Provider::ExtractUInt32Result(FString JsonRaw)
{
	auto Result = ExtractStringResult(JsonRaw);
	if(!Result.HasValue())
	{
		return MakeError(Result.GetError());
	}
	
	auto Convert =  HexStringToInt(Result.GetValue());
	if(!Convert.IsSet())
	{
		return MakeError(SequenceError(ResponseParseError, "Couldn't convert \"" + Result.GetValue() + "\" to a number."));
	}
	return MakeValue(Convert.GetValue());
}

FString Provider::SendRPC(FString Content)
{
	auto responseContent = NewObject<URequestHandler>()
		->PrepareRequest()
		->WithUrl(Url)
		->WithHeader("Content-type", "application/json")
		->WithVerb("POST")
		->WithContentAsString(Content)
		->Process()
		->GetContentAsString();

	UE_LOG(LogTemp, Display, TEXT("Received response: %s"), *responseContent);

	return responseContent;
}

TResult<uint32> Provider::TransactionCountHelper(Hash256 Hash, FString Number)
{
	const auto Content = RPCBuilder("eth_getTransactionCount").ToPtr()
		->AddArray("params").ToPtr()
			->AddString(Hash256ToHexString(Hash))
			->AddValue(Number)
			->EndArray()
		->ToString();
	return ExtractUInt32Result(SendRPC(Content));
}

FJsonBuilder Provider::RPCBuilder(const FString MethodName)
{
	return *FJsonBuilder().ToPtr()
		->AddString("jsonrpc", "2.0")
		->AddInt("id", 1)
		->AddString("method", MethodName);
}

Provider::Provider(FString Url) : Url(Url)
{
}

TResult<TSharedPtr<FJsonObject>>  Provider::BlockByNumber(uint16 Id)
{
	return GetBlockByNumberHelper(ConvertString(IntToHexString(Id)));
}

TResult<TSharedPtr<FJsonObject>> Provider::BlockByNumber(EBlockTag Tag)
{
	return GetBlockByNumberHelper(ConvertString(TagToString(Tag)));
}

TResult<TSharedPtr<FJsonObject>> Provider::BlockByHash(Hash256 Hash)
{
	const auto Content = RPCBuilder("eth_getBlockByHash").ToPtr()
		->AddArray("params").ToPtr()
			->AddString(Hash256ToHexString(Hash))
			->AddBool(true)
			->EndArray()
		->ToString();
	return ExtractJsonObjectResult(SendRPC(Content));
}

TResult<uint32> Provider::BlockNumber()
{
	const auto Content = RPCBuilder("eth_blockNumber").ToString();
	return ExtractUInt32Result(SendRPC(Content));
}

TResult<TSharedPtr<FJsonObject>> Provider::TransactionByHash(Hash256 Hash)
{
	const auto Content = RPCBuilder("eth_getTransactionByHash").ToPtr()
		->AddArray("params").ToPtr()
			->AddString(Hash256ToHexString(Hash))
			->EndArray()
		->ToString();
	return ExtractJsonObjectResult(SendRPC(Content));
}

TResult<uint32> Provider::TransactionCount(Hash256 Hash, uint16 Number)
{
	return TransactionCountHelper(Hash, ConvertInt(Number));
}

TResult<uint32> Provider::TransactionCount(Hash256 Hash, EBlockTag Tag)
{
	return TransactionCountHelper(Hash, ConvertString(TagToString(Tag)));
}

TResult<TSharedPtr<FJsonObject>> Provider::TransactionReceipt(Hash256 Hash)
{
	const auto Content = RPCBuilder("eth_getTransactionReceipt").ToPtr()
		->AddArray("params").ToPtr()
			->AddString(Hash256ToHexString(Hash))
			->EndArray()
		->ToString();
	return ExtractJsonObjectResult(SendRPC(Content));
}

TValueOrError<uint32, SequenceError> Provider::ChainId()
{
	const auto Content = RPCBuilder("eth_chainId").ToString();
	return ExtractUInt32Result(SendRPC(Content));
}