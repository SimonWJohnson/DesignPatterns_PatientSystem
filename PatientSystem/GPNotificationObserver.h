#pragma once

#include "PatientAlertObserver.h"
#include "GPNotificationSystemFacade.h"

// FR4 - Observer Pattern
// Observer that notifies the GP Notification system when 
// a Patient reaches a concerning alert level
class GPNotificationObserver : public PatientAlertObserver {
public:
	void update(Patient* patient) override;
private:
	GPNotificationSystemFacade _gpNotificationSystem;
};