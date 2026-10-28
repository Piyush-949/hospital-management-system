#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct MedicalRecord {
    int recordId;
    int patientId;
    int doctorId;
    std::string date;
    std::string diagnosis;
    std::string prescription;
};

class RecordManager {
private:
    std::vector<MedicalRecord> records;
    std::string filename;
    int nextId;
    void loadData();

public:
    RecordManager(const std::string& file);
    ~RecordManager();

    void addRecord(int patientId, int doctorId, const std::string& date, const std::string& diagnosis, const std::string& prescription);
    void viewRecordsByPatient(int patientId) const;
    void saveData() const;
};

#endif // MEDICAL_RECORD_H
