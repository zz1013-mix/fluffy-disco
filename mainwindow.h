#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addStudent();       // 添加学生记录
    void deleteStudent();    //删除学生记录
    void findStudent();      //查找学生记录
    void sortStudents();     //按总分排序学生
    void loadFromFile();     //从文件加载学生记录
    void saveToFile();       //保存学生记录到文件

private:
    Ui::MainWindow *ui;
    void updateTable();      //更新表格视图
};

#endif // MAINWINDOW_H
