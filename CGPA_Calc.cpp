#include <iostream>
#include <vector>
#include <iomanip> // for setprecision

using namespace std;

int main() {
    int n;
    cout << "Enter the number of courses taken this semester: ";
    cin >> n;

    vector<string> courses(n);
    vector<double> grade(n);
    vector<int> credit_h(n);

    double tgrade = 0.0;
    int tcredits = 0;

    cout << "\n--- Enter details for each course ---\n";
    for (int i = 0; i < n; ++i) {
        cout << "\nCourse " << i + 1 << " name: ";
        cin.ignore();
        getline(cin, courses[i]);

        cout << "Grade obtained in " << courses[i] <<": ";
        cin >> grade[i];

        cout << "Credit hours for " << courses[i] << ": ";
        cin >> credit_h[i];

        tgrade += grade[i] * credit_h[i];
        tcredits += credit_h[i];
    }

    double semester_gpa = tgrade / tcredits;

    cout << "\n\n===== Semester Grade Report =====\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; ++i) {
        cout << "Course: " << courses[i]
             << " | Grade: " << grade[i]
             << " | Credit Hours: " << credit_h[i] << endl;
    }

    cout << "----------------------------------\n";
    cout << "Total Credits: " << tcredits << endl;
    cout << "Total Grade Points: " << tgrade << endl;
    cout << "Semester GPA (CGPA): " << semester_gpa << endl;
    cout << "==================================\n";

    return 0;
}
