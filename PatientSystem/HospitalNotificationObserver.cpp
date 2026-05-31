#include "HospitalNotificationObserver.h"

void HospitalNotificationObserver::update(Patient* patient) 
{
	_hospitalAlertSystem.sendAlertForPatient(patient);
}