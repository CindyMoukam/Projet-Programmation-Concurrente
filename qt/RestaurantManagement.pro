QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/actors/chefdecuisine.cpp \
    ../src/actors/chefdepartie.cpp \
    ../src/actors/commiscuisine.cpp \
    ../src/actors/plongeur.cpp \
    ../src/database/databasemanager.cpp \
    ../src/materials/equipment.cpp \
    ../src/materials/materials.cpp \
    ../src/recipes/recipe.cpp \
    ../src/recipes/recipemanager.cpp \
    ../src/tasks/task.cpp \
    ../src/tasks/taskmanager.cpp \
    ../src/utils/logger.cpp \
    ../src/utils/timer.cpp \
    ../src/main.cpp \
    ../qt/ui/mainwindow.cpp \

HEADERS += \
    ../src/actors/ActorBase.h \
    ../src/actors/chefdecuisine.h \
    ../src/actors/chefdepartie.h \
    ../src/actors/commiscuisine.h \
    ../src/actors/plongeur.h \
    ../src/database/databasemanager.h \
    ../src/materials/MaterialStockManager.h \
    ../src/materials/equipment.h \
    ../src/materials/materials.h \
    ../src/recipes/recipe.h \
    ../src/recipes/recipemanager.h \
    ../src/tasks/Scheduler.h \
    ../src/tasks/task.h \
    ../src/tasks/taskmanager.h \
    ../src/utils/Constants.h \
    ../src/utils/logger.h \
    ../src/utils/timer.h \
    ../qt/ui/mainwindow.h \

FORMS += \
    ../qt/ui/mainwindow.ui \

TRANSLATIONS += \
    ../RestaurantManagement_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../README.md \
    ../src/database/restaurantmanagement \
    ../src/utils/Config.json
