#include "mainwindow.h"
<<<<<<< HEAD
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
=======
#include "characterwidget.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Créer un widget de personnage
    CharacterWidget *characterWidget = new CharacterWidget(this);

    // Ajouter le widget du personnage à la mise en page
    ui->centralwidget->layout()->addWidget(characterWidget);

    // Créer une animation pour déplacer le personnage horizontalement
    QPropertyAnimation *animation = new QPropertyAnimation(characterWidget, "pos");
    animation->setDuration(2000);  // Durée de l'animation en millisecondes (2 secondes)
    animation->setStartValue(QPoint(0, 100));  // Position de départ
    animation->setEndValue(QPoint(600, 100)); // Position d'arrivée
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Type de courbe d'animation (lissée)
    animation->start();
>>>>>>> 5fdc774 (Modélisation personnage)
}

MainWindow::~MainWindow()
{
<<<<<<< HEAD
    delete ui;  // Libérer les ressources de l'interface
    delete restaurantWidget;  // Libérer le widget personnalisé
=======
    delete ui;
>>>>>>> 5fdc774 (Modélisation personnage)
}
