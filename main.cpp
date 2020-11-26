#include "widget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget main_menu;
    main_menu.show();
    return a.exec();
}
