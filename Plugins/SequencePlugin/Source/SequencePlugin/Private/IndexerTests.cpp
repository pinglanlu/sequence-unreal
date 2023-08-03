// Fill out your copyright notice in the Description page of Project Settings.


#include "IndexerTests.h"



void pingTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<bool> GenericSuccess = [OnSuccess](const bool bSuccess)
	{
		if (bSuccess)
		{
			OnSuccess("Ping Success");
		}
		else
		{
			OnSuccess("Ping Failure");
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("Ping Failure", Error);
	};

	indexer->Ping(testingChainID, GenericSuccess, GenericFailure);
}

void versionTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FVersion> GenericSuccess = [OnSuccess](const FVersion version)
	{
		OnSuccess("Received Version Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FVersion>(version);
			UE_LOG(LogTemp, Display, TEXT("Parsed Version Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("Version Failure", Error);
	};

	indexer->Version(testingChainID, GenericSuccess, GenericFailure);
}

void runTimeStatusTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FRuntimeStatus> GenericSuccess = [OnSuccess](const FRuntimeStatus runTimeStatus)
	{
		OnSuccess("Received RunTimeStatus Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FRuntimeStatus>(runTimeStatus);
			UE_LOG(LogTemp, Display, TEXT("Parsed RunTimeStatus Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("RunTimeStatus Failure", Error);
	};

	indexer->RunTimeStatus(testingChainID, GenericSuccess, GenericFailure);
}

void getChainIDTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<int64> GenericSuccess = [OnSuccess](const int64 chainID)
	{
		OnSuccess("Received ChainID Data");
		if (printAll)
		{
			FString ret = FString::Printf(TEXT("%lld"), chainID);
			UE_LOG(LogTemp, Display, TEXT("ChainID: %s"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("ChainID Failure", Error);
	};

	indexer->GetChainID(testingChainID, GenericSuccess, GenericFailure);
}

void getEtherBalanceTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FEtherBalance> GenericSuccess = [OnSuccess](const FEtherBalance etherBalance)
	{
		OnSuccess("Received etherBalance Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FEtherBalance>(etherBalance);
			UE_LOG(LogTemp, Display, TEXT("Parsed EtherBalance Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("etherBalance Failure", Error);
	};

	indexer->GetEtherBalance(testingChainID, testingAddress, GenericSuccess, GenericFailure);
}

void getTokenBalanceTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FGetTokenBalancesReturn> GenericSuccess = [OnSuccess](const FGetTokenBalancesReturn tokenBalances)
	{
		OnSuccess("Received TokenBalances Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FGetTokenBalancesReturn>(tokenBalances);
			UE_LOG(LogTemp, Display, TEXT("Parsed TokenBalancesReturn Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("TokenBalances Failure", Error);
	};
	FGetTokenBalancesArgs args;
	args.accountAddress = testingAddress;
	indexer->GetTokenBalances(testingChainID, args, GenericSuccess, GenericFailure);
}

void getTokenSuppliesTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FGetTokenSuppliesReturn> GenericSuccess = [OnSuccess](const FGetTokenSuppliesReturn tokenSupplies)
	{
		OnSuccess("Received TokenSupplies Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FGetTokenSuppliesReturn>(tokenSupplies);
			UE_LOG(LogTemp, Display, TEXT("Parsed tokenSuppliesReturn Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("TokenSupplies Failure", Error);
	};
	FGetTokenSuppliesArgs args;
	args.contractAddress = testingContractAddress;
	args.includeMetaData = true;
	indexer->GetTokenSupplies(testingChainID, args, GenericSuccess, GenericFailure);
}

void getTokenSuppliesMapTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FGetTokenSuppliesMapReturn> GenericSuccess = [OnSuccess](const FGetTokenSuppliesMapReturn tokenSuppliesMap)
	{
		OnSuccess("Received TokenSuppliesMap Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FGetTokenSuppliesMapReturn>(tokenSuppliesMap);
			UE_LOG(LogTemp, Display, TEXT("Parsed TokenSuppliesMapReturn Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("TokenSuppliesMap Failure", Error);
	};

	FGetTokenSuppliesMapArgs args;
	TMap<FString, FTokenList> tokenMap;
	args.includeMetaData = true;
	args.tokenMap = tokenMap;
	indexer->GetTokenSuppliesMap(testingChainID, args, GenericSuccess, GenericFailure);
}

void getBalanceUpdatesTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FGetBalanceUpdatesReturn> GenericSuccess = [OnSuccess](const FGetBalanceUpdatesReturn balanceUpdates)
	{
		OnSuccess("Received balanceUpdates Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FGetBalanceUpdatesReturn>(balanceUpdates);
			UE_LOG(LogTemp, Display, TEXT("Parsed balanceUpdatesReturn Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("balanceUpdates Failure", Error);
	};

	FGetBalanceUpdatesArgs args;
	args.contractAddress = testingContractAddress;
	indexer->GetBalanceUpdates(testingChainID, args, GenericSuccess, GenericFailure);
}

void getTransactionHistoryTest(UIndexer* indexer, TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	const TSuccessCallback<FGetTransactionHistoryReturn> GenericSuccess = [OnSuccess](const FGetTransactionHistoryReturn transactionHistory)
	{
		OnSuccess("Received transactionHistory Data");
		if (printAll)
		{
			FString ret = UIndexerSupport::structToString<FGetTransactionHistoryReturn>(transactionHistory);
			UE_LOG(LogTemp, Display, TEXT("Parsed transactionHistoryReturn Struct:\n%s\n"), *ret);
		}
	};

	const TFailureCallback GenericFailure = [OnFailure](const SequenceError Error)
	{
		OnFailure("transactionHistory Failure", Error);
	};

	FGetTransactionHistoryArgs args;
	args.filter.accountAddress = testingAddress;
	args.includeMetaData = true;
	indexer->GetTransactionHistory(testingChainID, args, GenericSuccess, GenericFailure);
}

void emptyResponseTest(UIndexer * indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("EmptyResponseTest"));
	FString args = "{}";
	FPingReturn rep = indexer->BuildResponse<FPingReturn>(args);
	//by default this should still be false!
	if (!rep.status)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void invalidResponseTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Invalid Response Test"));
	FString args = "+)0asfjlkj;ksjfa{sdfkaljsa;f[}}}skaflasjfd;";
	FPingReturn rep = indexer->BuildResponse<FPingReturn>(args);
	//by default this should still be false!
	if (!rep.status)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void wrongResponseReceivedTest1(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Wrong Response Received Test 1"));
	FString args = "{\"wrong_arg\" : true}";
	FPingReturn rep = indexer->BuildResponse<FPingReturn>(args);
	//by default this should still be false!
	if (!rep.status)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void wrongResponseReceivedTest2(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Wrong Response Received Test 2"));
	FString args = "{ [ \"alt1\" , \"alt2\" , \"alt3\" ] }";
	FPingReturn rep = indexer->BuildResponse<FPingReturn>(args);
	//by default this should still be false!
	if (!rep.status)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void pingParsingTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Ping Parsing Test"));
	FString args = "{\"status\":true}";
	FPingReturn rep = indexer->BuildResponse<FPingReturn>(args);
	args = UIndexerSupport::simplifyString(args);

	//convert response to string testable string format
	FString repString = UIndexerSupport::structToSimpleString<FPingReturn>(rep);

	if (printAll)
	{
		UE_LOG(LogTemp, Display, TEXT("In:\n%s"),*args);
		UE_LOG(LogTemp, Display, TEXT("Out:\n%s"),*repString);
	}

	if (args.ToLower().Compare(repString.ToLower())==0)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void versionParsingTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Version Parsing Test"));
	FString args = "{\"version\":{\"webrpcVersion\":\"1.0\" , \"schemaVersion\":\"s1.0\" , \"schemaHash\":\"0x1\" , \"appVersion\":\"a1.0\"}}";
	FVersionReturn rep = indexer->BuildResponse<FVersionReturn>(args);
	args = UIndexerSupport::simplifyString(args);

	//convert response to string testable string format
	FString repString = UIndexerSupport::structToSimpleString<FVersionReturn>(rep);

	if (printAll)
	{
		UE_LOG(LogTemp, Display, TEXT("In:\n%s"), *args);
		UE_LOG(LogTemp, Display, TEXT("Out:\n%s"), *repString);
	}

	if (args.ToLower().Compare(repString.ToLower()) == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void runTimeStatusParsingTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Runtime Status Parsing Test"));
	FString args = "{\"status\":{\"healthOK\":true,\"indexerEnabled\":true,\"startTime\":\"now\",\"uptime\":10.1,\"ver\":\"1.1\",\"branch\":\"main\",\"commitHash\":\"0x12\",\"chainID\":1,\"checks\":{\"running\":true,\"syncMode\":\"Synced\",\"lastBlockNum\":10}}}";
	FRuntimeStatusReturn rep = indexer->BuildResponse<FRuntimeStatusReturn>(args);
	args = UIndexerSupport::simplifyString(args);

	//convert response to string testable string format
	FString repString = UIndexerSupport::structToSimpleString<FRuntimeStatusReturn>(rep);

	if (printAll)
	{
		UE_LOG(LogTemp, Display, TEXT("In:\n%s"), *args);
		UE_LOG(LogTemp, Display, TEXT("Out:\n%s"), *repString);
	}

	if (args.ToLower().Compare(repString.ToLower()) == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void getChainIDParsingTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Chain ID Parsing Test"));
	FString args = "{\"chainID\":169}";
	FGetChainIDReturn rep = indexer->BuildResponse<FGetChainIDReturn>(args);
	args = UIndexerSupport::simplifyString(args);

	//convert response to string testable string format
	FString repString = UIndexerSupport::structToSimpleString<FGetChainIDReturn>(rep);

	if (printAll)
	{
		UE_LOG(LogTemp, Display, TEXT("In:\n%s"), *args);
		UE_LOG(LogTemp, Display, TEXT("Out:\n%s"), *repString);
	}

	if (args.ToLower().Compare(repString.ToLower()) == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void getEtherBalanceParsingTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Ether Balance Parsing Test"));
	FString args = "{\"balance\":{\"accountAddress\":\"main_address\",\"balanceWei\":101}}";
	FGetEtherBalanceReturn rep = indexer->BuildResponse<FGetEtherBalanceReturn>(args);
	args = UIndexerSupport::simplifyString(args);

	//convert response to string testable string format
	FString repString = UIndexerSupport::structToSimpleString<FGetEtherBalanceReturn>(rep);

	if (printAll)
	{
		UE_LOG(LogTemp, Display, TEXT("In:\n%s"), *args);
		UE_LOG(LogTemp, Display, TEXT("Out:\n%s"), *repString);
	}

	if (args.ToLower().Compare(repString.ToLower()) == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void getTokenBalanceParsingTest(UIndexer* indexer)
{
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
	UE_LOG(LogTemp, Display, TEXT("Token Balance Parsing Test"));
	FString args = "{\"page\":{\"page\":10,\"column\":\"left\",\"before\":\"b1\",\"after\":\"a1\",\"sort\":[{\"column\":\"left\",\"order\":\"DESC\"}],\"pageSize\":64,\"more\":true},\"balances\":[{\"id\":15,\"contractAddress\":\"0xc1\",\"contractType\":\"ERC20\",\"accountAddress\":\"0xa1\",\"tokenID\":11,\"balance\":16384,\"blockHash\":\"0xb1\",\"blockNumber\":1,\"updateID\":3,\"chainId\":137,\"contractInfo\":{\"chainId\":137,\"address\":\"0xa11\",\"name\":\"coin\",\"type\":\"t1\",\"symbol\":\"%\",\"decimals\":101,\"logoURI\":\"http://stuff.ca\",\"extensions\":{\"link\":\"https://that.com\",\"description\":\"extension\",\"ogImage\":\"uint8[]\",\"originChainId\":137,\"originAddress\":\"http://origin.ca\",\"blacklist\":true}},\"tokenMetaData\":{\"tokenId\":101,\"contractAddress\":\"0xc112\",\"name\":\"testing_name\",\"description\":\"some_desc_stuff\",\"image\":\"string_image_data\",\"decimals\":101,\"video\":\"video data\",\"audio\":\"audo_data\",\"image_data\":\"image_data\",\"external_url\":\"external_url_data\",\"background_color\":\"red\",\"animation_url\":\"http://anim.ca\",\"properties\":{\"p1\":10,\"p2\":\"prop_2\",\"p3\":1},\"attributes\":[{\"a11\":\"a\",\"a12\":\"b\"},{\"a21\":\"c\",\"a22\":\"d\",\"a23\":\"e\"}]}}]}";
	FGetTokenBalancesReturn rep = indexer->BuildResponse<FGetTokenBalancesReturn>(args);
	args = UIndexerSupport::simplifyString(args);

	//convert response to string testable string format
	//because this objects uses custom setup and parsing we must use custom getting to test with it! unreal won't be able 
	//to parse it completely
	FString repString = UIndexerSupport::jsonToSimpleString(rep.Get());

	if (printAll)
	{
		UE_LOG(LogTemp, Display, TEXT("In:\n%s"), *args);
		UE_LOG(LogTemp, Display, TEXT("Out:\n%s"), *repString);
	}

	if (args.ToLower().Compare(repString.ToLower()) == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
	}
	UE_LOG(LogTemp, Display, TEXT("==========================================================="));
}

void getTokenSuppliesParsingTest(UIndexer* indexer)
{

}

void getTokenSuppliesMapParsingTest(UIndexer* indexer)
{

}

void getBalanceUpdatesParsingTest(UIndexer* indexer)
{

}

void getTransactionHistoryParsingTest(UIndexer* indexer)
{

}

void IndexerTest(TFunction<void(FString)> OnSuccess, TFunction<void(FString, SequenceError)> OnFailure)
{
	//now we need to test all the different calls!
	UIndexer* indexer = NewObject<UIndexer>();//for testing!

	//failure testing//
	//emptyResponseTest(indexer);
	//invalidResponseTest(indexer);
	//wrongResponseReceivedTest1(indexer);
	//wrongResponseReceivedTest2(indexer);

	//parsing tests//
	//buildResponse parsing tests//
	pingParsingTest(indexer);
	versionParsingTest(indexer);
	runTimeStatusParsingTest(indexer);
	getChainIDParsingTest(indexer);
	getEtherBalanceParsingTest(indexer);
	getTokenBalanceParsingTest(indexer);
	getTokenSuppliesParsingTest(indexer);
	getTokenSuppliesMapParsingTest(indexer);
	getBalanceUpdatesParsingTest(indexer);
	getTransactionHistoryParsingTest(indexer);

	//system tests//
	//pingTest(indexer, OnSuccess, OnFailure);
	//versionTest(indexer, OnSuccess, OnFailure);
	//runTimeStatusTest(indexer, OnSuccess, OnFailure);
	//getChainIDTest(indexer, OnSuccess, OnFailure);
	//getEtherBalanceTest(indexer, OnSuccess, OnFailure);
	//getTokenBalanceTest(indexer, OnSuccess, OnFailure);
	//getTokenSuppliesMapTest(indexer, OnSuccess, OnFailure);
	//getBalanceUpdatesTest(indexer, OnSuccess, OnFailure);
	//getTransactionHistoryTest(indexer, OnSuccess, OnFailure);
	return;//done
}