#include <QApplication>
#include "GeniusWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle("fusion");
    GeniusWindow window = GeniusWindow();
    window.show();
    return QApplication::exec();
}