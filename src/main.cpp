#include <QCoreApplication>
#include "./database/DatabaseManager.h"
#include "./tasks/TaskManager.h"
#include "./actors/ChefdeCuisine.h"
#include "./utils/Timer.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>


// Gestion globale de pause/play
std::atomic<bool> isPaused(false);
std::mutex pauseMutex;
std::condition_variable pauseCond;

void gestionPause() {
    std::cout << "L'application est en pause pendant 10 secondes..." << std::endl;

    // Mettre l'application en pause pendant 10 secondes
    isPaused = false;
    pauseCond.notify_all(); // Notifier tous les threads de mise en pause
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Relancer l'application après 10 secondes
    isPaused = false;
    pauseCond.notify_all(); // Notifier tous les threads de reprise
    std::cout << "L'application reprend..." << std::endl;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Chemin vers la base de données
    const QString dbPath = "C:/Users/user/Documents/RestaurantManagement/src/database/restaurantmanagement";

    // Récupérer l'instance du DatabaseManager
    DatabaseManager& dbManager = DatabaseManager::instance();

    // Connexion à la base de données
    if (!dbManager.connect(dbPath)) {
        qCritical() << "Impossible de se connecter à la base de données. Vérifiez le fichier log pour plus de détails.";
        return -1; // Quitter si la connexion échoue
    }

    qDebug() << "Base de données connectée avec succès.";

    // Initialiser le Timer
    Timer& timer = Timer::instance();
    timer.setTimeSpeed(60); // 5 minutes réelles = 1 seconde simulée
    timer.setCurrentTime(10, 0); // Démarrer à 10h00
    timer.start();

    // Système de gestion des commandes
    TaskManager taskManager;
    taskManager.gererCommandes();

    // Initialiser le Chef de Cuisine
    ChefDeCuisine chefDeCuisine;
    chefDeCuisine.start();

    // Simulation d'une durée de travail de l'application
    std::this_thread::sleep_for(std::chrono::seconds(10));

    /*// Lancer un thread pour gérer les pauses via l'entrée utilisateur
    std::thread pauseThread(gestionPause);

    // Boucle principale de l'application
    while (true) {
        {
            // Gestion de la pause
            std::unique_lock<std::mutex> lock(pauseMutex);
            pauseCond.wait(lock, [] { return !isPaused; }); // Attente si en pause
        }

        // Afficher l'heure actuelle
        std::cout << "Heure actuelle dans l'application : " << timer.getCurrentTime() << std::endl;

        // Simulation d'une boucle de travail
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }*/

    // Arrêt propre du chef de cuisine
    chefDeCuisine.stop();
    qDebug() << "Chef de cuisine arrêté.";

    //Arrêt du temps
    timer.stop();

    // Fermeture de la base de données
    //dbManager.close();
    //qDebug() << "Base de données déconnectée.";

    // Attendre la fin du thread pause/play
    /*if (pauseThread.joinable()) {
        pauseThread.join();
    }*/

    // Exécution de l'application
    return app.exec();
}
