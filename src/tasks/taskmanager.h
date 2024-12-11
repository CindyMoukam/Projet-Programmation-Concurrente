#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "../database/DatabaseManager.h"

class TaskManager {
public:
    TaskManager();
    void gererCommandes();        // Gérer les commandes en attente
    void mettreAJourTaskQueue();  // Mettre à jour la file des tâches

private:
    DatabaseManager& dbManager;
};

#endif // TASKMANAGER_H
