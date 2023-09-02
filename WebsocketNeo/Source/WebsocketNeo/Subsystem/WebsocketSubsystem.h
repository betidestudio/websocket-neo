// Copyright 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IWebSocket.h"
#include "WebsocketSubsystem.generated.h"

//Multicast for Responses
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWebsocketSubsystem, bool, bWasSuccess, const FString&, Response);

UCLASS()
class WEBSOCKETNEO_API UWebsocketSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//Delegate to give Response when the Websocket's is Connected/DisConnected
	UPROPERTY(BlueprintAssignable)
	FWebsocketSubsystem ResponseOnConnected;
	
	//Delegate to give Response when the Websocket send's a message
	UPROPERTY(BlueprintAssignable)
	FWebsocketSubsystem ResponseOnMessage;

	void OnConnected() const
	{
		ResponseOnConnected.Broadcast(true, "Successfully connected");
	}

	void OnConnectionError(const FString& Error) const
	{
		ResponseOnConnected.Broadcast(false, "Error + %S" + Error);
	}

	void OnMessageReceived(const FString& MessageString)
	{
		ResponseOnMessage.Broadcast(true, MessageString);
	}

	void F_OnMessageSent(const FString& MessageString)
	{
		
	}

	//Functions for WebSocket ->
	UFUNCTION(BlueprintCallable, Category="WebSocket Functions")
	void ConnectWebSocket(FString WebSocketURL);

	UFUNCTION(BlueprintCallable, Category="WebSocket Functions")
	void CloseWebSocketConnection();

	UFUNCTION(BlueprintCallable, Category="WebSocket Functions")
	bool IsWebSocketConnected();

	UFUNCTION(BlueprintCallable, Category="WebSocket Functions")
	void SendWebSocketMessage(FString Message);


	//Variable for WebSocket
	TSharedPtr<IWebSocket> WebSocket;

	
};