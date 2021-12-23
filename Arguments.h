#pragma once
#include <vector>
#include <string>
namespace Light
{
	
	enum COperator :int
	{
		None,
		Add,
		Sub,
		Div,
		Mul,
		Mod,
		And,
		Or,
		CmpE,
		CmpNE,
		CmpG,
		CmpL,
		CmpGE,
		CmpLE,
		Inc,
		Dec
	};

	enum ResultType: int
	{
		Undefined,
		Label,
		String,
		Number,
		Comment,
		Expression,
		Operador
	};
	struct CommandResult
	{
		ResultType resultType;
		void* value;
		std::string ToString();
		COperator ToOperador();
		std::vector<std::vector<CommandResult>> ToExpression();
		double ToDouble();
		int ToInt();
	};
	struct ResultNext
	{
		int index;
		ResultType resultType;
	};
	bool isOperator(std::string val, int index);
	bool IsSymbolStart(char val);
	std::vector<std::vector<CommandResult>> GetArguments(std::string str);
	COperator Op(std::string type);
	void Free(std::vector<std::vector<Light::CommandResult>> &v);
}
