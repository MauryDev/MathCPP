#pragma once
#include "Arguments.h"
namespace MathConstant
{
	template<typename T,typename T2>
	class KeyValue
	{
	public:
		T key;
		T2 val;
		KeyValue(T Key, T2 Val);
	};
	Light::Array_Enumerator<MathConstant::KeyValue<Light::string_view, double >> GetEnumerator();
	template<typename T, typename T2>
	inline KeyValue<T, T2>::KeyValue(T Key, T2 Val)
	{
		key = Key;
		val = Val;
	}
}
