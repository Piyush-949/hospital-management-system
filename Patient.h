#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Patient {
    int id;
    std::string name;
    int age;
    std::string contact;
    std::string medicalHistory;
};

class PatientManager {
private:
    std::vector<Patient> patients;
    std::string filename;

    void loadData();

public:
    PatientManager(const std::string& file);
    ~PatientManager();

    void addPatient(const Patient& p);
    void viewPatients() const;
    void searchPatients(const std::string& query) const;
    Patient* getPatientById(int id);
    bool updatePatient(int id, const Patient& newData);
    bool deletePatient(int id);
    void saveData() const;
};

#endif // PATIENT_H
