#pragma once

#include "PatientAlertLevels.h"

// Forward declare classes
class Patient;
class Vitals;

// FR3 - Strategy Pattern
// Defines the commone interface for all alert level algorithms
// Each concrete strategy calculates an Alertlevel differently

class AlertLevelStrategy {
public:
	// pure virtual keeps AlertLevelStrategy as an interface
	virtual ~AlertLevelStrategy() = default;

	virtual AlertLevel calculateAlertLevel(
		const Patient& patient,
		const Vitals& vitals
	) const = 0;
};