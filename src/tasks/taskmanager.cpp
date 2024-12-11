#include "TaskManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TaskManager::TaskManager()
    : dbManager(DatabaseManager::instance()) {}

// Gérer les commandes en attente
void TaskManager::gererCommandes() {
    QSqlQuery query(dbManager.getDatabase());

    if (!dbManager.getDatabase().isOpen()) {
        qCritical() << "La connexion à la base de données est fermée.";
        return;
    }

    if (!query.exec("SELECT task_id, recipe_id FROM tasks WHERE status = 'En attente' AND assigned = 0 ORDER BY task_id")) {
        qCritical() << "Erreur lors de la récupération des commandes en attente :" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Aucune commande en attente.";
        return;
    }

    qDebug() << "Commandes récupérées avec succès. Mise à jour de task_queue...";
    mettreAJourTaskQueue();
}

// Mettre à jour la table task_queue
void TaskManager::mettreAJourTaskQueue() {
    QSqlQuery query(dbManager.getDatabase());

    if (!dbManager.getDatabase().isOpen()) {
        qCritical() << "La connexion à la base de données est fermée.";
        return;
    }

    if (!query.exec("DELETE FROM task_queue WHERE task_id NOT IN (SELECT task_id FROM tasks WHERE assigned = 1)")) {
        qCritical() << "Erreur lors de la réinitialisation de task_queue :" << query.lastError().text();
        return;
    }

    QSqlQuery fetchQuery(dbManager.getDatabase());
    if (!fetchQuery.exec("SELECT task_id FROM tasks WHERE status = 'En attente' AND assigned = 0 ORDER BY task_id")) {
        qCritical() << "Erreur lors de la récupération des tâches pour task_queue :" << fetchQuery.lastError().text();
        return;
    }

    int position = 1;
    QSqlQuery insertQuery(dbManager.getDatabase());
    while (fetchQuery.next()) {
        int taskId = fetchQuery.value("task_id").toInt();

        insertQuery.prepare("INSERT INTO task_queue (task_id, queue_position) VALUES (:task_id, :queue_position)");
        insertQuery.bindValue(":task_id", taskId);
        insertQuery.bindValue(":queue_position", position++);

        if (!insertQuery.exec()) {
            qCritical() << "Erreur lors de l'insertion dans task_queue :" << insertQuery.lastError().text();
        }
    }

    qDebug() << "Mise à jour de task_queue terminée.";
}
