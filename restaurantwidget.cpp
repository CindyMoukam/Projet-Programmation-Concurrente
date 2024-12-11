#include "restaurantwidget.h"
#include <QPainter>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <QColor> // Inclure QColor pour définir des couleurs personnalisées

RestaurantWidget::RestaurantWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 600); // Taille fixe du widget pour la maquette du restaurant
}

RestaurantWidget::~RestaurantWidget() {}

void RestaurantWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dessiner le sol avec une image
    drawTileFloor(painter);

    // Dessiner les meubles et équipements
    drawFridge(painter, 700, 50); // Dessiner le frigo
    drawCooktop(painter, 650, 400); // Dessiner les plaques de cuisson
    drawMicrowave(painter, 700, 300); // Dessiner le micro-ondes

    // Dessiner l'image du plat au centre
    drawDish(painter);
}

void RestaurantWidget::drawTileFloor(QPainter &painter)
{
    QPixmap floorImage(":/static/sol.jpg"); // Charger l'image depuis le dossier `static`
    if (!floorImage.isNull()) {
        // Dessiner l'image en répétition pour couvrir tout le widget
        QBrush brush(floorImage);
        painter.setBrush(brush);
        painter.drawRect(0, 0, width(), height()); // Couvrir tout le sol avec l'image
    } else {
        // Afficher un message d'erreur ou utiliser une couleur par défaut si l'image n'est pas trouvée
        painter.setBrush(QBrush(Qt::gray));
        painter.drawRect(0, 0, width(), height());
    }
}

// Méthode pour afficher une image comme frigo
void RestaurantWidget::drawFridge(QPainter &painter, int x, int y)
{
    QPixmap fridgeImage(":/static/frigo.png"); // Charger l'image depuis le dossier `static`
    if (!fridgeImage.isNull()) {
        painter.drawPixmap(x, y, 100, 200, fridgeImage); // Dessiner l'image avec une taille spécifique
    } else {
        // Dessiner un rectangle gris si l'image n'est pas trouvée
        painter.setBrush(QBrush(Qt::lightGray));
        painter.setPen(QPen(Qt::black));
        painter.drawRect(x, y, 60, 100);
    }
}

// Méthode pour afficher une image comme plaques de cuisson
void RestaurantWidget::drawCooktop(QPainter &painter, int x, int y)
{
    QPixmap cooktopImage(":/static/cuisson.png"); // Charger l'image depuis le dossier `static`
    if (!cooktopImage.isNull()) {
        painter.drawPixmap(x, y, 170, 100, cooktopImage); // Dessiner l'image avec une taille spécifique
    } else {
        // Dessiner un rectangle gris si l'image n'est pas trouvée
        painter.setBrush(QBrush(Qt::darkGray));
        painter.setPen(QPen(Qt::black));
        painter.drawRect(x, y, 80, 40);
    }
}

// Méthode pour afficher une image comme micro-ondes
void RestaurantWidget::drawMicrowave(QPainter &painter, int x, int y)
{
    QPixmap microwaveImage(":/static/micro.png"); // Charger l'image depuis le dossier `static`
    if (!microwaveImage.isNull()) {
        painter.drawPixmap(x, y, 100, 100, microwaveImage); // Dessiner l'image avec une taille spécifique
    } else {
        // Dessiner un rectangle gris si l'image n'est pas trouvée
        painter.setBrush(QBrush(Qt::lightGray));
        painter.setPen(QPen(Qt::black));
        painter.drawRect(x, y, 80, 80);
    }
}

// Méthode pour afficher l'image du plat au centre
void RestaurantWidget::drawDish(QPainter &painter)
{
    QPixmap dishImage(":/static/vide.png"); // Charger l'image depuis le dossier `static`
    if (!dishImage.isNull()) {
        int dishWidth = 150; // Largeur réduite du plat
        int dishHeight = 150; // Hauteur réduite du plat

        // Calculer la position pour centrer l'image
        int x = (width() - dishWidth) / 2;
        int y = (height() - dishHeight) / 2;

        // Dessiner l'image réduite
        painter.drawPixmap(x, y, dishWidth, dishHeight, dishImage);
    } else {
        // Dessiner un carré gris au centre si l'image n'est pas trouvée
        painter.setBrush(QBrush(Qt::lightGray));
        painter.setPen(QPen(Qt::black));
        int dishWidth = 150;
        int dishHeight = 150;
        int x = (width() - dishWidth) / 2;
        int y = (height() - dishHeight) / 2;
        painter.drawRect(x, y, dishWidth, dishHeight);
    }
}
