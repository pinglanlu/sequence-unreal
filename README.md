# Sequence Unreal SDK

This SDK allows easy integration of Sequence Embedded Wallet from any Unreal Framework project.

[![Docs](https://img.shields.io/badge/Documentation-7334f8)](https://docs.sequence.xyz/sdk/unreal/introduction)
[![Boilerplate](https://img.shields.io/badge/Get%20started%20using%20our%20Boilerplate%20Project-7334f8)](https://github.com/0xsequence/unreal-embedded-wallet-boilerplate)

![Intro](https://docs.sequence.xyz/img/unreal/unreal_intro.gif)

## Supported Platforms

- Unreal Engine 5.2, 5.3, or 5.4
- PC Standalone
- Mac Standalone
- Android
- iOS

## Samples

The SDK comes with a number of samples that can be imported used from the `SequencePlugin Content/Core` directory.

## Upgrading to Unreal 5.4

If your project is currently on 5.2 or 5.3, then for this version you'll want to upgrade to 5.4. To do this close the Unreal Editor, Close your Code Editor. Right-click on your Unreal Project file. Then select Switch Unreal Engine Version, Choose 5.4 and click okay. Once done. Open your code editor and rebuild your source code.

As a way of future proofing we recommend installing visual studio 2022 in accordance with these docs as Unreal 5.4 and onward will be dropping support for visual studio 2019.

## Security

You must provide a 32 character encryption key in the [SequenceConfig.ini] file under [YourProject]/Config/SequenceConfig.ini under the config variable FallbackEncryptionKey

In order to prevent tampering with data you must encrypt your packaged project using Unreals packaging settings You can refer to these docs

Note: For generating secure keys feel free to use tools such as: Lastpass Password generator or equivalent, Encryption Key Generators, etc

Important for values you place in FallbackEncryptionKey
Be sure what ever key data you place in [FallbackEncryptionKey] is of hex form & does NOT contain any extraneous symbols, eg) *,/\ etc. In the event unrecognized symbols are seen the engine will not load the .ini file.

## TroubleShooting

In events where the editor crashes on launch, try deleting the following file, Saved/SaveGames/Cr.sav
This file contains the savegame data for credentials and if modified can result in an engine crash.
Deleting this file deletes local credentials, so you'll need to log back in.
