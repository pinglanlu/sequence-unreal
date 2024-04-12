Sequence Unreal SDK
===================

This SDK allows easy integration of Sequence Embedded Wallet from any Unreal Framework project.

## Manually Upgrading from previous versions

IF you are using release Beta_1_0_2 or older please backup the values you stored in `Config/Config.h`
when the new Config.h exists in your project simply update the values in that file with the ones you had existing prior

IF you are using a newer release you can leave the folder `SequencePlugin/PluginConfig` alone

To manually update the Sequence plugin delete the following folders contained within `SequencePlugin`:
`Binaries`,`Content`,`Intermediate`,`Resource`,`Source`

Then copy the following folders / files from the NEW SequencePlugin folder:
`Content`, `Resources`, `Source`, `README`, `SequencePlugin`

Then paste these folders / files into the SequencePlugin folder in your project, allowing the files to be replaced with new ones
in the case of `README.md` & `SequencePlugin.uplugin`

Once done rebuild the project from source and you'll be good to go!

### YourProject.Build.cs

In some instances your build.cs may not update properly for your project when this happens you'll be unable to import plugin,
if this occurs in your Projects Build.cs file please check the private Dependency module such that it includes "SequencePlugin":

    public SequenceTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        //The line below is what you want
		PrivateDependencyModuleNames.AddRange(new string[] { "SequencePlugin" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}

## Credentials

Before you can use this plugin, you need to acquire the following credentials from Sequence:

- `WaaSTenantKey`
- `ProjectAccessKey`

You can then add these credentials in the **[Config.h]** file under `SequencePlugin/PluginConfig/Config.h`.

## Security

You must provide a 32 character encryption key in `SequencePlugin/PluginConfig/Config.h` contained within
the following struct value **[FEncryptorConfig::Key]**

In order to prevent tampering with data you must encrypt your packaged project using Unreals packaging settings
You can refer to [these docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/packaging-unreal-engine-projects?application_version=5.2)

***

## Getting Started With the Builtin GUI

1) Once you have the `SequencePlugin` folder, you'll need to go to your project directory and create a `Plugins` folder in it, then copy over the `SequencePlugin` folder into the `Plugins` folder. If a `Plugins` folder already exists just copy the `SequencePlugin` folder into it.

2) Launch your project, then allow it to update the UProject Settings.

3) To find the `SequencePlugin` content folder in your content drawer enable view plugin content
  
4) If you wish to use the in built sequence UI for login you have to do the following:
 
    a) Create a C++ Class that Inherits from **[Pawn]** If you don't know how to do this refer to the doc [Creating C++ Classes in Unreal](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-the-cplusplus-class-wizard-in-unreal-engine?application_version=5.2),
       for the purpose of these docs I'll refer to the C++ Class created here as the **[C++ Parent]**

    b) In **[C++ Parent]** .h file include the Header **[SequenceAPI.h]** this will allow you to access the **[USequenceWallet]**

    c) Create a BlueprintCallable function within the **[C++ Parent]** that accepts **[FCredentials_BE]** as a Parameter.

    d) Create a Blueprint that inherits from **[C++ Parent]**, Then Attach the following Actor component to it **[AC_SequencePawn_Component]**. For in depth specifics on how to setup this blueprint
       please refer to the demonstration BP [Image](ReadmeImages/Example_BP.PNG), this is the BP Graph of **[BP_CustomSpectatorPawn]** contained within the plugins content folder. The important part here is forwarding the Credentials
       received from the inbuilt UI to your **[C++ Parent]** by binding to the delegate from **[AC_SequencePawn_Component]** that gives you Credentials **[Auth_Success_Forwarder]** & Calling your Blueprint Callable C++ function.
       You can do this by swapping the SetupCredentials node for your own setup node.

    d i) For those who aren't familiar with Unreal's Blueprint system you can create a blueprint by right clicking in the content
         drawer, then click blueprint class. Within the blueprint class selector select the All Classes dropdown & search  
         for your **[C++ Parent]** class you just made.
 
    d ii) For those who aren't familiar with Unreal's delegate system, There will be a red empty box on a delegate you'll wish
          to bind to. Click on this box and drag out into the blueprint editor. From the menu that appears Click the Add Event dropdown
          then click add custom event.

Note: You can simply duplicate the **[BP_CustomSpectatorPawn]** but since it & its parent class reside within the realm of the plugin,
during updates all code you place there could potentially be lost. These are here as a reference for how things should be done. If you wish to use these components
it's recommended you duplicate the BP_CustomSpectatorPawn out of the plugin folder, then update it's parent class to a C++ class of your own making that also
resides outside the plugins content folder.

5) Some additional setup of the GameMode will need to be done prior to any UI showing up. The SequencePlugin comes bundled with an example
   GameMode **[GM_Sequence]** stored within **[Demonstration]** in the plugin content folder. Duplicate this GameMode and move it outside the plugin folder.
   Then open up **[GM_Sequence]** and set the DefaultPawn to either the **[BP_CustomSpectatorPawn]** to the Pawn Blueprint that you just made.

6) Lastly in Project Settings you'll need to set this GameMode as the default GameMode. Specifically in ProjectSettings -> Maps & Modes
 
If you don't know what some of the Entities referred to above are / how they work in unreal please refer to the following Docs:
To learn more about GameModes and GameMode state refer to [these docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/game-mode-and-game-state-in-unreal-engine?application_version=5.2)
To learn more about Pawns refer to [these docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/pawn-in-unreal-engine?application_version=5.2)
[Pawns](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Framework/Pawn/)
[Components](https://dev.epicgames.com/documentation/en-us/unreal-engine/components-in-unreal-engine?application_version=5.2)
[PlayerController](https://dev.epicgames.com/documentation/en-us/unreal-engine/player-controllers-in-unreal-engine?application_version=5.2)
[UI in Unreal](https://dev.epicgames.com/documentation/en-us/unreal-engine/creating-widgets-in-unreal-engine?application_version=5.2)
[C++ & Blueprints](https://dev.epicgames.com/documentation/en-us/unreal-engine/cpp-and-blueprints-example?application_version=5.2)
[Creating C++ Classes in Unreal](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-the-cplusplus-class-wizard-in-unreal-engine?application_version=5.2)

##### Take away notes on setup
This isn't the only way you can setup the Builtin GUI, this is here as a quick start reference for those
just getting started with unreal.

### Customizing the builtin GUI

In the folder located at All/Plugins/SequencePlugin Content/Core/Style you'll find a struct F_SequenceUIStyle,
In the default values section of this struct you'll be able to update the colours and images displayed throughout the UI.
For beta we currently only read from Sequence_Style_Dark_Mode

### Custom UI Integration

In a C++ UObject with a series of pass through **[UFUNCTIONS]** setup similarly to **[SequenceBackendManager.h/.cpp]**. Each of these calls are implemented in **[UAuthenticator]** you just need to pass through the data with YOUR UAuthenticator UObject

```clike
//This call is platform dependent on windows & mac this is required for SSO WIP
UFUNCTION(BlueprintCallable, CATEGORY = "Login")
FString GetLoginURL(const ESocialSigninType& Type); 

//This Call is made after you've collected the ID_Token (Mac & Windows only) WIP
UFUNCTION(BlueprintCallable, CATEGORY = "Login")
void SocialLogin(const FString& IDTokenIn);

//This Call is made after you've collected the email address from the Users in the UI
UFUNCTION(BlueprintCallable, CATEGORY = "Login")
void EmailLogin(const FString& EmailIn);

//This is call is made after the Delegate **[AuthRequiresCode]** is fired
UFUNCTION(BlueprintCallable, CATEGORY = "Login")
void EmailCode(const FString& CodeIn);

//Optional call used to check if the credentials on disk are valid or not//
UFUNCTION(BlueprintCallable, Category = "Login")
bool StoredCredentialsValid();
```


To start you'll want to create a **[UAuthenticator]** UObject like so **[UAuthenticator * Auth = NewObject<UAuthenticator>()]**, this UObject manages the authentication side of Sequence.

Be sure to bind to the Delegates for **[AuthSuccess]**, **[AuthFailure]**, **[AuthRequiresCode]** prior to making any signin calls You can bind to these delegates like so:

```clike
this->authenticator->AuthRequiresCode.AddDynamic(this, &AYourClass::YourCallReadyToReceiveCode);
this->authenticator->AuthFailure.AddDynamic(this, &AYourClass::YourCallShowAuthFailureScreen);
```

In the case of **[AuthSuccess]** since a parameter is also passed we bind to it like this

```clike
FScriptDelegate del;
del.BindUFunction(this, "CallShowAuthSuccessScreen");
this->authenticator->AuthSuccess.Add(del);
```

Where **[CallShowAuthSuccessScreen]** is defined in `SequenceBackendManager.h` like so:

```clike
UFUNCTION()
void CallShowAuthSuccessScreen(const FCredentials_BE& CredentialsIn);
```

And in `SequenceBackendManager.cpp` like so:

```clike
void ASequenceBackendManager::CallShowAuthSuccessScreen(const FCredentials_BE& CredentialsIn) 
{
this->Credentials = CredentialsIn;
if (this->ShowAuthSuccessDelegate.IsBound())
  this->ShowAuthSuccessDelegate.Broadcast(Credentials);
else
  UE_LOG(LogTemp, Error, TEXT("**[Nothing bound to: ShowAuthSuccessDelegate]**"));
}
```

### Email based Authentication With CustomUI

1) To start email based authentication you'll start it with this call **[EmailLogin(const FString& EmailIn)]**, supplying an email you've collected from the User in your GUI.

2) Next **[AuthRequiresCode]** will fire when the **[UAuthenticator]** is ready to receive the Code from your UI. Collect this code from your GUI and send it to the authenticator using **[EmailCode(CodeIn)]**.

3) Finally **[AuthSuccess]** will fire with a Credentials_BE struct as a parameter. You are done Email Based Auth.

### Social Signin based Authentication on Desktop With CustomUI

1) To start SSO based authentication with desktop you can either use your own implementation to get the necessary id_token or you can make use of Unreal's web browser plugin.

2) To get the URL to navigate to you can use the UAuthenticator supplied call **[FString GetSigninURL(const ESocialSigninType& Type)]** where Type is the social login type you wish to use

3) With whatever implementation you chose you can forward the collected id_token to the UAuthenticator object with **[SocialLogin(const FString& IDTokenIn)]**, after which **[AuthSuccess]** will fire and you're done desktop based SSO.

### Social Signin based Authentication on Mobile With CustomUI

1) To start mobile SSO you will need to make use of the **[UAuthenticator::InitiateMobileSSO(const ESocialSigninType& Type)]**
   where type is the Type of SSO you want to use. IE) Google or Apple, for the time being Discord & Facebook aren't supported

### Android SSO Requirements

Google: Please ensure your project is setup according to **[Google SSO Setup]** listed below

Apple: Please ensure you have a proper **[AppleClientId]** set in **[Config.h]**

### IOS SSO Requirements

Google: Please ensure you have a proper **[GoogleClientId]** set in **[Config.h]** , you can optional change the **[UrlScheme]** in **[Config.h]** but this isn't required

Apple: Please ensure you have a proper **[AppleClientId]** set in **[Config.h]**,
       be sure you register and set your bundle identifier properly for your app

### Apple Specific SSO Requirements
For Apple SSO to work please be sure to register the **[RedirectURL]** in **[Config/Config.h]** appropriately for your app.

### Sequence API

After you've completed initial authentication and have intercepted the credentials either through your UI or ours, to use the Sequence API you'll need to create a **[USequenceWallet]** by using:
In order to gain access to the SequenceAPI be sure to #include "Sequence/SequenceAPI.h"

```clike
**[USequenceWallet * Api = USequenceWallet(CredentialsIn)]**
or
**[USequenceWallet * Api = USequenceWallet::Make(CredentialsIn, ProviderURL)]**
```

Once you have your **[USequenceWallet]** you can feel free to call any of the functions Supplied by the object, as the register call is now automatically done for you.

### USequenceWallet Functions

### Example SignMessage
##### Used to Sign a message
    
    const UAuthenticator * Auth = NewObject<UAuthenticator>();
	USequenceWallet * Api = USequenceWallet::Make(Auth->GetStoredCredentials().GetCredentials());    

	const TSuccessCallback<FSignedMessage> OnResponse = [=] (FSignedMessage Response)
	{
		//Response is the signed message
    };

	const FFailureCallback OnFailure = [=](const FSequenceError& Error)
	{
		UE_LOG(LogTemp,Display,TEXT("Error Message: %s"),*Error.Message);
    };
    FString Message = "Hi";
	Api->SignMessage(Message,OnResponse,GenericFailure);

### Example SendTransaction
##### Used to send a transaction / perform contract calls
Note: if you want call contracts with the Raw type you'll want include the header
`#include "ABI/ABI.h"` in order to use the ABI to encode the data for a contract call.

    const UAuthenticator * Auth = NewObject<UAuthenticator>();
    USequenceWallet * Api = USequenceWallet::Make(Auth->GetStoredCredentials().GetCredentials());

	const FFailureCallback OnFailure = [=](const FSequenceError& Error)
	{
		UE_LOG(LogTemp,Display,TEXT("Error Message: %s"),*Error.Message);
	};
	
    //Create the Transaction object list
	TArray<TUnion<FRawTransaction,FERC20Transaction,FERC721Transaction,FERC1155Transaction>> Txn;
	
    //Create the transactions you wish to perform

    //ERC20
	FERC20Transaction T20;
	T20.to = "0x0E0f9d1c4BeF9f0B8a2D9D4c09529F260C7758A2";
	T20.tokenAddress = "0x2791Bca1f2de4661ED88A30C99A7a9449Aa84174";
	T20.value = "1000";

    //ERC721

	FERC721Transaction T721;
	T721.safe = true;
	T721.id = "54530968763798660137294927684252503703134533114052628080002308208148824588621";
	T721.to = "0x0E0f9d1c4BeF9f0B8a2D9D4c09529F260C7758A2";
	T721.tokenAddress = "0xa9a6A3626993D487d2Dbda3173cf58cA1a9D9e9f";

    //ERC1155

	FERC1155Transaction T1155;
	T1155.to = "0x0E0f9d1c4BeF9f0B8a2D9D4c09529F260C7758A2";
	T1155.tokenAddress = "0x631998e91476DA5B870D741192fc5Cbc55F5a52E";
	
	FERC1155TxnValue Val;
	Val.amount = "1";
	Val.id = "66635";
	T1155.vals.Add(Val);

    //Raw (Example contract call)

    FString FunctionSignature = "balanceOf(address,uint256)";
	TFixedABIData Account = ABI::Address(FAddress::From("0E0f9d1c4BeF9f0B8a2D9D4c09529F260C7758A2"));
	TFixedABIData Id = ABI::UInt32(0x01);
	TArray<ABIEncodeable*> Arr;
	Arr.Add(&Account);
	Arr.Add(&Id);
	FUnsizedData EncodedData = ABI::Encode(FunctionSignature, Arr);
	
	TArray<TUnion<FRawTransaction,FERC20Transaction,FERC721Transaction,FERC1155Transaction>> Txn;
	FRawTransaction T;
	
	T.data = "0x" + EncodedData.ToHex();
	T.to = "0x64d9f9d527abe2a1c1ce3fada98601c4ac5bfdd2";
	T.value = "0";
	
    //Now append your transaction requests to the Txn object
    
	Txn.Push(TUnion<FRawTransaction,FERC20Transaction,FERC721Transaction,FERC1155Transaction>(T20));//ERC20
	Txn.Push(TUnion<FRawTransaction,FERC20Transaction,FERC721Transaction,FERC1155Transaction>(T721));//ERC721
	Txn.Push(TUnion<FRawTransaction,FERC20Transaction,FERC721Transaction,FERC1155Transaction>(T1155));//ERC1155
	Txn.Push(TUnion<FRawTransaction,FERC20Transaction,FERC721Transaction,FERC1155Transaction>(T));//ContractCall

    //Now send the transaction
	Api->SendTransaction(Txn,[=](FTransactionResponse Transaction)
	{
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(Transaction.Json.ToSharedRef(), Writer);
		UE_LOG(LogTemp,Display,TEXT("Transaction Hash: %s"),*Transaction.TransactionHash);
		OnSuccess(OutputString);
	},OnFailure);

### Example ListSessions
##### Lists the active sessions

	const UAuthenticator * Auth = NewObject<UAuthenticator>();
	USequenceWallet * Api = USequenceWallet::Make(Auth->GetStoredCredentials().GetCredentials());
    
    const TSuccessCallback<TArray<FSession>> OnSuccess = [=](TArray<FSession> Response)
    {
       //Response is a list of Sessions
    };

	const FFailureCallback OnFailure = [=](const FSequenceError& Error)
	{
		UE_LOG(LogTemp,Display,TEXT("Error Message: %s"),*Error.Message);
    };

	Api->ListSessions(OnSuccess,OnFailure);

### Example CloseSession
##### Closes the session

    const UAuthenticator * Auth = NewObject<UAuthenticator>();
    USequenceWallet * Api = USequenceWallet::Make(Auth->GetStoredCredentials().GetCredentials());

	const TFunction<void(FString)> OnSuccess = [=](const FString& Response)
	{
		//Response is just a confirmation string
    };

	const FFailureCallback OnFailure = [=](const FSequenceError& Error)
	{
		UE_LOG(LogTemp,Display,TEXT("Error Message: %s"),*Error.Message);
    };

	Api->CloseSession(OnSuccess,OnFailure);

### Example SignOut
##### Closes the session & clears out cached credentials with blank ones

    USequenceWallet * Api = USequenceWallet::Make(Credentials);
    Api->SignOut();

### Example RegisterSession
##### Used to register a session (done automatically for you by UAuthenticator)

	const UAuthenticator * Auth = NewObject<UAuthenticator>();
	USequenceWallet * Api = USequenceWallet::Make(Auth->GetStoredCredentials().GetCredentials());
    const TFunction<void(FCredentials_BE)> OnSuccess = [=](FCredentials_BE Response)
    {
        //Successful registration
    };

	const FFailureCallback OnFailure = [=](const FSequenceError& Error)
	{
		UE_LOG(LogTemp,Display,TEXT("Error Message: %s"),*Error.Message);
    };

	Api->RegisterSession(OnSuccess,OnFailure);

### Example GetWalletAddress
#### Gets the wallet address currently being used

    USequenceWallet * Api = USequenceWallet::Make(Credentials);
    Api->GetWalletAddress();

### Example GetNetworkId
#### Gets the network id being used

    USequenceWallet * Api = USequenceWallet::Make(Credentials);
    Api->GetNetworkId();

### Example UpdateNetworkId
#### Used to update the stored network id

    USequenceWallet * Api = USequenceWallet::Make(Credentials);
    Api->UpdateNetworkId(137);

### Example UpdateProviderUrl
#### Used to update the provider url of the wallet
    
    USequenceWallet * Api = USequenceWallet::Make(Credentials);
	Api->UpdateProviderURL(NewProviderUrl);

### Indexer & the Wallet

The indexer is tied nicely with the wallet to allow for ease of use.
One thing to note is the NetworkId you set with your wallet is the one that will be used with
the indexer. The default network we set is `137`

## Ping

    USequenceWallet * Api = USequenceWallet::Make(Credentials);
    
	const TSuccessCallback<bool> GenericSuccess = [=](const bool bSuccess)
	{
        //Ping response is in bSuccess
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//Ping failure
	};

	Api->Ping(GenericSuccess, GenericFailure);

## Version

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FVersion> GenericSuccess = [=](const FVersion version)
    {
        //Response contained in FVersion
    };

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//Version Failure
	};
    
	Api->Version(GenericSuccess, GenericFailure);

## RunTimeStatus

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FRuntimeStatus> GenericSuccess = [=](const FRuntimeStatus runTimeStatus)
    {
        //Response is in FRunTimeStatus
    };

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//RunTimeStatus Failure
	};

    Api->RunTimeStatus(GenericSuccess, GenericFailure);

## GetChainID

    USequenceWallet * Api = USequenceWallet::Make(Credentials);
    
    const TSuccessCallback<int64> GenericSuccess = [=](const int64 chainID)
	{
        //Response in int64
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//GetChainID Failure
	};

	Api->GetChainID(GenericSuccess, GenericFailure);

## GetEtherBalance

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FEtherBalance> GenericSuccess = [=](const FEtherBalance etherBalance)
	{
        //Response in FEtherBalance
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//GetEtherBalance Failure
	};

	Api->GetEtherBalance(Api->GetWalletAddress(), GenericSuccess, GenericFailure);

## GetTokenBalances

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FGetTokenBalancesReturn> GenericSuccess = [=](const FGetTokenBalancesReturn tokenBalances)
	{
        //Response in FGetTokenBalancesReturn
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//GetTokenBalances Failure
	};

	FGetTokenBalancesArgs args;
	args.accountAddress = Api->GetWalletAddress();
	args.includeMetaData = true;

	Api->GetTokenBalances(args, GenericSuccess, GenericFailure);

## GetTokenSupplies

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FGetTokenSuppliesReturn> GenericSuccess = [=](const FGetTokenSuppliesReturn tokenSupplies)
	{
        //Response is in FGetTokenSuppliesReturn
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//GetTokenSupplies Failure
	};

	FGetTokenSuppliesArgs args;
	args.contractAddress = "0x01";//Testing Contract Address in hex with leading 0x
	args.includeMetaData = true;

	Api->GetTokenSupplies(args, GenericSuccess, GenericFailure);

## GetTokenSuppliesMap

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FGetTokenSuppliesMapReturn> GenericSuccess = [=](const FGetTokenSuppliesMapReturn tokenSuppliesMap)
	{
        //Response is in FGetTokenSuppliesMapReturn
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
        //GetTokenSuppliesMap Failure
	};
    
	TMap<FString, FTokenList> tokenMap;
	TPair<FString,FTokenList> item;
	tokenMap.Add(item);

    FGetTokenSuppliesMapArgs args;
	args.includeMetaData = true;
	args.tokenMap = tokenMap;

	Api->GetTokenSuppliesMap(args, GenericSuccess, GenericFailure);

## GetBalanceUpdates

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FGetBalanceUpdatesReturn> GenericSuccess = [=](const FGetBalanceUpdatesReturn balanceUpdates)
	{
        //Response in FGetBalanceUpdatesReturn
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//GetBalanceUpdates Failure
	};

	FGetBalanceUpdatesArgs args;
	args.contractAddress = "0x0E0f9d1c4BeF9f0B8a2D9D4c09529F260C7758A2";
	args.page.page = 10;
	args.page.more = true;

	Api->GetBalanceUpdates(args, GenericSuccess, GenericFailure);

## GetTransactionHistory

    USequenceWallet * Api = USequenceWallet::Make(Credentials);

    const TSuccessCallback<FGetTransactionHistoryReturn> GenericSuccess = [=](const FGetTransactionHistoryReturn transactionHistory)
	{
        //Response is in FGetTransactionHistoryReturn
	};

	const FFailureCallback GenericFailure = [=](const FSequenceError Error)
	{
		//GetTransactionHistory Failure
	};

	FGetTransactionHistoryArgs args;
	args.filter.accountAddress = Api->GetWalletAddress();
	args.includeMetaData = true;
	args.page.page = 0;
	args.page.more = true;    

	Api->GetTransactionHistory(args, GenericSuccess, GenericFailure);

***

Assuming you've setup your controlling Actor with the **[AC_SequencePawn_Component]**
The sequence pawn component has functions to do the following:

Setup Sequence (sets up the sequence based systems), requires playerController input

Show GUI Shows the UI

Hide GUI Hides the UI

GUI Visible Simple Visibility test for the UI

Switch Platform (Switches which mode the UI will be in and how it will be displayed)

Note: this doesn't rotate the application into any one view it just make the UI responsive to that type of view.

Modes:
- Desktop (default)
- Mobile Portrait (Custom built for portrait mode reducing the X width where ever possible)
- Mobile Landscape

***

#### Unreal TFunctions & Async Best Practices

We make use of TFunctions with some callbacks:

```clike
TSuccessCallback
const TFunction<void(FString)> OnResponse = **[Capturable variables]**(const FString& Response)
{
//callback body where we can process Response
};

FFailureCallback
const TFunction<void(FSequenceError)> OnFailureTest = **[Capturable variables]**(const FSequenceError& Error)
{
//callback body where we can process Error
};
```

One thing to be aware of is keep an eye on capturables if you have lots of nested TFunctions it's very easy to miss something and start over writing memory. If you require lots of nesting swapping to a better approach using UFUNCTION callbacks helps to avoid these problems similar to how things are done in **[UAuthenticator.h/cpp]**

### Blockchain Functionality

Most users of the Sequence SDK will not need to interact with cryptographic functions directly. 

#### Binary Data

We encapsulate binary data using the ``FBinaryData`` structs, which is a wrapper around a pointer to a shared byte array `TSharedPtr<TArray<uint8>>`. 
Binary data is further subtyped into `FUnsizedData`, which represents data of any variable size, and `TSizedData<TSize>`, which represents data of a required byte length `TSize`.

Important cryptographic types of set size, such as 32-byte private keys, are defined as subtypes of ``TSizedData``- for example, we define `FPrivateKey : TSizedData<32>`. 
These can also be loaded from hex strings using ``From(FString Str)``, such as ``FPrivateKey::From("0x0...0");``. Ensure that the input string is the correct size.

#### The ABI

To call contracts on the blockchain, you will need to encode any data you wish to pass as arguments using the ABI. To read more about the ABI and its specification, check out the [solidity docs](https://docs.soliditylang.org/en/latest/abi-spec.html).

Our ABI implementation centers around the ``ABI`` class in `ABI/ABI.h`, which provides functions to convert the following types: `UInt32`, `Int32`, `Bool`, `FAddress`, and `FString`. Any other data may be transformed directly into `TFixedABIArray` or `TDynamicABIArray` for fixed-length and dynamic length arrays respectively, or to `TFixedABIData` and `TDynamicABIData` for fixed-length and dynamic length binary data.

Once you have your data stored in `ABIEncodeable` types, you can provide the ABI an array of the type `TArray<ABIEncodeable*>` to `ABI::Encode` to receive the binary encoding of the arguments.
See `TestABI.cpp` for an example.

#### Cryptographic Functions

`Eth/Crypto.h` provides some important ethereum functions for interacting directly with the blockchain:

```
// Derives a public key from a private key
FPublicKey GetPublicKey(FPrivateKey PrivateKey);

// Derives an address from the public key
FAddress GetAddress(FPublicKey PublicKey);

// Finds a keccak hash for some binary data
FHash256 GetKeccakHash(FBinaryData &Data);

// Derives contract address from a given sending address and nonce
FAddress GetContractAddress(FAddress Sender, FBlockNonce Nonce);
```

#### Raw Ethereum Transactions

`EthTransaction.h` contains a struct designed for managing raw ethereum transactions, including functions to sign and hash them. Note that transactions should usually be handled via the Sequence wallet interface, which sends the transactions via the Sequence WAAS.

### Packaging

To set your system up for Packaging please refer to the following links:

- [Windows and macOS](https://docs.unrealengine.com/5.0/en-US/packaging-unreal-engine-projects/)
- [Android](https://docs.unrealengine.com/4.27/en-US/SharingAndReleasing/Mobile/Android/PackagingAndroidProject/)
- [iOS](https://docs.unrealengine.com/5.0/en-US/packaging-ios-projects-in-unreal-engine/)

#### Google SSO Setup
In order to be able to properly use Google Auth, create and place the Keystore file by following [these instructions](https://docs.unrealengine.com/5.1/en-US/signing-android-projects-for-release-on-the-google-play-store-with-unreal-engine/).

You will also need to generate an **[Android client ID]** and a **[Web Application client ID]** for your application, as well as place the **[Web Application client ID]** in the `PluginConfig/Config.h` `FAuthenticatorConfig.GoogleClientID` field.

Refer to [these docs](https://developers.google.com/identity/one-tap/android/get-started#api-console) to generate **[Android client ID]** and **[Web Application client ID]**.

[This guide](https://developers.google.com/android/guides/client-auth) helps explain how to collect SHA-1 key fingerprints for the **[Android client ID]**.

#### iOS
For iOS apps you also need to setup provisioning, [following these docs](https://docs.unrealengine.com/5.1/en-US/setting-up-ios-tvos-and-ipados-provisioning-profiles-and-signing-certificates-for-unreal-engine-projects/).

### Hardware Requirements

For Hardware Requirements with Unreal please refer to [these docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/hardware-and-software-specifications-for-unreal-engine?application_version=5.2)

#### Unreal and Xcode Specifics
During the Unreal Package process in the event a code signing error occurs you can take the following steps within XCode to get your packaged .app file

1) After packaging the project in Unreal, open the Xcode project (Sequence-unreal folder -> Intermediate -> ProjectFilesIOS -> SequenceUnreal.xcodeproj)
2) Click on the project name on the left hand side to open up project settings
3) Click the Build Phase Tab
4) Click on the ‘+’ icon at the top left
5) Select Run Script
6) Drag the new run script to one below from the last item in the phase list
7) Expand the run script
8) In the script box, add the following command: `xattr -cr /path-to-your-project/sequence-unreal/Binaries/IOS/Payload/SequenceUnreal.app`
9) Click on the Build Settings tab
10) Click on each item under the Architectures header that contains macOS and hit the delete key
11) Click on the General tab
12) Click on Mac and Applevision Pro under supported destinations and hit the delete key
13) Now the project can be built (if the build fails at first, wait a few moments then try again. It can sometimes take a bit before the build registers the run script)
14) Once you have finished running the project, and want to make changes to the code, REMEMBER to delete this xcodeproj file in the sequence-unreal folder to ensure that a new xcodeproj is creating when you packaging the project again.
