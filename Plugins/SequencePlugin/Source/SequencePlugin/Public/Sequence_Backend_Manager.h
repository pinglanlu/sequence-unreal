// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "ObjectHandler.h"
#include "Backend.h"
#include "BE_Structs.h"
#include "Sequence_Backend_Manager.generated.h"

class UIndexer;

UCLASS()
class SEQUENCEPLUGIN_API ASequence_Backend_Manager : public AActor, public IBackend
{
	GENERATED_BODY()

private:
	FString glb_PublicAddress = "0x8e3E38fe7367dd3b52D1e281E4e8400447C8d8B9";//this is the signed in public addr
	int64 glb_ChainID = 137; //this is the chain we are currently using

	FString prvt_key; // private key for signin
	FString pblc_key; // public key for signin

	TArray<FString> hex_data;//this is our LUT of hexidecimal data!
	UIndexer* indexer;//indexer ref!
	
	//for right now we use these variables to bootstrap signin
	bool ready = false;
	FString recv_block_num;
	int32 recv_id;
	FString recv_block_hsh;
	FString user_email;
	//end of signin variables

	//ASYNC storage//
	TArray<UTexture2D*> fetched_imgs;
	int32 req_count;
	//ASYNC storage//

	UObjectHandler * request_handler;

private:
	void inc_request_count();
	void dec_request_count();
	void reset_request_count();

public:
	// Sets default values for this actor's properties
	ASequence_Backend_Manager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
//SYNC FUNCTIONAL CALLS// [THESE ARE BLOCKING CALLS AND WILL RETURN DATA IMMEDIATELY]
	/*
	* Used to send data to clipboard for ease of use!
	*/
	UFUNCTION(BlueprintCallable, CATEGORY="FUNCTION")
		void Copy_To_Clipboard(FString data);

	/*
	* Used to get data from clipboard for ease of use
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "FUNCTION")
		FString Get_From_Clipboard();

	/*
	* Used to initiate a passwordless signin!
	* @param FString email (email in)
	* @return the Oob code to be displayed for the user to enter on the site login!
	* NOTE: for the code we are expecting 6 digits!
	* 
	* ***DEPRECATED SWITCHING TO ASYNC VERSION ONCE ASYNC COMES ONLINE***
	* 
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "FUNCTION")
		FString Signin(FString email);
//SYNC FUNCTIONAL CALLS// [THESE ARE BLOCKING CALLS AND WILL RETURN DATA IMMEDIATELY]

//ASYNC FUNCTIONAL CALLS// [THESE ARE NON BLOCKING CALLS AND WILL USE A MATCHING UPDATE...FUNC TO RETURN DATA]

	/*
	* Meant to be overriden in blueprints to give the plugin access to the needed data!
	* @param the ether balance fetched from get_ether_balance()
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent,CATEGORY = "FUNCTION")
		void update_ether_balance(int64 ether_balance);//DO NOT ADD A BODY HERE THIS IS MEANT TO BE OVERRIDDEN IN BP'S

	/*
	* This is meant to initiate an ASYNC request with the backend
	* it will call update_wei when it completes where the child class of
	* Sequence_Backend_Manager will override the matching update_ether_balance in Blueprints
	* with that data
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "FUNCTION")
		void get_ether_balance();//uses the signed in account address


	//testing the async fetching process
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent,CATEGORY = "FUNCTION")
		void update_transaction_imgs(const TArray<UTexture2D *> &imgs);

	UFUNCTION(BlueprintCallable, CATEGORY = "ASYNC")
		void get_transaction_imgs();

	UFUNCTION(BlueprintCallable, CATEGORY = "TESTING")
		void testing_network_infrastructures();

	/*
	* Used to initiate a stored authentication call from the frontend
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "Authentication")
		void init_authentication(FStoredState_BE stored_state);

	/*
	* Used to let the frontend know if authentication succeeded or not
	* in an async. manner
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, CATEGORY = "Authentication")
		void update_authentication(bool authenticated);

	/*
	* Used to init. a call to fetch user data in an async manner
	*/
	UFUNCTION(BlueprintCallable, CATEGORY = "UserData")
		void init_user_data();

	/*
	* Used to update the frontend with the supplied user data
	* in an async manner
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, CATEGORY = "UserData")
		void update_user_data(const FUserData_BE &user_data);

	UFUNCTION(BlueprintCallable, CATEGORY="Signin")
		void init_signin(FString email);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, CATEGORY = "Signin")
		void update_signin(const FString &oob_code);

	void get_txn_imgs_manager();

//ASYNC FUNCTIONAL CALLS// [THESE ARE NON BLOCKING CALLS AND WILL USE A MATCHING UPDATE...FUNC TO RETURN DATA]

//Fetching Functions

	void add_img(UTexture2D * img_to_add);


//Fetching Functions

private:

	//Private handlers
	void signin_handler(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void get_blk_handler(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void get_hsh_handler(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	//Private handlers

	/*
	* Used for sending out ASYNC requests used to handle signin
	* NOTE: Looking at moving this code to a dedicated networking class for reuse
	* @Param URL (the full url to send the json payload to)
	* @Param json (the json payload in FString form) If invalid we will get a response but it'll be an error mesg from the server in json format
	* @param Handler (The ASYNC handler that will process the payload once we have received it)
	*/
	void post_json_request(FString url, FString json, void (ASequence_Backend_Manager::* handler)(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful));
	
	/*
	* Used to request block information from
	* the sequence app, 
	* @Return the block data we want from the latest block on the chain
	*/
	FString create_blk_req();

	/*
	* Used to get the block hash data based on the block number and givin id
	* Fetches this data from the sequence app
	* @Return the block hash we want!
	*/
	FString create_hsh_req(FString blk_num, int32 id);

	/*
	* Sets up the signin request body
	* @Return the signin req in json format in an FString
	*/
	FString create_req_body(FString email);

	/*
	* Sets up the intent for Signin
	* @Return the Intent in Json format in an FString
	*/
	FString create_intent(FString email);

	/*
	* Generates a random wallet ID used to bootstrap signin
	* @Return a Random wallet ID
	*/
	FString setup_random_wallet();//returns the public key!

	//These functions are used to generate the URL's need to interact with
	//the various aspects of the sequence app
	FString get_main_url();
	FString get_continue_url();
	FString get_signin_url();

public:
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TESTING FUNCTIONS
	/*
	* Used to test an indivual private key, to see how it's generated public key compares to a CORRECT
	* pre computed and and how the generated address from the generated public key compares to a precomputed
	* CORRECT address
	* returns true IFF gen_public_key matches the hard_public_key &&
	* gen_address matches hard_address
	*/
		bool test_address_gen(FString prvt_k, FString hrd_pblc_k, FString hrd_addr);

		/*
		* Used to test the public key generation and address generation in accordance with
		* the test chain!
		*/
		UFUNCTION(BlueprintCallable, CATEGORY = "TESTING")
			FString Testing_Address_Generation();

		/*
		* Testing function used for evaluating the indexer
		*/
		UFUNCTION(BlueprintCallable, CATEGORY = "TESTING")
			TArray<UTexture2D*> Testing_Indexer();
//TESTING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
