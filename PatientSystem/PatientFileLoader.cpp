#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

using namespace std;


std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
	vector<Patient*> patients{};

    std::ifstream inFile(file);

    // Add error handling for file not reachable/readable
    if (!inFile.is_open()) {
        cout << "Could not open patient file: " << file << endl;
        return patients;
    }
    
    // TODO: load your file here
    string line;
    
    while (getline(inFile, line)){
        if (line.empty()) {
            continue;
        }

        /* Patient Details */
        // Take each component of the patient record
        string uid;
        string name;
        string birthday;
        string diagnosis;
        string vitalsRecords;

        stringstream lineStream(line);

        // Getters for each string
        // Split / separate at the pipe '|'
        getline(lineStream, uid, '|');
        getline(lineStream, name, '|');
        getline(lineStream, birthday, '|');
        getline(lineStream, diagnosis, '|');
        getline(lineStream, vitalsRecords, '|');

        // Split the name field - LastName, FirstName
        string lastName;
        string firstName;

        // Getters for each string
        // Split / separate at the comma ','
        stringstream nameStream(name);
        getline(nameStream, lastName, ',');
        getline(nameStream, firstName, ',');

        // Convert birthday string into tm structure
        tm birthdayTm{};
        stringstream birthdayStream(birthday);
        birthdayStream >> get_time(&birthdayTm, "%d-%m-%Y");

        // Instantiate Patient object
        // Use a pointer
        // The Patient class includes a uid field, but currently does not store
        // Patient IDs directly. The uid isread so the remaining fields can be 
        // parsed in the correct order
        Patient* patient = new Patient(firstName, lastName, birthdayTm);
        patient->addDiagnosis(diagnosis);

        /* Vitals Details */
        // Historical vitals are loaded here
        // Alert levels should not be calculated for historical data***

        if (!vitalsRecords.empty()){
            string vitalRecord;
            stringstream vitalsStream(vitalsRecords);

            while (getline(vitalsStream, vitalRecord, ';')) {
                if (vitalRecord.empty()) {
                    continue;
                }

                // Take each component of the vitals record
                string bodyTemperature;
                string bloodPressure;
                string heartRate;
                string respiritoryRate;

                stringstream vitalStream(vitalRecord);

                // Getters for each string
                // Split / separate at the comma ','
                getline(vitalStream, bodyTemperature, ',');
                getline(vitalStream, bloodPressure, ',');
                getline(vitalStream, heartRate, ',');
                getline(vitalStream, respiritoryRate, ',');
                
                // Instantiate Vitals object
                // Use a pointer
                // Convert string values into the numeric types required by the Vitals constructor
                Vitals* vitals = new Vitals(
                    stof(bodyTemperature),
                    stoi(bloodPressure),
                    stoi(heartRate),
                    stoi(respiritoryRate)
                );

                patient->addVitals(vitals);
            }
        }

        patients.push_back(patient);

    }

    return patients;
}
