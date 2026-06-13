#include "AutoUpdater.h"
#include <ixwebsocket/IXHttpClient.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

using json = nlohmann::json;

#define CURRENT_APP_VERSION "1.0.6"

AutoUpdater& AutoUpdater::Get() {
    static AutoUpdater instance;
    return instance;
}

void AutoUpdater::CheckForUpdates() {
    if (m_state != UpdaterState::IDLE) return;
    m_state = UpdaterState::CHECKING;

    if (m_workerThread.joinable()) m_workerThread.join();

    m_workerThread = std::thread([this]() {
        ix::HttpClient httpClient;
        auto args = httpClient.createRequest();
        
        // Ajouter un timestamp pour contourner le cache CDN
        std::string ts = std::to_string(GetTickCount());
        auto response = httpClient.get("https://pub-7bd6715a1810463a94e5194e6ed940dd.r2.dev/version.json?t=" + ts, args);

        if (!response || response->statusCode != 200) {
            std::cout << "Aucune mise a jour trouvee ou erreur reseau." << std::endl;
            m_state = UpdaterState::UP_TO_DATE;
            return;
        }

        try {
            json data = json::parse(response->body);
            std::string latestVersion = data.value("version", CURRENT_APP_VERSION);
            
            // On ne met à jour que si la version du serveur est STRICTEMENT supérieure
            if (latestVersion > std::string(CURRENT_APP_VERSION)) {
                m_setupUrl = data.value("url", "");
                if (!m_setupUrl.empty()) {
                    m_state = UpdaterState::UPDATE_AVAILABLE;
                } else {
                    m_state = UpdaterState::UP_TO_DATE;
                }
            } else {
                m_state = UpdaterState::UP_TO_DATE;
            }
        } catch (...) {
            m_state = UpdaterState::UP_TO_DATE; // Fallback
        }
    });
    m_workerThread.detach();
}

void AutoUpdater::StartDownload() {
    if (m_state != UpdaterState::UPDATE_AVAILABLE) return;
    m_state = UpdaterState::DOWNLOADING;

    if (m_workerThread.joinable()) m_workerThread.join();

    m_workerThread = std::thread([this]() {
        char tempPath[MAX_PATH];
        GetTempPathA(MAX_PATH, tempPath);
        m_tempSetupPath = std::string(tempPath) + "FOCWorld_TCG_Update.exe";

        // Ajouter un timestamp pour forcer le téléchargement et ignorer le cache local IE
        std::string finalUrl = m_setupUrl + "?t=" + std::to_string(GetTickCount());

        HRESULT hr = URLDownloadToFileA(NULL, finalUrl.c_str(), m_tempSetupPath.c_str(), 0, NULL);
        if (hr == S_OK) {
            m_state = UpdaterState::READY_TO_INSTALL;
        } else {
            m_error = "Erreur lors du telechargement.";
            m_state = UpdaterState::FAILED;
        }
    });
    m_workerThread.detach();
}

void AutoUpdater::InstallAndExit() {
    if (m_state == UpdaterState::READY_TO_INSTALL) {
        m_state = UpdaterState::IDLE; // Empêcher un double appel
        
        // On lance un cmd qui attend 2 secondes pour laisser l'app se fermer, 
        // puis qui lance l'installeur silencieuxement
        std::string cmdArgs = "/C ping 127.0.0.1 -n 2 > nul & start \"\" \"" + m_tempSetupPath + "\" /SILENT";
        ShellExecuteA(NULL, "open", "cmd.exe", cmdArgs.c_str(), NULL, SW_HIDE);
        
        // TerminateProcess évite la destruction des singletons/threads et les crashs (0xc0000043)
        TerminateProcess(GetCurrentProcess(), 0);
    }
}
