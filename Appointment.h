#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Patient.h"
#include "Doctor.h"

struct Appointment {
    int id;
    int patientId;
    int doctorId;
    std::string date; // Format: YYYY-MM-DD
    std::string time;
};

class AppointmentManager {
private:
    std::vector<Appointment> appointments;
    std::string filename;
    int nextId;

    void loadData();

public:
    AppointmentManager(const std::string& file);
    ~AppointmentManager();

    void scheduleAppointment(int patientId, int doctorId, const std::string& date, const std::string& time);
    void viewAppointments(PatientManager& pm, DoctorManager& dm) const;
    bool cancelAppointment(int id);
    double calculatePatientBill(int patientId, DoctorManager& dm) const;
    void saveData() const;
};

#endif // APPOINTMENT_H
