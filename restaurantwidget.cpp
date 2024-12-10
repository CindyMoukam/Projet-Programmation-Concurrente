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

    // Dessiner le sol en carreaux
    drawTileFloor(painter);

    // Dessiner les meubles et équipements
    drawFridge(painter, 700, 50); // Dessiner le frigo en utilisant une image
    drawCooktop(painter, 650, 400); // Dessiner les plaques de cuisson en utilisant une image
}

void RestaurantWidget::drawTileFloor(QPainter &painter)
{
    painter.setPen(QPen(Qt::gray)); // Couleur des lignes de séparation des carreaux
    int tileSize = 40;

    // Boucle à travers les dimensions du sol
    for (int x = 0; x < width(); x += tileSize) {
        for (int y = 0; y < height(); y += tileSize) {
            // Alterner les couleurs entre noir et blanc
            if ((x / tileSize + y / tileSize) % 2 == 0) {
                painter.setBrush(QBrush(Qt::white));  // Couleur blanche
            } else {
                painter.setBrush(QBrush(Qt::black));  // Couleur noire
            }

            // Dessiner le carreau
            painter.drawRect(x, y, tileSize, tileSize); // Dessiner un carreau
        }
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
