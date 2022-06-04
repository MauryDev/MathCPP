#pragma once
#include "Literal.h"

namespace MathUtils
{
#define MathUtils_PI 3.14159265358979323846
	double fmax(Light::Array<double>& args);
	double fmin(Light::Array<double>& args);
	double random(double min, double max);
	double clamp(double val, double minval,double maxval);
	double average(Light::Array<double>& args);
	double sign(double val);
	double mode(Light::Array<double>& args);
	double median(Light::Array<double>& args);
	double degrees(double radians);
	double radians(double degrees);
	double fact(double num);

}