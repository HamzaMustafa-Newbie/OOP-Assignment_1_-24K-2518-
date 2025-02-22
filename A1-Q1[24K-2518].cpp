#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Skill {
public:
    int skillID;
    string skillName;
    string description;

    Skill(int id, string name, string desc) : skillID(id), skillName(name), description(desc) {}
    void showSkillDetails() {
        cout << "Skill ID: " << skillID << ", Name: " << skillName << ", Description: " << description << endl;
    }
    void updateSkillDescription(string newDescription) {
        description = newDescription;
    }
};

class Sport {
public:
    int sportID;
    string name;
    string description;
    vector<Skill> requiredSkills;

    Sport(int id, string name, string desc) : sportID(id), name(name), description(desc) {}
    void addSkill(Skill s) {
        requiredSkills.push_back(s);
    }
    void removeSkill(Skill s) {}
};

class Student;

class Mentor {
public:
    int mentorID;
    string name;
    vector<Sport> sportsExpertise;
    int maxLearners;
    vector<Student*> assignedLearners;

    Mentor(int id, string name, int maxLearners) : mentorID(id), name(name), maxLearners(maxLearners) {}
    void assignLearner(Student* s);
    void removeLearner(Student* s);
    void viewLearners();
    void provideGuidance();
};

class Student {
public:
    int studentID;
    string name;
    int age;
    vector<Sport> sportsInterests;
    Mentor* mentorAssigned;

    Student(int id, string name, int age) : studentID(id), name(name), age(age), mentorAssigned(nullptr) {}

    void registerForMentorship(Mentor* m) {
        mentorAssigned = m;
        m->assignLearner(this);
    }

    void viewMentorDetails() {
        if (mentorAssigned) {
            cout << "Mentor ID: " << mentorAssigned->mentorID << ", Name: " << mentorAssigned->name << endl;
        } else {
            cout << "No mentor assigned." << endl;
        }
    }

    void updateSportsInterest(Sport s) {
        sportsInterests.push_back(s);
    }
};

void Mentor::assignLearner(Student* s) {
    if (assignedLearners.size() < maxLearners) {
        assignedLearners.push_back(s);
    } else {
        cout << "Capacity Full, Cannot assign more learners." << endl;
    }
}

void Mentor::removeLearner(Student* s) {
	
}

void Mentor::viewLearners() {
    for (Student* s : assignedLearners) {
        cout << "Student ID: " << s->studentID << ", Name: " << s->name << endl;
    }
}

void Mentor::provideGuidance() {
    cout << "Providing guidance to learners." << endl;
}

int main() {
    Mentor ali(1, "Ali", 3);
    Mentor sara(2, "Sara", 2);

    Student saad(1, "Saad", 20);
    Student ahmed(2, "Ahmed", 22);
    Student zara(3, "Zara", 19);

    Sport tennis(1, "Tennis", "A racket sport");
    Sport football(2, "Football", "A team sport");
    Sport basketball(3, "Basketball", "A team sport");

    saad.registerForMentorship(&ali);
    ahmed.registerForMentorship(&ali);
    zara.registerForMentorship(&sara);

    saad.updateSportsInterest(tennis);
    ahmed.updateSportsInterest(football);
    zara.updateSportsInterest(basketball);

    cout<<"Mentors' details:"<<endl;
    saad.viewMentorDetails();
    ahmed.viewMentorDetails();
    zara.viewMentorDetails();

    cout<< endl;
    cout<< endl;
    cout << "Mentor Ali's learners:" << endl;
    ali.viewLearners();
    ali.provideGuidance();

    cout<< endl;
    cout<< endl;
    cout << "Mentor Sara's learners:" << endl;
    sara.viewLearners();
    sara.provideGuidance();

    return 0;
}