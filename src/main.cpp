#include <QApplication>
#include <QMessageBox>
#include "include/MainWindow.h"
#include "include/ContactManager.h"
#include "include/Logger.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize logger
    Logger *logger = new Logger("ContactManagmentSystem/resources/log.txt");
    logger->logINFO("Application started");

    // Create ContactManager
    std::unique_ptr<ContactManager> manager = std::make_unique<ContactManager>();
    try {
        manager->getAllContacts();
        logger->logINFO("Contacts loaded successfully");
    } catch (const std::exception& e) {
        logger->logERROR("Failed to load contacts: " + std::string(e.what()));
        QMessageBox::warning(nullptr, "Error", "Failed to load contacts. Starting with empty list.");
    }

    // Create and show MainWindow
    MainWindow window(std::move(manager));
    window.show();

    // Start event loop
    int result = app.exec();
    logger->logINFO("Application closed");
    delete logger; // Clean up logger
    return result;
}