#include "DatabaseManager.h"
#include <QFile>
#include <QSqlError>
#include <QTextStream>
#include <QDebug>

// Constructeur
DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE", "main_connection"); // Utilisation du pilote SQLite avec un alias
}

// Destructeur
DatabaseManager::~DatabaseManager() {
    close();
}

// Singleton
DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

// Méthode de connexion à la base de données
bool DatabaseManager::connect(const QString& dbPath) {
    QFile dbFile(dbPath);
    if (!dbFile.exists()) {
        QString errorMessage = "Erreur : Le fichier de base de données n'existe pas : " + dbPath;
        qCritical() << errorMessage;
        logError(errorMessage);
        return false;
    }

    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QString errorMessage = "Erreur de connexion à la base de données : " + db.lastError().text();
        qCritical() << errorMessage;
        logError(errorMessage);
        return false;
    }

    qDebug() << "Connexion à la base de données réussie : chemin =" << dbPath;
    return true;
}

// Fermer la connexion
void DatabaseManager::close() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Connexion à la base de données fermée.";
    }
}

// Récupérer l'objet QSqlDatabase
QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}

// Enregistrement des erreurs dans un fichier log
void DatabaseManager::logError(const QString& message) {
    QFile logFile("../../tests/database/error.log");

    if (!logFile.exists()) {
        if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qCritical() << "Impossible de créer le fichier log.";
            return;
        }
        logFile.close();
    }

    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << message << "\n";
        logFile.close();
    } else {
        qCritical() << "Impossible d'écrire dans le fichier log.";
    }
}
