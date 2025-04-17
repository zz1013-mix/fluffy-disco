#include "studentmanager.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
}

bool StudentManager::deleteStudentById(int id) {
    auto it = std::remove_if(students.begin(), students.end(), [id](const Student& student) {
        return student.getId() == id;
    });
    if (it != students.end()) {
        students.erase(it, students.end());
        return true;
    }
    return false;
}

Student* StudentManager::findStudentById(int id) {
    for (auto& student : students) {
        if (student.getId() == id) {
            return &student;
        }
    }
    return nullptr;
}

std::vector<Student*> StudentManager::findStudentsByName(const QString& namePart) {
    std::vector<Student*> results;
    for (auto& student : students) {
        if (student.getName().contains(namePart, Qt::CaseInsensitive)) {
            results.push_back(&student);
        }
    }
    return results;
}

void StudentManager::modifyStudentScores(int id, double math, double physics, double english) {
    Student* student = findStudentById(id);
    if (student) {
        student->setMathScore(math);
        student->setPhysicsScore(physics);
        student->setEnglishScore(english);
    }
}

void StudentManager::sortStudents() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.getTotalScore() != b.getTotalScore())
            return a.getTotalScore() > b.getTotalScore();
        if (a.getMathScore() != b.getMathScore())
            return a.getMathScore() > b.getMathScore();
        if (a.getPhysicsScore() != b.getPhysicsScore())
            return a.getPhysicsScore() > b.getPhysicsScore();
        return a.getId() < b.getId();
    });
}

double StudentManager::calculateAverageScore(const QString& subject) const {
    if (students.empty()) return 0.0;
    double total = 0.0;
    for (const auto& student : students) {
        total += getScoreBySubject(student, subject);
    }
    return total / students.size();
}

double StudentManager::calculateStandardDeviation(const QString& subject) const {
    if (students.empty()) return 0.0;
    double avg = calculateAverageScore(subject);
    double sum = 0.0;
    for (const auto& student : students) {
        double diff = getScoreBySubject(student, subject) - avg;
        sum += diff * diff;
    }
    return std::sqrt(sum / students.size());
}

double StudentManager::calculatePassRate(const QString& subject) const {
    if (students.empty()) return 0.0;
    int passCount = 0;
    for (const auto& student : students) {
        if (getScoreBySubject(student, subject) >= 60) {
            passCount++;
        }
    }
    return static_cast<double>(passCount) / students.size() * 100;
}

void StudentManager::loadFromFile(const QString& filename) {
    students.clear();
    std::ifstream file(filename.toStdString());
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int id;
        std::string name;
        double math, physics, english;
        if (ss >> id >> name >> math >> physics >> english) {
            students.emplace_back(id, QString::fromStdString(name), math, physics, english);
        }
    }
}

void StudentManager::saveToFile(const QString& filename) const {
    std::ofstream file(filename.toStdString());
    if (!file.is_open()) return;
    for (const auto& student : students) {
        file << student.getId() << " "
             << student.getName().toStdString() << " "
             << student.getMathScore() << " "
             << student.getPhysicsScore() << " "
             << student.getEnglishScore() << "\n";
    }
}

double StudentManager::getScoreBySubject(const Student& student, const QString& subject) const {
    if (subject == "math") return student.getMathScore();
    if (subject == "physics") return student.getPhysicsScore();
    if (subject == "english") return student.getEnglishScore();
    return 0.0;
}