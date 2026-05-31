#include "PatientManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>
#include <memory>

#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "Vitals.h"

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"
// add the Adapter as per FR1
#include "PatientFileLoaderAdapter.h"
// add the Composite as per FR2
#include "CompositePatientDatabaseLoader.h"

using namespace std;

// FR2 - Composite Pattern
// Create the default Patient loader used by the system
// The CompositePatientDatabaseLoader allows multiple loaders
// to be treated as a single AbstractPatientDatabaseLoader

// The database loader is created first followed by the file loader adapter
// this ensures Patients are loaded in the order specified by the requirements

// Use an anonymous namespace visible only to the PatientManagementSystem class
namespace 
{
	std::unique_ptr<AbstractPatientDatabaseLoader> createDefaultPatientLoader()
	{
		// Create the Composite loader
		std::unique_ptr<CompositePatientDatabaseLoader> loader =
			std::make_unique<CompositePatientDatabaseLoader>();

		// Add the database loader first
		// Patients from the database be loaded before file Patients
		loader->addLoader(std::make_unique<PatientDatabaseLoader>());

		// Add the file loader second
		// The Adapter created in FR1 aloows file loading to be
		// treated like any other AbstractPatientDatabaseLoader
		loader->addLoader(
			std::make_unique<PatientFileLoaderAdapter>("patients.txt")
		);

		// Return the Composite as an AbstractPatientDatabaseLoader
		// This allows PatientManagementSystem to remain unaware of the specific loader implementation being used
		return loader;
	}
}



PatientManagementSystem::PatientManagementSystem() :
	//_patientDatabaseLoader(std::make_unique<PatientDatabaseLoader>()),
	
	// FR1 Adapter Pattern
	// Use the PatientFileLoaderAdapter so Patient data is loaded from a text file through
	// the AbstractPatientDatabaseLoader interface.
	// Switching loaders requires changing only this line
	//_patientDatabaseLoader(std::make_unique<PatientFileLoaderAdapter>("patients.txt")),

	// FR2 Composite Pattern
	// Use a CompositePatientDatabaseLoader so multiple loaders (database and file)
	// can be treated as a single AbstractPatientDatabaseLoader
	// Switching between database only, file only, database & file can be achieved by changing
	// only the loader configuration
	_patientDatabaseLoader(createDefaultPatientLoader()),
	_hospitalAlertSystem(std::make_unique<HospitalAlertSystemFacade>()),
	_gpNotificationSystem(std::make_unique<GPNotificationSystemFacade>())
{
	// Initialise all loaders contained within the Composite
	_patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
	_patientDatabaseLoader->closeConnection();

	// clear patient memory
	for (Patient* p : _patients) {
		delete p;
	}
}

void PatientManagementSystem::init()
{
	_patientDatabaseLoader->loadPatients(_patients);
	for (Patient* p : _patients) {
		_patientLookup[p->uid()] = p;
	}

	for (Patient* p : _patients) {
		// TODO: do any processing you need here
		// FR4
		// Register Hospital and GP observers with each Patient
		// Observers notified automatically by Patient::setAlertLevel()
		p->addAlertObserver(&_hospitalAlertObserver);
		p->addAlertObserver(&_gpNotificationObserver);
	}
}

void PatientManagementSystem::run()
{
	printWelcomeMessage();

	bool running = true;
	while (running) {
		printMainMenu();
		int option = 0;
		cin >> option;

		// handle basic errors
		if (cin.bad()) {
			cin.clear();
			cin.ignore();
			continue;
		}

		// switch based on the selected option
		switch (option) {
		case 1:
			printPatients();
			break;
		case 2:
			addVitalsRecord();
			break;
		case 3:
			running = false;
			break;
		}
	}
}

void PatientManagementSystem::addVitalsRecord()
{
	cout << "Patients" << endl;
	printPatients();
	cout << endl;
	cout << "Enter the patient ID to declare vitals for > ";
	
	string pid { "" };
	cin >> pid;
	if (_patientLookup.count(pid)) {
		float bodyTemperature;
		int bloodPressure;
		int heartRate;
		int respitoryRate;

		cout << "enter body temperature: ";
		cin >> bodyTemperature;
		cout << "enter blood pressure: ";
		cin >> bloodPressure;
		cout << "enter heart rate: ";
		cin >> heartRate;
		cout << "enter respitory rate: ";
		cin >> respitoryRate;

		Vitals* v = new Vitals(bodyTemperature, bloodPressure, heartRate, respitoryRate);
		_patientLookup[pid]->addVitals(v);
	}
	else {
		cout << "Patient not found" << endl;
	}
}

void PatientManagementSystem::printWelcomeMessage() const
{
	cout << "WELCOME TO HEALTHCO 3000" << endl;
	cout << "------------------------" << endl;
}

void PatientManagementSystem::printMainMenu() const
{
	cout << endl << "Select an option:" << endl;
	cout << "1. List patients" << endl;
	cout << "2. Add vitals record" << endl;
	cout << "3. Quit" << endl;
	cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
	for (Patient* p : _patients) {
		std::cout << *p << std::endl;
	}
}
