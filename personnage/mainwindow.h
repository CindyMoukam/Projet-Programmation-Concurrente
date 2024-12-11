#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include "restaurantwidget.h"  // Inclure le widget personnalisé pour la maquette du restaurant
=======
>>>>>>> 5fdc774 (Modélisation personnage)

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;               // Pointeur vers l'interface utilisateur générée par Qt Designer
    RestaurantWidget *restaurantWidget; // Pointeur vers le widget personnalisé qui dessine la maquette du restaurant
=======
    MainWindow(QWidget *parent = nullptr); // Déclaration du constructeur
    ~MainWindow();

private:
    Ui::MainWindow *ui;
>>>>>>> 5fdc774 (Modélisation personnage)
};

#endif // MAINWINDOW_H
