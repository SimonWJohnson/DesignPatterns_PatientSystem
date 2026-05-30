#pragma once

#include "AbstractPatientDatabaseLoader.h"

#include <memory>
#include <vector>

// FR2 Composite Pattern
// Treats multiple patient loaders as one loader
class CompositePatientDatabaseLoader : public AbstractPatientDatabaseLoader {
public:
	void addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader);

	void initialiseConnection() override;
	void loadPatients(std::vector<Patient*>& patientsIn) override;
	void closeConnection() override;

private:
	// Stores all Patient loaders that form the Composite
	// Each loader implements AbstractPatientDatabaseLoader,
	// allowing the Composite to treat multiple loaders as one
	// unique_ptr automatically manages memory and cleans up loaders when the composite is destroyed
	std::vector<std::unique_ptr<AbstractPatientDatabaseLoader>> _loaders;
};