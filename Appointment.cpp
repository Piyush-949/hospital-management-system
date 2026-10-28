#include "Appointment.h"

void AppointmentManager::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    Appointment a;
    while (file >> a.id >> a.patientId >> a.doctorId >> a.date >> a.time) {
        appointments.push_back(a);
        if (a.id >= nextId) nextId = a.id + 1;
    }
}

void AppointmentManager::saveData() const {
    std::ofstream file(filename);
    for (const auto& a : appointments) {
        file << a.id << ' ' << a.patientId << ' ' << a.doctorId << ' ' << a.date << ' ' << a.time << '\n';
    }
}

AppointmentManager::AppointmentManager(const std::string& file) : filename(file), nextId(1) {
    loadData();
}

AppointmentManager::~AppointmentManager() {
    saveData();
}

void AppointmentManager::scheduleAppointment(int patientId, int doctorId, const std::string& date, const std::string& time) {
    Appointment a = {nextId++, patientId, doctorId, date, time};
    appointments.push_back(a);
    std::cout << "Appointment successfully scheduled with ID: " << a.id << "\n";
}

void AppointmentManager::viewAppointments(PatientManager& pm, DoctorManager& dm) const {
    std::cout << "--- Scheduled Appointments ---\n";
    for (const auto& a : appointments) {
        Patient* p = pm.getPatientById(a.patientId);
        Doctor* d = dm.getDoctorById(a.doctorId);
        std::cout << "Appt ID: " << a.id 
                  << " | Date: " << a.date << " " << a.time
                  << " | Patient: " << (p ? p->name : "Unknown")
                  << " | Doctor: " << (d ? "Dr. " + d->name : "Unknown") << "\n";
    }
}

bool AppointmentManager::cancelAppointment(int id) {
    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->id == id) {
            appointments.erase(it);
            return true;
        }
    }
    return false;
}

double AppointmentManager::calculatePatientBill(int patientId, DoctorManager& dm) const {
    double totalBill = 0.0;
    for (const auto& a : appointments) {
        if (a.patientId == patientId) {
            Doctor* d = dm.getDoctorById(a.doctorId);
            if (d) {
                totalBill += d->consultationFee;
            }
        }
    }
    return totalBill;
}
