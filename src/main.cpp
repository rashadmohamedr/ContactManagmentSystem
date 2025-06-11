#include <QApplication>
#include <QMessageBox>
#include "include/MainWindow.h"
#include "include/ContactManager.h"
#include "include/Logger.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize logger
    Logger* logger = Logger::getInstance();
    logger->logInfo("Application started");

    // Create ContactManager
    std::unique_ptr<ContactManager> manager = std::make_unique<ContactManager>();
    try {
        manager->loadContacts();
        logger->logInfo("Contacts loaded successfully");
    } catch (const std::exception& e) {
        logger->logError("Failed to load contacts: " + std::string(e.what()));
        QMessageBox::warning(nullptr, "Error", "Failed to load contacts. Starting with empty list.");
    }

    // Create and show MainWindow
    MainWindow window(std::move(manager));
    window.show();

    // Start event loop
    int result = app.exec();
    logger->logInfo("Application closed");
    return result;
}