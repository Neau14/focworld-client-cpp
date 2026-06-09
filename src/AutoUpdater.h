#pragma once
#include <string>
#include <atomic>
#include <thread>

enum class UpdaterState {
    IDLE,
    CHECKING,
    UPDATE_AVAILABLE,
    DOWNLOADING,
    READY_TO_INSTALL,
    UP_TO_DATE,
    FAILED
};

class AutoUpdater {
public:
    static AutoUpdater& Get();

    void CheckForUpdates();
    void StartDownload();
    void InstallAndExit();
    
    UpdaterState GetState() const { return m_state; }
    std::string GetErrorMessage() const { return m_error; }

private:
    AutoUpdater() = default;
    
    std::atomic<UpdaterState> m_state{UpdaterState::IDLE};
    std::string m_error;
    std::string m_setupUrl;
    std::string m_tempSetupPath;
    
    std::thread m_workerThread;
};
