#include "reservationwindow.h"
#include "ui_reservationwindow.h"
#include "verifyreservation.h"
#include "taketable.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void ReservationWindow::addReservation(const QString& clientName, const QString& date, int tableId)
{
    QSqlDatabase db = Database::instance().getDatabase();

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO reservations (client_name, reservation_date, table_id) VALUES (:clientName, :date, :tableId)");
        query.bindValue(":clientName", clientName);
        query.bindValue(":date", date);
        query.bindValue(":tableId", tableId);

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'ajout de la réservation :" << query.lastError().text();
        } else {
            qDebug() << "Réservation ajoutée avec succès.";
        }
    } else {
        qDebug() << "La base de données n'est pas ouverte.";
    }
}


ReservationWindow::ReservationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReservationWindow)
{
    ui->setupUi(this);

    // Modifier la police du texte
    QFont font;
    font.setPointSize(18); // Taille de police agrandie
    font.setBold(false);    // Police en gras
    ui->questionLabel->setFont(font);

    // Définir une hauteur fixe pour le bouton (optionnel si nécessaire)
    ui->yesButton->setFixedHeight(30);
    ui->noButton->setFixedHeight(30);

    // Connecter les boutons à leurs slots respectifs
    connect(ui->yesButton, &QPushButton::clicked, this, &ReservationWindow::onYesClicked);
    connect(ui->noButton, &QPushButton::clicked, this, &ReservationWindow::onNoClicked);
}

ReservationWindow::~ReservationWindow()
{
    delete ui;
}

// Slot pour le bouton "Oui"
void ReservationWindow::onYesClicked() {
    this->close();  // Fermer la fenêtre actuelle de réservation
    // Créer et afficher le widget VerifyReservation
    VerifyReservation *verifyWindow = new VerifyReservation();
    verifyWindow->show();
}

// Slot pour le bouton "Non"
void ReservationWindow::onNoClicked() {
    // Action lorsque "Non" est cliqué
    this->close();  // Par exemple, fermer la fenêtre de réservation
    // Créer et afficher le widget
    taketable *takeWindow = new taketable();
    takeWindow->show();
}
