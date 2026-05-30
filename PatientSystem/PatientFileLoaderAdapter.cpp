#include "PatientFileLoaderAdapter.h"

// Constructor
PatientFileLoaderAdapter::PatientFileLoaderAdapter(const std::string& fileName) :
	_fileName(fileName) 
{

}

// 'open' the connection
void PatientFileLoaderAdapter::initialiseConnection() 
{
	// No connection is required for file loading
	// This method exists so the file loader matches the
	// AbstractPatientDatabaseLoader interface
}

void PatientFileLoaderAdapter::loadPatients(std::vector<Patient*>& patientsIn) 
{
	// Load Patients into a vector
	std::vector<Patient*> filePatients = _fileLoader.loadPatientFile(_fileName);

	//for each Patient within the vector
	for (Patient* patient : filePatients) 
	{
		// place the Patient pointer on the end of the vector
		patientsIn.push_back(patient);
	}
}

// 'close' the connection
void PatientFileLoaderAdapter::closeConnection()
{
	// No connection needs to be closed for file loading
	// Patient memory is cleaned up by PatientManagementSystem
}