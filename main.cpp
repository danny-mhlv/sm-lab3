#include "mainwindow.h"

#include <QApplication>

#include <iostream> // for debug
#include <vector>
#include <time.h>

#include "rvg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    RandomValue x;
    x.linkWindowSignals(&w);
    w.linkRVGSignals(&x);

    w.show();
    return a.exec();
}
