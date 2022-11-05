#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Yuumi's Cypher");
    w.setWindowIcon(QIcon(":yuumi.ico"));
    w.show();
    return a.exec();
}
