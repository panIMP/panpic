#include <QApplication>
#include "uimainwindow.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    UiMainWindow mainWin;
    mainWin.show();
    return app.exec();
}
