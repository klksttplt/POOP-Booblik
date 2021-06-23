#include <QtWidgets>
#include "contactbook.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ContactBook addressBook;
    addressBook.show();

    return app.exec();
}
