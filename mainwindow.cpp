#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "restaurantwidget.h"  // Inclure l'en-tête du widget personnalisé

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    restaurantWidget(new RestaurantWidget(this)) // Initialiser le widget personnalisé
{
    ui->setupUi(this);  // Initialiser l'interface graphique

    // Définir le widget central de la fenêtre principale
    setCentralWidget(restaurantWidget); // Ajouter le widget RestaurantWidget comme widget central
}

MainWindow::~MainWindow()
{
    delete ui;  // Libérer les ressources de l'interface
    delete restaurantWidget;  // Libérer le widget personnalisé
}
