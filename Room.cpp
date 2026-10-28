#include "Room.h"

void RoomManager::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    Room r;
    while (file >> r.id >> std::ws) {
        std::getline(file, r.type);
        file >> r.isOccupied >> r.patientId >> r.chargePerDay >> std::ws;
        rooms.push_back(r);
    }
}

void RoomManager::saveData() const {
    std::ofstream file(filename);
    for (const auto& r : rooms) {
        file << r.id << '\n' << r.type << '\n' << r.isOccupied << '\n' << r.patientId << '\n' << r.chargePerDay << '\n';
    }
}

RoomManager::RoomManager(const std::string& file) : filename(file) {
    loadData();
}

RoomManager::~RoomManager() {
    saveData();
}

void RoomManager::addRoom(const Room& r) {
    rooms.push_back(r);
}

void RoomManager::viewRooms() const {
    std::cout << "--- Room List ---\n";
    for (const auto& r : rooms) {
        std::cout << "ID: " << r.id << " | Type: " << r.type 
                  << " | Charge/Day: $" << r.chargePerDay
                  << " | Status: " << (r.isOccupied ? ("Occupied by Patient ID " + std::to_string(r.patientId)) : "Available") 
                  << "\n";
    }
}

Room* RoomManager::getRoomById(int id) {
    for (auto& r : rooms) {
        if (r.id == id) return &r;
    }
    return nullptr;
}

Room* RoomManager::getRoomByPatientId(int patientId) {
    for (auto& r : rooms) {
        if (r.isOccupied && r.patientId == patientId) return &r;
    }
    return nullptr;
}

bool RoomManager::assignRoom(int roomId, int patientId) {
    Room* r = getRoomById(roomId);
    if (r && !r->isOccupied) {
        r->isOccupied = true;
        r->patientId = patientId;
        return true;
    }
    return false;
}

bool RoomManager::dischargePatient(int roomId) {
    Room* r = getRoomById(roomId);
    if (r && r->isOccupied) {
        r->isOccupied = false;
        r->patientId = 0;
        return true;
    }
    return false;
}
