#include "pch.h"
#include "MathUtils.h"
#include "MathConstant.h"
namespace MathConstant
{
	KeyValue<Light::string_view,double> str[] = {
		KeyValue<Light::string_view,double>("pi",MathUtils_PI),
		KeyValue<Light::string_view,double>("e",2.71828182845904523536),
		KeyValue<Light::string_view,double>("sqrt2",1.41421356237309504880),
		KeyValue<Light::string_view,double>("sqrt3",1.7320508075),
		KeyValue<Light::string_view,double>("sqrt5",2.23606797749978969640917366873127623),
		KeyValue<Light::string_view,double>("log2e",1.44269504088896340736),
		KeyValue<Light::string_view,double>("ln2",0.693147180559945309417),
		KeyValue<Light::string_view,double>("ln10",2.30258509299404568402),
		KeyValue<Light::string_view,double>("INFINITY",INFINITY),
		KeyValue<Light::string_view,double>("NAN",NAN),
		KeyValue<Light::string_view,double>("TRUE",1.0),
		KeyValue<Light::string_view,double>("FALSE",0.0)
	};
}

Light::Array_Enumerator<MathConstant::KeyValue<Light::string_view, double >> MathConstant::GetEnumerator()
{
	return Light::Array_Enumerator<MathConstant::KeyValue<Light::string_view, double>>(MathConstant::str,
		MathConstant::str +
		(sizeof(MathConstant::str) / sizeof(MathConstant::KeyValue<Light::string_view, double >))
	);
}
