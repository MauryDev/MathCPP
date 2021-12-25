#pragma once
#include "Arguments.h"
#include<vector>

namespace MathCPP
{
	struct VariableData
	{
		char* name;
		double value;
		VariableData(char* name, double val);
	};
	double Evaluate(std::vector<Light::CommandResult> parameters, std::vector<VariableData> data);
}
