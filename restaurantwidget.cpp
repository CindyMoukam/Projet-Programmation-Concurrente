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

    // Dessiner des tables et leurs chaises
    drawTable(painter, 50, 50, 4); // Table de 4 personnes à la position (50, 50)
    drawTable(painter, 300, 100, 6); // Table de 6 personnes à la position (300, 100)
    drawTable(painter, 500, 100, 4); // Table de 4 personnes à la position (500, 100)

    // Dessiner des chaises autour des tables
    drawChairsForTable(painter, 50, 50, 4);  // Chaises pour la table de 4
    drawChairsForTable(painter, 300, 100, 6); // Chaises pour la table de 6
    drawChairsForTable(painter, 500, 100, 4); // Chaises pour la table de 4
}

void RestaurantWidget::drawTable(QPainter &painter, int x, int y, int size)
{
    // Dessiner la table (cercle pour simplifier)
    painter.setBrush(QBrush(QColor("brown"))); // Couleur de la table
    painter.setPen(QPen(Qt::black)); // Contour de la table
    painter.drawEllipse(x, y, 80, 80); // Dessiner un cercle pour la table

    // Dessiner le nom de la table (en fonction de sa taille)
    painter.setPen(QPen(Qt::white)); // Texte blanc pour la taille de la table
    painter.drawText(x + 10, y + 40, QString("Table %1").arg(size));
}

void RestaurantWidget::drawChair(QPainter &painter, int x, int y)
{
    // Dessiner la chaise (petit cercle pour simplifier)
    painter.setBrush(QBrush(Qt::blue)); // Couleur de la chaise
    painter.setPen(QPen(Qt::black)); // Contour de la chaise
    painter.drawEllipse(x, y, 30, 30); // Dessiner un cercle pour la chaise
}

void RestaurantWidget::drawChairsForTable(QPainter &painter, int x, int y, int size)
{
    // Définir les positions des chaises en fonction de la taille de la table
    int chairDistance = 40; // Distance entre les chaises

    if (size == 4) {
        // Chaises autour d'une table de 4
        drawChair(painter, x - chairDistance, y); // Chaise gauche
        drawChair(painter, x + 80, y); // Chaise droite
        drawChair(painter, x, y - chairDistance); // Chaise haut
        drawChair(painter, x, y + 80); // Chaise bas
    }
    else if (size == 6) {
        // Chaises autour d'une table de 6
        drawChair(painter, x - chairDistance, y); // Chaise gauche
        drawChair(painter, x + 80, y); // Chaise droite
        drawChair(painter, x, y - chairDistance); // Chaise haut
        drawChair(painter, x, y + 80); // Chaise bas
        drawChair(painter, x - chairDistance, y + 80); // Chaise bas gauche
        drawChair(painter, x + 80, y + 80); // Chaise bas droite
    }
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
