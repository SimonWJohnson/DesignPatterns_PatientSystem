#pragma once

#include "AlertLevelStrategy.h"

// Strategy for Cordyceps Brain Infection
// Alert level is based on respiratory rate
class CordycepsBrainInfectionAlertLevelStrategy : public AlertLevelStrategy {
public:
	AlertLevel calculateAlertLevel(
		const Patient& patient,
		const Vitals& vitals
	) const override;
};

