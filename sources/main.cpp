#include <QApplication>
#include "fenetre.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MemoireService mem;
    AttentionService att;

    Fenetre f(&mem, &att);



    return app.exec();
}
