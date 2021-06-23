#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <QWidget>
#include <QMap>
#include "search.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE


class ContactBook : public QWidget
{
    Q_OBJECT

public:
    ContactBook(QWidget *parent = nullptr);
    enum Mode { NavigationMode, AddingMode, EditingMode, AddingNumberMode };

    void writeNumber(QString contactName);
    bool checkContact(QString number);

public slots:
            void addContact();
    void editContact();
    void addNumberContact();
    void submitContact();
    void cancel();
    void removeContact();
    void findContact();
    void next();
    void previous();


private:
    void updateBook(Mode mode);

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *addNumberButton;


    QLineEdit *nameLine;
    QTextEdit *phoneNumberLine;

    QMultiMap<QString, QString> contacts;

    Search *serch;
    QString oldName;
    QString oldPhoneNumber;
    Mode currentMode;
};

#endif
