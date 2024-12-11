#ifndef CHEFDEPARTIE_H
#define CHEFDEPARTIE_H

//#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <atomic>
//#include "../recipes/Recipe.h"

class ChefDePartie {
public:
    ChefDePartie(int id);
    ~ChefDePartie();

    void start();                      // Démarrer le thread
    void stop();                       // Arrêter le thread
    bool peutPrendreTache() const;     // Vérifier si le chef peut prendre une tâche
    void ajouterTache(int recipeId);   // Ajouter une tâche à la file
    void afficherTaches() const;       // Afficher les tâches en cours
    void executerTaches();

private:
    int id;                            // Identifiant du chef de partie
    std::queue<int> taches;            // File des tâches
    mutable std::mutex mutexTaches;    // Mutex pour protéger la file des tâches
    std::thread threadTaches;          // Thread du chef de partie
    std::atomic<bool> actif;           // Flag pour arrêter le thread proprement

    void cycleDeTravail();             // Fonction principale du thread
    void traiterTache(int recipeId);   // Traiter une tâche
};

#endif // CHEFDEPARTIE_H
