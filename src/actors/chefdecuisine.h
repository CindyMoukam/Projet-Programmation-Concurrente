#ifndef CHEFDECUISINE_H
#define CHEFDECUISINE_H

#include <vector>
#include <thread>
#include <atomic>
#include "../database/DatabaseManager.h"
#include "ChefDePartie.h"

class ChefDeCuisine {
public:
    ChefDeCuisine();
    ~ChefDeCuisine();

    void start(); // Démarrer le thread
    void stop();  // Arrêter le thread

private:
    DatabaseManager& dbManager;
    std::vector<ChefDePartie*> chefsDePartie;
    std::thread threadCuisine;
    std::atomic<bool> actif; // Flag pour arrêter proprement le thread
    int prochainChef; // Suivi du prochain chef à assigner

    void cycleDeTravail(); // Cycle de travail du Chef de Cuisine
    void gererCommandes(); // Gérer les commandes
    void distribuerTaches(); // Distribuer les tâches

    // Méthodes auxiliaires
    bool ingredientsDisponibles(int recipeId);
    void mettreAJourStocks(int recipeId);
    void afficherOrdreDeTraitement();
    void afficherRedistribution();
};

#endif // CHEFDECUISINE_H
