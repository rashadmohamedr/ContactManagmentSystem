#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "include/ContactManager.h"
#include "include/ContactDialog.h"
#include "include/Logger.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    // Pointer to ContactManager (using unique_ptr for dynamic memory management)
    std::unique_ptr<ContactManager> manager;
    // UI widgets
    QTableWidget* table;
    QPushButton* addButton;
    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* searchButton;
    QLineEdit* searchInput;
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonLayout;
    // Logger instance (assumed accessible, e.g., singleton)
    Logger* logger;

    // Setup UI components and layouts
    void setupUI();
    // Refresh table with contacts
    void updateTable();

private slots:
    // Handle button clicks
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onSearchClicked();
    // Enable/disable buttons based on selection
    void onSelectionChanged();

public:
    // Constructor takes ContactManager pointer
    MainWindow(std::unique_ptr<ContactManager> mgr, QWidget* parent = nullptr,Logger* logger= nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H