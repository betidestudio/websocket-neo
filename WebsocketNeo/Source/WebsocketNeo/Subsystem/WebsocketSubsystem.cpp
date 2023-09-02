// Copyright 2023 Betide Studio. All Rights Reserved.

#include "WebsocketSubsystem.h"
#include "WebSocketsModule.h"

//Functions for WebSocket ->

void UWebsocketSubsystem::ConnectWebSocket(FString WebSocketURL)
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(WebSocketURL);
	WebSocket->OnConnected().AddUObject(this, &UWebsocketSubsystem::OnConnected);
	WebSocket->OnConnectionError().AddUObject(this, &UWebsocketSubsystem::OnConnectionError);
	WebSocket->OnMessage().AddUObject(this, &UWebsocketSubsystem::OnMessageReceived);
	WebSocket->OnMessageSent().AddUObject(this, &UWebsocketSubsystem::F_OnMessageSent);

	WebSocket->Connect();
}

void UWebsocketSubsystem::CloseWebSocketConnection()
{
	if(WebSocket)
	{
		if (WebSocket->IsConnected())
		{
			WebSocket->Close();
			ResponseOnMessage.Broadcast(true, "Connection Closed");
		}
		else
		{
			ResponseOnMessage.Broadcast(false,"Connection not valid");
		}
	}
	else
	{
		ResponseOnMessage.Broadcast(false,"Connection not valid");
	}
}

bool UWebsocketSubsystem::IsWebSocketConnected()
{
	if(WebSocket)
	{
		if (WebSocket->IsConnected())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void UWebsocketSubsystem::SendWebSocketMessage(FString Message)
{
	
	if(WebSocket)
	{
		if (WebSocket->IsConnected())
		{
			WebSocket->Send(Message);
		}
		else
		{
			ResponseOnMessage.Broadcast(false,"Connection not valid");
		}
	}
	else
	{
		ResponseOnMessage.Broadcast(false,"Connection not valid");
	}
}

