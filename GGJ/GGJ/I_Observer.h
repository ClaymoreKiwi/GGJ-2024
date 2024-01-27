#pragma once
//credits for observer and subject classes to implement observer design pattern
class I_Observer
{
public:
	/// <summary>
	/// Updates the state of this observer, params passed from the subject
	/// </summary>
	/// <param name="lastPlayerPos">The last location the player was in (pixels)</param>
	/// <param name="newPlayerPos">The new location of the player (pixels)</param>
	virtual void ObserverUpdate() = 0;
};

