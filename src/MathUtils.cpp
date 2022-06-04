#include "pch.h"
#include "MathUtils.h"
#include <cmath>
#include <time.h>
#include <algorithm>
#include <random>
namespace MathUtils
{
	std::random_device rd;
	std::mt19937 mt(rd());
}
double MathUtils::fmax(Light::Array<double>& args)
{
	var iterator = args.get_Enumerator();
	if (iterator.Next())
	{
		var maxval = iterator.get_Current();
		while (iterator.Next())
		{
			maxval = ::fmax(maxval, iterator.get_Current());

		}
		return maxval;

	}
	else
	{
		return false;
	}
}

double MathUtils::fmin(Light::Array<double>& args)
{
	var iterator = args.get_Enumerator();
	if (iterator.Next())
	{
		var maxval = iterator.get_Current();
		while (iterator.Next())
		{
			maxval = ::fmin(maxval, iterator.get_Current());

		}
		return maxval;

	}
	else
	{
		return false;
	}
}

double MathUtils::random(double minval,double maxval)
{
	std::uniform_real_distribution<double> dist(minval,maxval);
	
	return dist(mt);
}

double MathUtils::clamp(double val, double minval, double maxval)
{
	if (val >= maxval)
	{
		return maxval;
	}
	else if (val <= minval)
	{
		return minval;
	}
	else
	{
		return val;
	}
}

double MathUtils::average(Light::Array<double>& args)
{
	var iterator = args.get_Enumerator();
	if (iterator.Next())
	{
		var ret = iterator.get_Current();
		while (iterator.Next())
		{
			ret += iterator.get_Current();

		}
		return ret / args.get_Count();

	}
	else
	{
		return 0.0;
	}
	
	
}

double MathUtils::sign(double val)
{
	if (val == 0.0)
	{
		return 0;
	}
	else if (val > 0)
	{
		return 1;
	}
	else if (val > 0)
	{
		return -1;
	}
	else
	{
		return NAN;
	}
}

double MathUtils::mode(Light::Array<double>& args)
{
	var count = args.get_Count();
	if (count > 0)
	{
		std::sort(args.begin(), args.end());
		var interator = args.get_Enumerator();

		double m0 = 0.0, val = 0.0;
		unsigned m0count = 0, count = 0;
		while (interator.Next())
		{
			var valor_atual = interator.get_Current();
			if (valor_atual != val)
			{
				val = valor_atual;
				count = 1;
			}
			else
			{
				count++;
				if (count > m0count)
				{
					m0count = count;
					m0 = val;
				}
			}
		}
		return m0;
	}
	else
	{
		return 0.0;
	}
	
}

double MathUtils::median(Light::Array<double>& args)
{

	size_t tamanho = args.get_Count();

	if (tamanho > 0)
	{
		auto tamanhodiv = tamanho / 2;
		std::sort(args.begin(), args.end());
		return (tamanho % 2 == 0 ?
			(args[tamanhodiv - 1] + args[tamanhodiv]) / 2 :
			args[tamanhodiv]
			);
	}
	return 0.0;
}

double MathUtils::degrees(double radians)
{
	return radians * (180.0 / MathUtils_PI);
}

double MathUtils::radians(double degrees)
{
	return degrees * (MathUtils_PI / 180.0);
}

double MathUtils::fact(double num)
{
	auto num2 = trunc(num);

	if (num2 == -1.0)
	{
		return num;
	}
	if (num2 == 1.0 || num2 == 0.0)
	{
		return 1.0;
	}
	auto abs_value = abs(num2);
	auto ret = 1.0;
	for (size_t i = 1; i <= abs_value; i++)
	{
		ret *= i;
	}
	return (num < 0.0 ? -ret: ret);
}
