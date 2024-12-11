#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager& instance(); // Singleton pour la gestion unique de la base de données
    bool connect(const QString& dbPath); // Méthode de connexion à la base de données
    void close(); // Ferme la connexion
    QSqlDatabase getDatabase() const; // Renvoie l'objet QSqlDatabase
    void logError(const QString& message); // Méthode pour enregistrer les erreurs dans un fichier log

private:
    DatabaseManager();  // Constructeur privé
    ~DatabaseManager(); // Destructeur
    DatabaseManager(const DatabaseManager&) = delete; // Empêche la copie
    DatabaseManager& operator=(const DatabaseManager&) = delete; // Empêche l'affectation

    QSqlDatabase db; // Objet de connexion à la base de données
};

#endif // DATABASEMANAGER_H
