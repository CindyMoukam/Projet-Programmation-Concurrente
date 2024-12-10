#ifndef TAKETABLE_H
#define TAKETABLE_H

#include <QWidget>
#include <QString>

namespace Ui {
class taketable;
}

class taketable : public QWidget
{
    Q_OBJECT

public:
    explicit taketable(QWidget *parent = nullptr);
    ~taketable();

private slots:
    void onBackButtonClicked();
    void onTextChanged(const QString &text); // Nouveau slot ajouté
    void onValidateClicked();

private:
    Ui::taketable *ui;
};

#endif // TAKETABLE_H
