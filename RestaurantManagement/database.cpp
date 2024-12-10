#include "Database.h"
#include <QSqlError>

// Constructeur privé
Database::Database() {
    db = QSqlDatabase::addDatabase("QPSQL"); // Utilisez le driver PostgreSQL
}

// Destructeur
Database::~Database() {
    if (db.isOpen()) {
        db.close();
    }
}

// Instance unique (singleton)
Database & Database::instance() {
    static Database instance;
    return instance;
}

// Connexion à la base de données
bool Database::connect(const QString& host, const QString& databaseName, const QString& username, const QString& password) {
    // Vérifier si la base est déjà connectée
    if (db.isOpen()) {
        qDebug() << "La connexion à la base de données est déjà ouverte.";
        return true;
    }

    // Configuration de la connexion
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);

    // Ouverture de la base
    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données : " << db.lastError().text();
        return false;
    }

    qDebug() << "Connexion réussie à la base de données PostgreSQL!";
    return true;
}

// Déconnexion de la base de données
void Database::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de données déconnectée.";
    } else {
        qDebug() << "Aucune connexion ouverte à fermer.";
    }
}


// Récupérer l'objet base de données
QSqlDatabase Database::getDatabase() const {
    return db;
}
