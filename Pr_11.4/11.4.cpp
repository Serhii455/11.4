#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <fstream>
using namespace std;


struct Note {
    char lastName[60];
    char firstName[60];
    long long int phoneNumber;
    int birthdate[3];
};


void Input_Data(string filename);
void Print_Data(string filename);
void Bubble_Sort(string filename);
void People_SearchFor_Month(string filename, int searchMonth);



int main() {
    int searchMonth;
    string filename;

    cout << "Input name of file: "; cin >> filename;


    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose exercise" << endl << endl;
        cout << " [1] - Input data from keyboard and print" << endl;
        cout << " [2] - Print data in display" << endl;
        cout << " [3] - Print sorted data" << endl;
        cout << " [4] - Search from month" << endl;
        cout << " [0] - Exit" << endl << endl;
        cout << "Input value: "; cin >> menuItem;
        cout << endl << endl << endl;


        switch (menuItem) {
        case 1:
            Input_Data(filename);
            break;
        case 2:
            Print_Data(filename);
            break;
        case 3:
            Bubble_Sort(filename);
            Print_Data(filename);
            break;
        case 4:
            cout << "Input month: "; cin >> searchMonth;
            People_SearchFor_Month(filename, searchMonth);
            break;
        case 0:
            break;
        default:
            cout << "You wrote mistake value!" << endl;
        }
    } while (menuItem != 0);

    return 0;
}


void Input_Data(string filename) {
    ofstream f(filename, ios::binary);
    Note n;
    char ch;
    int i = 0;
    do {
        i++;
        cin.get();
        cout << "Note #" << i << endl << endl;
        cout << "Last Name: ";
        cin >> n.lastName;
        cout << "Name: ";
        cin >> n.firstName;
        cout << "Phone number: ";
        cin >> n.phoneNumber;
        cout << "Birthday (day, month, year): " << endl;
        cin >> n.birthdate[0] >> n.birthdate[1] >> n.birthdate[2];
        cin.get();

        f.write((char*)&n, sizeof(Note));
        cout << "Continue? (Y/N): "; cin >> ch; cout << endl;
    } while (ch == 'Y' || ch == 'y');
    f.close();
    cout << endl;
}

void Print_Data(string filename) {
    ifstream f(filename, ios::binary);
    Note n;
    int i = 0;

    while (f.read((char*)&n, sizeof(Note))) {
        i++;
        cout << "Last_Name: " << n.lastName << endl;
        cout << "First_Name: " << n.firstName << endl;
        cout << "Phone_number: " << n.phoneNumber << endl;
        cout << "Birthday (day, month, year): " << n.birthdate[0] << "/" << n.birthdate[1] << "/" << n.birthdate[2] << endl;
        cout << "----------------------------------------------" << endl;
        cin.ignore();
    }

    f.close();
}



void Bubble_Sort(string filename) {
    ifstream f(filename, ios::binary);
    Note n;
    int numNotes = 0;

    while (f.read((char*)&n, sizeof(Note))) {
        numNotes++;
    }
    f.close();

    Note* notes = new Note[numNotes];
    f.open(filename, ios::binary);
    for (int i = 0; i < numNotes; i++) {
        f.read((char*)&notes[i], sizeof(Note));
    }
    f.close();

    for (int i0 = 0; i0 < numNotes - 1; i0++) {
        for (int i1 = 0; i1 < numNotes - i0 - 1; i1++) {
            if (strcmp(notes[i1].lastName, notes[i1 + 1].lastName) > 0) {
                swap(notes[i1], notes[i1 + 1]);
            }
        }
    }

    ofstream fout(filename, ios::binary);
    for (int i = 0; i < numNotes; i++) {
        fout.write((char*)&notes[i], sizeof(Note));
    }
    fout.close();

    delete[] notes;
}


void People_SearchFor_Month(string filename, int searchMonth) {
    ifstream f(filename, ios::binary);
    Note n;
    int numNotes = 0;

    while (f.read((char*)&n, sizeof(Note))) {
        numNotes++;
    }
    f.close();

    Note* notes = new Note[numNotes];
    f.open(filename, ios::binary);
    for (int i = 0; i < numNotes; i++) {
        f.read((char*)&notes[i], sizeof(Note));
    }
    f.close();

    bool found = false;
    for (int i = 0; i < numNotes; ++i) {
        if (notes[i].birthdate[1] == searchMonth) {
            cout << setw(15) << left << "Last Name: " << notes[i].lastName << endl;
            cout << setw(15) << left << "Name: " << notes[i].firstName << endl;
            cout << setw(15) << left << "Phone number: " << notes[i].phoneNumber << endl;
            cout << setw(15) << left << "Date of birth: " << notes[i].birthdate[0] << "/"
                << notes[i].birthdate[1] << "/" << notes[i].birthdate[2] << endl << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No data for people born in this month" << endl;
    }

    delete[] notes;
}
