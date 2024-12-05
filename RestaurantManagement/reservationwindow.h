#ifndef RESERVATIONWINDOW_H
#define RESERVATIONWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ReservationWindow;
}

class ReservationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationWindow(QWidget *parent = nullptr);
    ~ReservationWindow();

    // Déclaration de la méthode manquante
    void addReservation(const QString& clientName, const QString& date, int tableId);

private slots:
    void onYesClicked();
    void onNoClicked();

private:
    Ui::ReservationWindow *ui;
};

#endif // RESERVATIONWINDOW_H
