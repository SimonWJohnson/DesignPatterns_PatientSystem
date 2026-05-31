#include "Patient.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Vitals.h"
#include "AlertLevelStrategy.h"
#include "CordycepsBrainInfectionAlertLevelStrategy.h"
#include "KepralsSyndromeAlertLevelStrategy.h"
#include "AndromedaStrainAlertLevelStrategy.h"
#include "PatientAlertObserver.h"


using namespace std;

const std::string Diagnosis::CORDYCEPS_BRAIN_INFECTION = "Cordyceps Brain Infection";
const std::string Diagnosis::KEPRALS_SYNDROME = "Kepral’s Syndrome";
const std::string Diagnosis::ANDROMEDA_STRAIN= "Andromeda Strain";


Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green)
{
}

int Patient::age() const
{	
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0)) 
	   << (char)std::tolower(_firstName.at(0))
	   << std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1) 
	   << _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{
	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << p._lastName << "," << p._firstName << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p.primaryDiagnosis();
	
	os << "|";
	for (int i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

// Anonymous helper function to facilitate Alert Strategies
// This helper function acts as a simple factory that encapsulates the logic
// required to select the correct algorithm at runtime
namespace 
{
	// Create and return the appropriate Strategy object
	// Each disease has its own alert level calculation algorithm
	std::unique_ptr<AlertLevelStrategy> createAlertLevelStrategy(
		const std::string& diagnosis
	)
	{
		if (diagnosis == Diagnosis::CORDYCEPS_BRAIN_INFECTION) 
		{
			return std::make_unique<CordycepsBrainInfectionAlertLevelStrategy>();
		}
		if (diagnosis == Diagnosis::KEPRALS_SYNDROME) 
		{
			return std::make_unique<KepralsSyndromeAlertLevelStrategy>();
		}
		if (diagnosis == Diagnosis::ANDROMEDA_STRAIN) 
		{
			return std::make_unique<AndromedaStrainAlertLevelStrategy>();
		}

		// Else
		// No matching strategy exists for this diagnosis
		// // No calculation should be performed
		return nullptr;
	}
}

// Bool parameter 'calculateAlertLevel' passed in to avoid miscalculation
void Patient::addVitals(const Vitals* v, bool calculateAlertLevel)
{
	// Store the newly recorded vitals
	_vitals.push_back(v);
	// TODO: calculate alert levels
	// 
	// Historical vitals loaded from the database or file should
	// not trigger alert level calculation.
	// Only newly recorded vitals should calculate and update the Patient's alert level
	if (!calculateAlertLevel) 
	{
		return;
	}
	// 
	// FR3 - Strategy Pattern
	// Select the correct alert calculation algorithm based on
	// the Patient's primary diagnosis
	std::unique_ptr<AlertLevelStrategy> strategy = createAlertLevelStrategy(primaryDiagnosis());

	if (strategy != nullptr) 
	{
		AlertLevel level = strategy->calculateAlertLevel(*this, *v);
		setAlertLevel(level);
	}
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;

	if (_alertLevel > AlertLevel::Green) {
		cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;
	}
}

// FR4 - Observer Pattern
// Add an Observer to the collection of registered Observers
void Patient::addAlertObserver(PatientAlertObserver* observer) 
{
	_alertObservers.push_back(observer);
}

// Iterate through all registered Observers and notify them of
// the Patient's current alert status
void Patient::notifyAlertObservers() 
{
	for (PatientAlertObserver* observer : _alertObservers) 
	{
		observer->update(this);
	}
}