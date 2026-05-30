#pragma once
#include "AlertLevelStrategy.h"

// Strategy for Kepral's Syndrome
// ALert level is based on patient age and heart rate
class KepralsSyndromeAlertLevelStrategy : public AlertLevelStrategy {
public:
	AlertLevel calculateAlertLevel(
		const Patient& patient,
		const Vitals& vitals
	) const override;
};