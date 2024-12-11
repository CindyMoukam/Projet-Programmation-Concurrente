#ifndef RESTAURANTWIDGET_H
#define RESTAURANTWIDGET_H

#include <QWidget>

class RestaurantWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantWidget(QWidget *parent = nullptr);
    ~RestaurantWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    // Méthodes pour dessiner les éléments du restaurant
    void drawTable(QPainter &painter, int x, int y, int size);       // Dessiner une table
    void drawChair(QPainter &painter, int x, int y);                // Dessiner une chaise
    void drawChairsForTable(QPainter &painter, int x, int y, int size); // Dessiner les chaises autour d'une table
    void drawTileFloor(QPainter &painter);                          // Dessiner le sol en carreaux
    void drawFridge(QPainter &painter, int x, int y);               // Dessiner le frigo
    void drawCooktop(QPainter &painter, int x, int y);              // Dessiner les plaques de cuisson
    void drawDish(QPainter &painter);                               // Dessiner un plat au centre
    void drawMicrowave(QPainter &painter, int x, int y);            // Dessiner le micro-ondes
};

#endif // RESTAURANTWIDGET_H
