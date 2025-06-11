#include "include/ContactDialog.h"

ContactDialog::ContactDialog(QWidget* parent, Contact* contact,Logger* logger)
    : QDialog(parent), logger(logger) {
    setWindowTitle(contact ? "Edit Contact" : "Add Contact");
    logger->logINFO(contact ? "Edit Contact dialog opened" : "Add Contact dialog opened");
    setupUI();

    if (contact) {
        nameInput->setText(QString::fromStdString(contact->getName()));
        phoneInput->setText(QString::fromStdString(contact->getPhone()));
        emailInput->setText(QString::fromStdString(contact->getEmail()));
        // ID is not editable in UI
    }
}

void ContactDialog::setupUI() {
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter name");
    phoneInput = new QLineEdit(this);
    phoneInput->setPlaceholderText("Enter phone number");
    emailInput = new QLineEdit(this);
    emailInput->setPlaceholderText("Enter email");

    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    formLayout = new QFormLayout();
    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Phone:", phoneInput);
    formLayout->addRow("Email:", emailInput);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &ContactDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ContactDialog::reject);
}

bool ContactDialog::validateInputs() {
    if (nameInput->text().isEmpty()) {
        logger->logERROR("Validation failed: Name is empty");
        QMessageBox::warning(this, "Error", "Name cannot be empty.");
        return false;
    }
    if (!emailInput->text().contains("@") || !emailInput->text().contains(".")) {
        logger->logERROR("Validation failed: Invalid email format");
        QMessageBox::warning(this, "Error", "Please enter a valid email address.");
        return false;
    }
    QString phone = phoneInput->text();
    if (phone.isEmpty() || !phone.contains(QRegularExpression("^[0-9-+]+$"))) {
        logger->logERROR("Validation failed: Invalid phone format");
        QMessageBox::warning(this, "Error", "Please enter a valid phone number.");
        return false;
    }
    return true;
}

void ContactDialog::onSaveClicked() {
    if (validateInputs()) {
        logger->logINFO("Contact dialog saved: " + nameInput->text().toStdString());
        accept();
    }
}

std::tuple<QString, QString, QString> ContactDialog::getContactData() const {
    return {nameInput->text(), phoneInput->text(), emailInput->text()};
}