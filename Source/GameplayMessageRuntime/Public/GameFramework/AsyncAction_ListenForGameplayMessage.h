// Copyright Epic Games, Inc. All Rights Reserved.
// Modified by Broken Rock Studios
// See the LICENSE file for details.

#pragma once

#include "GameplayMessageSubsystem.h"
#include "GameplayMessageTypes2.h"
#include "Engine/CancellableAsyncAction.h"

#include "AsyncAction_ListenForGameplayMessage.generated.h"

class UScriptStruct;
class UWorld;
struct FFrame;

/**
 * Proxy object pin will be hidden in K2Node_GameplayMessageAsyncAction. Is used to get a reference to the object triggering the delegate for the follow up call of 'GetPayload'.
 *
 * @param ActualChannel		The actual message channel that we received Payload from (will always start with Channel, but may be more specific if partial matches were enabled)
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncGameplayMessageDelegate, UAsyncAction_ListenForGameplayMessage*, ProxyObject, FGameplayTag, ActualChannel);

UCLASS(BlueprintType, meta=(HasDedicatedAsyncNode))
class GAMEPLAYMESSAGERUNTIME_API UAsyncAction_ListenForGameplayMessage : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:
	/**
	 * Asynchronously waits for a gameplay message to be broadcast on the specified channel.
	 *
	 * @param Channel			The message channel to listen for
	 * @param PayloadType		The kind of message structure to use (this must match the same type that the sender is broadcasting)
	 * @param MatchType			The rule used for matching the channel with broadcasted messages
	 */
	UFUNCTION(BlueprintCallable, Category = Messaging, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UAsyncAction_ListenForGameplayMessage* ListenForGameplayMessages(UObject* WorldContextObject, FGameplayTag Channel, UScriptStruct* PayloadType, EGameplayMessageMatch MatchType = EGameplayMessageMatch::ExactMatch);

	/**
	 * Attempt to copy the payload received from the broadcasted gameplay message into the specified wildcard.
	 * The wildcard's type must match the type from the received message.
	 *
	 * @param OutPayload	The wildcard reference the payload should be copied into
	 * @return				If the copy was a success
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Messaging", meta = (CustomStructureParam = "OutPayload"))
	bool GetPayload(UPARAM(ref) int32& OutPayload);

	DECLARE_FUNCTION(execGetPayload);

	// ~Begin UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	virtual void SetReadyToDestroy() override;
	// ~End of UBlueprintAsyncActionBase interface
	
public:
	/** Called when a message is broadcast on the specified channel. Use GetPayload() to request the message payload. */
	UPROPERTY(BlueprintAssignable)
	FAsyncGameplayMessageDelegate OnMessageReceived;

private:
	
	/**
	 * Handles the reception of a gameplay message.
	 *
	 * @param Channel      The message channel that received the payload.
	 * @param StructType   The type of the message structure.
	 * @param Payload      The actual message payload.
	 */
	void HandleMessageReceived(FGameplayTag Channel, const UScriptStruct* StructType, const void* Payload);

private:
	const void* ReceivedMessagePayloadPtr = nullptr;

	TWeakObjectPtr<UWorld> WorldPtr;
	FGameplayTag ChannelToRegister;
	TWeakObjectPtr<UScriptStruct> MessageStructType = nullptr;
	EGameplayMessageMatch MessageMatchType = EGameplayMessageMatch::ExactMatch;

	FGameplayMessageListenerHandle ListenerHandle;
};
