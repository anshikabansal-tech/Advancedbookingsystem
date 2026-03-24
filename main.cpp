#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// ---------------- USER ----------------
class User {
public:
    string name;

    void input() {
        cout << "Enter your name: ";
        cin >> name;
    }
};

// ---------------- DRIVER ----------------
class Driver {
public:
    string name;
    bool available;

    Driver(string n) {
        name = n;
        available = true;
    }
};

// ---------------- CAB ----------------
class Cab {
public:
    string type;
    float rate;

    void selectCab() {
        int choice;
        cout << "\nSelect Cab Type:\n";
        cout << "1. Mini (10/km)\n2. Sedan (15/km)\n3. SUV (20/km)\n";
        cin >> choice;

        switch(choice) {
            case 1: type = "Mini"; rate = 10; break;
            case 2: type = "Sedan"; rate = 15; break;
            case 3: type = "SUV"; rate = 20; break;
            default: cout << "Invalid choice! Default Mini selected.\n";
                     type = "Mini"; rate = 10;
        }
    }
};

// ---------------- RIDE ----------------
class Ride {
public:
    int rideId;
    string pickup, drop;
    float distance;
    float fare;
    string driverName;
    string cabType;
    string status;

    void createRide(int id) {
        rideId = id;
        status = "Booked";

        cout << "Enter Pickup Location: ";
        cin >> pickup;
        cout << "Enter Drop Location: ";
        cin >> drop;
        cout << "Enter Distance (km): ";
        cin >> distance;
    }

    void calculateFare(float rate) {
        fare = distance * rate;
    }

    void display() {
        cout << "\n--- Ride Details ---\n";
        cout << "Ride ID: " << rideId << endl;
        cout << "Driver: " << driverName << endl;
        cout << "Cab Type: " << cabType << endl;
        cout << "Fare: " << fare << endl;
        cout << "Status: " << status << endl;
    }

    void saveToFile() {
        ofstream file("rides.txt", ios::app);
        file << rideId << " " << driverName << " "
             << cabType << " " << fare << " " << status << endl;
        file.close();
    }
};

// ---------------- SYSTEM ----------------
class CabSystem {
    vector<Driver> drivers;
    int rideCounter = 1;

public:
    CabSystem() {
        drivers.push_back(Driver("Aman"));
        drivers.push_back(Driver("Rahul"));
        drivers.push_back(Driver("Simran"));
    }

    void bookRide() {
        User u;
        u.input();

        Cab cab;
        cab.selectCab();

        Ride r;
        r.createRide(rideCounter);

        // Assign Driver
        bool found = false;
        for (auto &d : drivers) {
            if (d.available) {
                r.driverName = d.name;
                d.available = false;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No drivers available!\n";
            return;
        }

        r.cabType = cab.type;
        r.calculateFare(cab.rate);

        r.display();
        r.saveToFile();

        rideCounter++;
    }

    void showHistory() {
        ifstream file("rides.txt");
        string line;
        cout << "\n--- Ride History ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    void cancelRide() {
        cout << "Enter Ride ID to cancel: ";
        int id;
        cin >> id;

        // simple logic (demo purpose)
        cout << "Ride " << id << " cancelled (simulation).\n";
    }
};

// ---------------- MAIN ----------------
int main() {
    CabSystem system;
    int choice;

    while (true) {
        cout << "\n===== CAB BOOKING SYSTEM =====\n";
        cout << "1. Book Ride\n";
        cout << "2. View History\n";
        cout << "3. Cancel Ride\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: system.bookRide(); break;
            case 2: system.showHistory(); break;
            case 3: system.cancelRide(); break;
            case 4: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}