#include "NetworkManager.h"
#include <ixwebsocket/IXNetSystem.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

NetworkManager& NetworkManager::Get() {
    static NetworkManager instance;
    return instance;
}

NetworkManager::NetworkManager() : isConnected(false) {
    ix::initNetSystem();
}

NetworkManager::~NetworkManager() {
    webSocket.stop();
    ix::uninitNetSystem();
}

void NetworkManager::Connect(const std::string& url, const std::string& matchId, const std::string& token) {
    currentMatchId = matchId;
    currentToken = token;

    webSocket.setUrl(url);
    SetupCallbacks();
    
    // Run in background thread
    webSocket.start();
}

void NetworkManager::SetupCallbacks() {
    webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "Connecte au serveur !" << std::endl;
            isConnected = true;
            
            // Envoyer nos identifiants
            std::string authJson = "{\"matchId\":\"" + currentMatchId + "\", \"token\":\"" + currentToken + "\"}";
            SendJSON("auth_game", authJson);
        }
        else if (msg->type == ix::WebSocketMessageType::Close) {
            std::cout << "Deconnecte du serveur." << std::endl;
            isConnected = false;
        }
        else if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "Message recu: " << msg->str << std::endl;
            
            if (onMessageCallback) {
                try {
                    json parsed = json::parse(msg->str);
                    std::string msgType = parsed.value("type", "unknown");
                    // On extrait la partie 'data' sous forme de string pour le callback
                    std::string dataStr = parsed.contains("data") ? parsed["data"].dump() : "{}";
                    onMessageCallback(msgType, dataStr);
                } catch (const std::exception& e) {
                    std::cerr << "Erreur de parsing du message WebSocket: " << e.what() << std::endl;
                    onMessageCallback("raw", msg->str); // Fallback
                }
            }
        }
        else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cout << "Erreur WebSocket: " << msg->errorInfo.reason << std::endl;
        }
    });
}

void NetworkManager::Update() {
    // Si la lib WebSocket fonctionnait en polling on l'appellerait ici
    // ixwebsocket tourne dans son propre thread donc on peut s'en servir 
    // pour dépiler une queue thread-safe de messages si nécessaire pour l'UI.
}

void NetworkManager::SendJSON(const std::string& type, const std::string& dataJson) {
    if (!isConnected) return;
    
    std::string payload = "{\"type\":\"" + type + "\", \"data\":" + dataJson + "}";
    webSocket.send(payload);
}

void NetworkManager::OnMessageReceived(std::function<void(const std::string&, const std::string&)> callback) {
    onMessageCallback = callback;
}
