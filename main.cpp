#include <iostream>
#include <string>

using namespace std;

struct student {
    string id;
    double percent;
    char grade;
};

class Exams {
    public: 
        Exams();
        bool isIDCompat(string id);
        bool examAnsCompat();
        bool getStatus();
        char grade(double score);
        double score(string studentAns);
        int stringToNum(string stdID, int i);
        void loop();
        
    private:
        bool DEBUG;
        bool status;
        double getAvg(double x[]);
        double getHigh(double x[]);
        double getLow(double x[]);
        double studentScore;
        int examLength;
        int numStudents;
        string answerKey;
        string currentID;
        void displayStats(struct student students[]);
        void displayStudent(struct student students);
};

Exams::Exams(){
    DEBUG = true;
    status = true;
    answerKey = "";
    numStudents = 0;
    cout << "Answer key = ";
    cin >> answerKey;
    if ((examLength = answerKey.size()) > 0){
        if (examAnsCompat()){
            if (DEBUG)
                cout << "Successful save of answerKey" << "\nexamLength =" << examLength << endl;
        }
        else{
            cout << "Exam Solution was incompatible" << endl;
            status = false;
            return;
        }
    }
    cout << "Enter the number of students to be graded: ";
    cin >> numStudents;
    if(numStudents > 0){
        
        if (DEBUG)
            cout << "Successful save of numStudents" << endl;
    } else {
        cout << "Number of students was incompatible" << endl;
        status = false;
        return;
    }
}

bool Exams::getStatus(){
    return status;
}

void Exams::loop(){
    struct student students[numStudents];
    currentID = "";
    string studentEXAM;
    int studentScore;
    char studentGrade;
    for (int i = 0; i < numStudents; i++){
        cout << "Student " << i + 1 << " ID:";
        cin >> currentID;
        if(!isIDCompat(currentID)){
            cout << "Error, Incompatible ID" << endl;
            cout << "ID must be 7 digits" << endl;
            cout << "Re-enter ID: " << endl;
            i--;
            continue;
        }
        cout << "Student Exam :";
        cin >> studentEXAM;
        studentScore = score(studentEXAM);
        studentGrade = grade(studentScore);
        students[i].id = currentID;
        students[i].percent = studentScore;
        students[i].grade = studentGrade;
        displayStudent(students[i]);
    }
    displayStats(students);
}

int Exams::stringToNum(string stdID, int i){
    switch (stdID.at(i)){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -1;
    }
}

bool Exams::isIDCompat(string stdID){
    bool compat = false;
    int num = 0;
    if (stdID.length() == 7) {
        for (int i = 0; i < 7; i++){
            if (stringToNum(stdID, i) >= 0)
                num++;
        }   
    }
    
    if (num == 7)
        compat = true;
    if (DEBUG && compat)
            cout << "Successful save of student ID" << endl;
    return compat;
}

bool Exams::examAnsCompat(){
    int count = 0;
    for (int i = 0; i < examLength; i++){
        if (answerKey.at(i) >= 97 && answerKey.at(i) <= 102){
            count++;
        }
    }
    if (count == examLength)
        return true;
    else
        return false;
}

double Exams::score(string studentAns){
    int temp = 0;
    int testLength = studentAns.length();
    if (testLength >= examLength){
        for (int i = 0; i < examLength; i++){
            if (studentAns.at(i) == answerKey.at(i)){
                temp++;
            }
        }
    } else {
        for (int i = 0; i < testLength; i++){
            if (studentAns.at(i) == answerKey.at(i)){
                temp++;
            }
        }
    }
    return (double)temp/(double)examLength * 100.0;
}

char Exams::grade(double score){
    if (score >= 90.0)
        return 'A';
    else if (score >= 80.0)
        return 'B';
    else if (score >= 70.0)
        return 'C';
    else if (score >= 60.0)
        return 'D';
    else if (score >= 50.0)
        return 'E';
    else if (score < 50.0)
        return 'F';
    else
        return 'G';
}

void Exams::displayStudent(struct student students){
    cout << "Score: " << students.percent << "% " << students.grade << endl;
}

void Exams::displayStats(struct student students[]){
    double x[numStudents];
    for (int i = 0; i < numStudents; i++){
        x[i] = students[i].percent;
    }
    cout << "Average Score: " << (int)getAvg(x) << endl;
    cout << "High Score: " << (int)getHigh(x) << endl;
    cout << "Low Score: " << (int)getLow(x) << endl;
}

double Exams::getHigh(double x[]){
    double high = 0;
    for (int i = 0; i < numStudents; i++){
        if (x[i] > high)
            high = x[i];
    }
    return high;
}

double Exams::getLow(double x[]){
    double low = 100;
    for (int i = 0; i < numStudents; i++){
        if (x[i] < low)
            low = x[i];
    }
    return low;
}

double Exams::getAvg(double x[]){
    double total = 0;
    for (int i = 0; i < numStudents; i++){
        total += x[i];
    }
    return total/numStudents;
}

int main(){
    Exams exam;
    if (exam.getStatus())
        exam.loop();
    else
        return 1;
    return 0;
}