#include "game.h"
#include <QApplication>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    Game game;
    game.show();
    //game.run();
    return app.exec();
}