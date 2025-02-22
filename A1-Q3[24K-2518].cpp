#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User {
private:
    string name;
    int age;
    string licenseType;
    string contactInfo;
    int userID;

public:
    User(string name, int age, string licenseType, string contactInfo, int userID)
        : name(name), age(age), licenseType(licenseType), contactInfo(contactInfo), userID(userID) {}

    void updateDetails(string name, int age, string licenseType, string contactInfo) {
        this->name = name;
        this->age = age;
        this->licenseType = licenseType;
        this->contactInfo = contactInfo;
    }

    string getLicenseType() {
        return licenseType;
    }

    int getUserID() {
        return userID;
    }
};

class Vehicle {
private:
    string model;
    double rentalPricePerDay;
    string requiredLicenseType;

public:
    Vehicle(string model, double rentalPricePerDay, string requiredLicenseType)
        : model(model), rentalPricePerDay(rentalPricePerDay), requiredLicenseType(requiredLicenseType) {}

    bool isEligible(string licenseType) {
        if (licenseType == "Full") {
            return true;
        } else if (licenseType == "Intermediate" && (requiredLicenseType == "Intermediate" || requiredLicenseType == "Learner")) {
            return true;
        } else if (licenseType == "Learner" && requiredLicenseType == "Learner") {
            return true;
        }
        return false;
    }

    string getModel() {
        return model;
    }
    
};

class RentalSystem {
private:
    vector<User> users;
    vector<Vehicle*> vehicles;

public:
    void registerUser(User user) {
        users.push_back(user);
    }

    void updateUser(int userID, string name, int age, string licenseType, string contactInfo) {
        for (User &user : users) {
            if (user.getUserID() == userID) {
                user.updateDetails(name, age, licenseType, contactInfo);
                break;
            }
        }
    }

    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    void rentVehicle(int userID, string model) {
        for (User &user : users) {
            if (user.getUserID() == userID) {
                for (Vehicle* vehicle : vehicles) {
                    if (vehicle->getModel() == model && vehicle->isEligible(user.getLicenseType())) {
                        cout << "Vehicle rented successfully!" << endl;
                        return;
                    }
                }
                cout << "User is not eligible to rent this vehicle." << endl;
                return;
            }
        }
        cout << "User not found." << endl;
    }
    
};

int main() {
    RentalSystem rentalSystem;


    User user1("Hamza", 25, "Full", "123-456-7890", 2518);
    User user2("Ali", 22, "Intermediate", "234-567-8901", 2519);
    User user3("Sara", 20, "Learner", "345-678-9012", 2520);
    rentalSystem.registerUser(user1);
    rentalSystem.registerUser(user2);
    rentalSystem.registerUser(user3);


    Vehicle* vehicle1 = new Vehicle("Toyota Civic", 50.0, "Full");
    Vehicle* vehicle2 = new Vehicle("Honda Accord", 60.0, "Intermediate");
    Vehicle* vehicle3 = new Vehicle("Ford Fiesta", 40.0, "Learner");
    rentalSystem.addVehicle(vehicle1);
    rentalSystem.addVehicle(vehicle2);
    rentalSystem.addVehicle(vehicle3);


    cout << "User 1 (Full) renting Toyota Civic: ";
    rentalSystem.rentVehicle(2518, "Toyota Civic");

    cout << "User 1 (Full) renting Honda Accord: ";
    rentalSystem.rentVehicle(2518, "Honda Accord");

    cout << "User 1 (Full) renting Ford Fiesta: ";
    rentalSystem.rentVehicle(2518, "Ford Fiesta");
    
    cout <<endl;
    cout <<endl;

    cout << "User 2 (Intermediate) renting Toyota Civic: ";
    rentalSystem.rentVehicle(2519, "Toyota Civic");

    cout << "User 2 (Intermediate) renting Honda Accord: ";
    rentalSystem.rentVehicle(2519, "Honda Accord");

    cout << "User 2 (Intermediate) renting Ford Fiesta: ";
    rentalSystem.rentVehicle(2519, "Ford Fiesta");
    
    cout <<endl;
    cout <<endl;

    cout << "User 3 (Learner) renting Toyota Civic: ";
    rentalSystem.rentVehicle(2520, "Toyota Civic");

    cout << "User 3 (Learner) renting Honda Accord: ";
    rentalSystem.rentVehicle(2520, "Honda Accord");

    cout << "User 3 (Learner) renting Ford Fiesta: ";
    rentalSystem.rentVehicle(2520, "Ford Fiesta");


    delete vehicle1;
    delete vehicle2;
    delete vehicle3;

    return 0;
}