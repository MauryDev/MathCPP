#pragma once

#include "MathCPP.h"

namespace MathCPP
{
	Light::string_view* GetString(Light::CommandResult& arg, VariableList& data);
	bool Compare(double v1, Light::COperator op, double v2);
	Light::Array<double> GetArrayValue(Light::CommandResult&  arg, VariableList& data);
	void GetArrayValue(Light::CommandResult&  arg, VariableList& data, Light::Array<double>& ret);

	double GetResult(Light::List& v, VariableList& data);
	double GetValue(Light::CommandResult& arg, VariableList& data);
	Light::COperator GetOperator(Light::CommandResult arg, VariableList& data);
	Light::Dictionary* GetDictionary(Light::CommandResult arg, VariableList& data);
	Light::KeyValuePair* GetFromKeyByNumber(Light::Dictionary& arg, VariableList& data,double val);
	double ToDouble(bool val);
	bool ToBool(double val);
}