#include <QApplication>
#include "searchServer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    searchServer mainWindow;

    

    mainWindow.show();

    return app.exec();
}
