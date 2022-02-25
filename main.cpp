#include <QApplication>
#include <QStyleFactory>
#include "GeniusWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle("fusion");
    // palette set, time to initialize the window
    GeniusWindow window = GeniusWindow();
    window.show();
    return QApplication::exec();
}