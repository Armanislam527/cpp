#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <sstream>
#include <vector>

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonCalculate, &QPushButton::clicked, this, &MainWindow::calculateCGPA);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateCGPA()
{
    // Get input values
    QString name = ui->lineEditName->text();
    QString roll = ui->lineEditRoll->text();
    int numSemesters = ui->spinBoxSemesters->value();
    QString gradesInput = ui->textEditGrades->toPlainText();

    if (name.isEmpty() || roll.isEmpty() || gradesInput.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter all details.");
        return;
    }

    vector<float> grades;
    vector<float> credits;
    float totalPoints = 0.0, totalCredits = 0.0;

    // Parse grades input
    stringstream ss(gradesInput.toStdString());
    string line;
    while (getline(ss, line, '\n'))
    {
        stringstream subjectStream(line);
        float marks, credit;
        if (subjectStream >> marks >> credit)
        {
            auto gradeInfo = calculateGrade(marks);
            grades.push_back(gradeInfo.second);
            credits.push_back(credit);
            totalPoints += gradeInfo.second * credit;
            totalCredits += credit;
        }
    }

    float cgpa = (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;

    // Display result
    QString result = "Student Name: " + name + "\n";
    result += "Roll Number: " + roll + "\n";
    result += "Overall CGPA: " + QString::number(cgpa, 'f', 2) + "\n";

    ui->labelResult->setText(result);
}
