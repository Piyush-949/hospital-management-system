#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Room {
    int id;
    std::string type; // e.g., General, Private, ICU
    bool isOccupied;
    int patientId; // 0 if unoccupied
    double chargePerDay;
};

class RoomManager {
private:
    std::vector<Room> rooms;
    std::string filename;
    void loadData();

public:
    RoomManager(const std::string& file);
    ~RoomManager();

    void addRoom(const Room& r);
    void viewRooms() const;
    Room* getRoomById(int id);
    Room* getRoomByPatientId(int patientId);
    bool assignRoom(int roomId, int patientId);
    bool dischargePatient(int roomId);
    void saveData() const;
};

#endif // ROOM_H
