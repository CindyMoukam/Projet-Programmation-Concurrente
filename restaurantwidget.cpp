#include "restaurantwidget.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>  // Inclure QColor pour définir des couleurs personnalisées

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

    // Dessiner des tables et leurs chaises
    drawTable(painter, 50, 50, 4); // Table de 4 personnes à la position (100, 100)
    drawTable(painter, 300, 100, 6); // Table de 6 personnes à la position (300, 100)
    drawTable(painter, 500, 100, 4); // Table de 4 personnes à la position (500, 100)

    // Dessiner des chaises autour des tables
    // Table de 4
    drawChair(painter, 70, 130);  // Chaise pour la table de 4, position 1
    drawChair(painter, 130, 130); // Chaise pour la table de 4, position 2
    drawChair(painter, 70, 190);  // Chaise pour la table de 4, position 3
    drawChair(painter, 130, 190); // Chaise pour la table de 4, position 4

    // Table de 6
    drawChair(painter, 270, 130); // Chaise pour la table de 6, position 1
    drawChair(painter, 330, 130); // Chaise pour la table de 6, position 2
    drawChair(painter, 270, 190); // Chaise pour la table de 6, position 3
    drawChair(painter, 330, 190); // Chaise pour la table de 6, position 4
    drawChair(painter, 270, 250); // Chaise pour la table de 6, position 5
    drawChair(painter, 330, 250); // Chaise pour la table de 6, position 6

    // Table de 4
    drawChair(painter, 470, 130); // Chaise pour la table de 4, position 1
    drawChair(painter, 530, 130); // Chaise pour la table de 4, position 2
    drawChair(painter, 470, 190); // Chaise pour la table de 4, position 3
    drawChair(painter, 530, 190); // Chaise pour la table de 4, position 4
}

void RestaurantWidget::drawTable(QPainter &painter, int x, int y, int size)
{
    // Dessiner la table (cercle pour simplifier)
    painter.setBrush(QBrush(QColor("brown"))); // Couleur de la table : "brown"
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

void RestaurantWidget::drawTileFloor(QPainter &painter)
{
    // Dessiner un sol en carreaux (dessin de petits rectangles)
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

