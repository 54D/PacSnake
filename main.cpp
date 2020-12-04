// SNADBOX / PLAYGROUND / WHATEVER YOU LIKE TO CALL, JUST USE TO TEST STUFF
#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include "main_container.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    main_container main_menu;
    main_menu.show();
    return a.exec();

    int response = QFontDatabase::addApplicationFont(":/assets/font/8-BIT-WONDER.TTF");
    if(response==-1){
        qDebug() << "main | Could not load one or more fonts!";
    }
}
