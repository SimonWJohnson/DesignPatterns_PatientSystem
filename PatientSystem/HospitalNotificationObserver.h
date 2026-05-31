#pragma once

#include "PatientAlertObserver.h"
#include "HospitalAlertSystemFacade.h"

// FR4 = Observer Pattern
// Observer that notifies the hospital alert system when 
// a Patient reaches a concerning alert level

class HospitalNotificationObserver : public PatientAlertObserver {
public:
	void update(const Patient& patient) override;

private:
	HospitalAlertSystemFacade _hospitalAlertSystem;
};