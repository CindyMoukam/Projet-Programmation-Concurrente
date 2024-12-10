#ifndef PLAT_H
#define PLAT_H

#include <QWidget>
#include <QVariantMap>

namespace Ui {
class plat;
}

class plat : public QWidget
{
    Q_OBJECT

public:
    explicit plat(QWidget *parent = nullptr);
    ~plat();

private slots:
    void onCardClicked(const QVariantMap &platData);

private:
    Ui::plat *ui;
};

#endif // PLAT_H
