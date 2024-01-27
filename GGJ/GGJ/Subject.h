#pragma once
#include "I_Observer.h"

#include <vector>
class I_Subject
{
	std::vector<I_Observer*> observers;
public:
	/// <summary>
	/// Must be overridden.
	/// This Registers an observer to this subject
	/// </summary>
	/// <param name="observer">The observer to register</param>
	virtual void RegisterObserver(I_Observer* observer);

	/// <summary>
	/// Must be overidden
	/// This unsubscribes an observer from this subject
	/// </summary>
	/// <param name="observer">The observer to unregister</param>
	virtual void RemoveObserver(I_Observer* observer);

	/// <summary>
	/// Must be overidden
	/// This notifys all subscribers of a subject when an interesting event has happened
	/// </summary>
	virtual void NotifyObservers();
};

