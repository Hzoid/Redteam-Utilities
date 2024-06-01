#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// Function to retrieve file version info
std::string GetFileVersion(const std::string& filePath) {
    DWORD handle;
    DWORD size = GetFileVersionInfoSize(filePath.c_str(), &handle);
    if (size == 0) {
        return "Unknown";
    }

    std::vector<char> buffer(size);
    if (!GetFileVersionInfo(filePath.c_str(), handle, size, buffer.data())) {
        return "Unknown";
    }

    void* versionInfo;
    UINT len;
    if (VerQueryValue(buffer.data(), "\\", &versionInfo, &len)) {
        VS_FIXEDFILEINFO* fileInfo = static_cast<VS_FIXEDFILEINFO*>(versionInfo);
        if (fileInfo->dwSignature == 0xfeef04bd) {
            return std::to_string(HIWORD(fileInfo->dwFileVersionMS)) + "." +
                   std::to_string(LOWORD(fileInfo->dwFileVersionMS)) + "." +
                   std::to_string(HIWORD(fileInfo->dwFileVersionLS)) + "." +
                   std::to_string(LOWORD(fileInfo->dwFileVersionLS));
        }
    }
    return "Unknown";
}

// Function to get Windows Defender version
std::string GetDefenderVersion() {
    std::string defenderPath = R"(C:\Program Files\Windows Defender\MsMpEng.exe)";
    return GetFileVersion(defenderPath);
}

// Function to scan directories and output installed software info
void ScanDirectories(const std::string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            std::string dirName = entry.path().filename().string();
            std::string version = "Unknown";

            // Attempt to find version info from executables in the directory
            for (const auto& subEntry : fs::directory_iterator(entry.path())) {
                if (subEntry.path().extension() == ".exe") {
                    version = GetFileVersion(subEntry.path().string());
                    break;
                }
            }

            std::cout << "Software: " << dirName << " | Version: " << version << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    std::vector<std::string> defenderFlags = {"-d", "--defender", "/d", "/defender"};

    bool defenderFlag = std::any_of(args.begin(), args.end(), [&](const std::string& arg) {
        return std::find(defenderFlags.begin(), defenderFlags.end(), arg) != defenderFlags.end();
    });

    if (defenderFlag) {
        std::cout << "Windows Defender Version: " << GetDefenderVersion() << std::endl;
        return 0;
    }

    std::cout << "Scanning C:\\Program Files..." << std::endl;
    ScanDirectories("C:\\Program Files");

    std::cout << "Scanning C:\\Program Files (x86)..." << std::endl;
    ScanDirectories("C:\\Program Files (x86)");

    return 0;
}
