#include "taketable.h"
#include "ui_taketable.h"
#include "reservationwindow.h"
#include "menu.h"

taketable::taketable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taketable)
{
    ui->setupUi(this);

    // Configurer le bouton de retour
    connect(ui->backButton, &QPushButton::clicked, this, &taketable::onBackButtonClicked);

    // Alignement et configuration des autres widgets (comme déjà existant)
    ui->iconLabel->setAlignment(Qt::AlignCenter);
    ui->iconLabel->setScaledContents(true);

    connect(ui->responsableLineEdit, &QLineEdit::textChanged, this, &taketable::onTextChanged);
    connect(ui->validateButton, &QPushButton::clicked, this, &taketable::onValidateClicked);

    QFont font;
    font.setPointSize(12);
    font.setBold(false);
    ui->label->setFont(font);

    ui->responsableLineEdit->setFixedHeight(30);
    ui->personSpinBox->setFixedHeight(30);
    ui->validateButton->setFixedHeight(35);

    ui->responsableLineEdit->setValidator(nullptr);
    ui->errorLabel->clear(); // Effacer les erreurs initiales
}


taketable::~taketable()
{
    delete ui;
}

void taketable::onBackButtonClicked()
{
    this->close(); // Ferme le widget actuel
    // Créer et afficher le widget VerifyReservation
    ReservationWindow *reservationwindow = new ReservationWindow();
    reservationwindow->show();
}

void taketable::onTextChanged(const QString &text)
{
    Q_UNUSED(text);
    ui->errorLabel->clear(); // Effacer les erreurs en cas de modification
}

void taketable::onValidateClicked()
{
    QString inputText = ui->responsableLineEdit->text();

    // Vérifier si le champ est vide
    if (inputText.isEmpty()) {
        ui->errorLabel->setText("Le nom ne peut pas être vide.");
        ui->errorLabel->setStyleSheet("color: red;");
    } else {
        ui->errorLabel->clear(); // Valide si tout est correct
        this->close();  // Par exemple, fermer la fenêtre
        // Créer et afficher le widget
        MenuPage *menuWindow = new MenuPage();
        menuWindow->show();
    }
}
