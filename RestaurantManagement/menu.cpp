#include "menu.h"
#include "ui_menu.h"
#include "plat.h"
#include <QPushButton>
#include <QDebug>

MenuPage::MenuPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPage)
{
    ui->setupUi(this);

    ui->titleLayout->setAlignment(Qt::AlignHCenter);

    // Définir une hauteur fixe pour le bouton et d'autres composants (optionnel si nécessaire)
    ui->dishButton->setFixedHeight(100);
    ui->drinkButton->setFixedHeight(100);

    // Connecter les boutons à des actions
    connect(ui->dishButton, &QPushButton::clicked, this, &MenuPage::onDishButtonClicked);
    connect(ui->drinkButton, &QPushButton::clicked, this, &MenuPage::onDrinkButtonClicked);
}

MenuPage::~MenuPage()
{
    delete ui;
}

void MenuPage::onDishButtonClicked()
{
    this->close();  // Par exemple, fermer la fenêtre
    // Créer et afficher le widget
    plat *platWindow = new plat();
    platWindow->show();
}

void MenuPage::onDrinkButtonClicked()
{
    // Logique pour naviguer vers la page des boissons
    qDebug() << "Naviguer vers la page des boissons";
}
