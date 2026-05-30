#include "AndromedaStrainAlertLevelStrategy.h"
#include "Vitals.h"
#include "Patient.h"

AlertLevel AndromedaStrainAlertLevelStrategy::calculateAlertLevel(
	const Patient& patient,
	const Vitals& vitals
	) const
{
	if (vitals.BP() > 140) 
	{
		return AlertLevel::Red;
	}
	if (vitals.BP() > 130) 
	{
		return AlertLevel::Orange;
	}
	if (vitals.BP() > 110) 
	{
		return AlertLevel::Yellow;
	}
	// ELse
	return AlertLevel::Green;
}

