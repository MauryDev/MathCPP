#include "pch.h"
#include "Utils.h"
#include "MathCPP.h"
Light::string_view* MathCPP::GetString(Light::CommandResult & arg, VariableList & data)
{
	if (arg.resultType != Light::ResultType::String || arg.resultType != Light::ResultType::Label || arg.resultType != Light::ResultType::Number)
	{
		return arg.str;
	}
	return NULL;
}
bool MathCPP::Compare(double v1, Light::COperator op, double v2)
{
	bool result = false;
	if (op == Light::COperator::CmpE)
	{
		result = v1 == v2;
	}
	else if (op == Light::COperator::CmpNE)
	{
		result = v1 != v2;
	}
	else if (op == Light::COperator::CmpG)
	{
		result = v1 > v2;
	}
	else if (op == Light::COperator::CmpGE)
	{
		result = v1 >= v2;
	}
	else if (op == Light::COperator::CmpL)
	{
		result = v1 < v2;
	}
	else if (op == Light::COperator::CmpLE)
	{
		result = v1 <= v2;
	}
	return result;
}

Light::Array<double> MathCPP::GetArrayValue(Light::CommandResult&  arg, VariableList & data)
{

	if (arg.resultType == Light::ResultType::List)
	{
		Light::Array<double> ret;

		var list = arg.list->get_Enumerator();
		while (list.Next())
		{
			ret.Add(GetValue(list.get_Current(), data));
		}
		return ret;
	}
	return Light::Array<double>::Empty();
}
void MathCPP::GetArrayValue(Light::CommandResult & arg, VariableList & data, Light::Array<double>& ret)
{
	if (arg.resultType == Light::ResultType::List)
	{
		var list = arg.list->get_Enumerator();
		while (list.Next())
		{
			ret.Add(GetValue(list.get_Current(), data));
		}
	}
}
double MathCPP::GetResult(Light::List& v, VariableList& data)
{
	if (v.get_Count() < 1)
	{
		return 0.0;
	}
	else
	{
		return Evaluate(v, data);

	}
}



double MathCPP::GetValue(Light::CommandResult& arg, VariableList& data)
{
	if (arg.resultType == Light::ResultType::Number)
	{
		return arg.ToDouble();
	}
	else if (arg.resultType == Light::ResultType::Expression)
	{
		return GetResult(arg.expression->at(0), data);
	}
	else if (arg.resultType == Light::ResultType::Function)
	{
		return FromMethod(*arg.fn, data);
	}
	else if (arg.resultType == Light::ResultType::Label)
	{
		auto key = arg.str;
		if (key->at(0) == '$')
		{
			auto vdat = data.Get(key->data() + 1);
			if (vdat != NULL)
			{
				return vdat->value;
			}
		}
		else
		{
			return Constant(*key);
		}
	}
	return 0.0;
}

Light::COperator MathCPP::GetOperator(Light::CommandResult arg, VariableList& data)
{
	if (arg.resultType == Light::ResultType::Operador)
	{
		return *arg.operador;
	}

	return Light::COperator::None;
}

Light::Dictionary* MathCPP::GetDictionary(Light::CommandResult arg, VariableList & data)
{
	if (arg.resultType != Light::ResultType::Dictionary)
	{
		return NULL;
	}
	return arg.dictionary;
}
double MathCPP::ToDouble(bool val)
{
	return val ? 1.0 : 0.0;
}
bool MathCPP::ToBool(double val)
{
	return val != 0.0;
}
Light::KeyValuePair * MathCPP::GetFromKeyByNumber(Light::Dictionary& arg, VariableList& data, double val)
{
	var enumerator = arg.get_Enumerator();
	while (enumerator.Next())
	{
		var& current = enumerator.get_Current();
		var key = MathCPP::GetValue(current.key, data);
		if (key == val)
		{
			return &current;
		}
	}
	return NULL;
}

