#include "MathCPP.h"
namespace MathCPP
{
	void Rewrite(int* val, int index, int len)
	{
		for (size_t i = index; i < len - 2; i++)
		{
			val[i] = val[i + 2];
		}
	}
	int FromMethod(std::vector<Light::CommandResult> v)
	{
		auto name = v[0].ToString();
		if (name == "pow")
		{
			return pow(v[1].ToInt(), v[2].ToInt());
		}
		return 0;
	}
	int GetResult(std::vector<Light::CommandResult> v)
	{
		if (v.size() < 1)
		{
			return 0;
		}
		else
		{
			auto first = v[0];
			if (first.resultType == Light::Number)
			{
				return Evaluate(v);
			}
			else if (first.resultType == Light::Label)
			{
				return FromMethod(v);
			}
			return 0;

		}
	}
	int Evaluate(std::vector<Light::CommandResult> parameters)
	{
		int size = parameters.size();
		auto vals = new int[size];
		for (size_t i = 0; i < size; i++)
		{
			auto current = parameters[i];
			if (current.resultType == Light::ResultType::Number)
			{
				vals[i] = current.ToInt();
			}
			else if (current.resultType == Light::ResultType::Operador)
			{
				vals[i] = current.ToOperador();
			}
			else if (current.resultType == Light::ResultType::Expression)
			{
				vals[i] = GetResult(current.ToExpression()[0]);
			}
		}
		if (size % 2 != 0)
		{
			while (size > 1)
			{
				auto case1 = true;
				for (size_t i = 0; i < size - 1; i += 2)
				{
					auto op = (Light::COperator)vals[i + 1];
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
						auto op = (Light::COperator)vals[i + 1];
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
}
