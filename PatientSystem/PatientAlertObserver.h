#pragma once

// forward declaration
class Patient;

// FR4 - Observer Pattern
// Define a common interface for objects that need to be notified
// when a Patient's alert level changes

class PatientAlertObserver {
public:
	// Destructor
	virtual ~PatientAlertObserver() = default;

	// Send Alert / Notification
	// Override in implementation
	virtual void update(Patient* patient) = 0;
};