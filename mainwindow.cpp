#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentmanager.h"
#include <QMessageBox>
#include <QFileDialog>

StudentManager manager;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteStudent);
    connect(ui->findButton, &QPushButton::clicked, this, &MainWindow::findStudent);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortStudents);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveToFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addStudent() {
    // Show dialog to input student details
    // Use manager.addStudent() to add the student
}

void MainWindow::deleteStudent() {
    // Show dialog to input student ID
    // Use manager.deleteStudentById() to delete the student
}

void MainWindow::findStudent() {
    // Show dialog to input search criteria (ID, name, etc.)
    // Use manager.findStudentById() or manager.findStudentsByName()
}

void MainWindow::sortStudents() {
    manager.sortStudents();
    QMessageBox::information(this, "Success", "Students sorted successfully.");
}

void MainWindow::loadFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        manager.loadFromFile(filename);
        QMessageBox::information(this, "Success", "Data Loaded Successfully!");
    }
}

void MainWindow::saveToFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        manager.saveToFile(filename);
        QMessageBox::information(this, "Success", "Data Saved Successfully!");
    }
}