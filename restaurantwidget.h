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
    void drawTable(QPainter &painter, int x, int y, int size);
    void drawChair(QPainter &painter, int x, int y);
    void drawTileFloor(QPainter &painter);
};

#endif // RESTAURANTWIDGET_H
