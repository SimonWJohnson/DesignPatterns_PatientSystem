#include "CompositePatientDatabaseLoader.h"

// Add a loader to the Composite's collection of loaders
// Ownership of the loader is transferred into the _loaders
// collection using std::move() because unique_ptr objects can't be copied
void CompositePatientDatabaseLoader::addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader) 
{
	_loaders.push_back(std::move(loader));
}

// Initialise a connection for each loader in the vector of loaders
void CompositePatientDatabaseLoader::initialiseConnection() 
{
	for (const std::unique_ptr<AbstractPatientDatabaseLoader>& loader : _loaders) 
	{
		loader->initialiseConnection(); 
	}
}

// Ask each loader in the Composite to load its Patients into the shared patientsIn vector
void CompositePatientDatabaseLoader::loadPatients(std::vector<Patient*>& patientsIn) 
{
	for (const std::unique_ptr<AbstractPatientDatabaseLoader>& loader : _loaders) 
	{
		loader->loadPatients(patientsIn);
	}
}
// Close the connection for each loader in the vector of loaders
void CompositePatientDatabaseLoader::closeConnection() 
{
	for (const std::unique_ptr<AbstractPatientDatabaseLoader>& loader : _loaders) 
	{
		loader->closeConnection();
	}
}