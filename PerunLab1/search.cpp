#include "search.h"
#include <QtWidgets>



Search::Search(QWidget *parent)
        : QDialog(parent)
{
    QLabel *findNameLabel = new QLabel(tr("Enter the name:"));
    nameInputField = new QLineEdit;

    findByNameButton = new QPushButton(tr("&Find by name"));
    findByNameText = "";

    QLabel *findNumerLabel = new QLabel(tr("Enter the number:"));
    findByNumberButton =  new QPushButton(tr("&Find by number"));
    numberInputField = new QLineEdit;
    findByNumberText = "";

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(findNameLabel, 0, 0);
    layout->addWidget(nameInputField, 0, 1);
    layout->addWidget(findByNameButton, 0, 2);

    layout->addWidget(findNumerLabel, 1, 0);
    layout->addWidget(numberInputField, 1,1);
    layout->addWidget(findByNumberButton, 1, 2);


    setLayout(layout);
    setWindowTitle(tr("Find Contact"));
    connect(findByNameButton, &QPushButton::clicked,
            this, &Search::findByNameClicked);
    connect(findByNameButton, &QPushButton::clicked,
            this, &Search::accept);

    connect(findByNumberButton, &QPushButton::clicked,
            this, &Search::findByNumberClicked);
    connect(findByNumberButton, &QPushButton::clicked,
            this, &Search::accept);
}

void Search::findByNameClicked()
{
    QString text = nameInputField->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Enter the name"));
        return;
    } else {
        findByNameText = text;
        nameInputField->clear();
        hide();
    }
}
void Search::setFindByNameTextEmpty(){
    findByNameText = "";
}

void Search::setFindByNumberTextEmpty(){
    findByNumberText = "";
}

void Search::findByNumberClicked()
{
    QString text = numberInputField->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Enter the number"));
        return;
    } else {
        findByNumberText = text;
        numberInputField->clear();
        hide();
    }
}


QString Search::getFindByNameText()
{
    return findByNameText;
}

QString Search::getFindByNumberText()
{
    return findByNumberText;
}
