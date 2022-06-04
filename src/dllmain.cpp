// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "pch.h"
#include "MathCPP.h"
#include "Utils.h"
#include <chrono>
#include <iostream>
MathCPP::VariableList variablelist;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
extern "C"
{
	DllExport void MathLib_SetVariable(const char* str,double valor)
	{
		var len = strlen(str);
		auto name = new char[len + 1];
		strcpy_s(name,len + 1, str);
		variablelist.Set((const char*)name, valor);
	}
	DllExport double MathLib_GetVariable(const char* str)
	{
		return variablelist.Get(str)->value;
	}
	DllExport void MathLib_SetMethod(const char* str, MathCPP::MethodCustom::Callback callback)
	{
		var len = strlen(str);
		auto name = new char[len + 1];
		strcpy_s(name, len + 1, str);
		MathCPP::methodcustom.Add(name, callback);
	}
	DllExport Light::CommandResult* MathLib_Commands_Get(Light::List& v,int index)
	{
		return &v[index];
	}
	DllExport double MathLib_Command_GetNumber(Light::CommandResult& v)
	{
		return MathCPP::GetValue(v, variablelist);
	}
	DllExport double MathLib_Commands_GetNumber(Light::List& v)
	{
		return MathCPP::GetResult(v, variablelist);
	}
	DllExport Light::List* MathLib_Function_GetArgument(Light::Expression& v,int index)
	{
		return &v[index];
	}
	DllExport const char* MathLib_Command_String(Light::CommandResult& v)
	{
		if (v.resultType == Light::ResultType::String || v.resultType == Light::ResultType::Label || v.resultType == Light::ResultType::Number)
		{
			var str = MathCPP::GetString(v, variablelist);
			if (str == nullptr)
			{
				return nullptr;
			}

			return str->data();
		}
		return nullptr;
	}
	DllExport Light::List* MathLib_Command_List(Light::CommandResult& v)
	{
		if (v.resultType != Light::ResultType::List)
		{
			return NULL;
		}
		return v.list;
	}
	DllExport Light::Dictionary* MathLib_Command_Dictionary(Light::CommandResult& v)
	{
		if (v.resultType != Light::ResultType::Dictionary)
		{
			return NULL;
		}
		return MathCPP::GetDictionary(v, variablelist);
	}
	DllExport Light::COperator MathLib_Command_Operador(Light::CommandResult& v)
	{
		if (v.resultType != Light::ResultType::Operador)
		{
			return Light::COperator::None;
		}
		return *v.operador;
	}
	DllExport Light::KeyValuePair* MathLib_Dictionary_KeyValuePair(std::vector<Light::KeyValuePair>& v,const char* name)
	{
		Light::KeyValuePair* ret = NULL;
		var len = v.size();
		for (auto i = 0; i < len; i++)
		{
			var current = &v[i];
			var key = MathCPP::GetString(current->key, variablelist);
			if (key != NULL && key->Equals(name))
			{
				return current;
			}
		}
		return ret;
	}
	DllExport Light::CommandResult* MathLib_KeyValuePair_Key(Light::KeyValuePair& v)
	{

		return &(v.key);
	}
	DllExport Light::CommandResult* MathLib_KeyValuePair_Value(Light::KeyValuePair& v)
	{

		return &(v.value);
	}
	DllExport Light::ResultType MathLib_Command_Type(Light::CommandResult& v)
	{
		return v.resultType;
	}

	DllExport size_t MathLib_Commands_Size(std::vector<Light::CommandResult>& v)
	{
		return v.size();
	}
	DllExport void MathLib_Free(Light::Expression* commands)
	{
		Light::Free(*commands);
		delete commands;
	}

	DllExport Light::Expression* MathLib_Compile(const char* str)
	{
		Light::string_view strdata(str);
		return Light::GetInstructions(strdata);
	}
	DllExport double MathLib_EvaluateFromCompile(Light::Expression* commands)
	{
		if (commands->get_Count() > 0)
		{
			var value = MathCPP::Evaluate(commands->at(0), variablelist);
			return value;
		}
		else
		{
			return 0.0;
		}
	}
	DllExport double MathLib_Evaluate(const char* str)
	{
		Light::string_view strdata(str);
		var commands = Light::GetInstructions(strdata);

		if (commands->get_Count() > 0)
		{
			var value = MathCPP::Evaluate(commands->at(0), variablelist);
			Light::Free(*commands);
			delete commands;
			return value;
		}
		else
		{
			delete commands;

			return 0.0;
		}
		
	}

}