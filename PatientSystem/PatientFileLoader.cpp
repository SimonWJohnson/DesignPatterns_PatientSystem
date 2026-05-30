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
    if (inFile.is_open()) {
        // TODO: load your file here
        // Add error handling for file not reachable/readable

        // Split the name field - LastName, FirstName

        // Convert birthday string into tm structure

        // Historical vitals are loaded here
        // Alert levels should not be calculated for historical data***
    }

    return patients;
}
