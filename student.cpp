#include "student.h"

Student::Student(int id, QString name, double math, double physics, double english)
    : id(id), name(name), mathScore(math), physicsScore(physics), englishScore(english) {}

int Student::getId() const {
    return id;
}

QString Student::getName() const {
    return name;
}

double Student::getMathScore() const {
    return mathScore;
}

double Student::getPhysicsScore() const {
    return physicsScore;
}

double Student::getEnglishScore() const {
    return englishScore;
}

double Student::getTotalScore() const {
    return mathScore + physicsScore + englishScore;
}

void Student::setMathScore(double score) {
    mathScore = score;
}

void Student::setPhysicsScore(double score) {
    physicsScore = score;
}

void Student::setEnglishScore(double score) {
    englishScore = score;
}