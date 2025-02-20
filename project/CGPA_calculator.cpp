#include <bits/stdc++.h>
#include <fstream>
using namespace std;
pair<string, float> calculateGrade(float marks)
{
    if (marks >= 80)
        return {"A+", 4.0};
    if (marks >= 75)
        return {"A", 3.75};
    if (marks >= 70)
        return {"A-", 3.5};
    if (marks >= 65)
        return {"B+", 3.25};
    if (marks >= 60)
        return {"B", 3.0};
    if (marks >= 55)
        return {"B-", 2.75};
    if (marks >= 50)
        return {"C+", 2.5};
    if (marks >= 45)
        return {"C", 2.25};
    if (marks >= 40)
        return {"D", 2.0};
    return {"F", 0.0};
}
class CGPACalculator
{
private:
    string studentName;
    string studentRoll;
    int currentSemester;
    vector<int> numSubjects;
    vector<vector<float>> subjectMarks;
    vector<vector<float>> subjectCredits;
    vector<float> semesterCGPA;
    vector<float> semesterTotalCredits;
    float totalpointsecured = 0;
    float TotalCredit = 0;

public:
    void displayTitleAndInstructions()
    {
        cout << "******************* CGPA Calculator *******************" << endl;
        cout << "-------------------------------------------------------" << endl;
        // cout << fixed << setprecision(2);
        cout << "Instructions: " << endl;
        cout << "1. Enter the student's name and roll number." << endl;
        cout << "2. Enter the total number of semesters to calculate the CGPA." << endl;
        cout << "3. For each semester:" << endl;
        cout << " a. Enter the number of subjects in the semester." << endl;
        cout << " b. For each subject:" << endl;
        cout << " i. Enter the marks obtained." << endl;
        cout << " ii. Enter the corresponding credit hours." << endl;
        cout << "4. The program will display:" << endl;
        cout << " - Grade and grade point for each subject." << endl;
        cout << " - Total credits of the semester." << endl;
        cout << " - CGPA for the semester." << endl;
        cout << fixed << setprecision(2) << "5. The overall CGPA will be calculated based on the total grade points and total credits across all semesters." << endl;
        cout << fixed << setprecision(2) << "6. The results will be saved to a text file named 'CGPA_Result.txt' for future reference." << endl;
        cout << fixed << setprecision(2) << "-------------------------------------------------------" << endl;
        cout << "Press Enter to continue..." << endl;
    }
    void inputDetails()
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("clear");
        cout << "Enter the student's name: ";
        getline(cin, studentName);
        cout << "Enter the student's roll number: ";
        getline(cin, studentRoll);
        cout << "Enter the number of semesters: ";
        cin >> currentSemester;
        cout << "\n";
        numSubjects.resize(currentSemester);
        subjectMarks.resize(currentSemester);
        subjectCredits.resize(currentSemester);
        semesterCGPA.resize(currentSemester);
        semesterTotalCredits.resize(currentSemester);
        for (int i = 0; i < currentSemester; ++i)
        {

            cout
                << "For Semester " << i + 1 << ":\n";
            cout << "Enter the number of subjects: ";
            cin >> numSubjects[i];
            subjectMarks[i].resize(numSubjects[i]);
            subjectCredits[i].resize(numSubjects[i]);
            semesterTotalCredits[i] = 0;
            for (int j = 0; j < numSubjects[i]; ++j)
            {
                float totalWeightedGrade = 0;
                cout << "Enter marks for Subject " << j + 1 << ": ";
                cin >> subjectMarks[i][j];
                cout << "Enter credit hours for Subject " << j + 1 << ": ";
                cin >> subjectCredits[i][j];
                pair<string, float> gradeInfo = calculateGrade(subjectMarks[i][j]);
                string grade = gradeInfo.first;
                float gradePoint = gradeInfo.second;
                cout << "Subject " << j + 1 << ": Marks = " << subjectMarks[i][j]
                     << ", Grade = " << grade << ", Grade Point = " << gradePoint
                     << ", Credits = " << subjectCredits[i][j] << endl;
                totalWeightedGrade += gradePoint * subjectCredits[i][j];
                semesterTotalCredits[i] += subjectCredits[i][j];
                cout << "Points Secured " << totalWeightedGrade << endl;
                totalpointsecured += totalWeightedGrade;
            }
            TotalCredit += semesterTotalCredits[i];
            cout << "Total Credit of the Semester: " << semesterTotalCredits[i] << endl;
            cout << "Total CGPA of the Semester: " << totalpointsecured / semesterTotalCredits[i] << endl;
            cout << endl;
        }
    }
    void saveToFile()
    {
        system("clear");
        ofstream file("CGPA_Result.txt");
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        file << "Student Name: " << studentName << endl;
        file << "Roll Number: " << studentRoll << endl;
        file << "Total Semester: " << currentSemester << endl;
        for (int i = 0; i < currentSemester; ++i)
        {
            file << "\nSemester " << i + 1 << " Results:\n";
            for (int j = 0; j < numSubjects[i]; ++j)
            {
                pair<string, float> gradeInfo = calculateGrade(subjectMarks[i][j]);
                string grade = gradeInfo.first;
                float gradePoint = gradeInfo.second;
                file << "\t Subject " << j + 1 << ":\n\t\t Marks = " << subjectMarks[i][j]
                     << ",\n\t\t Grade = " << grade << ",\n\t\t Grade Point = " << gradePoint
                     << ",\n\t\t Credits = " << subjectCredits[i][j] << endl;
            }
            cout << endl;
            file << "Total Credit of the Semester: " << semesterTotalCredits[i] << endl;
            file << "Total CGPA of the Semester: " << totalpointsecured / semesterTotalCredits[i] << endl;
        }
        file << "\nOverall CGPA: " << fixed << setprecision(2) << totalpointsecured / TotalCredit << endl;
        file << "Total Points Secured: " << fixed << setprecision(2) << totalpointsecured << endl;
        file << "Semester Total Credit: " << fixed << setprecision(2) << TotalCredit << endl;
        file.close();
    }
    void displayFooter()
    {
        system("clear");
        cout << "-------------------------------------------------------" << endl;
        cout << "Result saved Successfully in .txt file" << endl;
        cout << "Result will be shown in the .txt file" << endl;
        cout << "-------------------------------------------------------\n\n\n"
             << endl;
        cout
            << "CGPA Calculator was made by \n Arman \n Roll : 230623 \n Reg : 1065512 \n Department of Information and Communication Engineering \n Pabna University of Science and Technology \n \n \n " << endl;
        cout
            << "-------------------------------------------------------" << endl;
    }
};
int main()
{
    CGPACalculator calculator;
    calculator.displayTitleAndInstructions();
    calculator.inputDetails();
    calculator.saveToFile();
    calculator.displayFooter();
    return 0;
}