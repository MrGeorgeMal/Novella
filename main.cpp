#include "mainwindow.h"
#include "novellagame.h"

#include <QApplication>
#include <QMainWindow>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    novellagame.InitializeGame(&w);
    novellagame.OpenMainMenu();

    w.show();

    return a.exec();
}
