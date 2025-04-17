#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "student.h"
#include <vector>
#include <QString>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

class StudentManager {
public:
    // 核心功能
    void addStudent(const Student& student);                 // 添加学生
    bool deleteStudentById(int id);                         // 按学号删除
    Student* findStudentById(int id);                        // 按学号查找
    std::vector<Student*> findStudentsByName(const QString& namePart);  // 按姓名模糊查找
    void modifyStudentScores(int id, double math, double physics, double english);  // 修改成绩
    void sortStudents();                                     // 按规则排序（总分降序，数学、物理、学号升序）

    // 统计分析
    double calculateAverageScore(const QString& subject) const;   // 单科平均分
    double calculateAverageTotalScore() const;                  // 总分平均分（重载）
    double calculateStandardDeviation(const QString& subject) const;  // 标准差
    double calculatePassRate(const QString& subject) const;      // 合格率（≥60分）

    // 文件操作
    void loadFromFile(const QString& filename);                // 从文件加载数据
    void saveToFile(const QString& filename) const;            // 保存数据到文件

private:
    std::vector<Student> students;                            // 学生数据容器

    // 私有辅助函数：根据科目获取成绩
    double getScoreBySubject(const Student& student, const QString& subject) const;
};

#endif // STUDENTMANAGER_H
