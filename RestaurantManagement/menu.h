#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QPixmap>

class menu {
public:
    menu(const QString& name, const QString& photoPath, int prepTime);

    QString getName() const;
    QPixmap getPhoto() const;
    int getPrepTime() const;

private:
    QString name;
    QString photoPath;
    int prepTime;
};

#endif // MENU_H
