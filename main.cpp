#include<iostream>
using namespace std;
// First project with C++
// Before Learning DS and Algorithms

// Global variables
const auto MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

string names[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int status[MAX_SPECIALIZATION+1][MAX_QUEUE+1];		// 0 regular, 1 urgent
int queue_length[MAX_SPECIALIZATION+1];

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "\nEnter your choice:\n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;

        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;	// loop keep working
        }
    }
    return choice;
}

// To remove the Patient: 1-Move each patient to the left. E.g if patient in position 5, it will be in 4
void shift_left(int spec, string names_sp[], int status_sp[])
{
    int len = queue_length[spec];
    for (int i = 1; i < len; ++i) {
        names_sp[i-1] = names_sp[i];
        status_sp[i-1] = status_sp[i];
    }
    queue_length[spec]--;
}

//To add the Patient: 1-Move each patient to the right. E.g if patient in position 5, it will be in 6

void shift_right(int spec, string names_sp[], int status_sp[])
{
    int len = queue_length[spec];
    for (int i = len-1; i >= 0; --i) {	// critical to start from END
        names_sp[i+1] = names_sp[i];
        status_sp[i+1] = status_sp[i];
    }
    queue_length[spec]++;
}
//2- Add Function
bool add_patient() {
    int spec;
    string name;
    int st;

    cout << "Enter specialization, name, statis: ";
    cin >> spec >> name >> st;

    int pos = queue_length[spec];
    if (pos >= MAX_QUEUE) {
        cout << "Sorry we can't add more patients for this specialization\n";
        return false;
    }

    if (st == 0)	// regular, add to end
    {
        names[spec][pos] = name;
        status[spec][pos] = st;
        queue_length[spec]++;
    }
    else {
        // urgent, add to begin. Shift, then add
        shift_right(spec, names[spec], status[spec]);
        names[spec][0] = name;
        status[spec][0] = st;
    }


    return true;
}

void print_patient(int spec, string names_sp[], int status_sp[]) {
    int len = queue_length[spec];
    if (len == 0)
        return;

    cout << "There are " << len << " patients in specialization " << spec << "\n";
    for (int i = 0; i < len; ++i) {
        cout << names_sp[i] << " ";
        if (status_sp[i])
            cout << "urgent\n";
        else
            cout << "regular\n";
    }
    cout << "\n";
}
// Printing Current Patients
void print_patients() {
    cout << "****************************\n";
    for (int spec = 0; spec < MAX_SPECIALIZATION; ++spec) {
        print_patient(spec, names[spec], status[spec]);
    }
}
// 2-Removing Patients from Queue
void get_next_patients() {
    int spec;
    cout << "Enter specialization: ";
    cin >> spec;

    int len = queue_length[spec];

    if(len == 0) {
        cout<<"No patients at the moment. Have rest, Dr\n";
        return;
    }

    cout<<names[spec][0]<<" please go with the Dr\n";
    shift_left(spec, names[spec], status[spec]);
}

// Wrapping Up
void hospital_system() {
    while (true) {
        int choice = menu();

        if (choice == 1)
            add_patient();
        else if (choice == 2)
            print_patients();
        else if (choice == 3)
            get_next_patients();
        else
            break;
    }
}

int main() {
    hospital_system();
    return 0;
}

