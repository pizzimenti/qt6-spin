#include <QApplication>
#include "cubeview.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CubeView w;
    w.show();

    return a.exec();
}
