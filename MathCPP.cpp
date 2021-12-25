#include "MathCPP.h"
#include <cmath>

namespace MathCPP
{
	double Constant(char* name)
	{
		if (strcmp(name, "pi")  == 0)
		{
			return 3.14159265358979323846;
		}
		else if (strcmp(name, "e") == 0)
		{
			return 2.71828182845904523536;
		}
		else if (strcmp(name ,"sqrt2") == 0)
		{
			return 1.41421356237309504880;
		}
		else if (strcmp(name , "sqrt3") == 0)
		{
			return 1.7320508075;
		}
		else if (strcmp(name ,"sqrt5") == 0)
		{
			return 2.23606797749978969640917366873127623;
		}
		else if (strcmp(name ,"log2e") == 0)
		{
			return 1.44269504088896340736;
		}
		else if (strcmp(name, "ln2") == 0)
		{
			return 0.693147180559945309417;
		}
		else if (strcmp(name , "ln10") == 0)
		{
			return 2.30258509299404568402;
		}
		else if (strcmp(name, "log10e") == 0)
		{
			return 0.434294481903251827651;
		}
		return 0;
	}
	double FindVar(char* name, std::vector<VariableData> data)
	{
		for (auto v : data)
		{
			if (strcmp(name+1, v.name) == 0)
			{
				return v.value;
			}
		}
		return 0;
	}
	double GetResult(std::vector<Light::CommandResult> v, std::vector<VariableData> data);
	double GetValue(Light::CommandResult arg, std::vector<VariableData> data)
	{
		if (arg.resultType == Light::ResultType::Number)
		{
			return arg.ToDouble();
		}
		else if (arg.resultType == Light::ResultType::Operador)
		{
			return arg.ToOperador();
		}
		else if (arg.resultType == Light::ResultType::Expression)
		{
			return GetResult(arg.ToExpression()[0], data);
		}
		else if (arg.resultType == Light::ResultType::Label)
		{
			auto key = arg.ToString();
			if (key[0] == '$')
			{
				return FindVar((char*)key.data(), data);
			}
			return Constant((char*)key.data());
		}
		else if (arg.resultType == Light::ResultType::Label)
		{
			auto key = arg.ToString();
			if (key[0] == '$')
			{
				key = key.substr(1);

				for (auto v : data)
				{
					if (key == v.name)
					{
						return v.value;
					}
				}
			}
			else
			{
				return Constant((char*)key.data());
			}
		}
		return 0;
	}
	double FromOp(std::vector<Light::CommandResult> v, std::vector<VariableData> data)
	{
		auto name = v[0].ToOperador();
		if (name == Light::Sub)
		{
			auto val = GetValue(v[1],data);
			return -val;
		}
		return 0;
	}

	void Rewrite(double* val, int index, int len)
	{
		for (size_t i = index; i < len - 2; i++)
		{
			val[i] = val[i + 2];
		}
	}
	double FromMethod(std::vector<Light::CommandResult> v, std::vector<VariableData> data)
	{
		auto name = v[0].ToString();
		if (name == "pow")
		{
			return pow(GetValue(v[1], data), GetValue(v[2], data));
		} else if (name == "max")
		{
			return fmax(GetValue(v[1], data), GetValue(v[2], data));
		}
		else if (name == "min")
		{
			return fmin(GetValue(v[1], data), GetValue(v[2], data));
		}
		else if (name == "sqrt")
		{
			return sqrt(GetValue(v[1], data));
		}
		else if (name == "round")
		{
			return round(GetValue(v[1], data));
		}
		else if (name == "log")
		{
			return log(GetValue(v[1], data));
		}
		else if (name == "abs")
		{
			return abs(GetValue(v[1], data));
		}
		else if (name == "acos")
		{
			return acos(GetValue(v[1], data));
		}
		else if (name == "asin")
		{
			return asin(GetValue(v[1], data));
		}
		else if (name == "atan")
		{
			return atan(GetValue(v[1], data));
		}
		else if (name == "cbrt")
		{
			return cbrt(GetValue(v[1], data));
		}
		else if (name == "ceil")
		{
			return ceil(GetValue(v[1], data));
		}
		else if (name == "cos")
		{
			return cos(GetValue(v[1], data));
		}
		else if (name == "cosh")
		{
			return cosh(GetValue(v[1], data));
		}
		else if (name == "exp")
		{
			return exp(GetValue(v[1], data));
		}
		else if (name == "expm1")
		{
			return expm1(GetValue(v[1], data));
		}
		else if (name == "dim")
		{
			return fdim(GetValue(v[1], data), GetValue(v[2], data));
		}
		else if (name == "floor")
		{
			return floor(GetValue(v[1], data));
		}
		else if (name == "hypot")
		{
			return hypot(GetValue(v[1], data), GetValue(v[2], data));
		}
		else if (name == "mod")
		{
			return fmod(GetValue(v[1], data), GetValue(v[2], data));
		}
		else if (name == "floor")
		{
			return floor(GetValue(v[1], data));
		}
		else if (name == "sin")
		{
			return sin(GetValue(v[1], data));
		}
		else if (name == "sinh")
		{
			return sinh(GetValue(v[1], data));
		}
		else if (name == "tan")
		{
			return tan(GetValue(v[1], data));
		}
		else if (name == "tanh")
		{
			return tanh(GetValue(v[1], data));
		}
		return Constant((char*)name.data());
	}
	double GetResult(std::vector<Light::CommandResult> v, std::vector<VariableData> data)
	{
		if (v.size() < 1)
		{
			return 0;
		}
		else
		{
			auto first = v[0];
			if (first.resultType == Light::Number || first.resultType == Light::String)
			{
				return Evaluate(v, data);
			}
			else if (first.resultType == Light::Label)
			{
				auto str = first.ToString();
				if (str[0] == '$')
				{
					return Evaluate(v, data);
				}
				return FromMethod(v, data);
			}
			else if (first.resultType == Light::Operador)
			{
				return FromOp(v, data);
			}
			return 0;

		}
	}
	double Evaluate(std::vector<Light::CommandResult> parameters, std::vector<VariableData> data)
	{
		int size = parameters.size();
		auto vals = new double[size];
		for (size_t i = 0; i < size; i++)
		{
			vals[i] = GetValue(parameters[i], data);
		}
		if (size % 2 != 0)
		{
			while (size > 1)
			{
				auto case1 = true;
				for (size_t i = 0; i < size - 1; i += 2)
				{
					auto op = (Light::COperator)(int)vals[i + 1];
					if (op == Light::Mul)
					{
						vals[i] = vals[i] * vals[i + 2];
						Rewrite(vals, i + 1, size);
						size -= 2;
						case1 = false;
						break;
					}
					else if (op == Light::Div)
					{
						vals[i] = vals[i] / vals[i + 2];
						Rewrite(vals, i + 1, size);
						size -= 2;
						case1 = false;
						break;
					}
				}
				if (case1)
				{
					auto case2 = true;
					for (size_t i = 0; i < size - 1; i += 2)
					{
						auto op = (Light::COperator)(int)vals[i + 1];
						if (op == Light::Add)
						{
							vals[i] = vals[i] + vals[i + 2];
							Rewrite(vals, i + 1, size);
							size -= 2;
							case2 = false;
							break;
						}
						else if (op == Light::Sub)
						{
							vals[i] = vals[i] - vals[i + 2];
							Rewrite(vals, i + 1, size);
							size -= 2;
							case2 = false;

							break;
						}
					}
					if (case2)
						throw "Invalid";

				}
			}
			auto ret = vals[0];
			free(vals);
			return ret;
		}

		return 0;
	}
	VariableData::VariableData(char * name, double val)
	{

		this->name = name;

		this->value = val;
	}
}
