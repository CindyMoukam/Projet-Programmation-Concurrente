#include "plat.h"
#include "ui_plat.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

plat::plat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plat)
{
    ui->setupUi(this);

    // Exemple de données pour les plats
    QList<QVariantMap> plats = {
        {{"nom", "Pizza"}, {"description", "Fromage, Tomate, Basilic"}, {"temps", "Prêt dans 20 mins"}, {"image", ":/resources/search_icon.png"}},
        {{"nom", "Burger"}, {"description", "Viande, Fromage, Salade"}, {"temps", "Prêt dans 20 mins"}, {"image", ":/resources/search_icon.png"}},
        {{"nom", "Sushi"}, {"description", "Poisson, Riz, Algues"}, {"temps", "Prêt dans 20 mins"}, {"image", ":/resources/search_icon.png"}},
        {{"nom", "Pizza"}, {"description", "Fromage, Tomate, Basilic"}, {"temps", "Prêt dans 20 mins"}, {"image", ":/resources/search_icon.png"}},
        {{"nom", "Burger"}, {"description", "Viande, Fromage, Salade"}, {"temps", "Prêt dans 20 mins"}, {"image", ":/resources/search_icon.png"}},
        {{"nom", "Sushi"}, {"description", "Poisson, Riz, Algues"}, {"temps", "Prêt dans 20 mins"}, {"image", ":/resources/search_icon.png"}}
    };

    QGridLayout *layout = ui->scrollAreaWidgetContents->findChild<QGridLayout *>("gridLayout");
    int row = 0, col = 0;

    for (const auto &platData : plats) {
        // Création d'une carte pour chaque plat
        QWidget *card = new QWidget();
        card->setFixedSize(350, 450); // Dimensions ajustées pour occuper plus de place
        card->setStyleSheet(
            "QWidget { "
            "border: 1px solid #ccc; "
            "border-radius: 15px; "
            "background-color: transparent; "
            "} "
            "QWidget:hover { "
            "background-color: #d9d9d9; "
            "}"
            );

        QVBoxLayout *cardLayout = new QVBoxLayout(card);

        // Image du plat dans un conteneur circulaire
        QLabel *imageLabel = new QLabel(card);
        imageLabel->setPixmap(QPixmap(platData["image"].toString()).scaled(120, 120, Qt::KeepAspectRatioByExpanding));
        imageLabel->setFixedSize(120, 120);
        imageLabel->setStyleSheet("border-radius: 60px; border: 2px solid #ccc; background-color: white;");
        imageLabel->setAlignment(Qt::AlignCenter);

        // Nom du plat
        QLabel *nameLabel = new QLabel(platData["nom"].toString(), card);
        nameLabel->setStyleSheet("font-size: 30px; font-weight: bold; text-align: center; margin: 15px 0; border: none");
        nameLabel->setAlignment(Qt::AlignCenter);

        // Description
        QLabel *descriptionLabel = new QLabel(platData["description"].toString(), card);
        descriptionLabel->setStyleSheet("font-size: 18px; color: #666; text-align: center; margin-bottom: 10px; border: none");
        descriptionLabel->setAlignment(Qt::AlignCenter);

        // Temps
        QLabel *timeLabel = new QLabel(platData["temps"].toString(), card);
        timeLabel->setStyleSheet("font-size: 16px; color: #999; text-align: center; border: none");
        timeLabel->setAlignment(Qt::AlignCenter);

        // Bouton pour capturer le clic
        QPushButton *button = new QPushButton(card);
        button->setStyleSheet("background: transparent; border: none;");
        button->setCursor(Qt::PointingHandCursor);
        button->setFixedSize(card->size());
        button->raise();

        connect(button, &QPushButton::clicked, this, [this, platData]() {
            onCardClicked(platData);
        });

        // Ajouter les éléments dans la carte
        cardLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
        cardLayout->addWidget(nameLabel);
        cardLayout->addWidget(descriptionLabel);
        cardLayout->addWidget(timeLabel);

        // Ajouter la carte au layout principal
        layout->addWidget(card, row, col, Qt::AlignCenter);

        // Gestion des colonnes (2 par ligne)
        col++;
        if (col >= 2) {
            col = 0;
            row++;
        }
    }
}

plat::~plat()
{
    delete ui;
}

void plat::onCardClicked(const QVariantMap &platData)
{
    // Exemple d'action lorsqu'une carte est cliquée
    QMessageBox::information(this, "Détails du plat",
                             "Nom : " + platData["nom"].toString() + "\n" +
                                 "Description : " + platData["description"].toString() + "\n" +
                                 "Temps : " + platData["temps"].toString());
}
