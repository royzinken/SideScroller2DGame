// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef SIDESCROLLER2D_Item_generated_h
#error "Item.generated.h already included, missing '#pragma once' in Item.h"
#endif
#define SIDESCROLLER2D_Item_generated_h

#define SideScroller2D_Source_SideScroller2D_Item_h_18_SPARSE_DATA
#define SideScroller2D_Source_SideScroller2D_Item_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execBeginOverlap);


#define SideScroller2D_Source_SideScroller2D_Item_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execBeginOverlap);


#define SideScroller2D_Source_SideScroller2D_Item_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAItem(); \
	friend struct Z_Construct_UClass_AItem_Statics; \
public: \
	DECLARE_CLASS(AItem, APaperFlipbookActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SideScroller2D"), NO_API) \
	DECLARE_SERIALIZER(AItem)


#define SideScroller2D_Source_SideScroller2D_Item_h_18_INCLASS \
private: \
	static void StaticRegisterNativesAItem(); \
	friend struct Z_Construct_UClass_AItem_Statics; \
public: \
	DECLARE_CLASS(AItem, APaperFlipbookActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SideScroller2D"), NO_API) \
	DECLARE_SERIALIZER(AItem)


#define SideScroller2D_Source_SideScroller2D_Item_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AItem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AItem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AItem(AItem&&); \
	NO_API AItem(const AItem&); \
public:


#define SideScroller2D_Source_SideScroller2D_Item_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AItem(AItem&&); \
	NO_API AItem(const AItem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AItem)


#define SideScroller2D_Source_SideScroller2D_Item_h_18_PRIVATE_PROPERTY_OFFSET
#define SideScroller2D_Source_SideScroller2D_Item_h_15_PROLOG
#define SideScroller2D_Source_SideScroller2D_Item_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SideScroller2D_Source_SideScroller2D_Item_h_18_PRIVATE_PROPERTY_OFFSET \
	SideScroller2D_Source_SideScroller2D_Item_h_18_SPARSE_DATA \
	SideScroller2D_Source_SideScroller2D_Item_h_18_RPC_WRAPPERS \
	SideScroller2D_Source_SideScroller2D_Item_h_18_INCLASS \
	SideScroller2D_Source_SideScroller2D_Item_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SideScroller2D_Source_SideScroller2D_Item_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SideScroller2D_Source_SideScroller2D_Item_h_18_PRIVATE_PROPERTY_OFFSET \
	SideScroller2D_Source_SideScroller2D_Item_h_18_SPARSE_DATA \
	SideScroller2D_Source_SideScroller2D_Item_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	SideScroller2D_Source_SideScroller2D_Item_h_18_INCLASS_NO_PURE_DECLS \
	SideScroller2D_Source_SideScroller2D_Item_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIDESCROLLER2D_API UClass* StaticClass<class AItem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SideScroller2D_Source_SideScroller2D_Item_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
