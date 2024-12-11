#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Ajout de quelques menus pour tester
    addMenu(menu("Burger", ":/static/burger.jpeg", 15));
    addMenu(menu("Fries", ":/static/frites.jpeg", 5));
    addMenu(menu("Ice Cream", ":/static/burger.jpeg", 7));
    addMenu(menu("Burger", ":/static/burger.jpeg", 15));
    addMenu(menu("Fries", ":/static/frites.jpeg", 5));
    addMenu(menu("Ice Cream", ":/static/burger.jpeg", 7));
    addMenu(menu("Burger", ":/static/burger.jpeg", 15));
    addMenu(menu("Fries", ":/static/frites.jpeg", 5));
    addMenu(menu("Ice Cream", ":/static/burger.jpeg", 7));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addMenu(const menu& menu) {
    menuList.append(menu);
    populateMenuList();
}

void MainWindow::populateMenuList() {
    // Nettoyer la mise en page existante
    QLayout* layout = ui->menuListLayout->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }

    // Ajouter chaque menu
    for (int i = 0; i < menuList.size(); ++i) {
        const menu& menu = menuList[i];

        // Widget pour un produit
        QWidget* menuItem = new QWidget(this);
        QHBoxLayout* menuLayout = new QHBoxLayout(menuItem);

        QLabel* photoLabel = new QLabel(menuItem);
        photoLabel->setPixmap(menu.getPhoto().scaled(100, 100, Qt::KeepAspectRatio));

        QLabel* nameLabel = new QLabel(menu.getName(), menuItem);
        QLabel* prepTimeLabel = new QLabel(QString("%1 min").arg(menu.getPrepTime()), menuItem);

        menuLayout->addWidget(photoLabel);
        menuLayout->addWidget(nameLabel);
        menuLayout->addWidget(prepTimeLabel);

        ui->menuListLayout->addWidget(menuItem);

        // Ajouter une ligne de séparation sauf pour le dernier produit
        if (i != menuList.size() - 1) {
            QFrame* line = new QFrame(this);
            line->setFrameShape(QFrame::HLine);  // Ligne horizontale
            line->setFrameShadow(QFrame::Sunken);  // Ombre pour donner un effet 3D
            ui->menuListLayout->addWidget(line);
        }
    }
}
