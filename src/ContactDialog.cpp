#include "include/ContactDialog.h"

ContactDialog::ContactDialog(QWidget* parent, Contact* contact)
    : QDialog(parent), logger(Logger::getInstance()) {
    // Set dialog title
    setWindowTitle(contact ? "Edit Contact" : "Add Contact");
    // Log dialog creation
    logger->logInfo(contact ? "Edit Contact dialog opened" : "Add Contact dialog opened");
    // Setup UI
    setupUI();

    // Pre-fill fields if editing
    if (contact) {
        nameInput->setText(contact->getName());
        phoneInput->setText(contact->getPhone());
        emailInput->setText(contact->getEmail());
    }
}

void ContactDialog::setupUI() {
    // Create input fields
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter name");
    phoneInput = new QLineEdit(this);
    phoneInput->setPlaceholderText("Enter phone number");
    emailInput = new QLineEdit(this);
    emailInput->setPlaceholderText("Enter email");

    // Create buttons
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    // Create form layout
    formLayout = new QFormLayout();
    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Phone:", phoneInput);
    formLayout->addRow("Email:", emailInput);

    // Create button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(saveButton, &QPushButton::clicked, this, &ContactDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ContactDialog::reject);
}

bool ContactDialog::validateInputs() {
    if (nameInput->text().isEmpty()) {
        logger->logError("Validation failed: Name is empty");
        QMessageBox::warning(this, "Error", "Name cannot be empty.");
        return false;
    }
    if (!emailInput->text().contains("@") || !emailInput->text().contains(".")) {
        logger->logError("Validation failed: Invalid email format");
        QMessageBox::warning(this, "Error", "Please enter a valid email address.");
        return false;
    }
    // Basic phone validation (non-empty, allows digits, -, +)
    QString phone = phoneInput->text();
    if (phone.isEmpty() || !phone.contains(QRegularExpression("^[0-9-+]+$"))) {
        logger->logError("Validation failed: Invalid phone format");
        QMessageBox::warning(this, "Error", "Please enter a valid phone number.");
        return false;
    }
    return true;
}

void ContactDialog::onSaveClicked() {
    if (validateInputs()) {
        logger->logInfo("Contact dialog saved: " + nameInput->text().toStdString());
        accept();
    }
}

std::tuple<QString, QString, QString> ContactDialog::getContactData() const {
    return {nameInput->text(), phoneInput->text(), emailInput->text()};
}