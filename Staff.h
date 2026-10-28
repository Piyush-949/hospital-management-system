#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Staff {
    int id;
    std::string name;
    std::string role; // Nurse, Receptionist, Janitor, etc.
    std::string shift; // Morning, Evening, Night
    double salary;
};

class StaffManager {
private:
    std::vector<Staff> staffMembers;
    std::string filename;
    void loadData();

public:
    StaffManager(const std::string& file);
    ~StaffManager();

    void addStaff(const Staff& s);
    void viewStaff() const;
    Staff* getStaffById(int id);
    bool updateStaff(int id, const Staff& newData);
    bool deleteStaff(int id);
    void saveData() const;
};

#endif // STAFF_H
