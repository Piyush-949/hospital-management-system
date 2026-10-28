#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Room.h"
#include "Staff.h"
#include "MedicalRecord.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool loginSystem() {
    string id, pass;
    int attempts = 0;
    cout << "\n============================================\n";
    cout << "       HOSPITAL SYSTEM ADMIN LOGIN          \n";
    cout << "============================================\n";
    while (attempts < 3) {
        cout << "Admin ID: ";
        getline(cin, id);
        cout << "Password: ";
        getline(cin, pass);
        
        if (id == "admin" && pass == "piyush9976") {
            cout << "\nAccess Granted. Welcome, Admin!\n";
            return true;
        } else {
            cout << "Invalid credentials. Remaining attempts: " << (2 - attempts) << "\n\n";
            attempts++;
        }
    }
    cout << "Maximum attempts reached. System locked out.\n";
    return false;
}

void patientMenu(PatientManager& pm, RoomManager& rmm) {
    int choice;
    do {
        cout << "\n--- Patient Management ---\n";
        cout << "1. Add Patient(s)\n2. View All Patients\n3. Update Patient(s)\n4. Delete Patient(s)\n5. Search Patients\n6. Back to Main Menu\nChoice: ";
        if (!(cin >> choice)) { clearInput(); continue; }
        switch (choice) {
            case 1: {
                char addMore;
                do {
                    Patient p; cout << "Enter ID: "; cin >> p.id; clearInput();
                    cout << "Name: "; getline(cin, p.name);
                    cout << "Age: "; cin >> p.age; clearInput();
                    cout << "Contact: "; getline(cin, p.contact);
                    cout << "Medical History: "; getline(cin, p.medicalHistory);
                    pm.addPatient(p); cout << "Patient added.\n";
                    cout << "Add another patient? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2: pm.viewPatients(); break;
            case 3: {
                char addMore;
                do {
                    int id; cout << "Enter ID to Update: "; cin >> id; clearInput();
                    if (!pm.getPatientById(id)) { cout << "Not found!\n"; }
                    else {
                        Patient p; cout << "New Name: "; getline(cin, p.name);
                        cout << "New Age: "; cin >> p.age; clearInput();
                        cout << "New Contact: "; getline(cin, p.contact);
                        cout << "New Med History: "; getline(cin, p.medicalHistory);
                        if (pm.updatePatient(id, p)) cout << "Updated.\n";
                    }
                    cout << "Update another patient? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 4: {
                char addMore;
                do {
                    int id; cout << "Enter ID to Delete: "; cin >> id; clearInput();
                    Room* r = rmm.getRoomByPatientId(id);
                    if (pm.deletePatient(id)) {
                        if (r) rmm.dischargePatient(r->id);
                        cout << "Deleted.\n";
                    } else {
                        cout << "Not found.\n";
                    }
                    cout << "Delete another patient? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 5: {
                string query; cout << "Enter name or contact to search: "; clearInput(); getline(cin, query);
                pm.searchPatients(query); break;
            }
        }
    } while (choice != 6);
}

void doctorMenu(DoctorManager& dm) {
    int choice;
    do {
        cout << "\n--- Doctor Management ---\n";
        cout << "1. Add Doctor(s)\n2. View All Doctors\n3. Update Doctor(s)\n4. Delete Doctor(s)\n5. Search by Specialty\n6. Back to Main Menu\nChoice: ";
        if (!(cin >> choice)) { clearInput(); continue; }
        switch (choice) {
            case 1: {
                char addMore;
                do {
                    Doctor d; cout << "Enter ID: "; cin >> d.id; clearInput();
                    cout << "Name: "; getline(cin, d.name);
                    cout << "Specialty: "; getline(cin, d.specialty);
                    cout << "Consultation Fee: "; cin >> d.consultationFee;
                    dm.addDoctor(d); cout << "Doctor added.\n";
                    cout << "Add another doctor? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2: dm.viewDoctors(); break;
            case 3: {
                char addMore;
                do {
                    int id; cout << "Enter ID to Update: "; cin >> id; clearInput();
                    if (!dm.getDoctorById(id)) { cout << "Not found!\n"; }
                    else {
                        Doctor d; cout << "New Name: "; getline(cin, d.name);
                        cout << "New Specialty: "; getline(cin, d.specialty);
                        cout << "New Fee: "; cin >> d.consultationFee;
                        if (dm.updateDoctor(id, d)) cout << "Updated.\n";
                    }
                    cout << "Update another doctor? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 4: {
                char addMore;
                do {
                    int id; cout << "Enter ID to Delete: "; cin >> id; clearInput();
                    if (dm.deleteDoctor(id)) cout << "Deleted.\n"; else cout << "Not found.\n";
                    cout << "Delete another doctor? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 5: {
                string spec; cout << "Enter specialty to search: "; clearInput(); getline(cin, spec);
                dm.searchDoctorsBySpecialty(spec); break;
            }
        }
    } while (choice != 6);
}

void appointmentMenu(AppointmentManager& am, PatientManager& pm, DoctorManager& dm, RecordManager& rm) {
    int choice;
    do {
        cout << "\n--- Appointment & Records ---\n";
        cout << "1. Schedule Appointment(s)\n2. View Appointments\n3. Cancel Appointment(s)\n4. Add Medical Record(s)\n5. View Medical Records\n6. Back to Main Menu\nChoice: ";
        if (!(cin >> choice)) { clearInput(); continue; }
        switch (choice) {
            case 1: {
                char addMore;
                do {
                    int pid, did; string date, time;
                    cout << "Patient ID: "; cin >> pid; cout << "Doctor ID: "; cin >> did; clearInput();
                    if (!pm.getPatientById(pid) || !dm.getDoctorById(did)) { cout << "Invalid ID(s)!\n"; }
                    else {
                        cout << "Date (YYYY-MM-DD): "; getline(cin, date);
                        cout << "Time (HH:MM): "; getline(cin, time);
                        am.scheduleAppointment(pid, did, date, time);
                    }
                    cout << "Schedule another? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2: am.viewAppointments(pm, dm); break;
            case 3: {
                char addMore;
                do {
                    int id; cout << "Appointment ID to cancel: "; cin >> id; clearInput();
                    if (am.cancelAppointment(id)) cout << "Canceled.\n"; else cout << "Not found.\n";
                    cout << "Cancel another? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 4: {
                char addMore;
                do {
                    int pid, did; string date, diag, pres;
                    cout << "Patient ID: "; cin >> pid; cout << "Doctor ID: "; cin >> did; clearInput();
                    if (!pm.getPatientById(pid) || !dm.getDoctorById(did)) { cout << "Invalid ID(s)!\n"; }
                    else {
                        cout << "Date (YYYY-MM-DD): "; getline(cin, date);
                        cout << "Diagnosis: "; getline(cin, diag);
                        cout << "Prescription: "; getline(cin, pres);
                        rm.addRecord(pid, did, date, diag, pres);
                    }
                    cout << "Add another medical record? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 5: {
                int pid; cout << "Patient ID: "; cin >> pid; clearInput();
                rm.viewRecordsByPatient(pid); break; // Usually viewed once
            }
        }
    } while (choice != 6);
}

void roomMenu(RoomManager& rmm, PatientManager& pm) {
    int choice;
    do {
        cout << "\n--- Room Management ---\n";
        cout << "1. Add Room(s)\n2. View Rooms\n3. Assign Patient(s)\n4. Discharge Patient(s)\n5. Back to Main Menu\nChoice: ";
        if (!(cin >> choice)) { clearInput(); continue; }
        switch (choice) {
            case 1: {
                char addMore;
                do {
                    Room r; r.isOccupied = false; r.patientId = 0;
                    cout << "Room ID: "; cin >> r.id; clearInput();
                    cout << "Room Type: "; getline(cin, r.type);
                    cout << "Charge per Day: "; cin >> r.chargePerDay;
                    rmm.addRoom(r); cout << "Room added.\n";
                    cout << "Add another room? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2: rmm.viewRooms(); break;
            case 3: {
                char addMore;
                do {
                    int rid, pid; cout << "Room ID: "; cin >> rid; cout << "Patient ID: "; cin >> pid; clearInput();
                    if (!pm.getPatientById(pid)) { cout << "Patient not found!\n"; }
                    else {
                        if (rmm.assignRoom(rid, pid)) cout << "Assigned.\n"; else cout << "Failed/Occupied/Not Found.\n";
                    }
                    cout << "Assign another room? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 4: {
                char addMore;
                do {
                    int rid; cout << "Room ID: "; cin >> rid; clearInput();
                    if (rmm.dischargePatient(rid)) cout << "Discharged.\n"; else cout << "Failed to discharge.\n";
                    cout << "Discharge another? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
        }
    } while (choice != 5);
}

void staffMenu(StaffManager& sm) {
    int choice;
    do {
        cout << "\n--- Staff Management ---\n";
        cout << "1. Add Staff\n2. View All Staff\n3. Update Staff\n4. Delete Staff\n5. Back to Main Menu\nChoice: ";
        if (!(cin >> choice)) { clearInput(); continue; }
        switch (choice) {
            case 1: {
                char addMore;
                do {
                    Staff s; cout << "Staff ID: "; cin >> s.id; clearInput();
                    cout << "Name: "; getline(cin, s.name);
                    cout << "Role: "; getline(cin, s.role);
                    cout << "Shift: "; getline(cin, s.shift);
                    cout << "Salary: "; cin >> s.salary;
                    sm.addStaff(s); cout << "Staff added.\n";
                    cout << "Add another staff member? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2: sm.viewStaff(); break;
            case 3: {
                char addMore;
                do {
                    int id; cout << "Enter ID to Update: "; cin >> id; clearInput();
                    if (!sm.getStaffById(id)) { cout << "Not found!\n"; }
                    else {
                        Staff s; cout << "New Name: "; getline(cin, s.name);
                        cout << "New Role: "; getline(cin, s.role);
                        cout << "New Shift: "; getline(cin, s.shift);
                        cout << "New Salary: "; cin >> s.salary;
                        if (sm.updateStaff(id, s)) cout << "Updated.\n";
                    }
                    cout << "Update another staff member? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 4: {
                char addMore;
                do {
                    int id; cout << "Enter ID to Delete: "; cin >> id; clearInput();
                    if (sm.deleteStaff(id)) cout << "Deleted.\n"; else cout << "Not found.\n";
                    cout << "Delete another staff member? (Y/N): "; cin >> addMore; clearInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
        }
    } while (choice != 5);
}

void billingMenu(AppointmentManager& am, PatientManager& pm, DoctorManager& dm, RoomManager& rmm) {
    char addMore;
    do {
        cout << "\n--- Advanced Billing System ---\n";
        int pid;
        cout << "Enter Patient ID for Billing: ";
        if (!(cin >> pid)) { clearInput(); return; }

        Patient* p = pm.getPatientById(pid);
        if (!p) { 
            cout << "Error: Patient not found!\n"; 
        } else {
            double consBill = am.calculatePatientBill(pid, dm);
            double roomBill = 0.0;
            
            Room* r = rmm.getRoomByPatientId(pid);
            if (r) {
                int days;
                cout << "Patient is currently assigned to Room " << r->id << " (" << r->type << ").\n";
                cout << "Enter number of days stayed: ";
                if (!(cin >> days)) { clearInput(); return; }
                roomBill = days * r->chargePerDay;
            }

            double totalBill = consBill + roomBill;
            cout << "\n============================================\n";
            cout << "               HOSPITAL BILL                \n";
            cout << "============================================\n";
            cout << "Patient ID: " << p->id << "\n";
            cout << "Patient Name: " << p->name << "\n";
            cout << "--------------------------------------------\n";
            cout << "Consultation Fees: $" << consBill << "\n";
            if (r) cout << "Room Charges (Room " << r->id << "): $" << roomBill << "\n";
            cout << "--------------------------------------------\n";
            cout << "TOTAL AMOUNT DUE: $" << totalBill << "\n";
            cout << "============================================\n";
        }

        cout << "Generate another bill? (Y/N): "; cin >> addMore; clearInput();
    } while (addMore == 'Y' || addMore == 'y');
}

void showMainMenu() {
    cout << "\n============================================\n";
    cout << "        HOSPITAL MANAGEMENT SYSTEM          \n";
    cout << "============================================\n";
    cout << "1. Patient Management\n";
    cout << "2. Doctor Management\n";
    cout << "3. Appointment & Records\n";
    cout << "4. Room Management\n";
    cout << "5. Staff Management\n";
    cout << "6. Billing System\n";
    cout << "7. Exit properly (Saves all data)\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    cout << fixed << setprecision(2);
    
    if (!loginSystem()) {
        return 1; // Exit program if authentication fails
    }
    
    PatientManager pm("patients.txt");
    DoctorManager dm("doctors.txt");
    AppointmentManager am("appointments.txt");
    RoomManager rmm("rooms.txt");
    StaffManager sm("staff.txt");
    RecordManager rm("records.txt");

    int choice;
    do {
        showMainMenu();
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: patientMenu(pm, rmm); break;
            case 2: doctorMenu(dm); break;
            case 3: appointmentMenu(am, pm, dm, rm); break;
            case 4: roomMenu(rmm, pm); break;
            case 5: staffMenu(sm); break;
            case 6: billingMenu(am, pm, dm, rmm); break;
            case 7: cout << "Exiting system. Data saved. Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
