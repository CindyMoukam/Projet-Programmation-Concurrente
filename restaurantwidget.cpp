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
    drawFridge(painter, 700, 50); // Dessiner le frigo en utilisant une image
    drawCooktop(painter, 650, 400); // Dessiner les plaques de cuisson en utilisant une image
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
    QPixmap fridgeImage(":/static/frigo.png"); // Charge l'image depuis le dossier `static`
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
    QPixmap cooktopImage(":/static/cuisson.png"); // Charge l'image depuis le dossier `static`
    if (!cooktopImage.isNull()) {
        painter.drawPixmap(x, y, 170, 100, cooktopImage); // Dessiner l'image avec une taille spécifique
    } else {
        // Dessiner un rectangle gris si l'image n'est pas trouvée
        painter.setBrush(QBrush(Qt::darkGray));
        painter.setPen(QPen(Qt::black));
        painter.drawRect(x, y, 80, 40);
    }
}
