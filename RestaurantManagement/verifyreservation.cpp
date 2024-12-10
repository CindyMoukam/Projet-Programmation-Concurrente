#include "verifyreservation.h"
#include "ui_verifyreservation.h"
#include "reservationwindow.h"
#include "menu.h"
#include <QRegularExpressionValidator>
#include <QPixmap>
#include <QDir>

// Dans le constructeur de VerifyReservation
//QPixmap pixmap(QDir::currentPath() + "/static/search_icon.png");

//QPixmap pixmap(":/static/search_icon.png");



VerifyReservation::VerifyReservation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerifyReservation)
{
    ui->setupUi(this);

    // Centrer le texte
    ui->iconLabel->setAlignment(Qt::AlignCenter);

    // Centrer le texte
    ui->label->setAlignment(Qt::AlignCenter);

    ui->iconLabel->setAlignment(Qt::AlignCenter);
    ui->iconLabel->setScaledContents(true); // Redimensionne pour remplir l’espace

    // Modifier la police du texte
    QFont font;
    font.setPointSize(12); // Taille de police
    font.setBold(false);    // Police en gras
    ui->label->setFont(font);

    // Définir une hauteur fixe pour le bouton et d'autres composants (optionnel si nécessaire)
    ui->comboBox->setFixedHeight(30);
    ui->lineEdit->setFixedHeight(25);
    ui->validateButton->setFixedHeight(35);

    // Créer un validateur pour l'Id (chiffres uniquement)
    QRegularExpression regex("^[0-9]+$"); // Accepte uniquement des chiffres
    idValidator = new QRegularExpressionValidator(regex, this);

    // Configurer le bouton de retour
    connect(ui->backButton, &QPushButton::clicked, this, &VerifyReservation::onBackButtonClicked);

    // Connecter la sélection de la liste déroulante au slot
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &VerifyReservation::onSelectionChanged);

    // Connecter le bouton "Valider" au slot
    connect(ui->validateButton, &QPushButton::clicked, this, &VerifyReservation::onValidateClicked);

    // Initialiser avec aucun validateur
    ui->lineEdit->setValidator(nullptr);
    ui->errorLabel->clear();  // Effacer les erreurs initiales
}

VerifyReservation::~VerifyReservation()
{
    delete ui;
}

void VerifyReservation::onBackButtonClicked()
{
    this->close(); // Ferme le widget actuel
    // Créer et afficher le widget VerifyReservation
    ReservationWindow *reservationwindow = new ReservationWindow();
    reservationwindow->show();
}

void VerifyReservation::onSelectionChanged(const QString &text)
{
    if (text == "Id") {
        ui->lineEdit->setValidator(idValidator); // Appliquer le validateur pour les Id
        //ui->errorLabel->clear();
    } else {
        ui->lineEdit->setValidator(nullptr);    // Aucun validateur pour les noms
        //ui->errorLabel->clear();
    }
    ui->errorLabel->clear(); // Effacer toute erreur lors du changement de sélection
}

void VerifyReservation::onValidateClicked()
{
    QString currentSelection = ui->comboBox->currentText();
    QString inputText = ui->lineEdit->text();

    if (currentSelection == "Id") {
        // Vérifier si le texte est vide ou contient des caractères invalides
        if (inputText.isEmpty()) {
            ui->errorLabel->setText("Le champ ID ne peut pas être vide.");
            ui->errorLabel->setStyleSheet("color: red;");
        } else if (!ui->lineEdit->hasAcceptableInput()) {
            ui->errorLabel->setText("L'ID doit être constitué uniquement de chiffres.");
            ui->errorLabel->setStyleSheet("color: red;");
        } else {
            ui->errorLabel->clear(); // Valide si tout est correct
            // Action pour valider la réservation
            this->close();  // Par exemple, fermer la fenêtre
            // Créer et afficher le widget
            MenuPage *menuWindow = new MenuPage();
            menuWindow->show();
        }
    } else if (currentSelection == "Nom") {
        // Vérifier si le champ est vide
        if (inputText.isEmpty()) {
            ui->errorLabel->setText("Le nom ne peut pas être vide.");
            ui->errorLabel->setStyleSheet("color: red;");
        } else {
            ui->errorLabel->clear(); // Valide si tout est correct
            // Action pour valider la réservation
            this->close();  // Par exemple, fermer la fenêtre
            // Créer et afficher le widget
            MenuPage *menuWindow = new MenuPage();
            menuWindow->show();
        }
    }
}

