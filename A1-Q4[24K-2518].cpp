#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Card {
private:
    bool active;

public:
    Card() : active(false) {}
    ~Card() {}

    bool isActive() const { return active; }

    void activate() { active = true; }
    void deactivate() { active = false; }
};

class Student {
private:
    string name;
    int id;
    Card card;
    static const double semesterFee;

public:
    Student(const string& name, int id) : name(name), id(id) {}
    ~Student() {}

    string getName() const { return name; }
    int getId() const { return id; }
    Card& getCard() { return card; }

    void paySemesterFees(double amount) {
        if (amount >= semesterFee) {
            card.activate();
            cout << "Payment successful! Transport card activated for " << name << endl;
        } else {
            cout << "Insufficient amount! Please pay the full semester fee of " << semesterFee << endl;
        }
    }
};

const double Student::semesterFee = 1500.0;

class Stop {
private:
    string name;
    vector<Student*> students;

public:
    Stop(const string& name) : name(name) {}
    ~Stop() { students.clear(); }

    string getName() const { return name; }
    void addStudent(Student* student) { students.push_back(student); }
    const vector<Student*>& getStudents() const { return students; }
};

class Route {
private:
    string name;
    vector<Stop*> stops;

public:
    Route(const string& name) : name(name) {}
    ~Route() { stops.clear(); }

    string getName() const { return name; }
    void addStop(Stop* stop) { stops.push_back(stop); }
    const vector<Stop*>& getStops() const { return stops; }
};

class Bus {
private:
    Route* route;
    vector<Student*> attendance;

public:
    Bus(Route* route) : route(route) {}
    ~Bus() { attendance.clear(); }

    void recordAttendance(Student* student) {
        if (student->getCard().isActive()) {
            attendance.push_back(student);
            cout << "Attendance recorded for student ID: " << student->getId() << endl;
        } else {
            cout << "Card inactive for student ID: " << student->getId() << ". Please pay the semester fee.\n";
        }
    }

    void showRoute() const {
        cout << "Route: " << route->getName() << endl;
        for (const auto& stop : route->getStops()) {
            cout << "Stop: " << stop->getName() << endl;
            for (const auto& student : stop->getStudents()) {
                cout << "  Student: " << student->getName() << " (ID: " << student->getId() << ")" << endl;
            }
        }
    }
};

int main() {
    Student student1("Hamza", 12345);
    Student student2("Mustafa", 67890);
    
    
    student1.paySemesterFees(1500.0);
    cout << endl;
    student2.paySemesterFees(1000.0);
    cout << endl;

    Stop stop1("Stop 1");
    stop1.addStudent(&student1);
    cout << endl;
    Stop stop2("Stop 2");
    stop2.addStudent(&student2);

    Route route("Route 1");
    route.addStop(&stop1);
    route.addStop(&stop2);

    Bus bus(&route);

    bus.recordAttendance(&student1);
    cout << endl;
    bus.recordAttendance(&student2);

	cout << endl;
    bus.showRoute();

    return 0;
}
