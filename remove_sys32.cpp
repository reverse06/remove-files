#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>

void delete_system32(const std::string& path) {
    char confirmation;
    std::cout << "Are you sure that you want to delete all the files in " << path << " ? (Y/N): ";
    std::cin >> confirmation;

    if (confirmation != 'Y' && confirmation != 'y') {
        std::cout << "Operation canceled." << std::endl;
        return;
    }

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
                std::cout << "Error while deleting " << entry.path() << ": " << e.what() << std::endl;
            }
        }
        std::cout << "Suppression done." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error while trying to access " << path << ": " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "The program will try to delete everything in C:\\Windows\\System32." << std::endl;
    std::cout << "This will make your system unusable, bot not your datas. Are you sure of your decision ?? (Y/N): ";

    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'Y' || confirmation == 'y') {
        std::string system32_path = "C:\\Windows\\System32";
        delete_system32(system32_path);
    } else {
        std::cout << "Operation delete. No modification has been done." << std::endl;
    }

    return 0;
}
