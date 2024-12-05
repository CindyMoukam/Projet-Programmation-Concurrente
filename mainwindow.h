#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "restaurantwidget.h"  // Inclure le widget personnalisé pour la maquette du restaurant

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;               // Pointeur vers l'interface utilisateur générée par Qt Designer
    RestaurantWidget *restaurantWidget; // Pointeur vers le widget personnalisé qui dessine la maquette du restaurant
};

#endif // MAINWINDOW_H
