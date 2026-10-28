#include "Staff.h"

void StaffManager::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    Staff s;
    while (file >> s.id >> std::ws) {
        std::getline(file, s.name);
        std::getline(file, s.role);
        std::getline(file, s.shift);
        file >> s.salary >> std::ws;
        staffMembers.push_back(s);
    }
}

void StaffManager::saveData() const {
    std::ofstream file(filename);
    for (const auto& s : staffMembers) {
        file << s.id << '\n' << s.name << '\n' << s.role << '\n' << s.shift << '\n' << s.salary << '\n';
    }
}

StaffManager::StaffManager(const std::string& file) : filename(file) {
    loadData();
}

StaffManager::~StaffManager() {
    saveData();
}

void StaffManager::addStaff(const Staff& s) {
    staffMembers.push_back(s);
}

void StaffManager::viewStaff() const {
    std::cout << "--- Staff List ---\n";
    for (const auto& s : staffMembers) {
        std::cout << "ID: " << s.id << " | Name: " << s.name 
                  << " | Role: " << s.role << " | Shift: " << s.shift 
                  << " | Salary: $" << s.salary << "\n";
    }
}

Staff* StaffManager::getStaffById(int id) {
    for (auto& s : staffMembers) {
        if (s.id == id) return &s;
    }
    return nullptr;
}

bool StaffManager::updateStaff(int id, const Staff& newData) {
    for (auto& s : staffMembers) {
        if (s.id == id) {
            s.name = newData.name;
            s.role = newData.role;
            s.shift = newData.shift;
            s.salary = newData.salary;
            return true;
        }
    }
    return false;
}

bool StaffManager::deleteStaff(int id) {
    for (auto it = staffMembers.begin(); it != staffMembers.end(); ++it) {
        if (it->id == id) {
            staffMembers.erase(it);
            return true;
        }
    }
    return false;
}
