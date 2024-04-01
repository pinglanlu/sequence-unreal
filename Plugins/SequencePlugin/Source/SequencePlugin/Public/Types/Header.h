// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.
#pragma once
#include "BinaryData.h"
#include "Dom/JsonObject.h"
#include "Types.h"

struct FHeader
{
	FHash256 ParentHash;
	FHash256 UncleHash;
	FAddress Coinbase;
	FHash256 Root;
	FHash256 TxHash;
	FHash256 ReceiptHash;
	FBloom Bloom;
	FUnsizedData Difficulty;
	FUnsizedData Number;
	uint64 GasLimit;
	uint64 GasUsed;
	uint64 Time;
	FUnsizedData ExtraData;
	FHash256 MixDigest;
	FBlockNonce Nonce;
	FUnsizedData BaseFee;
};

FHeader JsonToHeader(TSharedPtr<FJsonObject> Json);
