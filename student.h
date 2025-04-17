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
    double getTotalScore() const;

    void setMathScore(double score);
    void setPhysicsScore(double score);
    void setEnglishScore(double score);

private:
    int id;
    QString name;
    double mathScore;
    double physicsScore;
    double englishScore;
};

#endif // STUDENT_H