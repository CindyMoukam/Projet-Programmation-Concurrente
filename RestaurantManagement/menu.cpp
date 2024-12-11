#include "menu.h"

menu::menu(const QString& name, const QString& photoPath, int prepTime)
    : name(name), photoPath(photoPath), prepTime(prepTime) {}

QString menu::getName() const {
    return name;
}

QPixmap menu::getPhoto() const {
    return QPixmap(photoPath);
}

int menu::getPrepTime() const {
    return prepTime;
}
