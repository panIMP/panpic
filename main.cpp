#include <QApplication>
#include "uiMainWin.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    UiMainWindow* mainWin = new UiMainWindow();
    mainWin->show();
    return app.exec();
}
