// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Templates/SharedPointer.h"
#include "JsonLibrary.generated.h"

USTRUCT(BlueprintType)
struct JSONLIBRARIES_API FBlueprintJsonObject
{
    GENERATED_BODY()

    TSharedPtr<FJsonObject> InternalObject;

    FBlueprintJsonObject() : InternalObject(MakeShared<FJsonObject>()) {}
    explicit FBlueprintJsonObject(const TSharedPtr<FJsonObject>& JsonObj) : InternalObject(JsonObj) {}
};

UCLASS()
class JSONLIBRARIES_API UJsonLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool ParseJSON(const FString& JSONString, FBlueprintJsonObject& OutJsonObject);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetStringField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, FString& OutValue);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetIntegerField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, int32& OutValue);
	
    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetFloatField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, float& OutValue);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetBoolField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, bool& OutValue);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetArrayField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, TArray<FBlueprintJsonObject>& OutArray);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetObjectField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, FBlueprintJsonObject& OutObject);
    
};