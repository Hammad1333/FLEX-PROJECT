#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib> 
#include <string>
using namespace std;

const int MAX_TEACHERS = 50;
const int MAX_STUDENTS = 30;
const int MAX_SUBJECTS = 8;
// Passwords
string admin_username = "asd";
string admin_password = "123";
// Teacher structure
struct Teacher {
    int id = 0;
    string name = "";
    string subject = "";
    string password = "";
};

Teacher teachers[MAX_TEACHERS];
int teachercount = 0;

struct Student {
    int id = 0;
    string name = "";
    string subjects[MAX_SUBJECTS] = {};
    string password = "";
    int quizzes[MAX_SUBJECTS][2] = {};
    int assignments[MAX_SUBJECTS][3] = {};
    int midterms[MAX_SUBJECTS][2] = {};
    int finalExam[MAX_SUBJECTS] = {};
    float subjectCGPA[MAX_SUBJECTS] = {};
    float cgpa = 0.0f;
    int subjectCount = 0;
    int creditHours[MAX_SUBJECTS] = {};
};

int creditHours[MAX_SUBJECTS] = { 1, 1, 3, 3, 3, 1, 2, 2 };
string subjects[MAX_SUBJECTS] = {
    "ICT",
    "PF Lab",
    "Programming Fundamentals",
    "Calculus",
    "Applied Physics",
    "FE - Lab",
    "Islamic Studies",
    "Functional English"
};

Student students[MAX_STUDENTS];
int studentcount = 0;
int subjectChoice;


void mainmenu();
void adminmenu();
void teachermenu(int teacherIndex);
void studentmenu(int studentIndex);
bool checkpassword(const string& correct_username, const string& correct_password);
int teacherlogin();
void addteacher();
void deleteteacher();
void viewteachers();
void addstudent();
void deletestudent();
bool isValidNumber(const string& input);
void assignmarks(int teacherIndex);
void viewstudentssorted(int teacherIndex);
void listpassedstudents(int teacherIndex);
void listfailedstudents(int teacherIndex);
void calculateAverageSubjectCGPA(int teacherIndex);
void viewstudentgrades(int index);
void viewstudentcgpa(int index);
void calculateClassAverageCGPA();
void viewstudentcgpa(int index);
void saveteacherstofile();
void loadteachersfromfile();
void savestudentstofile();
void calculateCGPA(int index);
void calculateAllStudentsCGPA();
void loadstudentsfromfile();
int studentlogin();
void calculateClassAverageCGPA();
double calculateGrade(double totalMarks);
void calculateSubjectCGPA(int studentIndex, int subjectIndex);

int main() {
    loadteachersfromfile();
    loadstudentsfromfile();
    mainmenu();
    return 0;
}

void mainmenu() {
    int choice;
    int teacherIndex = -1;

    do {
        cout << "                          ******************************************" << endl;
        cout << "                          *                                        *" << endl;
        cout << "                          * STUDENT LEARNING AND MANAGEMENT SYSTEM *" << endl;
        cout << "                          *                                        *" << endl;
        cout << "                          ******************************************" << endl;
        cout << "\n\n\t\t........................... Main Menu ...........................\n\n";
        cout << "\t\t.\t\tPress 1 for Admin : \t\t\t." << endl;
        cout << "\t\t.\t\tPress 2 for Teacher : \t\t\t." << endl;
        cout << "\t\t.\t\tPress 3 for Student : \t\t\t." << endl;
        cout << "\t\t.\t\tPress 4 to EXIT : \t\t\t." << endl;
        cout << "\n\n\t\t.................................................................\n\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin) {
            switch (choice) {
            case 1:
                if (checkpassword(admin_username, admin_password)) {
                    adminmenu();
                    system("cls");
                }
                break;
            case 2:
                teacherIndex = teacherlogin();
                if (teacherIndex != -1) {
                    teachermenu(teacherIndex);
                    system("cls");
                }
                break;
            case 3: {
                int studentIndex = studentlogin();
                if (studentIndex != -1) {
                    studentmenu(studentIndex);
                }
                break;
            }
            case 4:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            system("cls");
        }
    } while (choice != 4);
}

bool checkpassword(const string& correct_username, const string& correct_password) {
    string entered_username, entered_password;

    while (true) {
        cout << "Enter username: ";
        cin >> entered_username;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid username.\n";
            continue;
        }

        cout << "Enter password: ";
        cin >> entered_password;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid password.\n";
            continue;
        }

        if (entered_username == correct_username && entered_password == correct_password) {
            system("cls");
            return true;
        }
        else {
            cout << "Invalid username or password. Please try again.\n";
        }
    }
}

int teacherlogin() {
    int teacher_id;
    while (true) {
        cout << "Enter Teacher ID (4 digits): ";
        cin >> teacher_id;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid Teacher ID.\n";
            continue;
        }

        int index = -1;
        for (int i = 0; i < teachercount; i++) {
            if (teachers[i].id == teacher_id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Teacher ID not found. Please try again.\n";
            continue;
        }

        string entered_password;
        cout << "Enter password for Teacher ID " << teacher_id << ": ";
        cin >> entered_password;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid password.\n";
            continue;
        }

        if (entered_password == teachers[index].password) {
            system("cls");
            cout << "Logged in as " << teachers[index].name << " teaching " << teachers[index].subject << ".\n";
            return index;
        }
        else {
            cout << "Incorrect password. Please try again.\n";
        }
    }
}

int studentlogin() {
    int student_id;

    while (true) {
        cout << "Enter Student ID (4 digits): ";
        cin >> student_id;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid Student ID.\n";
            continue;
        }

        int index = -1;
        for (int i = 0; i < studentcount; i++) {
            if (students[i].id == student_id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Student ID not found. Please try again.\n";
            continue;
        }

        string entered_password;
        cout << "Enter password for Student ID " << student_id << ": ";
        cin.ignore();
        getline(cin, entered_password);

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid password.\n";
            continue;
        }

        if (entered_password == students[index].password) {
            system("cls");
            cout << "Roll Number : " << students[index].id;
            cout << "\nName : " << students[index].name << ".\n";
            return index;
        }
        else {
            cout << "Incorrect password. Please try again.\n";
        }
    }
}

void adminmenu() {
    int choice;
    do {
        cout << "                          *******************************************" << endl;
        cout << "                          *                                         *" << endl;
        cout << "                          *            Admin Menu                   *" << endl;
        cout << "                          *                                         *" << endl;
        cout << "                          *******************************************" << endl;
        cout << "\n\n\t\t.................... Admin Menu ....................\n\n";
        cout << "\t\t.\t\tPress 1 for Add Teacher : \t\t." << endl;
        cout << "\t\t.\t\tPress 2 for Delete Teacher : \t." << endl;
        cout << "\t\t.\t\tPress 3 for View Teachers : \t." << endl;
        cout << "\t\t.\t\tPress 4 to Back : \t\t." << endl;
        cout << "\n\n\t\t...................................................\n\n";

        cout << "Enter your choice: ";
        cin >> choice;
        if (cin) {
            switch (choice) {
            case 1:
                addteacher();
                system("cls");
                break;
            case 2:
                deleteteacher();
                system("cls");
                break;
            case 3:
                viewteachers();
                system("cls");
                break;
            case 4:
                system("cls");
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            system("cls");
        }
    } while (choice != 4);
}

void addteacher() {
    if (teachercount >= MAX_TEACHERS) {
        cout << "Cannot add more teachers. Maximum limit reached.\n";
        return;
    }

    Teacher newTeacher;

    //Validate teacher ID (must be numeric, 1 to 4 digits, and not already exist)
    while (true) {
        cout << "Enter teacher ID (1 to 4 digits): ";
        string input;
        cin >> input;

        //Check if the input is numeric and falls within the valid range for IDs
            bool validId = true;
        if (input.length() >= 1 && input.length() <= 4) {
            for (char c : input) {
                if (!isdigit(c)) {
                    validId = false;
                    break;
                }
            }

            if (validId) {
                newTeacher.id = stoi(input); // Convert the valid string ID to integer
                bool idExists = false;
                for (int i = 0; i < teachercount; i++) {
                    if (teachers[i].id == newTeacher.id) {
                        idExists = true;
                        cout << "Teacher ID already exists. Please enter a different ID.\n";
                        break;
                    }
                }
                if (!idExists) break;
            }
        }

        if (!validId) {
            cout << "Invalid input. Please enter a valid ID with 1 to 4 digits.\n";
        }
    }

    //Ensure the name only contains alphabetic characters
        cin.ignore(); // To clear any leftover input in the buffer
    while (true) {
        cout << "Enter teacher name: ";
        getline(cin, newTeacher.name);

        //Ensure the name only contains alphabetic characters and is not empty
            bool validName = true;
        for (char c : newTeacher.name) {
            if (!(isalpha(c) || c == ' ')) {
                validName = false;
                break;
            }
        }

        if (!newTeacher.name.empty() && validName) {
            break;
        }
        else {
            cout << "Name can contain only alphabetic characters and spaces. Please try again.\n";
        }
    }

    //Subject selection
        int subjectChoice;
    cout << "\nAvailable subjects:\n";
    cout << "1. ICT\n";
    cout << "2. PF Lab\n";
    cout << "3. Programming Fundamentals\n";
    cout << "4. Calculus\n";
    cout << "5. Applied Physics\n";
    cout << "6. FE Lab\n";
    cout << "7. Islamic Studies\n";
    cout << "8. Functional English\n";

    while (true) {
        cout << "Select subject by number: ";
        cin >> subjectChoice;

        if (cin && subjectChoice >= 1 && subjectChoice <= 8) {
            switch (subjectChoice) {
            case 1: newTeacher.subject = "ICT"; break;
            case 2: newTeacher.subject = "PF Lab"; break;
            case 3: newTeacher.subject = "Programming Fundamentals"; break;
            case 4: newTeacher.subject = "Calculus"; break;
            case 5: newTeacher.subject = "Applied Physics"; break;
            case 6: newTeacher.subject = "FE Lab"; break;
            case 7: newTeacher.subject = "Islamic Studies"; break;
            case 8: newTeacher.subject = "Functional English"; break;
            }
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    //Password entry
        while (true) {
            cout << "Enter teacher password: ";
            cin >> newTeacher.password;

            if (cin && !newTeacher.password.empty()) {
                break;
            }
            else {
                cout << "Password cannot be empty. Please try again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

    //Add teacher to the list
        teachers[teachercount++] = newTeacher;
    saveteacherstofile();  // Save the new teacher list to the file

    cout << "Teacher added successfully.\n";
    system("pause");
}

void deleteteacher() {
    int id;
    while (true) {
        cout << "Enter teacher ID to delete (1 to 4 digits): ";
        string input;
        cin >> input;

        //Check if the input is numeric and between 1 and 4 digits long
            bool isValid = true;
        if (input.length() < 1 || input.length() > 4) {
            isValid = false;  // ID length is not valid
        }
        else {
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) {
            //Convert the input to an integer if it's valid
                id = stoi(input);
            break;  // ID is valid, break out of the loop
        }
        else {
            cout << "Invalid input. Please enter a valid numeric ID (1 to 4 digits).\n";
        }
    }

    int index = -1;
    //Search for the teacher by ID
        for (int i = 0; i < teachercount; i++) {
            if (teachers[i].id == id) {
                index = i;
                break;
            }
        }

    if (index == -1) {
        cout << "Teacher not found.\n";
        system("pause");
        return;
    }

    //Shift all teachers after the deleted teacher to the left
        for (int i = index; i < teachercount - 1; i++) {
            teachers[i] = teachers[i + 1];
        }

    teachercount--;  // Decrease the count of teachers

    saveteacherstofile();  // Save the updated list to the file

    cout << "Teacher deleted successfully!\n";
    system("pause");
}

void viewteachers() {
    if (teachercount == 0) {
        cout << "No teacher data is entered.\n";
    }
    else {
        // header
            cout << "+------+-------------------------+--------------------------------+\n";
        cout << "|  ID  |         Name            |             Subject            |\n";
        cout << "+------+-------------------------+--------------------------------+\n";

        //Loop through each teacher and display their information
            for (int i = 0; i < teachercount; i++) {
                cout << "| " << setw(4) << left << teachers[i].id << " | "
                    << setw(23) << left << teachers[i].name << " | "
                    << setw(30) << left << teachers[i].subject << " |\n";
            }


        //Table footer
            cout << "+------+-------------------------+--------------------------------+\n";
    }
    system("pause");
}

void loadteachersfromfile() {
    ifstream file("teacherdata.txt");
    if (file.is_open()) {
        teachercount = 0;
        while (file >> teachers[teachercount].id) {
            file.ignore();
            getline(file, teachers[teachercount].name);
            getline(file, teachers[teachercount].subject);
            getline(file, teachers[teachercount].password);
            teachercount++;
        }
        file.close();
        cout << "Teachers loaded successfully! Total: " << teachercount << "\n";
    }
    else {
        cout << "No teacher data found. Starting fresh.\n";
    }
}

void saveteacherstofile() {
    ofstream file("teacherdata.txt"); // Overwrite the file with updated teacher data
    if (file.is_open()) {
        for (int i = 0; i < teachercount; i++) {
            file << teachers[i].id << "\n"
                << teachers[i].name << "\n"
                << teachers[i].subject << "\n"
                << teachers[i].password << "\n"; // Save the password
        }
        file.close();
        cout << "Teachers saved successfully! Total: " << teachercount << "\n";
    }
    else {
        cout << "Error saving teacher data.\n";
    }
}

void teachermenu(int teacherIndex) {
    int choice;
    do {
        cout << "                          *******************************************" << endl;
        cout << "                          *                                         *" << endl;
        cout << "                          *           Teacher Menu                  *" << endl;
        cout << "                          *                                         *" << endl;
        cout << "                          *******************************************" << endl;
        cout << "\n\n\t\t.................... Teacher Menu ....................\n\n";
        cout << "\t\t.\t\tPress 1 for Add Student : \t\t." << endl;
        cout << "\t\t.\t\tPress 2 for Delete Student : \t." << endl;
        cout << "\t\t.\t\tPress 3 for Assign Marks : \t." << endl;
        cout << "\t\t.\t\tPress 4 for View Students : \t." << endl;
        cout << "\t\t.\t\tPress 5 for List Passed Students : \t." << endl;
        cout << "\t\t.\t\tPress 6 for List Failed Students : \t." << endl;
        cout << "\t\t.\t\tPress 7 for Average CGPA for Subject : \t." << endl;  // New option
        cout << "\t\t.\t\tPress 8 to Back : \t\t." << endl;
        cout << "\n\n\t\t...................................................\n\n";

        cout << "Enter your choice: ";
        cin >> choice;
        if (cin) {
            switch (choice) {
            case 1:
                addstudent();
                system("cls");
                break;
            case 2:
                deletestudent();
                system("cls");
                break;
            case 3:
                assignmarks(teacherIndex);  // Pass teacherIndex here
                system("cls");
                break;
            case 4:
                viewstudentssorted(teacherIndex);  // Pass teacherIndex here
                system("cls");
                break;
            case 5:
                listpassedstudents(teacherIndex);  // Pass teacherIndex here
                system("cls");
                break;
            case 6:
                listfailedstudents(teacherIndex);  // Pass teacherIndex here
                system("cls");
                break;
            case 7:
                calculateAverageSubjectCGPA(teacherIndex);  // Call the new function
                system("cls");
                break;
            case 8:
                system("cls");
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
        else { // Invalid input
            cin.clear();                // Clear error flags
            cin.ignore(1000, '\n');     // Ignore invalid input
            cout << "Invalid input. Please enter a number between 1 and 8.\n";
            system("cls");
        }
    } while (choice != 8);
}

void addstudent() {
    if (studentcount >= MAX_STUDENTS) {
        cout << "Cannot add more students. Maximum limit reached." << endl;
        return;
    }

    Student newStudent;

    // Input unique student ID (1 to 4 digits, i.e., from 1 to 9999)
    while (true) {
        cout << "Enter student ID (1 to 4 digits): ";
        string input;
        cin >> input;

        // Check if the input is numeric and falls between 1 and 9999
        bool isValid = true;
        if (input.length() > 0 && input.length() <= 4) {
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                newStudent.id = stoi(input); // Convert the string to integer

                // Check if ID is between 1 and 9999
                if (newStudent.id >= 1 && newStudent.id <= 9999) {
                    bool idExists = false;
                    for (int i = 0; i < studentcount; i++) {
                        if (students[i].id == newStudent.id) {
                            idExists = true;
                            cout << "Student ID already exists. Please enter a different ID." << endl;
                            break;
                        }
                    }
                    if (!idExists) break; // Exit loop if ID is valid and unique
                }
                else {
                    cout << "Invalid ID. Please enter a number between 1 and 9999." << endl;
                }
            }
        }

        if (!isValid) {
            cout << "Invalid input. Please enter a valid numeric ID between 1 and 9999." << endl;
        }
    }

    cin.ignore(); // Clear newline after ID input

    // Input student name with validation for alphabetic characters and spaces
    while (true) {
        cout << "Enter student name (alphabetic characters and spaces only): ";
        getline(cin, newStudent.name);

        // Ensure the name only contains alphabetic characters and is not empty
        bool validName = true;
        for (char c : newStudent.name) {
            if (!(isalpha(c) || c == ' ')) {
                validName = false;
                break;
            }
        }

        if (!newStudent.name.empty() && validName) {
            break;
        }
        else {
            cout << "Name can contain only alphabetic characters and spaces. Please try again.\n";
        }
    }

    // Input student password
    while (true) {
        cout << "Enter student password: ";
        cin >> newStudent.password;

        if (cin && !newStudent.password.empty()) {
            break;
        }
        else {
            cout << "Password cannot be empty. Please try again." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // Automatically assign subjects and initialize data
    newStudent.subjectCount = MAX_SUBJECTS;  // Assigning all subjects to the student
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        newStudent.subjects[i] = subjects[i];  // Assign default subjects
        newStudent.creditHours[i] = creditHours[i];  // Assign default credit hours
        newStudent.subjectCGPA[i] = 0.0f;  // Initialize CGPA for each subject to 0

        // Initialize all marks to zero
        for (int j = 0; j < 2; j++) {
            newStudent.quizzes[i][j] = 0;  // Initialize quizzes
            newStudent.midterms[i][j] = 0;  // Initialize midterms
        }
        for (int j = 0; j < 3; j++) {
            newStudent.assignments[i][j] = 0;  // Initialize assignments
        }
        newStudent.finalExam[i] = 0;  // Initialize final exam marks
    }

    newStudent.cgpa = 0.0f;  // Initialize total CGPA to 0

    // Add student to the system
    students[studentcount++] = newStudent;
    savestudentstofile();  // Save student data to file

    cout << "Student added successfully." << endl;
    cout << "Students saved successfully! Total: " << studentcount << endl;
    system("pause");
}

void deletestudent() {
    int id, index = -1;
    while (true) {
        cout << "Enter student ID to delete (1 to 4 digits): ";
        string input;
        cin >> input;

        // Check if the input is numeric and between 1 and 9999
        bool isValid = true;
        if (input.length() >= 1 && input.length() <= 4) {
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                id = stoi(input);  // Convert to integer

                // Check if ID is between 1 and 9999
                if (id >= 1 && id <= 9999) {
                    break;  // Exit loop if ID is valid
                }
                else {
                    cout << "Invalid ID. Please enter again." << endl;
                }
            }
        }

        if (!isValid) {
            cout << "Invalid input. Please enter again." << endl;
            cin.clear();  // Reset stream state
            cin.ignore(1000, '\n');  // Skip invalid input
        }
    }

    // Search for the student by ID
    for (int i = 0; i < studentcount; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student not found.\n";
        system("pause");
        return;
    }

    // Shift all students after the deleted student to the left
    for (int i = index; i < studentcount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentcount--;  // Decrease the count of students
    savestudentstofile();  // Save the updated list to the file

    cout << "Student deleted successfully!\n";
    system("pause");
}

double calculateGrade(double totalMarks) {
    if (totalMarks >= 90) return 4.0;  // A (Excellent)
    if (totalMarks >= 80) return 3.5;  // B+ (Good)
    if (totalMarks >= 70) return 3.0;  // B (Average)
    if (totalMarks >= 60) return 2.5;  // C+ (Satisfactory)
    if (totalMarks >= 50) return 2.0;  // C (Pass)
    return 0.0;  // F (Fail)
}

void calculateSubjectCGPA(int studentIndex, int subjectIndex) {
    double totalWeightedMarks = 0.0;
    double totalWeightage = 100.0; // Ensure total weightage adds up to 100

    // Weighted marks for quizzes (Weightage: 10)
    double quizWeightage = 10.0;
    double quizTotalMarks = 0.0;
    for (int i = 0; i < 2; i++) {
        quizTotalMarks += students[studentIndex].quizzes[subjectIndex][i];
    }
    quizTotalMarks = (quizTotalMarks / 20.0) * quizWeightage; // Normalize quiz marks to weightage
    totalWeightedMarks += quizTotalMarks;

    // Weighted marks for assignments (Weightage: 10)
    double assignmentWeightage = 10.0;
    double assignmentTotalMarks = 0.0;
    for (int i = 0; i < 3; i++) {
        assignmentTotalMarks += students[studentIndex].assignments[subjectIndex][i];
    }
    assignmentTotalMarks = (assignmentTotalMarks / 300.0) * assignmentWeightage; // Normalize assignment marks
    totalWeightedMarks += assignmentTotalMarks;

    // Weighted marks for midterms (Weightage: 30)
    double midtermWeightage = 30.0;
    double midtermTotalMarks = 0.0;
    for (int i = 0; i < 2; i++) {
        midtermTotalMarks += students[studentIndex].midterms[subjectIndex][i];
    }
    midtermTotalMarks = (midtermTotalMarks / 100.0) * midtermWeightage; // Normalize midterm marks
    totalWeightedMarks += midtermTotalMarks;

    // Weighted marks for final exam (Weightage: 50)
    double finalExamWeightage = 50.0;
    double finalExamMarks = students[studentIndex].finalExam[subjectIndex];
    finalExamMarks = (finalExamMarks / 100.0) * finalExamWeightage; // Normalize final exam marks
    totalWeightedMarks += finalExamMarks;

    // Calculate CGPA for the subject based on weighted total marks
    students[studentIndex].subjectCGPA[subjectIndex] = calculateGrade(totalWeightedMarks);
}

bool isValidNumber(const string& input) {
    // Check if the string contains only digits
    for (char c : input) {
        if (!isdigit(c)) {
            return false;  // Contains non-digit characters
        }
    }
    return true;
}

void assignmarks(int teacherIndex) {
    string subject = teachers[teacherIndex].subject;  // Get the teacher's subject
    int subjectIndex = -1;

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        if (subjects[i] == subject) {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1) {
        cout << "Error: Subject not found.\n";
        return;
    }

    cout << "Teacher " << teachers[teacherIndex].name << " is assigning marks for " << subject << ".\n";

    int studentID, studentIndex = -1;
    string inputID;

    cout << "Enter Student ID to assign marks: ";

    // Ensure the ID is valid and exists in the system
    while (true) {
        cin >> inputID;
        if (isValidNumber(inputID)) {
            studentID = stoi(inputID);
            for (int i = 0; i < studentcount; i++) {
                if (students[i].id == studentID) {
                    studentIndex = i;
                    break;
                }
            }
        }

        if (studentIndex == -1) {
            cout << "Invalid Student ID. Please enter a valid ID." << endl;
        }
        else {
            break;  // Exit loop when valid ID is entered
        }
    }

    // Assign marks for quizzes, assignments, midterms, and final exam
    double quizMarks[2], assignmentMarks[3], midtermMarks[2], finalExamMarks;
    cout << "Enter quiz marks (out of 10 for each): ";
    for (int i = 0; i < 2; i++) {
        cin >> quizMarks[i];
        students[studentIndex].quizzes[subjectIndex][i] = quizMarks[i];
    }

    cout << "Enter assignment marks (out of 100 for each): ";
    for (int i = 0; i < 3; i++) {
        cin >> assignmentMarks[i];
        students[studentIndex].assignments[subjectIndex][i] = assignmentMarks[i];
    }

    cout << "Enter midterm marks (out of 100 for each): ";
    for (int i = 0; i < 2; i++) {
        cin >> midtermMarks[i];
        students[studentIndex].midterms[subjectIndex][i] = midtermMarks[i];
    }

    cout << "Enter final exam marks (out of 100): ";
    cin >> finalExamMarks;
    students[studentIndex].finalExam[subjectIndex] = finalExamMarks;

    // Recalculate subject CGPA after assigning marks
    calculateSubjectCGPA(studentIndex, subjectIndex);
    cout << "Marks assigned successfully!" << endl;
}

void viewstudentssorted(int teacherIndex) {
    string subject = teachers[teacherIndex].subject;

    cout << "\n+-----------------------------------+\n";
    cout << "|             Students              |\n";
    cout << "+-----------------------------------+\n";

    cout << "+------------+----------------------+\n";
    cout << "| Student ID |          Name        |\n";
    cout << "+------------+----------------------+\n";

    bool found = false;

    // Iterate through students to find those enrolled in the teacher's subject
    for (int i = 0; i < studentcount; i++) {
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            if (students[i].subjects[j] == subject && !students[i].subjects[j].empty()) {
                cout << "| " << setw(10) << left << students[i].id << " | "
                    << setw(20) << left << students[i].name << " |\n";
                found = true;
                break; // Stop searching once the student is found
            }
        }
    }

    // Display a message if no students are found for the subject
    if (!found) {
        cout << "| No students found for this subject |\n";
    }

    cout << "+------------+----------------------+\n";
    system("pause");
}

void listpassedstudents(int teacherIndex) {
    string subject = teachers[teacherIndex].subject;

    cout << "\n+------------------------------------------------------+\n";
    cout << "|             List of Passed Students                  |\n";
    cout << "+------------------------------------------------------+\n";

    cout << "+------------+----------------------+------------------+\n";
    cout << "| Student ID |          Name        |  CGPA in Subject |\n";
    cout << "+------------+----------------------+------------------+\n";

    bool found = false;

    // Iterate through students to list those who passed the subject
    for (int i = 0; i < studentcount; i++) {
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            if (students[i].subjects[j] == subject && !students[i].subjects[j].empty() &&
                students[i].subjectCGPA[j] >= 2.0f) {
                cout << "| " << setw(10) << left << students[i].id << " | "
                    << setw(20) << left << students[i].name << " | "
                    << setw(16) << left << students[i].subjectCGPA[j] << " |\n";
                found = true;
                break; // Stop searching once the student is found
            }
        }
    }

    // If no passed students are found, display a message
    if (!found) {
        cout << "|            No passed students found.                 |\n";
    }

    cout << "+------------+----------------------+------------------+\n";
    system("pause");
}

void listfailedstudents(int teacherIndex) {
    string subject = teachers[teacherIndex].subject;

    cout << "\n+------------------------------------------------------+\n";
    cout << "|             List of Failed Students                  |\n";
    cout << "+------------------------------------------------------+\n";

    cout << "+------------+----------------------+------------------+\n";
    cout << "| Student ID |          Name        |  CGPA in Subject |\n";
    cout << "+------------+----------------------+------------------+\n";

    bool found = false;

    // Iterate through students to list those who failed the subject
    for (int i = 0; i < studentcount; i++) {
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            if (students[i].subjects[j] == subject && !students[i].subjects[j].empty() &&
                students[i].subjectCGPA[j] < 2.0f) {
                cout << "| " << setw(10) << left << students[i].id << " | "
                    << setw(20) << left << students[i].name << " | "
                    << setw(16) << left << students[i].subjectCGPA[j] << " |\n";
                found = true;
                break; // Stop searching once the student is found
            }
        }
    }

    // If no failed students are found, display a message
    if (!found) {
        cout << "|            No failed students found.                 |\n";
    }

    cout << "+------------+----------------------+------------------+\n";
    system("pause");
}

void calculateAverageSubjectCGPA(int teacherIndex) {
    string subject = teachers[teacherIndex].subject;
    int subjectIndex = -1;

    // Find the index of the teacher's subject
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        if (subjects[i] == subject) {
            subjectIndex = i;
            break;
        }
    }

    // Display error if subject not found
    if (subjectIndex == -1) {
        cout << "Error: Subject not found.\n";
        system("pause");
        return;
    }

    double totalCGPA = 0.0;
    int studentCount = 0;

    // Calculate the total CGPA for students in the subject
    for (int i = 0; i < studentcount; i++) {
        bool isStudentInSubject = false;

        // Check if the student is enrolled in the teacher's subject
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            if (students[i].subjects[j] == subject) {
                isStudentInSubject = true;
                break;
            }
        }

        // Add CGPA for students enrolled in the subject
        if (isStudentInSubject) {
            totalCGPA += students[i].subjectCGPA[subjectIndex];
            studentCount++;
        }
    }

    // Calculate and display the average CGPA
    if (studentCount > 0) {
        double averageCGPA = totalCGPA / studentCount;
        cout << "Average CGPA for subject " << subject << ": " << averageCGPA << endl;
    }
    else {
        cout << "No students found for the subject " << subject << ".\n";
    }
    system("pause");
}

void loadstudentsfromfile() {
    ifstream file("studentdata.txt");
    if (file.is_open()) {
        studentcount = 0;  // Reset the student count
        while (file >> students[studentcount].id) {  // Read student ID
            file.ignore();  // Ignore newline or space after the ID
            getline(file, students[studentcount].name);  // Read student name
            getline(file, students[studentcount].password);  // Read student password

            // Read subjects and associated data
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                getline(file, students[studentcount].subjects[i]);  // Read subject name

                // Read quizzes
                for (int j = 0; j < 2; j++) {
                    file >> students[studentcount].quizzes[i][j];
                }
                file.ignore();  // Ignore newline after quizzes

                // Read assignments
                for (int j = 0; j < 3; j++) {
                    file >> students[studentcount].assignments[i][j];
                }
                file.ignore();  // Ignore newline after assignments

                // Read midterms
                for (int j = 0; j < 2; j++) {
                    file >> students[studentcount].midterms[i][j];
                }
                file.ignore();  // Ignore newline after midterms

                // Read final exam and subject CGPA
                file >> students[studentcount].finalExam[i];
                file >> students[studentcount].subjectCGPA[i];
                file.ignore();  // Ignore newline after final exam and CGPA
            }
            studentcount++;
        }
        file.close();
        cout << "Students loaded successfully! Total: " << studentcount << "\n";
    }
    else {
        cout << "No student data found. Starting fresh.\n";
    }
}


void savestudentstofile() {
    ofstream file("studentdata.txt", ios::out | ios::trunc);
    if (file.is_open()) {
        for (int i = 0; i < studentcount; i++) {
            file << students[i].id << "\n"
                << students[i].name << "\n"
                << students[i].password << "\n";

            for (int j = 0; j < MAX_SUBJECTS; j++) {
                file << students[i].subjects[j] << "\n";

                // Write quizzes
                for (int k = 0; k < 2; k++) {
                    file << students[i].quizzes[j][k] << " ";
                }
                file << "\n";

                // Write assignments
                for (int k = 0; k < 3; k++) {
                    file << students[i].assignments[j][k] << " ";
                }
                file << "\n";

                // Write midterms
                for (int k = 0; k < 2; k++) {
                    file << students[i].midterms[j][k] << " ";
                }
                file << "\n";

                // Write final exam and CGPA
                file << students[i].finalExam[j] << " "
                    << students[i].subjectCGPA[j] << "\n";
            }
        }
        file.close();
        cout << "Students saved successfully!\n";
    }
    else {
        cout << "Error saving student data.\n";
    }
}


void studentmenu(int studentIndex) {
    int choice;
    do {
        cout << "                          *******************************************" << endl;
        cout << "                          *                                         *" << endl;
        cout << "                          *           Student Menu                  *" << endl;
        cout << "                          *                                         *" << endl;
        cout << "                          *******************************************" << endl;
        cout << "\n\n\t\t.................... Student Menu ....................\n\n";
        cout << "\t\t.\t\tPress 1 to View My Grades : \t\t." << endl;
        cout << "\t\t.\t\tPress 2 to View My CGPA : \t\t." << endl;
        cout << "\t\t.\t\tPress 3 to Back to Main Menu : \t." << endl;
        cout << "\n\n\t\t...................................................\n\n";

        cout << "Enter your choice: ";
        cin >> choice;
        if (cin) {
            switch (choice) {
            case 1:
                viewstudentgrades(studentIndex);
                system("cls");
                break;
            case 2:
                loadstudentsfromfile();
                calculateAllStudentsCGPA();
                viewstudentcgpa(studentIndex);
                system("cls");
                break;
            case 3:
                system("cls");
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            system("cls");
        }
    } while (choice != 3);
}

void viewstudentgrades(int index) {
    if (index < 0 || index >= studentcount) {
        cout << "Invalid student index.\n";
        return;
    }

    cout << "+----------------------------+------------+--------------------+-------------+--------------+----------------+ \n";
    cout << "|          Subject           |   Quizzes  |     Assignments    |   Midterms  |  Final Exam  | Subject CGPA   | \n";
    cout << "|                            |   1  |   2 |   1  |   2  |   3  |   1  |   2  |              |                | \n";
    cout << "+----------------------------+------------+--------------------+-------------+--------------+----------------+ \n";

    string subjectNames[MAX_SUBJECTS] = {
        "ICT                       ", "PF Lab                    ", "Programming Fundamentals  ", "Calculus                  ", "Applied Physics           ",
        "FE - Lab                  ", "Islamic Studies           ", "Functional English        "
    };


    for (int j = 0; j < MAX_SUBJECTS; j++) {
        cout << "| " << subjectNames[j] << " | ";

        for (int q = 0; q < 2; q++) {
            cout << setw(4) << students[index].quizzes[j][q] << setw(5);
        }
        cout << " | ";

        for (int a = 0; a < 3; a++) {
            cout << setw(5) << students[index].assignments[j][a] << setw(6);
        }
        cout << "| ";

        for (int m = 0; m < 2; m++) {
            cout << setw(5) << students[index].midterms[j][m] << setw(4);
        }
        cout << "| ";


        cout << setw(12) << students[index].finalExam[j]
            << " | " << setw(15) << fixed << setprecision(2) << students[index].subjectCGPA[j] << "|" << endl;
    }

    cout << "+----------------------------+------------+--------------------+-------------+--------------+----------------+ \n";
    system("pause");
}

void calculateCGPA(int index) {
    float totalWeightedCGPA = 0.0f;
    float totalCreditHours = 0.0f;

    // Iterate over each subject for the student
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        totalWeightedCGPA += students[index].subjectCGPA[i] * creditHours[i]; // Weighted by credit hours
        totalCreditHours += creditHours[i]; // Sum of credit hours
    }

    // Calculate the final CGPA for the student
    if (totalCreditHours > 0) {
        students[index].cgpa = totalWeightedCGPA / totalCreditHours; // CGPA = weighted average
    }
    else {
        students[index].cgpa = 0.0f; // Default CGPA if no subjects
    }
}

// Function to calculate CGPA for all students
void calculateAllStudentsCGPA() {
    for (int i = 0; i < studentcount; i++) {
        calculateCGPA(i);  // Calculate CGPA for each student
    }
}
// Function to calculate and display the class average CGPA
void calculateClassAverageCGPA() {
    float totalCGPA = 0.0f;
    int studentCount = 0;

    // Iterate over all students and accumulate their CGPAs
    for (int i = 0; i < studentcount; i++) {
        totalCGPA += students[i].cgpa; // Add the student's CGPA
        studentCount++;
    }

    // Calculate and display the class average CGPA
    if (studentCount > 0) {
        float averageCGPA = totalCGPA / studentCount;
        cout << "The average CGPA for your batch is: " << fixed << setprecision(2) << averageCGPA << endl;
    }
    else {
        cout << "No students found to calculate class average CGPA.\n";
    }
}

// Function to display CGPA for a student
void viewstudentcgpa(int index) {
    if (index < 0 || index >= studentcount) {
        cout << "Invalid student index.\n";
        return;
    }

    // Calculate CGPA for the selected student
    calculateCGPA(index);

    // Display the student's CGPA
    cout << "Hi " << students[index].name << endl;
    cout << "Your CGPA for this semester is: "
        << fixed << setprecision(2) << students[index].cgpa << endl;

    // Display the class average CGPA
    calculateClassAverageCGPA();

    system("pause");
}