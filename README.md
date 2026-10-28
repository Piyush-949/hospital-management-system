# Hospital Management System (C++)

A modular, file-based Hospital Management System built in C++.

## 🚀 Features

- **Patient Management**: Register, view, and update patient information.
- **Doctor Management**: Manage doctor profiles, specialties, and schedules.
- **Appointment Booking**: Schedule and track patient-doctor appointments.
- **Medical Records**: Maintain and view patient medical history.
- **Room Allocation**: Track and allocate hospital rooms and beds.
- **Staff Management**: Keep track of hospital administrative and nursing staff.
- **Data Persistence**: Stores data reliably in text-based database files.

## 🛠️ Project Structure

```
hospital_management/
├── main.cpp              # Entry point and interactive console UI
├── Patient.h / .cpp      # Patient module
├── Doctor.h / .cpp       # Doctor module
├── Appointment.h / .cpp  # Appointment booking module
├── MedicalRecord.h / .cpp# Medical history module
├── Room.h / .cpp         # Room allocation module
├── Staff.h / .cpp        # Staff management module
└── build.bat             # Compilation script using MinGW g++
```

## ⚙️ How to Build & Run

### Using GCC / G++ (Windows Command Prompt or PowerShell)

Execute the build script:
```cmd
build.bat
```

Or manually compile:
```bash
g++ main.cpp Patient.cpp Doctor.cpp Appointment.cpp Room.cpp Staff.cpp MedicalRecord.cpp -o hospital_system.exe
```

Run the application:
```cmd
hospital_system.exe
```

## 📝 License

This project is open source and available under the [MIT License](LICENSE).
