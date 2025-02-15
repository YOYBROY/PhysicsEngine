#pragma once

#include "Application.h"
#include "Maths.h"

class Example : public Application
{
private:
	//Any data that should persist for the duration of your program,
	//declare it here.
	float someTestValue = 3.0f;

public:
	Example();
	void Initialise() override;

	void Update(float delta) override;

	void OnLeftClick() override;
};