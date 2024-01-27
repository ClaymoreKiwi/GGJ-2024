#include "Subject.h"

void I_Subject::RegisterObserver(I_Observer* observer)
{
	this->observers.push_back(observer);
}

void I_Subject::RemoveObserver(I_Observer* observer)
{
	auto iterator = std::find(this->observers.begin(), this->observers.end(), observer);

	if (iterator != this->observers.end()) {
		this->observers.erase(iterator);
	}
}

void I_Subject::NotifyObservers()
{
	for (I_Observer* observer : this->observers) {
		observer->ObserverUpdate();
	}
}
