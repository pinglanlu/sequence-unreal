#pragma once
#include "BinaryData.h"
#include "Types.h"

class FEthTransaction
{
	FBlockNonce Nonce;
	FNonUniformData GasPrice;
	FNonUniformData GasLimit;
	FAddress To;
	FNonUniformData Value;
	FNonUniformData Data;
	FNonUniformData V;
	FHash256 R;
	FHash256 S;
public:
	FEthTransaction(FBlockNonce Nonce, FNonUniformData GasPrice, FNonUniformData GasLimit, FAddress To, FNonUniformData Value, FNonUniformData Data);

	void Sign(FPrivateKey PrivateKey, int ChainID);
	FNonUniformData GetSignedTransaction(FPrivateKey PrivateKey, int ChainID);
};