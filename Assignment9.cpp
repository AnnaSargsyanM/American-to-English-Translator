//****************************************************************************************************
//     File:               Assignment9.cpp
// 
//     Student:            Anna Sargsyan
// 
//     Assignment:         Program #9
// 
//     Course Name:        Programming II
// 
//     Course Number:      COSC 1560-01
// 
//     Due:                November 13, 2023
//
//     This program translates from American to English.
//
//****************************************************************************************************

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

struct Translation
{
    string american;
    string english;  
};

struct Date
{
    int day;
    int month;
    int year;
};

struct Person
{
    char name[20];
    double score;
    Date testTaken;
};

Translation* readTranslation(const string& , int&);
Person* readTesters(const string&, int&);
void testingOptions(const Translation[], int, Person[], int);
void takeTest(const Translation[], int, Person&);
void displayTesters(const Person[], int);
void writeTesters(const string&, const Person[], int);

//****************************************************************************************************

int main()
{
    srand(static_cast<unsigned>(time(0)));

    int numTranslations;
    Translation* translations = readTranslation("Translation.txt", 
        numTranslations);

    if (translations == nullptr)
    {
        cout << "Error reading translations." << endl;
        return 1; 
    }

    int numTesters;
    Person* testers = readTesters("Testers.txt", numTesters);

    if (testers == nullptr)
    {
        cout << "Error reading testers." << endl;
        delete[] translations;
        return 1; 
    }

    testingOptions(translations, numTranslations, testers, numTesters);

    displayTesters(testers, numTesters);

    writeTesters("UpdatedTesters.txt", testers, numTesters);

    delete[] translations;
    delete[] testers;

    return 0;
}


//****************************************************************************************************

Translation* readTranslation(const string& filename, int& num)
{
    ifstream file(filename, ios::in);
  
    file >> num;
    file.ignore();
        
    Translation* translations = new Translation[num];

    for (int i = 0; i < num; i++)
    {
        getline(file, translations[i].american, ',');
        getline(file, translations[i].english);
    }

    file.close();

    return translations;
}

//****************************************************************************************************

Person* readTesters(const string& filename, int& num)
{
    ifstream file(filename);
    Person* testers = nullptr;

    if (file.fail())
    {
        cout << "File " << filename << "doesn't exist." << endl;
    }

    else
    {
        file >> num;
        file.ignore();

        testers = new Person[num];

        for (int i = 0; i < num; i++)
        {
            //file.ignore(); 
            file.getline(testers[i].name, sizeof(testers[i].name));
            //testers[i].name[sizeof(testers[i].name) - 1] = '\0';  
            file >> testers[i].score;
            file.ignore();
            file >> testers[i].testTaken.day;
            file.ignore();
            file >> testers[i].testTaken.month;
            file.ignore();
            file >> testers[i].testTaken.year;
            file.ignore();
        }

        file.close();
    }
    
    return testers;
}

//****************************************************************************************************

void testingOptions(const Translation t[], int numT, Person people[], int numP)
{
    Date currentDate;

    cout << "Enter the current day(Month/Day/Year): ";
    cin >> currentDate.month;
    cin.ignore();
    cin >> currentDate.day;
    cin.ignore();
    cin >> currentDate.year;

    int randomIndex = rand() % numP;
    takeTest(t, numT, people[randomIndex]);
}

//****************************************************************************************************

void takeTest(const Translation t[], int numT, Person& p)
{
    const int numQuestions = 5;

    double totalScore = 0;

    for (int questionCount = 0; questionCount < numQuestions; questionCount++)
    {
        int randomIndex = rand() % numT;
        string question = t[randomIndex].american;
        string answer;

        cout << "Translate '" << question << "' to English: ";
        cin >> answer;

        if (answer == t[randomIndex].english)
        {
            cout << "Correct!" << endl;
            totalScore ++;
        }
        else
        {
            cout << "Incorrect. The correct translation is: '"
                << t[randomIndex].english << "'" << endl;
        }
    }

    p.score = totalScore;
 

}

//****************************************************************************************************

void displayTesters(const Person p[], int numP)
{
    cout << "Testers Information:\n\n";
    cout << left << setw(20) << "Name" << setw(10) << "Score" << "Test Taken Date\n\n";

    for (int i = 0; i < numP; i++)
    {
        cout << left << setw(20) << p[i].name << setw(10) << p[i].score << p[i].testTaken.day 
            << " " << p[i].testTaken.month << " " 
            << p[i].testTaken.year << "\n";
    }
}

//****************************************************************************************************

void writeTesters(const string& filename, const Person testers[], int numP)
{
    ofstream file(filename);
    if (file.fail())
    {
        cout << "File " << filename << "doesn't exist." << endl;
    }

    else
    {
        file << numP << endl; 

        for (int i = 0; i < numP; i++)
        {
            file << testers[i].name << endl;
            file << testers[i].score << "," <<  testers[i].testTaken.month << "/" << testers[i].testTaken.day << 
                "/" << testers[i].testTaken.year << endl;
        }

        file.close();
    }    
}

//****************************************************************************************************
/*

Enter the current day : 13
Enter the current month : 12
Enter the current year : 2023
Translate 'pants' to English : trousers
Correct!
Translate 'pants' to English : trousers
Correct!
Translate 'cookie' to English : biscuit
Correct!
Translate 'restroom' to English : toilet
Correct!
Translate 'sidewalk' to English : pavement
Correct!
Translate 'hood' to English :

*/


