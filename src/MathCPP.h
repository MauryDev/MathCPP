#pragma once
#include "Arguments.h"
#include<vector>
namespace MathCPP
{
	struct VariableData
	{
		const char* name;
		double value;
		VariableData();
		VariableData(const char* name, double val);
	};
	struct VariableList
	{
		Light::Array<VariableData> data;
		VariableData* Get(const char* name);
		int FindIndex(const char* name);

		void Set(const char* name, double value);
		void Delete(const char* name);
	};
	struct MethodCustom
	{
		typedef double(__stdcall  *Callback) (Light::Expression& v);

		struct Info
		{
			const char* name;
			Callback value;
		};
		Light::Array<Info> methodInfo;
		Info* GetFromName(const char* name);
		void Add(const char* name, Callback method);
	};
	double Evaluate(Light::List& parameters, VariableList& data);
	double Constant(Light::string_view& name);
	double FromMethod(Light::Function & v, VariableList & data);
	extern MethodCustom methodcustom;
}