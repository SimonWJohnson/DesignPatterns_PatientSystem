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
        Patient* patient = new Patient(firstName, lastName, birthdayTm);
        patient->addDiagnosis(diagnosis);

        // Historical vitals are loaded here
        // Alert levels should not be calculated for historical data***


    }


    return patients;
}
