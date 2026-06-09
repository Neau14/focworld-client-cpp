#pragma once

#include <string>
#include <memory>
#include <functional>
#include <ixwebsocket/IXWebSocket.h>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    // Singleton pattern
    static NetworkManager& Get();

    // Connects to the WebSocket server using the match token
    void Connect(const std::string& url, const std::string& matchId, const std::string& token);
    
    // Process networking events (call this every frame in the main loop)
    void Update();

    // Send a JSON payload
    void SendJSON(const std::string& type, const std::string& dataJson);

    // Callbacks
    void OnMessageReceived(std::function<void(const std::string&, const std::string&)> callback);

    bool IsConnected() const { return isConnected; }

private:
    ix::WebSocket webSocket;
    bool isConnected;
    std::string currentMatchId;
    std::string currentToken;

    std::function<void(const std::string&, const std::string&)> onMessageCallback;

    void SetupCallbacks();
};
