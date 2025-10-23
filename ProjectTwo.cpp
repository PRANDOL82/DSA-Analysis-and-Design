#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string number;
    string title;
    vector<string> prerequisites;
};

// Global map to store courses
map<string, Course> courseMap;

// Parse a line of CSV into a Course object
Course parseCourseLine(const string& line) {
    stringstream ss(line);
    string token;
    Course course;

    getline(ss, course.number, ',');
    getline(ss, course.title, ',');

    while (getline(ss, token, ',')) {
        if (!token.empty()) {
            course.prerequisites.push_back(token);
        }
    }

    return course;
}

// Load courses from file into map
void loadDataStructure(string filename) {
    ifstream file(filename);
    while (!file.is_open()) {
        cout << "File not found. Try again: ";
        cin >> filename;
        file.open(filename);
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        Course course = parseCourseLine(line);
        courseMap[course.number] = course;
        count++;
    }

    file.close();
    cout << count << " courses loaded successfully.\n";
}

// Print all courses sorted by course number
void printCourseList() {
    cout << "\nHere is a sample schedule:\n\n";
    for (const auto& pair : courseMap) {
        cout << pair.second.number << ", " << pair.second.title << endl;
    }
}

// Print detailed info for a specific course
void printCourseInfo(const string& inputNumber) {
    string key = inputNumber;
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    if (courseMap.find(key) == courseMap.end()) {
        cout << "Course not found.\n";
        return;
    }

    Course course = courseMap[key];
    cout << course.number << ", " << course.title << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            string prereq = course.prerequisites[i];
            cout << prereq;
            if (courseMap.find(prereq) != courseMap.end()) {
                cout << " (" << courseMap[prereq].title << ")";
            }
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Display menu and handle user input
void displayMenu() {
    int choice = 0;
    string filename;

    while (choice != 9) {
        cout << "\n1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> filename;
            loadDataStructure(filename);
            break;
        case 2:
            if (courseMap.empty()) {
                cout << "Please load data first.\n";
            }
            else {
                printCourseList();
            }
            break;
        case 3:
            if (courseMap.empty()) {
                cout << "Please load data first.\n";
            }
            else {
                cout << "What course do you want to know about? ";
                string courseNumber;
                cin >> courseNumber;
                printCourseInfo(courseNumber);
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!\n";
            break;
        default:
            cout << choice << " is not a valid option.\n";
        }
    }
}

int main() {
    cout << "Welcome to the course planner.\n";
    displayMenu();
    return 0;
}
