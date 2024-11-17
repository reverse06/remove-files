#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>

// Fonction pour supprimer des fichiers dans C:\Windows\System32
void delete_system32(const std::string& path) {
    // Demander confirmation à l'utilisateur
    char confirmation;
    std::cout << "Êtes-vous sûr de vouloir supprimer tous les fichiers dans " << path << " ? (O/N): ";
    std::cin >> confirmation;

    if (confirmation != 'O' && confirmation != 'o') {
        std::cout << "Opération annulée." << std::endl;
        return;
    }

    // Parcourir le répertoire System32 et supprimer les fichiers
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            try {
                if (entry.is_regular_file()) {
                    std::filesystem::remove(entry.path());
                    std::cout << "Supprimé : " << entry.path() << std::endl;
                } else if (entry.is_directory()) {
                    std::filesystem::remove_all(entry.path());
                    std::cout << "Répertoire supprimé : " << entry.path() << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Erreur lors de la suppression de " << entry.path() << ": " << e.what() << std::endl;
            }
        }
        std::cout << "Suppression terminée." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erreur lors de l'accès au répertoire " << path << ": " << e.what() << std::endl;
    }
}

int main() {
    // Demander à l'utilisateur une confirmation avant d'agir
    std::cout << "Le programme va tenter de supprimer les fichiers dans C:\\Windows\\System32." << std::endl;
    std::cout << "Cela rendra le système inutilisable. Êtes-vous sûr de vouloir continuer ? (O/N): ";
    
    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'O' || confirmation == 'o') {
        std::string system32_path = "C:\\Windows\\System32";
        delete_system32(system32_path);
    } else {
        std::cout << "Opération annulée. Aucune modification effectuée." << std::endl;
    }

    return 0;
}
