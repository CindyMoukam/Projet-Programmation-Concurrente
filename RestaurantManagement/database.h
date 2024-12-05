#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>

class Database {
public:
    // Méthode pour obtenir l'instance unique
    static Database & instance();

    // Méthode pour se connecter à la base de données
    bool connect(const QString& host, const QString& databaseName, const QString& username, const QString& password);

    // Méthode pour fermer la connexion
    void disconnect();

    // Récupérer l'objet base de données
    QSqlDatabase getDatabase() const;

private:
    Database();                     // Constructeur privé (singleton)
    ~Database();                    // Destructeur

    QSqlDatabase db;                       // Instance de QSqlDatabase

    Database(const Database&) = delete; // Suppression du constructeur par copie
    Database& operator=(const Database&) = delete; // Suppression de l'opérateur d'affectation
};

#endif // DATABASEMANAGER_H
