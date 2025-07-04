// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameplayMessageNodes/Public/K2Node_AsyncAction_ListenForGameplayMessages.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeK2Node_AsyncAction_ListenForGameplayMessages() {}

// Begin Cross Module References
BLUEPRINTGRAPH_API UClass* Z_Construct_UClass_UK2Node_AsyncAction();
GAMEPLAYMESSAGENODES_API UClass* Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages();
GAMEPLAYMESSAGENODES_API UClass* Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_NoRegister();
UPackage* Z_Construct_UPackage__Script_GameplayMessageNodes();
// End Cross Module References

// Begin Class UK2Node_AsyncAction_ListenForGameplayMessages
void UK2Node_AsyncAction_ListenForGameplayMessages::StaticRegisterNativesUK2Node_AsyncAction_ListenForGameplayMessages()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UK2Node_AsyncAction_ListenForGameplayMessages);
UClass* Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_NoRegister()
{
	return UK2Node_AsyncAction_ListenForGameplayMessages::StaticClass();
}
struct Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Blueprint node which is spawned to handle the async logic for UAsyncAction_RegisterGameplayMessageReceiver\n */" },
#endif
		{ "IncludePath", "K2Node_AsyncAction_ListenForGameplayMessages.h" },
		{ "ModuleRelativePath", "Public/K2Node_AsyncAction_ListenForGameplayMessages.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint node which is spawned to handle the async logic for UAsyncAction_RegisterGameplayMessageReceiver" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UK2Node_AsyncAction_ListenForGameplayMessages>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UK2Node_AsyncAction,
	(UObject* (*)())Z_Construct_UPackage__Script_GameplayMessageNodes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics::ClassParams = {
	&UK2Node_AsyncAction_ListenForGameplayMessages::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics::Class_MetaDataParams), Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages()
{
	if (!Z_Registration_Info_UClass_UK2Node_AsyncAction_ListenForGameplayMessages.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UK2Node_AsyncAction_ListenForGameplayMessages.OuterSingleton, Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UK2Node_AsyncAction_ListenForGameplayMessages.OuterSingleton;
}
template<> GAMEPLAYMESSAGENODES_API UClass* StaticClass<UK2Node_AsyncAction_ListenForGameplayMessages>()
{
	return UK2Node_AsyncAction_ListenForGameplayMessages::StaticClass();
}
UK2Node_AsyncAction_ListenForGameplayMessages::UK2Node_AsyncAction_ListenForGameplayMessages(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UK2Node_AsyncAction_ListenForGameplayMessages);
UK2Node_AsyncAction_ListenForGameplayMessages::~UK2Node_AsyncAction_ListenForGameplayMessages() {}
// End Class UK2Node_AsyncAction_ListenForGameplayMessages

// Begin Registration
struct Z_CompiledInDeferFile_FID_Samples_Games_LyraStarterGame_Plugins_GameplayMessageRouter_Source_GameplayMessageNodes_Public_K2Node_AsyncAction_ListenForGameplayMessages_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UK2Node_AsyncAction_ListenForGameplayMessages, UK2Node_AsyncAction_ListenForGameplayMessages::StaticClass, TEXT("UK2Node_AsyncAction_ListenForGameplayMessages"), &Z_Registration_Info_UClass_UK2Node_AsyncAction_ListenForGameplayMessages, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UK2Node_AsyncAction_ListenForGameplayMessages), 193482932U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Samples_Games_LyraStarterGame_Plugins_GameplayMessageRouter_Source_GameplayMessageNodes_Public_K2Node_AsyncAction_ListenForGameplayMessages_h_3848873811(TEXT("/Script/GameplayMessageNodes"),
	Z_CompiledInDeferFile_FID_Samples_Games_LyraStarterGame_Plugins_GameplayMessageRouter_Source_GameplayMessageNodes_Public_K2Node_AsyncAction_ListenForGameplayMessages_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Samples_Games_LyraStarterGame_Plugins_GameplayMessageRouter_Source_GameplayMessageNodes_Public_K2Node_AsyncAction_ListenForGameplayMessages_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
