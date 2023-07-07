#include "ABI/ABI.h"
#include "HexUtility.h"
#include "Misc/AutomationTest.h"
#include "ABI/ABITypes.h"
#include "ABI/ABIDynamicArray.h"
#include "ABI/ABIDynamicFixedArray.h"
#include "ABI/ABIStaticFixedBytesProperty.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestABI, "Public.TestABI",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool EncoderTest(FABIProperty* MProperty, const FString& MethodSig, const FString& CorrectVal)
{
	TArray<FABIProperty*> Properties;
	Properties.Push(MProperty);
	const FString encoding = ABI::Encode(MethodSig, Properties).ToHex();
	UE_LOG(LogTemp, Display, TEXT("String encoding: %s"), *encoding);
	return encoding.Equals(CorrectVal);
}

bool TestABI::RunTest(const FString& Parameters)
{
	//Test 0 
	//TestInt256(int256)
	//TestInt256(15)
	//0x42166d6a000000000000000000000000000000000000000000000000000000000000000f
	auto P0 = FABIInt32Property(15);
	if(!EncoderTest(&P0, FString("TestInt256(int256)"), FString("42166d6a000000000000000000000000000000000000000000000000000000000000000f"))) return false;
	
	
	 //Test 1 
	 //TestUint256(uint256)
	 //TestUint256(15)
	 //0x6a6040e8000000000000000000000000000000000000000000000000000000000000000f
	auto P1 = FABIUInt32Property(15);
	if(!EncoderTest(&P1, FString("TestUint256(uint256)"), FString("6a6040e8000000000000000000000000000000000000000000000000000000000000000f"))) return false;
	
	//Test 2 
	//TestInt256(int256)
	//TestInt256(-15)
	//0x42166d6afffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff1
	auto P2 = FABIInt32Property(-15);
	if(!EncoderTest(&P2, FString("TestInt256(int256)"), FString("42166d6afffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff1"))) return false;
	
	//Test 3 
	//TestUint(uint)
	//TestUint(15)
	//0x949df7cd000000000000000000000000000000000000000000000000000000000000000f
	auto P3 = FABIUInt32Property(15);
	if(!EncoderTest(&P3, FString("TestUint(uint)"), FString("949df7cd000000000000000000000000000000000000000000000000000000000000000f"))) return false;

	//Test 4 
	//Testint(int)
	//Testint(-15)
	//0x87698e9ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff1
	auto P4 = FABIInt32Property(-15);
	if(!EncoderTest(&P4, FString("Testint(int)"), FString("87698e9ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff1"))) return false;
	
	//Test 5 (ask Peter of larger types)
	//TestUint256(uint256)
	//TestUint256(150000000000000)
	//0x6a6040e80000000000000000000000000000000000000000000000000000886c98b76000
	//auto P5 = FABIUInt32Property(150000000000000);
	//if(!EncoderTest(&P5, FString("TestUint256(uint256)"), FString("6a6040e80000000000000000000000000000000000000000000000000000886c98b76000"))) return false;
	
	//Test 6 (ask Peter of larger types)
	//TestInt256(int256)
	//TestInt256(-150000000000000)
	//0x42166d6affffffffffffffffffffffffffffffffffffffffffffffffffff77936748a000
	//auto P6 = FABIIntProperty(-150000000000000);
	//if(!EncoderTest(&P6, FString("TestInt256(int256)"), FString("42166d6affffffffffffffffffffffffffffffffffffffffffffffffffff77936748a000"))) return false;
	
	//Test 7
	//TestAddress(address)
	//TestAddress(0x71C7656EC7ab88b098defB751B7401B5f6d8976F)
	//0xb447d16100000000000000000000000071c7656ec7ab88b098defb751b7401b5f6d8976f
	auto P7 = FABIAddressProperty(FAddress::From("71C7656EC7ab88b098defB751B7401B5f6d8976F"));
	if(!EncoderTest(&P7, FString("TestAddress(address)"), FString("b447d16100000000000000000000000071c7656ec7ab88b098defb751b7401b5f6d8976f"))) return false;

	//Test 8
	//TestBool(bool)
	//TestBool(true)
	//0x05aca3060000000000000000000000000000000000000000000000000000000000000001
	auto P8 = FABIBooleanProperty(true);
	if(!EncoderTest(&P8, FString("TestBool(bool)"), FString("05aca3060000000000000000000000000000000000000000000000000000000000000001"))) return false;

	//Test 9
	//TestBool(bool)
	//TestBool(false)
	//0x05aca3060000000000000000000000000000000000000000000000000000000000000000
	auto P9 = FABIBooleanProperty(false);
	if(!EncoderTest(&P9, FString("TestBool(bool)"), FString("05aca3060000000000000000000000000000000000000000000000000000000000000000"))) return false;

	//Test 10
	//TestFixedByte(bytes10)
	//TestFixedByte("abcdeabcde")
	//0xb8b97ccc6162636465616263646500000000000000000000000000000000000000000000
	auto byte10 = FUniformData<(uint32)10>();
	byte10.Arr = StringToUTF8("abcdeabcde").Arr;
	auto P10 = FABIStaticFixedBytesProperty<10>{byte10};
	if(!EncoderTest(&P10, "TestFixedByte(bytes10)", FString("b8b97ccc6162636465616263646500000000000000000000000000000000000000000000"))) return false;


	//Test 11 not working similar to unity project
	//TestStaticFixedArray(uint256[5])
	//TestStaticFixedArray([15, 200, 12, 20, 20])
	//0x33bd6a09000000000000000000000000000000000000000000000000000000000000000f00000000000000000000000000000000000000000000000000000000000000c8000000000000000000000000000000000000000000000000000000000000000c00000000000000000000000000000000000000000000000000000000000000140000000000000000000000000000000000000000000000000000000000000014
	
	//Test 12
	//TestDynamicFixedArray(string[5])
	//TestDynamicFixedArray(["a", "ab", "abc", "yz", "z"])
	//0xac355f05000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000000000000000000000000000000000000000000e00000000000000000000000000000000000000000000000000000000000000120000000000000000000000000000000000000000000000000000000000000016000000000000000000000000000000000000000000000000000000000000001a00000000000000000000000000000000000000000000000000000000000000001610000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000026162000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000361626300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002797a00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000017a00000000000000000000000000000000000000000000000000000000000000
	//x986d3a8d00000000000000000000000000000000000000000000000000000000000000a000000000000000000000000000000000000000000000000000000000000000e00000000000000000000000000000000000000000000000000000000000000120000000000000000000000000000000000000000000000000000000000000016000000000000000000000000000000000000000000000000000000000000001a00000000000000000000000000000000000000000000000000000000000000001610000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000026162000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000361626300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002797a00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000017a00000000000000000000000000000000000000000000000000000000000000
	TArray<FABIStringProperty> myStrs2{FABIStringProperty("a"), FABIStringProperty("ab"), FABIStringProperty("abc"), FABIStringProperty("yz"), FABIStringProperty("z")};
	auto P12 = FABIDynamicFixedArrayProperty<FABIStringProperty, 5>(&myStrs2);
	if(!EncoderTest(&P12, "TestDynamicFixedArray(string[5])", FString("ac355f05000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000000000000000000000000000000000000000000e00000000000000000000000000000000000000000000000000000000000000120000000000000000000000000000000000000000000000000000000000000016000000000000000000000000000000000000000000000000000000000000001a00000000000000000000000000000000000000000000000000000000000000001610000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000026162000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000361626300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002797a00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000017a00000000000000000000000000000000000000000000000000000000000000"))) return false;


	//Test 13
	//TestString(string)
	//TestString("abcdef")
	//0x4979abcc000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000066162636465660000000000000000000000000000000000000000000000000000
	auto P13 = FABIStringProperty("abcdef");
	if(!EncoderTest(&P13, FString("TestString(string)"), FString("4979abcc000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000066162636465660000000000000000000000000000000000000000000000000000"))) return false;

	
	//Test 14
	//TestBytes(bytes)
	//TestBytes("abcdeabcde")
	//0x229bb9e90000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000a6162636465616263646500000000000000000000000000000000000000000000
	char s[] = "abcdeabcde";
	auto P14 = FABIBytesProperty(FNonUniformData((uint8*)s, 10));
	if(!EncoderTest(&P14, FString("TestBytes(bytes)"), FString("229bb9e90000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000a6162636465616263646500000000000000000000000000000000000000000000"))) return false;

	//Test 15
	//TestStaticNonFixedArray(uint256[])
	//TestStaticNonFixedArray([110000, 34, 3])
	//0x00903ba500000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000003000000000000000000000000000000000000000000000000000000000001adb000000000000000000000000000000000000000000000000000000000000000220000000000000000000000000000000000000000000000000000000000000003
	TArray<FABIUInt32Property> myNums{FABIUInt32Property(110000), FABIUInt32Property(34), FABIUInt32Property(3)};
	auto P15 = FABIDynamicArrayProperty<FABIUInt32Property>(&myNums);
	if(!EncoderTest(&P15, FString("TestStaticNonFixedArray(uint256[])"), FString("00903ba500000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000003000000000000000000000000000000000000000000000000000000000001adb000000000000000000000000000000000000000000000000000000000000000220000000000000000000000000000000000000000000000000000000000000003"))) return false;

	//Test 16
	//TestDynamicNonFixedArray(string[])
	//TestDynamicNonFixedArray(["xyz", "abc"])
	//0x411548440000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000378797a000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000036162630000000000000000000000000000000000000000000000000000000000
	TArray<FABIStringProperty> myStrs{FABIStringProperty("xyz"), FABIStringProperty("abc")};
	auto P16 = FABIDynamicArrayProperty<FABIStringProperty>(&myStrs);
	if(!EncoderTest(&P16, FString("TestDynamicNonFixedArray(string[])"), FString("411548440000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000378797a000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000036162630000000000000000000000000000000000000000000000000000000000"))) return false;

	//Test 17
	//TestManyInputs(string,uint256,int256[],address,bool)
	//TestManyInputs("sequence", 55, [10, 2, 2], "0x71C7656EC7ab88b098defB751B7401B5f6d8976F", true)*/
	//0xc28546fd00000000000000000000000000000000000000000000000000000000000000a0000000000000000000000000000000000000000000000000000000000000003700000000000000000000000000000000000000000000000000000000000000e000000000000000000000000071c7656ec7ab88b098defb751b7401b5f6d8976f0000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000873657175656e63650000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003000000000000000000000000000000000000000000000000000000000000000a00000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000002
	FABIStringProperty mStr = FABIStringProperty(FString("sequence"));
	FABIUInt32Property mInt = FABIUInt32Property(55);
	TArray<FABIUInt32Property> nums{FABIUInt32Property(10), FABIUInt32Property(2), FABIUInt32Property(2)};
	auto myNums2 = FABIDynamicArrayProperty<FABIUInt32Property>(&nums);
	FABIAddressProperty mAddy{FAddress::From("71C7656EC7ab88b098defB751B7401B5f6d8976F")};
	FABIBooleanProperty mBool{true};
	TArray<FABIProperty*> Properties{(FABIProperty*)&mStr, (FABIProperty*) &mInt, (FABIProperty*)&myNums2, (FABIProperty*)&mAddy, (FABIProperty*)&mBool};
	FString CorrectVal{"c28546fd00000000000000000000000000000000000000000000000000000000000000a0000000000000000000000000000000000000000000000000000000000000003700000000000000000000000000000000000000000000000000000000000000e000000000000000000000000071c7656ec7ab88b098defb751b7401b5f6d8976f0000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000873657175656e63650000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003000000000000000000000000000000000000000000000000000000000000000a00000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000002"};
	FString encodedFunction = ABI::Encode("TestManyInputs(string,uint256,int256[],address,bool)", Properties).ToHex();
	if(!encodedFunction.Equals(CorrectVal)) return false;
	UE_LOG(LogTemp, Display, TEXT("String encoding: %s"), *encodedFunction);
	
	return true;
}

