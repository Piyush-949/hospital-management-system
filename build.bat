@echo off
echo Compiling Hospital Management System...
g++ main.cpp Patient.cpp Doctor.cpp Appointment.cpp Room.cpp Staff.cpp MedicalRecord.cpp -o hospital_system.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
) else (
    echo Compilation successful! You can now run hospital_system.exe
)
pause
