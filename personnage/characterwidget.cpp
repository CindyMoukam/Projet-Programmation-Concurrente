#include "characterwidget.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPainterPath>


CharacterWidget::CharacterWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(200, 200); // Taille fixe du widget
}

CharacterWidget::~CharacterWidget() {}

void CharacterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Lissage des formes

    // Dessiner la tête (cercle noir)
    painter.setBrush(QBrush(Qt::black)); // Tête noire
    painter.setPen(Qt::black); // Contour noir
    painter.drawEllipse(50, 30, 100, 100); // Position et taille du cercle

    // Dessiner les yeux (rouges)
    painter.setBrush(QBrush(Qt::red)); // Couleur des yeux
    painter.drawEllipse(80, 60, 15, 15); // Oeil gauche
    painter.drawEllipse(120, 60, 15, 15); // Oeil droit

    // Dessiner la bouche
    QPainterPath path;
    path.moveTo(80, 100);
    path.quadTo(100, 130, 120, 100);
    painter.setPen(Qt::black); // Contour noir pour la bouche
    painter.drawPath(path);

    // Dessiner la veste (rectangle bleu)
    painter.setBrush(QBrush(Qt::blue)); // Couleur de la veste
    painter.setPen(Qt::black); // Contour noir
    painter.drawRect(50, 130, 100, 60); // Position et taille du rectangle de la veste
}
