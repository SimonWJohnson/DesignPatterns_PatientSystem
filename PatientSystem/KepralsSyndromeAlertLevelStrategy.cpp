#include "KepralsSyndromeAlertLevelStrategy.h"

#include "Patient.h"
#include "Vitals.h"

AlertLevel KepralsSyndromeAlertLevelStrategy::calculateAlertLevel(
	const Patient& patient,
	const Vitals& vitals
) const
{
	if (patient.age() < 12 && vitals.HR() > 120)
	{
		return AlertLevel::Red;
	}
	if (patient.age() >= 12 && vitals.HR() > 100) 
	{
		return AlertLevel::Red;
	}

	// Else
	return AlertLevel::Green;
}