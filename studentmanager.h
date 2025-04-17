#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "student.h"
#include <vector>
#include <QString>

class StudentManager {
public:
    void addStudent(const Student& student);
    bool deleteStudentById(int id);
    Student* findStudentById(int id);
    std::vector<Student*> findStudentsByName(const QString& namePart);
    void modifyStudentScores(int id, double math, double physics, double english);
    void sortStudents();

    double calculateAverageScore(const QString& subject) const;
    double calculateStandardDeviation(const QString& subject) const;
    double calculatePassRate(const QString& subject) const;

    void loadFromFile(const QString& filename);
    void saveToFile(const QString& filename) const;

private:
    std::vector<Student> students;
    double getScoreBySubject(const Student& student, const QString& subject) const;
};

#endif // STUDENTMANAGER_H