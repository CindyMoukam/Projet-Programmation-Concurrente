#include "ChefDePartie.h"
#include "../database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <iostream>
#include <chrono>
#include <thread>

extern std::mutex dbMutex; // Déclarez ce mutex global

ChefDePartie::ChefDePartie(int id) : id(id), actif(false) {}

ChefDePartie::~ChefDePartie() {
    stop();
}

void ChefDePartie::start() {
    if (actif) return; // Éviter de démarrer plusieurs fois
    actif = true;
    threadTaches = std::thread(&ChefDePartie::cycleDeTravail, this);
    std::cout << "Chef de Partie " << id << " démarré." << std::endl;
}

void ChefDePartie::stop() {
    actif = false;
    if (threadTaches.joinable()) {
        threadTaches.join(); // Attendre la fin du thread
    }
    std::cout << "Chef de Partie " << id << " arrêté." << std::endl;
}

bool ChefDePartie::peutPrendreTache() const {
    std::lock_guard<std::mutex> lock(mutexTaches);
    return taches.size() < 5; // Limite de 5 tâches simultanées
}

void ChefDePartie::ajouterTache(int recipeId) {
    std::lock_guard<std::mutex> lock(mutexTaches);
    taches.push(recipeId);
    std::cout << "Chef de Partie " << id << " a reçu une nouvelle tâche pour la recette " << recipeId << "." << std::endl;
}

void ChefDePartie::afficherTaches() const {
    std::lock_guard<std::mutex> lock(mutexTaches);
    std::cout << "Chef de Partie " << id << " traite les tâches suivantes : ";
    std::queue<int> temp = taches; // Copier la file pour l'affichage
    while (!temp.empty()) {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}

void ChefDePartie::cycleDeTravail() {
    while (actif) {
        int recipeId = -1;

        {
            std::lock_guard<std::mutex> lock(mutexTaches);
            if (!taches.empty()) {
                recipeId = taches.front();
                taches.pop();
            }
        }

        if (recipeId != -1) {
            traiterTache(recipeId);
        } else {
            // Si aucune tâche, attendre un peu avant de vérifier à nouveau
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void ChefDePartie::traiterTache(int recipeId) {
    std::lock_guard<std::mutex> lock(dbMutex); // Verrouiller pendant l'accès à la base de données

    std::cout << "Chef de Partie " << id << " commence la tâche pour la recette " << recipeId << "." << std::endl;

    // Simuler le temps de préparation
    std::this_thread::sleep_for(std::chrono::seconds(2));

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("UPDATE tasks SET status = 'Terminé' WHERE recipe_id = :recipe_id");
    query.bindValue(":recipe_id", recipeId);

    if (!query.exec()) {
        qCritical() << "Erreur lors de la mise à jour de l'état de la tâche :" << query.lastError().text();
    } else {
        std::cout << "Chef de Partie " << id << " a terminé la tâche pour la recette " << recipeId << "." << std::endl;
    }
}
