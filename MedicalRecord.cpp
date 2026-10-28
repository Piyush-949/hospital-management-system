#include "MedicalRecord.h"

void RecordManager::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    MedicalRecord r;
    while (file >> r.recordId >> r.patientId >> r.doctorId >> r.date >> std::ws) {
        std::getline(file, r.diagnosis);
        std::getline(file, r.prescription);
        records.push_back(r);
        if (r.recordId >= nextId) nextId = r.recordId + 1;
    }
}

void RecordManager::saveData() const {
    std::ofstream file(filename);
    for (const auto& r : records) {
        file << r.recordId << ' ' << r.patientId << ' ' << r.doctorId << ' ' << r.date << '\n'
             << r.diagnosis << '\n' << r.prescription << '\n';
    }
}

RecordManager::RecordManager(const std::string& file) : filename(file), nextId(1) {
    loadData();
}

RecordManager::~RecordManager() {
    saveData();
}

void RecordManager::addRecord(int patientId, int doctorId, const std::string& date, const std::string& diagnosis, const std::string& prescription) {
    MedicalRecord r = {nextId++, patientId, doctorId, date, diagnosis, prescription};
    records.push_back(r);
    std::cout << "Medical record added successfully with ID: " << r.recordId << "\n";
}

void RecordManager::viewRecordsByPatient(int patientId) const {
    bool found = false;
    std::cout << "--- Medical Records for Patient ID " << patientId << " ---\n";
    for (const auto& r : records) {
        if (r.patientId == patientId) {
            std::cout << "Record ID: " << r.recordId 
                      << " | Date: " << r.date 
                      << " | Doctor ID: " << r.doctorId << "\n"
                      << "Diagnosis: " << r.diagnosis << "\n"
                      << "Prescription: " << r.prescription << "\n"
                      << "----------------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No medical records found for this patient.\n";
    }
}
