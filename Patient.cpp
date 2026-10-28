#include "Patient.h"

void PatientManager::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    Patient p;
    while (file >> p.id >> std::ws) {
        std::getline(file, p.name);
        file >> p.age >> std::ws;
        std::getline(file, p.contact);
        std::getline(file, p.medicalHistory);
        patients.push_back(p);
    }
}

void PatientManager::saveData() const {
    std::ofstream file(filename);
    for (const auto& p : patients) {
        file << p.id << '\n' << p.name << '\n' << p.age << '\n' << p.contact << '\n' << p.medicalHistory << '\n';
    }
}

PatientManager::PatientManager(const std::string& file) : filename(file) {
    loadData();
}

PatientManager::~PatientManager() {
    saveData();
}

void PatientManager::addPatient(const Patient& p) {
    patients.push_back(p);
}

void PatientManager::viewPatients() const {
    std::cout << "--- Patient List ---\n";
    for (const auto& p : patients) {
        std::cout << "ID: " << p.id << ", Name: " << p.name << ", Age: " << p.age << "\n";
    }
}

void PatientManager::searchPatients(const std::string& query) const {
    std::cout << "--- Search Results ---\n";
    bool found = false;
    for (const auto& p : patients) {
        if (p.name.find(query) != std::string::npos || p.contact.find(query) != std::string::npos) {
            std::cout << "ID: " << p.id << ", Name: " << p.name << ", Contact: " << p.contact << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No patients matched the search query.\n";
    }
}

Patient* PatientManager::getPatientById(int id) {
    for (auto& p : patients) {
        if (p.id == id) return &p;
    }
    return nullptr;
}

bool PatientManager::updatePatient(int id, const Patient& newData) {
    for (auto& p : patients) {
        if (p.id == id) {
            p.name = newData.name;
            p.age = newData.age;
            p.contact = newData.contact;
            p.medicalHistory = newData.medicalHistory;
            return true;
        }
    }
    return false;
}

bool PatientManager::deletePatient(int id) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->id == id) {
            patients.erase(it);
            return true;
        }
    }
    return false;
}
