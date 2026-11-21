#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// ---------- Class 1: Person (Base Class) ----------
class Person {
private:
    string name;
    int age;
    string phone;

public:
    Person(string n, int a, string p) {
        name = n;
        age = a;
        phone = p;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getPhone() const {
        return phone;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone: " << phone << endl;
    }
};


// ---------- Class 2: Patient ----------
class Patient : public Person {
private:
    int patientId;
    string disease;
    string admitDate;

public:
    Patient(string n, int a, string p,
            int id, string d, string date)
        : Person(n, a, p) {

        patientId = id;
        disease = d;
        admitDate = date;
    }

    int getId() const {
        return patientId;
    }

    string getDisease() const {
        return disease;
    }

    void display() const {
        Person::display();

        cout << "Patient ID: " << patientId << endl;
        cout << "Disease: " << disease << endl;
        cout << "Admit Date: " << admitDate << endl;
    }
};


// ---------- Class 3: Doctor ----------
class Doctor : public Person {
private:
    int doctorId;
    string specialty;

public:
    Doctor(string n, int a, string p,
           int id, string s)
        : Person(n, a, p) {

        doctorId = id;
        specialty = s;
    }

    int getId() const {
        return doctorId;
    }

    string getSpecialty() const {
        return specialty;
    }

    void display() const {
        Person::display();

        cout << "Doctor ID: " << doctorId << endl;
        cout << "Specialty: " << specialty << endl;
    }
};


// ---------- Class 4: Appointment ----------
class Appointment {
private:
    int patientId;
    int doctorId;
    string date;

public:
    Appointment(int pId, int dId, string d) {
        patientId = pId;
        doctorId = dId;
        date = d;
    }

    void display() const {
        cout << "Patient ID: " << patientId << endl;
        cout << "Doctor ID: " << doctorId << endl;
        cout << "Appointment Date: " << date << endl;
    }
};


// ---------- Class 5: Hospital ----------
class Hospital {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

public:

    // Add Patient
    void addPatient() {
        string name, phone, disease, date;
        int age, id;

        cout << "\nEnter Patient Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Patient ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Disease: ";
        getline(cin, disease);

        cout << "Enter Admit Date: ";
        getline(cin, date);

        patients.push_back(
            Patient(name, age, phone, id, disease, date)
        );

        cout << "\nPatient Added Successfully!\n";
    }


    // Add Doctor
    void addDoctor() {
        string name, phone, specialty;
        int age, id;

        cout << "\nEnter Doctor Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Doctor ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Specialty: ";
        getline(cin, specialty);

        doctors.push_back(
            Doctor(name, age, phone, id, specialty)
        );

        cout << "\nDoctor Added Successfully!\n";
    }


    // View Patients
    void viewPatients() const {
        if (patients.empty()) {
            cout << "\nNo Patients Found!\n";
            return;
        }

        cout << "\n------ PATIENT LIST ------\n";

        for (int i = 0; i < patients.size(); i++) {
            cout << "\nPatient " << i + 1 << endl;
            patients[i].display();
            cout << "----------------------\n";
        }
    }


    // Search Patient
    void searchPatient() const {
        int id;

        cout << "\nEnter Patient ID to Search: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < patients.size(); i++) {
            if (patients[i].getId() == id) {
                cout << "\nPatient Found!\n";
                patients[i].display();
                return;
            }
        }

        cout << "\nPatient Not Found!\n";
    }


    // Discharge Patient
    void dischargePatient() {
        int id;

        cout << "\nEnter Patient ID to Discharge: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < patients.size(); i++) {
            if (patients[i].getId() == id) {

                patients.erase(patients.begin() + i);

                cout << "\nPatient Discharged Successfully!\n";
                return;
            }
        }

        cout << "\nPatient Not Found!\n";
    }


    // Book Appointment
    void bookAppointment() {
        int pId, dId;
        string date;

        cout << "\nEnter Patient ID: ";
        cin >> pId;

        cout << "Enter Doctor ID: ";
        cin >> dId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool patientFound = false;
        bool doctorFound = false;

        // Check Patient
        for (int i = 0; i < patients.size(); i++) {
            if (patients[i].getId() == pId) {
                patientFound = true;
                break;
            }
        }

        // Check Doctor
        for (int i = 0; i < doctors.size(); i++) {
            if (doctors[i].getId() == dId) {
                doctorFound = true;
                break;
            }
        }

        if (!patientFound) {
            cout << "\nPatient ID Not Found!\n";
            return;
        }

        if (!doctorFound) {
            cout << "\nDoctor ID Not Found!\n";
            return;
        }

        cout << "Enter Appointment Date: ";
        getline(cin, date);

        appointments.push_back(
            Appointment(pId, dId, date)
        );

        cout << "\nAppointment Booked Successfully!\n";
    }

};


// ---------- main ----------
int main() {
    Hospital h;
    int choice;

    do {
        cout << "\n========== HOSPITAL MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. View Patients\n";
        cout << "4. Search Patient\n";
        cout << "5. Book Appointment\n";
        cout << "6. Discharge Patient\n";
        cout << "7. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                h.addPatient();
                break;

            case 2:
                h.addDoctor();
                break;

            case 3:
                h.viewPatients();
                break;

            case 4:
                h.searchPatient();
                break;

            case 5:
                h.bookAppointment();
                break;

            case 6:
                h.dischargePatient();
                break;

            case 7:
                cout << "\nExiting Hospital Management System...\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 7);

    return 0;
}
