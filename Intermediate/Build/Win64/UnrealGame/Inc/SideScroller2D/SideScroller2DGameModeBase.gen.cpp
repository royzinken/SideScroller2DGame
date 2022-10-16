// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScroller2D/SideScroller2DGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSideScroller2DGameModeBase() {}
// Cross Module References
	SIDESCROLLER2D_API UClass* Z_Construct_UClass_ASideScroller2DGameModeBase_NoRegister();
	SIDESCROLLER2D_API UClass* Z_Construct_UClass_ASideScroller2DGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_SideScroller2D();
// End Cross Module References
	void ASideScroller2DGameModeBase::StaticRegisterNativesASideScroller2DGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ASideScroller2DGameModeBase_NoRegister()
	{
		return ASideScroller2DGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ASideScroller2DGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SideScroller2D,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering LOD WorldPartition DataLayers Utilities|Transformation" },
		{ "IncludePath", "SideScroller2DGameModeBase.h" },
		{ "ModuleRelativePath", "SideScroller2DGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScroller2DGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::ClassParams = {
		&ASideScroller2DGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASideScroller2DGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASideScroller2DGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASideScroller2DGameModeBase, 2827388394);
	template<> SIDESCROLLER2D_API UClass* StaticClass<ASideScroller2DGameModeBase>()
	{
		return ASideScroller2DGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASideScroller2DGameModeBase(Z_Construct_UClass_ASideScroller2DGameModeBase, &ASideScroller2DGameModeBase::StaticClass, TEXT("/Script/SideScroller2D"), TEXT("ASideScroller2DGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScroller2DGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
