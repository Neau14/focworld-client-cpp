#include "AutoUpdater.h"
#include <ixwebsocket/IXHttpClient.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

using json = nlohmann::json;

#define CURRENT_APP_VERSION "1.0.2"

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
        auto response = httpClient.get("https://pub-7bd6715a1810463a94e5194e6ed940dd.r2.dev/version.json", args);

        if (!response || response->statusCode != 200) {
            std::cout << "Aucune mise a jour trouvee ou erreur reseau." << std::endl;
            m_state = UpdaterState::UP_TO_DATE;
            return;
        }

        try {
            json data = json::parse(response->body);
            std::string latestVersion = data.value("version", CURRENT_APP_VERSION);
            
            if (latestVersion != CURRENT_APP_VERSION) {
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
}

void AutoUpdater::StartDownload() {
    if (m_state != UpdaterState::UPDATE_AVAILABLE) return;
    m_state = UpdaterState::DOWNLOADING;

    if (m_workerThread.joinable()) m_workerThread.join();

    m_workerThread = std::thread([this]() {
        char tempPath[MAX_PATH];
        GetTempPathA(MAX_PATH, tempPath);
        m_tempSetupPath = std::string(tempPath) + "FOCWorld_TCG_Update.exe";

        HRESULT hr = URLDownloadToFileA(NULL, m_setupUrl.c_str(), m_tempSetupPath.c_str(), 0, NULL);
        if (hr == S_OK) {
            m_state = UpdaterState::READY_TO_INSTALL;
        } else {
            m_error = "Erreur lors du telechargement.";
            m_state = UpdaterState::FAILED;
        }
    });
}

void AutoUpdater::InstallAndExit() {
    if (m_state == UpdaterState::READY_TO_INSTALL) {
        ShellExecuteA(NULL, "open", m_tempSetupPath.c_str(), "/SILENT", NULL, SW_SHOWNORMAL);
        exit(0);
    }
}
