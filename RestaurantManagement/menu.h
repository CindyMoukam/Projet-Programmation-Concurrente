#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class MenuPage;  // Déclaration anticipée, définie par l'outil de Qt
}

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPage(QWidget *parent = nullptr);
    ~MenuPage();

private slots:
    void onDishButtonClicked();
    void onDrinkButtonClicked();

private:
    Ui::MenuPage *ui;  // Pointeur vers l'interface générée par Qt Designer
};

#endif // MENU_H
