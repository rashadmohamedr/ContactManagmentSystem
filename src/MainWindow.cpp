#include "include/MainWindow.h"

MainWindow::MainWindow(std::unique_ptr<ContactManager> mgr, QWidget* parent)
    : QMainWindow(parent), manager(std::move(mgr)), logger(Logger::getInstance()) {
    // Set window title
    setWindowTitle("Contact Management System");
    // Log UI initialization
    logger->logInfo("MainWindow initialized");
    // Setup UI
    setupUI();
}

MainWindow::~MainWindow() {
    // Widgets are managed by Qt's parent-child hierarchy
    // unique_ptr automatically deletes manager
    logger->logInfo("MainWindow destroyed");
}

void MainWindow::setupUI() {
    // Create central widget and layouts
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);
    buttonLayout = new QHBoxLayout();

    // Create table with 3 columns
    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Name", "Phone", "Email"});
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setStretchLastSection(true);

    // Create buttons and search input
    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Search by name");
    addButton = new QPushButton("Add Contact", this);
    editButton = new QPushButton("Edit Contact", this);
    deleteButton = new QPushButton("Delete Contact", this);
    searchButton = new QPushButton("Search", this);

    // Initially disable edit/delete buttons
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);

    // Add widgets to layouts
    buttonLayout->addWidget(searchInput);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    // Set central widget
    setCentralWidget(centralWidget);

    // Connect signals to slots
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::onEditClicked);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);

    // Populate table initially
    updateTable();
}

void MainWindow::updateTable() {
    // Clear table
    table->clearContents();
    table->setRowCount(0);

    try {
        // Get contacts from manager
        auto contacts = manager->getAllContacts();
        table->setRowCount(contacts.size());

        // Populate table
        for (size_t i = 0; i < contacts.size(); ++i) {
            table->setItem(i, 0, new QTableWidgetItem(contacts[i]->getName()));
            table->setItem(i, 1, new QTableWidgetItem(contacts[i]->getPhone()));
            table->setItem(i, 2, new QTableWidgetItem(contacts[i]->getEmail()));
        }
        table->resizeColumnsToContents();
        logger->logInfo("Table updated with " + std::to_string(contacts.size()) + " contacts");
    } catch (const std::exception& e) {
        logger->logError("Failed to update table: " + std::string(e.what()));
        QMessageBox::warning(this, "Error", "Failed to load contacts.");
    }
}

void MainWindow::onAddClicked() {
    logger->logInfo("Add button clicked");
    ContactDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        try {
            auto [name, phone, email] = dialog.getContactData();
            manager->addContact(name, phone, email);
            updateTable();
            logger->logInfo("Added contact: " + name.toStdString());
        } catch (const std::exception& e) {
            logger->logError("Failed to add contact: " + std::string(e.what()));
            QMessageBox::warning(this, "Error", "Failed to add contact.");
        }
    }
}

void MainWindow::onEditClicked() {
    logger->logInfo("Edit button clicked");
    int row = table->currentRow();
    if (row < 0) {
        logger->logError("No contact selected for edit");
        QMessageBox::warning(this, "Error", "Please select a contact to edit.");
        return;
    }

    try {
        auto contacts = manager->getAllContacts();
        ContactDialog dialog(this, contacts[row].get());
        if (dialog.exec() == QDialog::Accepted) {
            auto [name, phone, email] = dialog.getContactData();
            manager->editContact(row, name, phone, email);
            updateTable();
            logger->logInfo("Edited contact: " + name.toStdString());
        }
    } catch (const std::exception& e) {
        logger->logError("Failed to edit contact: " + std::string(e.what()));
        QMessageBox::warning(this, "Error", "Failed to edit contact.");
    }
}

void MainWindow::onDeleteClicked() {
    logger->logInfo("Delete button clicked");
    int row = table->currentRow();
    if (row < 0) {
        logger->logError("No contact selected for delete");
        QMessageBox::warning(this, "Error", "Please select a contact to delete.");
        return;
    }

    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this contact?") == QMessageBox::Yes) {
        try {
            manager->deleteContact(row);
            updateTable();
            logger->logInfo("Deleted contact at index " + std::to_string(row));
        } catch (const std::exception& e) {
            logger->logError("Failed to delete contact: " + std::string(e.what()));
            QMessageBox::warning(this, "Error", "Failed to delete contact.");
        }
    }
}

void MainWindow::onSearchClicked() {
    logger->logInfo("Search button clicked");
    QString query = searchInput->text();
    try {
        auto contacts = manager->searchContact(query);
        table->clearContents();
        table->setRowCount(contacts.size());
        for (size_t i = 0; i < contacts.size(); ++i) {
            table->setItem(i, 0, new QTableWidgetItem(contacts[i]->getName()));
            table->setItem(i, 1, new QTableWidgetItem(contacts[i]->getPhone()));
            table->setItem(i, 2, new QTableWidgetItem(contacts[i]->getEmail()));
        }
        table->resizeColumnsToContents();
        logger->logInfo("Searched for: " + query.toStdString() + ", found " + std::to_string(contacts.size()) + " contacts");
    } catch (const std::exception& e) {
        logger->logError("Search failed: " + std::string(e.what()));
        QMessageBox::warning(this, "Error", "Search failed.");
    }
}

void MainWindow::onSelectionChanged() {
    bool hasSelection = table->currentRow() >= 0;
    editButton->setEnabled(hasSelection);
    deleteButton->setEnabled(hasSelection);
}