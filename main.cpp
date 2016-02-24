#include <iostream>
#include <string>

using namespace std;

class Exams {
    public: 
        Exams();
        bool isIDCompat(string id);
        double score();
        char grade();
        void loop();
        string getInput();
        int stringToNum(int i);
        
    private:
        string answerKey;
        string currentID;
        double studentScore;
        string buffer[100];
        void displayStats();
        int numStudents;
        bool DEBUG = true;
};

Exams::Exams(){
    answerKey = "";
    numStudents = 0;
    cout << "Answer key = ";
    cin >> answerKey;
    if (answerKey.size() > 0){
        if (DEBUG)
            cout << "Successful save of answerKey" << endl;
    }
    cout << "Enter the number of students to be graded: ";
    cin >> numStudents;
    if(numStudents > 0){
        if (DEBUG)
            cout << "Successful save of numStudents" << endl;
    }
}

void Exams::loop(){
    currentID = "";
    for (int i = 0; i < numStudents; i++){
        cout << "Student " << i + 1 << " ID:";
        cin >> currentID;
        if(isIDCompat())
            continue;
        else {
            cout << "Error, Incompatible ID" << endl;
            cout << "ID must be 7 digits" << endl;
            cout << "Re-enter ID: " << endl;
            i--;
        }
    }
}

int Exams::stringToNum(int i){
    switch (currentID.at(i)){
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

bool Exams::isIDCompat(){
    bool compat = false;
    int num = 0;
    for (int i = 0; i < 7; i++){
        if (stringToNum(i) >= 0)
            num++;
    }    
    if (num == 7 && currentID.length() == 7)
        compat = true;
    if (DEBUG && compat)
            cout << "Successful save of student ID" << endl;
    return compat;
}

int main(){
    Exams exam;
    exam.loop();
    return 0;
}