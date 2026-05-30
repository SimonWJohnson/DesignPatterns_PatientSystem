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
    

    // Split the name field - LastName, FirstName

    // Convert birthday string into tm structure

    // Historical vitals are loaded here
    // Alert levels should not be calculated for historical data***

    return patients;
}
