#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Yuumi's Cypher");
    w.setWindowIcon(QIcon(":Yuumi.ico"));
    w.show();
    return a.exec();
}
