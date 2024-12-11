#include "mainwindow.h"
<<<<<<< HEAD

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
=======
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);    // Crée une application Qt
    MainWindow w;                   // Crée une instance de votre fenêtre principale
    w.show();                       // Affiche la fenêtre principale
    return a.exec();                // Exécute l'application
>>>>>>> 5fdc774 (Modélisation personnage)
}
