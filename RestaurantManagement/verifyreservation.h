#ifndef VERIFYRESERVATION_H
#define VERIFYRESERVATION_H

#include <QWidget>
#include <QRegularExpressionValidator>  // Remplacer QRegExpValidator par QRegularExpressionValidator

namespace Ui {
class VerifyReservation;
}

class VerifyReservation : public QWidget
{
    Q_OBJECT

public:
    explicit VerifyReservation(QWidget *parent = nullptr);
    ~VerifyReservation();

private slots:
    void onBackButtonClicked();
    void onSelectionChanged(const QString &text);  // Slot pour gérer le changement dans la liste déroulante
    void onValidateClicked();   // Slot pour le bouton "Valider"

private:
    Ui::VerifyReservation *ui;
    QRegularExpressionValidator *idValidator;  // Validator pour l'Id (chiffres seulement)
};

#endif // VERIFYRESERVATION_H
