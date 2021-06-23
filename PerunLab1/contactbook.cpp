#include <QtWidgets>
#include "contactbook.h"

ContactBook::ContactBook(QWidget *parent)
        : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *phoneLabel = new QLabel(tr("Phone number:"));
    phoneNumberLine = new QTextEdit;
    phoneNumberLine->setReadOnly(true);

    addButton = new QPushButton(tr("&Add"));
    addNumberButton = new QPushButton(tr("&Add Number"));
    addNumberButton->setEnabled(false);
    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();

    nextButton = new QPushButton(tr("&->"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&<-"));
    previousButton->setEnabled(false);


    serch = new Search(this);

    connect(addButton, &QPushButton::clicked,
            this, &ContactBook::addContact);
    connect(addNumberButton, &QPushButton::clicked,
            this, &ContactBook::addNumberContact);
    connect(submitButton, &QPushButton::clicked,
            this, &ContactBook::submitContact);
    connect(editButton, &QPushButton::clicked,
            this, &ContactBook::editContact);
    connect(removeButton, &QPushButton::clicked,
            this, &ContactBook::removeContact);
    connect(cancelButton, &QPushButton::clicked,
            this, &ContactBook::cancel);
    connect(findButton, &QPushButton::clicked,
            this, &ContactBook::findContact);
    connect(nextButton, &QPushButton::clicked,
            this, &ContactBook::next);
    connect(previousButton, &QPushButton::clicked,
            this, &ContactBook::previous);

    QHBoxLayout *panelLayout = new QHBoxLayout;
    panelLayout->addWidget(addButton);
    panelLayout->addWidget(addNumberButton);
    panelLayout->addWidget(editButton);
    panelLayout->addWidget(removeButton);
    panelLayout->addWidget(findButton);
    panelLayout->addWidget(submitButton);
    panelLayout->addWidget(cancelButton);
    panelLayout->addStretch();

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(previousButton);
    controlsLayout->addWidget(nextButton);

    QGridLayout *viewLayout = new QGridLayout;
    viewLayout->addLayout(controlsLayout, 0, 1);
    viewLayout->addWidget(nameLabel, 2, 0);
    viewLayout->addWidget(nameLine, 2, 1);
    viewLayout->addWidget(phoneLabel, 3, 0, Qt::AlignTop);
    viewLayout->addWidget(phoneNumberLine, 3, 1);
    viewLayout->addLayout(panelLayout, 1, 1);


    setLayout(viewLayout);
    setWindowTitle(tr("Telephone Book"));
}

void ContactBook::addContact()
{
    oldName = nameLine->text();
    oldPhoneNumber = phoneNumberLine->toPlainText();
    nameLine->clear();
    phoneNumberLine->clear();

    updateBook(AddingMode);
}

void ContactBook::submitContact()
{
    QString name = nameLine->text();
    QString phoneNumber = phoneNumberLine->toPlainText();

    if (name.isEmpty() || phoneNumber.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Enter a name and phone number"));
        return;
    }

    if (currentMode == AddingMode) {
        if (!contacts.contains(name)) {

            if (checkContact(phoneNumber) != 1){
                contacts.insert(name, phoneNumber);
                QMessageBox::information(this, tr("Success"),
                                         tr("Added \"%1\" ").arg(name));
            }

        } else {
            QMessageBox::information(this, tr("Error"),
                                     tr("\"%1\" already exists").arg(name));
        }


    } else if (currentMode == EditingMode) {
        if (oldName != name) {
            if (!contacts.contains(name)) {
                QMessageBox::information(this, tr("Success"),
                                         tr("\"%1\" edited").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name, phoneNumber);
            } else {
                QMessageBox::information(this, tr("Error"),
                                         tr("\"%1\" already exists").arg(name));
            }
        }
    }
    updateBook(NavigationMode);
}


void ContactBook::writeNumber(QString contactName)
{
    QString numbers = "";
    QList<QString> values = contacts.values(contactName);
    for (int i = 0; i < values.size(); i++){
        numbers.append(values.at(i)).append("\n");
    }
    phoneNumberLine->clear();
    phoneNumberLine->setPlainText(numbers);
}

void ContactBook::addNumberContact()
{
    oldName = nameLine->text();
    oldPhoneNumber = phoneNumberLine->toPlainText();
    QString text = QInputDialog::getText(this,tr("Adding new number"),tr("New number: "));
    if (!text.isEmpty()){

        if (checkContact(text) != 1){
            contacts.insert(oldName, text);
        }

        writeNumber(oldName);
    } else {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Enter the phone number"));
        return;
    }

    updateBook(AddingNumberMode);
}


void ContactBook::editContact()
{
    oldName = nameLine->text();
    oldPhoneNumber = phoneNumberLine->toPlainText();

    updateBook(EditingMode);
}

bool ContactBook::checkContact(QString number){
    foreach (QString key, contacts.keys())
    {
        QList<QString> values = contacts.values(key);

        foreach (QString value, values)
        {
            if (QString::compare(value, number, Qt::CaseInsensitive) == 0){
                QMessageBox::information(this, tr("Can't add this number"),
                                         tr("Such number already exists"));
                return true;
            }

        }
    }
    return false;
}


void ContactBook::cancel()
{
    nameLine->setText(oldName);
    phoneNumberLine->setText(oldPhoneNumber);
    updateBook(NavigationMode);
}

void ContactBook::removeContact()
{
    QString name = nameLine->text();


    if (contacts.contains(name)) {

        int button = QMessageBox::question(this,
                                           tr("Confirm Remove"),
                                           tr("Are you sure you want to remove \"%1\"?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {
            previous();
            contacts.remove(name);
            QMessageBox::information(this, tr("Success"),
                                     tr("\"%1\" removed").arg(name));
        }
    }

    updateBook(NavigationMode);
}

void ContactBook::next()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i != contacts.end()){
        if (contacts.count(name) > 1){
            i+=contacts.count(name);
        } else {
            i++;
        }
    }

    if (i == contacts.end()){
        i = contacts.begin();
    }

    nameLine->setText(i.key());
    writeNumber(i.key());

}

void ContactBook::previous()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i == contacts.end()) {
        nameLine->clear();
        phoneNumberLine->clear();
        return;
    }

    if (i == contacts.begin()){
        i = contacts.end();
    }
    i--;

    nameLine->setText(i.key());
    writeNumber(i.key());

}

void ContactBook::findContact()
{
    serch->show();

    if (serch->exec() == 1) {

        if (serch->getFindByNameText().length() != 0){
            QString contactName = serch->getFindByNameText();
            if (contacts.contains(contactName)) {
                nameLine->setText(contactName);
                phoneNumberLine->setText(contacts.value(contactName));
                serch->setFindByNameTextEmpty();
            } else {
                QMessageBox::information(this, tr("Contact Not Found"),
                                         tr("\"%1\" does not exist").arg(contactName));
                serch->setFindByNameTextEmpty();
                return;
            }
        }

        if (serch->getFindByNumberText().length() != 0) {
            QString contactNumber = serch->getFindByNumberText();

            bool foundAnswer = 0;
            foreach (QString key, contacts.keys())
            {
                QList<QString> values = contacts.values(key);

                foreach (QString value, values)
                {
                    if (QString::compare(value, contactNumber, Qt::CaseInsensitive) == 0){
                        nameLine->setText(key);
                        writeNumber(key);
                        foundAnswer = 1;
                        break;
                    }
                    if (foundAnswer){
                        break;
                    }
                }

            }

            if (foundAnswer == 0){
                QMessageBox::information(this, tr("Contact Not Found"),
                                         tr("\"%1\" does not exist").arg(contactNumber));
                serch->setFindByNumberTextEmpty();
                return;
            }

            serch->setFindByNumberTextEmpty();
        }

    }

    updateBook(NavigationMode);
}


void ContactBook::updateBook(Mode mode)
{
    currentMode = mode;

    switch (currentMode) {

        case AddingMode:
            nameLine->setReadOnly(false);
            nameLine->setFocus(Qt::OtherFocusReason);
            phoneNumberLine->setReadOnly(false);
            addButton->setEnabled(false);
            editButton->setEnabled(false);
            removeButton->setEnabled(false);
            addNumberButton->setEnabled(false);
            nextButton->setEnabled(false);
            previousButton->setEnabled(false);
            findButton->setEnabled(false);
            submitButton->show();
            cancelButton->show();


            break;

        case EditingMode:

            nameLine->setReadOnly(false);
            nameLine->setFocus(Qt::OtherFocusReason);
            phoneNumberLine->setReadOnly(true);
            addButton->setEnabled(true);
            editButton->setEnabled(true);
            removeButton->setEnabled(true);
            findButton->setEnabled(false);
            nextButton->setEnabled(false);
            previousButton->setEnabled(false);
            submitButton->show();
            cancelButton->hide();


            break;

        case AddingNumberMode:
            nameLine->setReadOnly(true);
            nameLine->setFocus(Qt::OtherFocusReason);
            phoneNumberLine->setReadOnly(true);
            addButton->setEnabled(true);
            editButton->setEnabled(true);
            removeButton->setEnabled(true);
            findButton->setEnabled(true);
            submitButton->hide();
            cancelButton->show();


            break;

        case NavigationMode:

            if (contacts.isEmpty()) {
                nameLine->clear();
                phoneNumberLine->clear();
            }

            nameLine->setReadOnly(true);
            phoneNumberLine->setReadOnly(true);
            addButton->setEnabled(true);

            int number = contacts.uniqueKeys().size();
            editButton->setEnabled(number >= 1);
            addNumberButton->setEnabled(number >= 1);
            removeButton->setEnabled(number >= 1);
            findButton->setEnabled(number > 1);
            nextButton->setEnabled(number > 1);
            previousButton->setEnabled(number > 1);

            submitButton->hide();
            cancelButton->hide();

            break;


    }
}
