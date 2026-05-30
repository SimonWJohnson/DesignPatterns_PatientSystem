#pragma once

#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"

#include <string>

// FR1
// Adapter Pattern
// Allows PatientFileLoader to be used anywhere an 
// AbstractPatientDatabaseLoader is expected
class PatientFileLoaderAdapter : public AbstractPatientDatabaseLoader {
public:
	PatientFileLoaderAdapter(const std::string& fileName);

	// PatientManagementSystem expects the following interface
	void initialiseConnection() override;
	void loadPatients(std::vector<Patient*>& patientsIn) override;
	void closeConnection() override;

private:
	PatientFileLoader _fileLoader;
	std::string _fileName;
};
