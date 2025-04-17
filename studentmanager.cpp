#include "studentmanager.h"

// ====================== 核心功能实现 ======================
void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
}

bool StudentManager::deleteStudentById(int id) {
    auto it = std::remove_if(students.begin(), students.end(), [id](const Student& s) {
        return s.getId() == id;
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
        if (student.getName().contains(namePart, Qt::CaseInsensitive)) {  // 不区分大小写模糊匹配
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
        // 主排序：总分降序
        if (a.getTotalScore() != b.getTotalScore()) {
            return a.getTotalScore() > b.getTotalScore();
        }
        // 次排序：数学降序
        if (a.getMathScore() != b.getMathScore()) {
            return a.getMathScore() > b.getMathScore();
        }
        // 第三排序：物理降序
        if (a.getPhysicsScore() != b.getPhysicsScore()) {
            return a.getPhysicsScore() > b.getPhysicsScore();
        }
        // 最终排序：学号升序
        return a.getId() < b.getId();
    });
}

// ====================== 统计分析实现 ======================
double StudentManager::calculateAverageScore(const QString& subject) const {
    if (students.empty()) return 0.0;
    double total = 0.0;
    for (const auto& student : students) {
        total += getScoreBySubject(student, subject);
    }
    return total / students.size();
}

double StudentManager::calculateAverageTotalScore() const {
    if (students.empty()) return 0.0;
    double total = 0.0;
    for (const auto& student : students) {
        total += student.getTotalScore();
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

// ====================== 文件操作实现 ======================
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
    file.close();
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
    file.close();
}

// 私有辅助函数：根据科目获取成绩
double StudentManager::getScoreBySubject(const Student& student, const QString& subject) const {
    if (subject == "math") return student.getMathScore();
    if (subject == "physics") return student.getPhysicsScore();
    if (subject == "english") return student.getEnglishScore();
    return 0.0;  // 科目不存在时返回0
}
