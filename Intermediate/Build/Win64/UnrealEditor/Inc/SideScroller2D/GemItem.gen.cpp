// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScroller2D/GemItem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGemItem() {}
// Cross Module References
	SIDESCROLLER2D_API UClass* Z_Construct_UClass_AGemItem_NoRegister();
	SIDESCROLLER2D_API UClass* Z_Construct_UClass_AGemItem();
	SIDESCROLLER2D_API UClass* Z_Construct_UClass_AItem();
	UPackage* Z_Construct_UPackage__Script_SideScroller2D();
// End Cross Module References
	void AGemItem::StaticRegisterNativesAGemItem()
	{
	}
	UClass* Z_Construct_UClass_AGemItem_NoRegister()
	{
		return AGemItem::StaticClass();
	}
	struct Z_Construct_UClass_AGemItem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGemItem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AItem,
		(UObject* (*)())Z_Construct_UPackage__Script_SideScroller2D,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGemItem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "GemItem.h" },
		{ "ModuleRelativePath", "GemItem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGemItem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGemItem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AGemItem_Statics::ClassParams = {
		&AGemItem::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGemItem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGemItem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGemItem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGemItem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGemItem, 4208438597);
	template<> SIDESCROLLER2D_API UClass* StaticClass<AGemItem>()
	{
		return AGemItem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGemItem(Z_Construct_UClass_AGemItem, &AGemItem::StaticClass, TEXT("/Script/SideScroller2D"), TEXT("AGemItem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGemItem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
