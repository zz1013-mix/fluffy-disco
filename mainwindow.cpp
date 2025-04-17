#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentmanager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>

StudentManager manager;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化表格
    ui->studentTable->setColumnCount(6);
    QStringList headers = {"学号", "姓名", "数学", "物理", "英语", "总分"};
    ui->studentTable->setHorizontalHeaderLabels(headers);
    ui->studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 连接信号与槽
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

// 更新表格显示
void MainWindow::updateTable() {
    ui->studentTable->setRowCount(manager.students.size());
    for (int i = 0; i < manager.students.size(); ++i) {
        const Student& student = manager.students[i];
        // 学号
        ui->studentTable->setItem(i, 0, new QTableWidgetItem(QString::number(student.getId())));
        // 姓名
        ui->studentTable->setItem(i, 1, new QTableWidgetItem(student.getName()));
        // 数学成绩
        ui->studentTable->setItem(i, 2, new QTableWidgetItem(QString::number(student.getMathScore(), 'f', 1)));
        // 物理成绩
        ui->studentTable->setItem(i, 3, new QTableWidgetItem(QString::number(student.getPhysicsScore(), 'f', 1)));
        // 英语成绩
        ui->studentTable->setItem(i, 4, new QTableWidgetItem(QString::number(student.getEnglishScore(), 'f', 1)));
        // 总分
        ui->studentTable->setItem(i, 5, new QTableWidgetItem(QString::number(student.getTotalScore(), 'f', 1)));
    }
}

// 添加学生对话框
void MainWindow::addStudent() {
    QDialog dialog(this);
    QFormLayout layout(&dialog);

    QLineEdit* idEdit = new QLineEdit();
    QLineEdit* nameEdit = new QLineEdit();
    QDoubleSpinBox* mathSpin = new QDoubleSpinBox();
    QDoubleSpinBox* physicsSpin = new QDoubleSpinBox();
    QDoubleSpinBox* englishSpin = new QDoubleSpinBox();

    mathSpin->setRange(0, 100);
    physicsSpin->setRange(0, 100);
    englishSpin->setRange(0, 100);
    mathSpin->setSingleStep(0.5);
    physicsSpin->setSingleStep(0.5);
    englishSpin->setSingleStep(0.5);

    layout.addRow("学号:", idEdit);
    layout.addRow("姓名:", nameEdit);
    layout.addRow("数学:", mathSpin);
    layout.addRow("物理:", physicsSpin);
    layout.addRow("英语:", englishSpin);

    QPushButton* okBtn = new QPushButton("确定");
    QPushButton* cancelBtn = new QPushButton("取消");
    QHBoxLayout btnLayout;
    btnLayout.addWidget(okBtn);
    btnLayout.addWidget(cancelBtn);
    layout.addLayout(&btnLayout);

    connect(okBtn, &QPushButton::clicked, [&]() {
        bool ok;
        int id = idEdit->text().toInt(&ok);
        if (!ok || id <= 0) {
            QMessageBox::warning(this, "错误", "学号必须为正整数");
            return;
        }
        QString name = nameEdit->text().trimmed();
        if (name.isEmpty()) {
            QMessageBox::warning(this, "错误", "姓名不能为空");
            return;
        }
        double math = mathSpin->value();
        double physics = physicsSpin->value();
        double english = englishSpin->value();

        Student student(id, name, math, physics, english);
        manager.addStudent(student);
        dialog.accept();
    });

    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        updateTable();
    }
}

// 删除学生
void MainWindow::deleteStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "删除学生", "请输入学号:", 0, 1, 10000, 1, &ok);
    if (!ok) return;

    Student* student = manager.findStudentById(id);
    if (!student) {
        QMessageBox::warning(this, "错误", "未找到该学号的学生");
        return;
    }

    if (QMessageBox::question(this, "确认删除",
        QString("确定删除学号 %1（%2）的学生吗？").arg(id).arg(student->getName()),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        if (manager.deleteStudentById(id)) {
            updateTable();
            QMessageBox::information(this, "成功", "删除学生成功");
        } else {
            QMessageBox::warning(this, "错误", "删除学生失败");
        }
    }
}

// 查找学生
void MainWindow::findStudent() {
    QStringList options = {"按学号精确查找", "按姓名模糊查找"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "查找方式", "选择查找方式:", options, 0, false, &ok);
    if (!ok) return;

    if (choice == "按学号精确查找") {
        int id = QInputDialog::getInt(this, "学号查找", "输入学号:", 0, 1, 10000, 1, &ok);
        if (!ok) return;

        Student* student = manager.findStudentById(id);
        if (student) {
            QDialog dialog(this);
            QFormLayout layout(&dialog);
            layout.addRow("学号:", new QLabel(QString::number(student->getId())));
            layout.addRow("姓名:", new QLabel(student->getName()));
            layout.addRow("数学:", new QLabel(QString::number(student->getMathScore(), 'f', 1)));
            layout.addRow("物理:", new QLabel(QString::number(student->getPhysicsScore(), 'f', 1)));
            layout.addRow("英语:", new QLabel(QString::number(student->getEnglishScore(), 'f', 1)));
            layout.addRow("总分:", new QLabel(QString::number(student->getTotalScore(), 'f', 1)));
            dialog.exec();
        } else {
            QMessageBox::warning(this, "结果", "未找到该学号的学生");
        }
    } else {
        QString key = QInputDialog::getText(this, "姓名查找", "输入姓名关键词:");
        if (key.isEmpty()) return;

        std::vector<Student*> results = manager.findStudentsByName(key);
        if (results.empty()) {
            QMessageBox::warning(this, "结果", "未找到匹配的学生");
            return;
        }

        QDialog dialog(this);
        QTableWidget* table = new QTableWidget(&dialog);
        table->setColumnCount(6);
        table->setHorizontalHeaderLabels({"学号", "姓名", "数学", "物理", "英语", "总分"});
        table->setRowCount(results.size());

        for (int i = 0; i < results.size(); ++i) {
            Student* stu = results[i];
            table->setItem(i, 0, new QTableWidgetItem(QString::number(stu->getId())));
            table->setItem(i, 1, new QTableWidgetItem(stu->getName()));
            table->setItem(i, 2, new QTableWidgetItem(QString::number(stu->getMathScore(), 'f', 1)));
            table->setItem(i, 3, new QTableWidgetItem(QString::number(stu->getPhysicsScore(), 'f', 1)));
            table->setItem(i, 4, new QTableWidgetItem(QString::number(stu->getEnglishScore(), 'f', 1)));
            table->setItem(i, 5, new QTableWidgetItem(QString::number(stu->getTotalScore(), 'f', 1)));
        }

        QVBoxLayout layout(&dialog);
        layout.addWidget(table);
        dialog.exec();
    }
}

// 排序学生（按总分降序）
void MainWindow::sortStudents() {
    manager.sortStudents();
    updateTable();
    QMessageBox::information(this, "成功", "排序完成（按总分从高到低）");
}

// 加载文件
void MainWindow::loadFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "打开学生数据文件", "", "文本文件 (*.txt)");
    if (!filename.isEmpty()) {
        manager.loadFromFile(filename);
        updateTable();
        QMessageBox::information(this, "成功", "数据加载完成");
    }
}

// 保存文件
void MainWindow::saveToFile() {
    QString filename = QFileDialog::getSaveFileName(this, "保存学生数据文件", "", "文本文件 (*.txt)");
    if (!filename.isEmpty()) {
        manager.saveToFile(filename);
        QMessageBox::information(this, "成功", "数据保存完成");
    }
}
