#include "GPNotificationObserver.h"

void GPNotificationObserver::update(Patient* patient) 
{
	_gpNotificationSystem.sendGPNotificationForPatient(patient);
}