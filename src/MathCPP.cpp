#include "pch.h"
#include "MathCPP.h"
#include <cmath>
#include "MemoryHandler.h"
#include "Utils.h"
#include <algorithm>
#include "MathUtils.h"

#include "MathConstant.h"


namespace MathCPP
{
	MethodCustom methodcustom;
	double Constant(Light::string_view& name)
	{
		var enumerator = MathConstant::GetEnumerator();

		while (enumerator.Next())
		{
			var& current = enumerator.get_Current();
			var key = current.key;
			if (key.Equals(name))
			{
				return current.val;
			}
		}
		/*
		if (name.Equals("pi"))
		{
			return MathUtils_PI;
		}
		else if (name.Equals("e"))
		{
			return 2.71828182845904523536;
		}
		else if (name.Equals("sqrt2"))
		{
			return 1.41421356237309504880;
		}
		else if (name.Equals("sqrt3"))
		{
			return 1.7320508075;
		}
		else if (name.Equals("sqrt5"))
		{
			return 2.23606797749978969640917366873127623;
		}
		else if (name.Equals("log2e"))
		{
			return 1.44269504088896340736;
		}
		else if (name.Equals("ln2"))
		{
			return 0.693147180559945309417;
		}
		else if (name.Equals("ln10"))
		{
			return 2.30258509299404568402;
		}
		else if (name.Equals("log10e"))
		{
			return 0.434294481903251827651;
		}
		else if (name.Equals("INFINITY"))
		{
			return INFINITY;
		}
		else if (name.Equals("NAN"))
		{
			return NAN;
		}
		else if (name.Equals("TRUE"))
		{
			return 1.0;
		}
		else if (name.Equals("FALSE"))
		{
			return 0.0;
		}
		*/
		return 0;
	}


	void Rewrite(double* val, int index, int len)
	{
		for (size_t i = index; i < len - 2; i++)
		{
			val[i] = val[i + 2];
		}
	}

	double MathCPP::FromMethod(Light::Function & v, VariableList & data)
	{
		var name = v.name.str;
		var &args = *v.args.expression;
		if (name->Equals("pow"))
		{

			return pow(GetResult(args[0], data), GetResult(args[1], data));
		}
		else if (name->Equals("max"))
		{
			Light::Array<double> v1(10, (double*)alloca(80));
			GetArrayValue(args[0][0], data, v1);
			auto result = MathUtils::fmax(v1);
			if (v1.get_Capacity() > 10) v1.Free();
			return result;
		}
		else if (name->Equals("min"))
		{
			Light::Array<double> v1(10, (double*)alloca(80));
			GetArrayValue(args[0][0], data, v1);
			auto result = MathUtils::fmin(v1);
			if (v1.get_Capacity() > 10) v1.Free();
			return result;
		}
		else if (name->Equals("sqrt"))
		{
			return sqrt(GetResult(args[0], data));
		}
		else if (name->Equals("round"))
		{
			return round(GetResult(args[0], data));
		}
		else if (name->Equals("log"))
		{
			return log(GetResult(args[0], data));
		}
		else if (name->Equals("abs"))
		{
			return abs(GetResult(args[0], data));
		}
		else if (name->Equals("acos"))
		{
			return acos(GetResult(args[0], data));
		}
		else if (name->Equals("asin"))
		{
			return asin(GetResult(args[0], data));
		}
		else if (name->Equals("atan"))
		{
			return atan(GetResult(args[0], data));
		}
		else if (name->Equals("cbrt"))
		{
			return cbrt(GetResult(args[0], data));
		}
		else if (name->Equals("ceil"))
		{
			return ceil(GetResult(args[0], data));
		}
		else if (name->Equals("cos"))
		{
			return cos(GetResult(args[0], data));
		}
		else if (name->Equals("cosh"))
		{
			return cosh(GetResult(args[0], data));
		}
		else if (name->Equals("exp"))
		{
			return exp(GetResult(args[0], data));
		}
		else if (name->Equals("expm1"))
		{
			return expm1(GetResult(args[0], data));
		}
		else if (name->Equals("fdim"))
		{
			return fdim(GetResult(args[0], data), GetResult(args[1], data));
		}
		else if (name->Equals("floor"))
		{
			return floor(GetResult(args[0], data));
		}
		else if (name->Equals("hypot"))
		{
			return hypot(GetResult(args[0], data), GetResult(args[1], data));
		}
		else if (name->Equals("mod"))
		{
			return fmod(GetResult(args[0], data), GetResult(args[1], data));
		}
		else if (name->Equals("floor"))
		{
			return floor(GetResult(args[0], data));
		}
		else if (name->Equals("sin"))
		{
			return sin(GetResult(args[0], data));
		}
		else if (name->Equals("sinh"))
		{

			return sinh(GetResult(args[0], data));
		}
		else if (name->Equals("tan"))
		{
			return tan(GetResult(args[0], data));
		}
		else if (name->Equals("tanh"))
		{

			return tanh(GetResult(args[0], data));
		}
		else if (name->Equals("if"))
		{
			auto compare = ToBool(GetResult(args[0], data));
			auto v1 = GetResult(args[1], data);
			auto v2 = GetResult(args[2], data);
			return (compare ? v1 : v2);
		}
		else if (name->Equals("summation"))
		{
			auto num = (size_t)GetResult(args[0], data);
			double result = 0.0;
			data.Set("i", 0.0);
			auto variable = data.Get("i");

			for (size_t i = 0; i < num; i++)
			{
				variable->value = i + 1;
				result += GetResult(args[1], data);
			}
			variable->value = 0.0;

			return result;
		}
		else if (name->Equals("bin"))
		{
			auto v1 = GetString(args[0][0], data);
			
			return (double)strtol(v1->data(), nullptr, 2);
		}
		else if (name->Equals("hex"))
		{
			auto v1 = GetString(args[0][0], data);

			return (double)strtol(v1->data(), nullptr, 16);
		}
		else if (name->Equals("log"))
		{
			return log(GetResult(args[0], data));
		}
		else if (name->Equals("log10"))
		{
			return log10(GetResult(args[0], data));
		}
		else if (name->Equals("log2"))
		{
			return log2(GetResult(args[0], data));
		}
		else if (name->Equals("random"))
		{
			return MathUtils::random(GetResult(args[0], data), GetResult(args[1], data));
		}
		else if (name->Equals("sign"))
		{
			return round(GetResult(args[0], data));
		}
		else if (name->Equals("trunc"))
		{
			return trunc(GetResult(args[0], data));
		}
		else if (name->Equals("isfinite"))
		{
			return isfinite(GetResult(args[0], data)) ? 1.0 : 0.0;
		}
		else if (name->Equals("fpclassify"))
		{
			return fpclassify(GetResult(args[0], data));
		}
		else if (name->Equals("isinf"))
		{
			return isinf(GetResult(args[0], data));
		}
		else if (name->Equals("isnan"))
		{
			return isnan(GetResult(args[0], data));
		}
		else if (name->Equals("isnormal"))
		{
			return isnormal(GetResult(args[0], data));
		}
		else if (name->Equals("fma"))
		{
			return fma(GetResult(args[0], data), GetResult(args[1], data), GetResult(args[2], data));
		}
		else if (name->Equals("copysign"))
		{
			return copysign(GetResult(args[0], data), GetResult(args[0], data));
		}
		else if (name->Equals("fractpart"))
		{
			double val;
			return modf(GetResult(args[0], data), &val);
		}
		else if (name->Equals("intpart"))
		{
			double val;
			modf(GetResult(args[0], data), &val);
			return val;
		}
		else if (name->Equals("clamp"))
		{
			return MathUtils::clamp(GetResult(args[0], data), GetResult(args[1], data), GetResult(args[2], data));
		}
		else if (name->Equals("switch"))
		{
			auto val = GetResult(args[0], data);
			auto keyvaluepair = GetFromKeyByNumber(*GetDictionary(args[1][0], data), data, val);
			auto defautval = GetResult(args[2], data);
			return keyvaluepair != NULL ? GetValue(keyvaluepair->value, data) : defautval;
		}
		else if (name->Equals("average"))
		{
			Light::Array<double> v1(10, (double*)alloca(80));
			GetArrayValue(args[0][0], data, v1);
			auto result = MathUtils::average(v1);
			if (v1.get_Capacity() > 10) v1.Free();
			return result;
		}
		else if (name->Equals("median"))
		{
			Light::Array<double> v1(10, (double*)alloca(80));
			GetArrayValue(args[0][0], data, v1);
			auto result = MathUtils::median(v1);
			if (v1.get_Capacity() > 10) v1.Free();
			return result;
		}
		else if (name->Equals("mode"))
		{
			Light::Array<double> v1(10, (double*)alloca(80));
			GetArrayValue(args[0][0], data, v1);
			auto result = MathUtils::mode(v1);
			if (v1.get_Capacity() > 10) v1.Free();
			return result;
		}
		else if (name->Equals("not"))
		{
			auto v1 = GetResult(args[0], data);

			return ToDouble(!ToBool(v1));
		}
		else if (name->Equals("degrees"))
		{
			auto v1 = GetResult(args[0], data);

			return MathUtils::degrees(v1);
		}
		else if (name->Equals("radians"))
		{
			auto v1 = GetResult(args[0], data);

			return MathUtils::radians(v1);
		}
		else if (name->Equals("fact"))
		{
			auto v1 = GetResult(args[0], data);

			return MathUtils::fact(v1);
		}
		var methodCustom = methodcustom.GetFromName(name->data());
		if (methodCustom != NULL)
		{
			return methodCustom->value(args);
		}
		return 0.0;
	}
	double Evaluate(Light::List& parameters, VariableList& data)
	{
		int size = parameters.get_Count();
		if (size == 0)
		{
			return 0.0;
		}
		
		auto vals = std::Array_PTR<double>(new double[size]);
		var usedop = 1;
		var tamanho = 0;
		for (size_t i = 0; i < size; i++)
		{
			var current = parameters[i];
			if (current.resultType == Light::ResultType::Operador)
			{
				var op = GetOperator(parameters[i], data);
				usedop++;
				if (usedop >= 2)
				{
					var num = GetValue(parameters[i + 1], data);

					if (op == Light::COperator::Sub)
					{
						vals[tamanho] = -num;
					}
					else if (op == Light::COperator::Add)
					{
						vals[tamanho] = num;
					}
					else
					{
						throw "Bad Evalution Format";
					}
					i++;
					tamanho++;
					usedop = 0;

				}
				else
				{
					vals[tamanho] = (double)op;
					tamanho++;
				}
			}
			else
			{
				usedop = 0;
				var num = GetValue(parameters[i], data);
				vals[tamanho] = (double)num;

				tamanho++;
			}
		}
		size = tamanho;
		if (size % 2 != 0)
		{
			for (size_t i = 0; i < size - 1; i += 2)
			{
				auto current = vals[i + 1];
				auto op = (Light::COperator)(int)current;
				if (op == Light::COperator::Mul)
				{
					vals[i] = vals[i] * vals[i + 2];
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::Div)
				{
					vals[i] = vals[i] / vals[i + 2];
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::Mod)
				{
					vals[i] = fmod(vals[i], vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
			}
			for (size_t i = 0; i < size - 1; i += 2)
			{
				auto current = vals[i + 1];

				auto op = (Light::COperator)(int)current;
				if (op == Light::COperator::Add)
				{
					vals[i] = vals[i] + vals[i + 2];
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::Sub)
				{
					vals[i] = vals[i] - vals[i + 2];
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
			}
			for (size_t i = 0; i < size - 1; i += 2)
			{
				auto current = vals[i + 1];

				auto op = (Light::COperator)(int)current;
				if (op == Light::COperator::CmpE)
				{
					vals[i] = ToDouble(vals[i] == vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::CmpG)
				{
					vals[i] = ToDouble(vals[i] > vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::CmpGE)
				{
					vals[i] = ToDouble(vals[i] >= vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::CmpL)
				{
					vals[i] = ToDouble(vals[i] < vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::CmpLE)
				{
					vals[i] = ToDouble(vals[i] <= vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::CmpNE)
				{
					vals[i] = ToDouble(vals[i] != vals[i + 2]);
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
			}
			for (size_t i = 0; i < size - 1; i += 2)
			{
				auto current = vals[i + 1];

				auto op = (Light::COperator)(int)current;
				if (op == Light::COperator::And)
				{
					vals[i] = ToDouble(ToBool(vals[i]) && ToBool(vals[i + 2]));
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
				else if (op == Light::COperator::Or)
				{
					vals[i] = ToDouble(ToBool(vals[i]) || ToBool(vals[i + 2]));
					Rewrite(vals, i + 1, size);
					size -= 2;
					i -= 2;
				}
			}

			if (size != 1)
			{
				vals.Free();
				throw "Invalid";
			}
			auto ret = vals[0];
			return ret;
		}
		return 0.0;
	}
	VariableData::VariableData()
	{
		name = NULL;
		value = 0.0;
	}
	VariableData::VariableData(const char * name, double val)
	{

		this->name = name;

		this->value = val;
	}

	VariableData * VariableList::Get(const char * name)
	{
		var enumerator = data.get_Enumerator();
		while (enumerator.Next())
		{
			auto& current = enumerator.get_Current();
			if (current.name == name || strcmp(current.name, name) == 0)
			{
				return &current;
			}
		}
		return NULL;
	}

	int VariableList::FindIndex(const char * name)
	{
		var enumerator = this->data.get_Enumerator();
		int index = -1;
		while (enumerator.Next())
		{
			index++;
			auto& current = enumerator.get_Current();
			if (strcmp(current.name, name) == 0)
			{
				return index;
			}
		}
		return -1;
	}

	void VariableList::Set(const char * name, double value)
	{
		var vardata = Get(name);
		if (vardata != NULL)
		{
			vardata->value = value;
		}
		else
		{
			auto len = strnlen(name, 25) + 1;
			auto str = new char[len];
			strcpy_s(str, len, name);
			VariableData datav(str, value);
			this->data.Add(datav);

		}
	}

	void VariableList::Delete(const char * name)
	{
		var index = FindIndex(name);
		if (index != -1)
		{
			delete[] (data.at(index).name);
			data.RemoveAt(index);
		}
	}

	MethodCustom::Info * MethodCustom::GetFromName(const char* name)
	{
		var enumerator = methodInfo.get_Enumerator();
		while (enumerator.Next())
		{
			var& current = enumerator.get_Current();
			if (strcmp(name, current.name) == 0)
			{
				return &current;
			}
		}
		return NULL;
	}

	void MethodCustom::Add(const char* name, Callback method)
	{
		auto info = GetFromName(name);
		if (info != NULL)
		{
			info->name = name;
			info->value = method;
		}
		else
		{
			MethodCustom::Info infodata;
			infodata.name = name;
			infodata.value = method;
			methodInfo.Add(infodata);
		}
	}

}