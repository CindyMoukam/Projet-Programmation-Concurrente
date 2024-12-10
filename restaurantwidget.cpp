#include "restaurantwidget.h"
#include <QPainter>
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
    drawFridge(painter, 700, 50); // Dessiner le frigo dans le coin supérieur droit
    drawCooktop(painter, 650, 400); // Dessiner les plaques de cuisson en bas à droite
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

// Méthodes pour dessiner le frigo et les plaques de cuisson
void RestaurantWidget::drawFridge(QPainter &painter, int x, int y)
{
    painter.setBrush(QBrush(Qt::lightGray)); // Couleur du frigo
    painter.setPen(QPen(Qt::black)); // Contour du frigo
    painter.drawRect(x, y, 60, 100); // Dessiner un rectangle pour le frigo
}

void RestaurantWidget::drawCooktop(QPainter &painter, int x, int y)
{
    painter.setBrush(QBrush(Qt::darkGray)); // Couleur des plaques de cuisson
    painter.setPen(QPen(Qt::black)); // Contour des plaques de cuisson
    painter.drawRect(x, y, 80, 40); // Dessiner un rectangle pour les plaques de cuisson

    // Dessiner les cercles représentant les plaques de cuisson
    painter.setBrush(QBrush(Qt::black)); // Plaques de cuisson noires
    painter.drawEllipse(x + 10, y + 10, 20, 20); // Plaque 1
    painter.drawEllipse(x + 40, y + 10, 20, 20); // Plaque 2
    painter.drawEllipse(x + 10, y + 25, 20, 20); // Plaque 3
    painter.drawEllipse(x + 40, y + 25, 20, 20); // Plaque 4
}
