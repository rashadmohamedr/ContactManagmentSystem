#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include "include/Contact.h"
#include "include/Logger.h"

class ContactDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* nameInput;
    QLineEdit* phoneInput;
    QLineEdit* emailInput;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QFormLayout* formLayout;
    Logger* logger;

    // Setup UI components
    void setupUI();
    // Validate inputs
    bool validateInputs();

private slots:
    void onSaveClicked();

public:
    // Constructor for adding (no contact) or editing (with contact)
    ContactDialog(QWidget* parent = nullptr, Contact* contact = nullptr);
    // Return entered data
    std::tuple<QString, QString, QString> getContactData() const;
};

#endif // CONTACTDIALOG_H