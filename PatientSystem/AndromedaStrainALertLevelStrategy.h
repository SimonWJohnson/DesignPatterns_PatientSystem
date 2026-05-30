#pragma once
#include "AlertLevelStrategy.h"

// Strategy for Andromeda Strain
// ALert level is based on blood pressure
class AndromedaStrainAlertLevelStrategy : public AlertLevelStrategy {
public:
	AlertLevel calculateAlertLevel(
		const Patient& patient,
		const Vitals& vitals
	) const override;
};
