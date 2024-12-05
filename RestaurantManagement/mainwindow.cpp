#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reservationwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Modifier la police du texte
    QFont font;
    font.setPointSize(24); // Taille de police agrandie
    font.setBold(true);    // Police en gras
    ui->label->setFont(font);

    // Centrer le texte dans le QLabel
    ui->label->setAlignment(Qt::AlignCenter);


    // Définir une hauteur fixe pour le bouton (optionnel si nécessaire)
    ui->pushButton->setFixedHeight(50);

    // Connecter le bouton à la méthode pour ouvrir la fenêtre de réservation
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openReservationWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openReservationWindow() {
    // Fermer la fenêtre principale
    this->close();

    // Créer et afficher la fenêtre de réservation
    ReservationWindow *reservationWindow = new ReservationWindow();
    reservationWindow->show();
}
