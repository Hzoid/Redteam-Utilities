#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <direct.h>

void displayStorageInfo(bool allDrives) {
    char drive = 'A';
    do {
        std::string drivePath = std::string(1, drive) + ":\\";
        UINT driveType = GetDriveTypeA(drivePath.c_str());
        std::string type;
        switch (driveType) {
            case DRIVE_FIXED:
                type = "LOCAL";
                break;
            case DRIVE_REMOTE:
                type = "NET";
                break;
            default:
                type = "UNKNOWN";
                break;
        }
        ULARGE_INTEGER freeBytesAvailableToCaller, totalNumberOfBytes, totalNumberOfFreeBytes;
        if (GetDiskFreeSpaceExA(drivePath.c_str(), &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            double totalGB = totalNumberOfBytes.QuadPart / (1024.0 * 1024 * 1024);
            double usedGB = (totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / (1024.0 * 1024 * 1024);
            std::cout << drivePath << " (" << type << ")\t\t" 
                      << std::fixed << std::setprecision(2)
                      << usedGB << "/" << totalGB << "GB" 
                      << std::endl;
        }
        ++drive;
    } while (allDrives && drive <= 'Z');
}

int main(int argc, char* argv[]) {
    bool showAllDrives = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--all") == 0 || strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "/a") == 0 || strcmp(argv[i], "/all") == 0) {
            showAllDrives = true;
        }
    }

    if (showAllDrives) {
        displayStorageInfo(true);
    } else {
        int currentDriveNumber = _getdrive();
        char currentDrive = 'A' + currentDriveNumber - 1;
        std::string currentDrivePath = std::string(1, currentDrive) + ":\\";
        UINT driveType = GetDriveTypeA(currentDrivePath.c_str());
        std::string type;
        switch (driveType) {
            case DRIVE_FIXED:
                type = "LOCAL";
                break;
            case DRIVE_REMOTE:
                type = "NET";
                break;
            default:
                type = "UNKNOWN";
                break;
        }
        ULARGE_INTEGER freeBytesAvailableToCaller, totalNumberOfBytes, totalNumberOfFreeBytes;
        if (GetDiskFreeSpaceExA(currentDrivePath.c_str(), &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            double totalGB = totalNumberOfBytes.QuadPart / (1024.0 * 1024 * 1024);
            double usedGB = (totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / (1024.0 * 1024 * 1024);
            std::cout << currentDrivePath << " (" << type << ")\t\t" 
                      << std::fixed << std::setprecision(2)
                      << usedGB << "/" << totalGB << "GB" 
                      << std::endl;
        }
    }

    return 0;
}
