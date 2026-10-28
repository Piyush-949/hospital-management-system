#include "Doctor.h"

void DoctorManager::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    Doctor d;
    while (file >> d.id >> std::ws) {
        std::getline(file, d.name);
        std::getline(file, d.specialty);
        file >> d.consultationFee >> std::ws;
        doctors.push_back(d);
    }
}

void DoctorManager::saveData() const {
    std::ofstream file(filename);
    for (const auto& d : doctors) {
        file << d.id << '\n' << d.name << '\n' << d.specialty << '\n' << d.consultationFee << '\n';
    }
}

DoctorManager::DoctorManager(const std::string& file) : filename(file) {
    loadData();
}

DoctorManager::~DoctorManager() {
    saveData();
}

void DoctorManager::addDoctor(const Doctor& d) {
    doctors.push_back(d);
}

void DoctorManager::viewDoctors() const {
    std::cout << "--- Doctor List ---\n";
    for (const auto& d : doctors) {
        std::cout << "ID: " << d.id << ", Name: Dr. " << d.name 
                  << ", Specialty: " << d.specialty 
                  << ", Fee: $" << d.consultationFee << "\n";
    }
}

void DoctorManager::searchDoctorsBySpecialty(const std::string& specialty) const {
    std::cout << "--- Doctors specializing in " << specialty << " ---\n";
    bool found = false;
    for (const auto& d : doctors) {
        if (d.specialty.find(specialty) != std::string::npos) {
            std::cout << "ID: " << d.id << ", Name: Dr. " << d.name 
                      << ", Fee: $" << d.consultationFee << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No doctors found with that specialty.\n";
    }
}

Doctor* DoctorManager::getDoctorById(int id) {
    for (auto& d : doctors) {
        if (d.id == id) return &d;
    }
    return nullptr;
}

bool DoctorManager::updateDoctor(int id, const Doctor& newData) {
    for (auto& d : doctors) {
        if (d.id == id) {
            d.name = newData.name;
            d.specialty = newData.specialty;
            d.consultationFee = newData.consultationFee;
            return true;
        }
    }
    return false;
}

bool DoctorManager::deleteDoctor(int id) {
    for (auto it = doctors.begin(); it != doctors.end(); ++it) {
        if (it->id == id) {
            doctors.erase(it);
            return true;
        }
    }
    return false;
}
