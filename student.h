#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student {
public:
    Student(int id, QString name, double math, double physics, double english);

    int getId() const;
    QString getName() const;
    double getMathScore() const;
    double getPhysicsScore() const;
    double getEnglishScore() const;
    double getTotalScore() const;  // 计算总分

    void setMathScore(double score);
    void setPhysicsScore(double score);
    void setEnglishScore(double score);  // 修改成绩

private:
    int id;                // 学号
    QString name;          // 姓名
    double mathScore;      // 数学成绩
    double physicsScore;   // 物理成绩
    double englishScore;   // 英语成绩
};

#endif // STUDENT_H
