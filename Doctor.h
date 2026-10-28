#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Doctor {
    int id;
    std::string name;
    std::string specialty;
    double consultationFee;
};

class DoctorManager {
private:
    std::vector<Doctor> doctors;
    std::string filename;

    void loadData();

public:
    DoctorManager(const std::string& file);
    ~DoctorManager();

    void addDoctor(const Doctor& d);
    void viewDoctors() const;
    void searchDoctorsBySpecialty(const std::string& specialty) const;
    Doctor* getDoctorById(int id);
    bool updateDoctor(int id, const Doctor& newData);
    bool deleteDoctor(int id);
    void saveData() const;
};

#endif // DOCTOR_H
