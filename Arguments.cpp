#include <string>
#include <string.h>
#include <sstream> 
#include <list>
#include "Arguments.h"
namespace Light
{
	void Free(std::vector<std::vector<Light::CommandResult>> &v)
	{
		for (auto i : v)
		{
			for (auto i2 : i)
			{
				auto type = i2.resultType;
				switch (type)
				{
				case Light::Label:
				case Light::String:
				case Light::Number:
				case Light::Operador:
					free(i2.value);
					break;
				case Light::Expression:
				{
					auto list = *(std::vector<std::vector<Light::CommandResult>>*)i2.value;
					free(i2.value);
					Free(list);
				}
					break;
				}
			}
			i.clear();
		}
		v.clear();
	}
	ResultNext Next(std::string str, int index)
	{
		ResultNext ret;
		if (index == -1)
		{
			ret.index = -1;
			ret.resultType = ResultType::Undefined;
			return ret;
		}
		auto len = str.size();
		for (int i = index; i < len; i++)
		{
			auto currentchar = str[i];
			if (currentchar == '\'')
			{
				ret.index = i;
				ret.resultType = ResultType::Label;
				return ret;

			}
			else if (IsSymbolStart(currentchar))
			{
				ret.index = i;
				ret.resultType = ResultType::Label;
				return ret;
			}
			else if (isOperator(str, i))
			{
				ret.index = i;
				ret.resultType = ResultType::Operador;
				return ret;
			}
			else if (currentchar == ';')
			{
				ret.index = str.find('\n', i);
				ret.resultType = ResultType::Comment;
				return ret;
			}
			else if (currentchar == '"')
			{
				ret.index = i;
				ret.resultType = ResultType::String;
				return ret;
			}
			else if (isdigit(currentchar) || currentchar == '-')
			{
				ret.index = i;
				ret.resultType = ResultType::Number;
				return ret;
			}
			else if (currentchar == '(')
			{
				ret.index = i;
				ret.resultType = ResultType::Expression;
				return ret;
			}
			else if (!isspace(currentchar))
			{
				throw "Invalid char " + currentchar;
			}
		}
		ret.index = -1;
		ret.resultType = ResultType::Undefined;
		return ret;
	}
	bool IgnoredChar(char val)
	{
		return val == ')' || val == ';' || isspace(val);
	}
	bool isOperator(std::string val, int index)
	{

		if (index == -1 || index >= val.size())
		{
			return false;
		}
		auto free = val.size() - index;
		auto current = val[index];
		if (current == '+' || current == '-' || current == '*' || current == '/' || current == '>' || current == '<')
		{
			if (free == 1)
			{
				return true;
			}
			current = val[index + 1];
			if (IgnoredChar(current))
			{
				return true;
			}
		}
		if (free >= 2)
		{
			auto current2 = val.substr(index, 2);
			if (current2 == "&&" || current2 == "||" || current2 == "!=" || current2 == "==" || current2 == ">=" || current2 == "<=" || current2 == "++" || current2 == "--")
			{
				if (free == 2)
				{
					return true;
				}
				current = val[index + 2];
				return IgnoredChar(current);
			}
		}
		return false;
	}
	bool IsSymbolStart(char val)
	{
		return isalpha(val) || val == '_' || val == '$';
	}
	bool IsSymbol(char val)
	{
		return isalnum(val) || val == '_' || val == '$' || val == '.';
	}
	bool FindEndExpression(std::string str, int& index)
	{
		if (index == -1)
		{
			return false;
		}
		auto len = str.size();
		for (int i = index; i < len; i++)
		{
			auto current = str[i];
			if (isspace(current))
			{
				continue;
			}
			else if (current == ')')
			{
				index = i;
				return true;
			}
			else
			{
				index = i;
				return false;
			}
		}
		index = -1;
		return false;
	}
	COperator GetOperador(std::string str, int& index)
	{
		auto free = str.size() - index;
		auto current = str[index];
		auto start = index;
		if (current == '+' || current == '-' || current == '*' || current == '/' || current == '>' || current == '<')
		{
			if (free == 1)
			{
				index += 1;
				return Op(str.substr(start, 1));
			}
			auto current2 = str[index + 1];
			if (IgnoredChar(current2))
			{
				index += 2;
				return Op(str.substr(start,1));
			}
		}
		if (free >= 2)
		{
			auto current2 = str.substr(index, 2);
			if (current2 == "&&" || current2 == "||" || current2 == "!=" || current2 == "==" || current2 == ">=" || current2 == "<=" || current2 == "++" || current2 == "--")
			{

				if (free == 2)
				{
					index += 2;
					return Op(current2);
				}
				auto current3 = str[index + 2];
				if (IgnoredChar(current3))
				{
					index += 3;
					return Op(current2);
				}
			}
		}
		return COperator::None;
	}
	std::string GetString(std::string str, int& index)
	{
		std::stringstream str2;
		bool on = true;
		std::string result;
		while (on)
		{
			if (index >= str.size())
			{
				throw "Invalid String";
			}
			else
			{
				if (str[index] == '\\')
				{
					if (index + 1 >= str.size())
					{
						throw "Invalid String";
					}
					auto val = str[index + 1];
					if (val == 'n')
					{
						str2 << '\n';
					}
					else if (val == 't')
					{
						str2 << '\t';
					}
					else if (val == 'r')
					{
						str2 << '\r';
					}
					else if (val == 'v')
					{
						str2 << '\v';
					}
					else if (val == 'f')
					{
						str2 << '\f';
					}
					else if (val == 'a')
					{
						str2 << '\a';
					}
					else if (val == 'b')
					{
						str2 << '\b';
					}
					else
					{
						str2 << str[index + 1];
					}
					index += 2;
				}
				else if (str[index] == '"')
				{
					result = str2.str();
					index++;
					on = false;
				}
				else
				{
					str2 << (str[index]);
					index++;
				}
			}
		}
		return result;
	}
	std::string GetLabel(std::string str, int& index)
	{
		std::stringstream str2;
		bool on = true;
		std::string result;
		while (on)
		{
			if (index >= str.size())
			{
				throw "Invalid String";
			}
			else
			{
				if (str[index] == '\\')
				{
					if (index + 1 >= str.size())
					{
						throw "Invalid String";
					}
					auto val = str[index + 1];
					if (val == 'n')
					{
						str2 << '\n';
					}
					else if (val == 't')
					{
						str2 << '\t';
					}
					else if (val == 'r')
					{
						str2 << '\r';
					}
					else if (val == 'v')
					{
						str2 << '\v';
					}
					else if (val == 'f')
					{
						str2 << '\f';
					}
					else if (val == 'a')
					{
						str2 << '\a';
					}
					else if (val == 'b')
					{
						str2 << '\b';
					}
					else
					{
						str2 << str[index + 1];
					}
					index += 2;
				}
				else if (str[index] == '\'')
				{
					result = str2.str();
					index++;
					on = false;
				}
				else
				{
					str2 << (str[index]);
					index++;
				}
			}
		}
		return result;
	}
	std::string GetLabel2(std::string str, int& index)
	{
		std::stringstream str2;
		bool on = true;
		std::string result;
		while (on)
		{
			if (index >= str.size())
			{
				throw "Invalid String";
			}
			else
			{
				auto current = str[index];
				if (IsSymbol(current))
				{
					str2 << current;
				}
				else if (isspace(current) || current == ')' || current == ';')
				{
					result = str2.str();
					on = false;
					break;
				}
				else
				{
					throw "Invalid String";
				}
				index++;
			}
		}
		return result;
	}
	std::string GetNumber(std::string str, int& index)
	{
		std::stringstream str2;
		bool on = true;
		bool numberadd = false;
		bool pontoadd = false;
		bool numberaddpoint = false;
		std::string result;
		while (on)
		{
			if (index >= str.size())
			{
				on = false;
				if (numberadd && !(pontoadd && !numberaddpoint))
				{
					result = str2.str();
					return result;
				}
				else
				{
					throw "Invalid Number";
				}

			}
			else
			{
				auto current = str[index];
				if (isdigit(current))
				{
					str2 << current;
					numberadd = true;
					if (pontoadd)
					{
						numberaddpoint = true;
					}
				}
				else if (current == '-' && !numberadd)
				{
					str2 << current;
				}
				else if (current == '.' && numberadd && !pontoadd)
				{
					str2 << current;
				}
				else if (isspace(current) || current == ';' || current == ')' && numberadd && !(pontoadd && !numberaddpoint))
				{
					result = str2.str();
					on = false;
					break;
				}
				else
				{
					throw "Invalid Number";
				}
				index++;
			}
		}
		return result;
	}
	std::vector<std::vector<CommandResult>> GetExpression2(std::string str, int& index)
	{
		std::vector<std::vector<CommandResult>> ret;
		std::vector<CommandResult> args;
		auto result = Next(str, index);
		while (result.index != -1 && result.resultType != ResultType::Undefined)
		{
			index = -1;
			if (result.resultType == ResultType::Label)
			{
				index = result.index;
				auto currentchar = str[index];
				if (currentchar == '\'')
				{
					index += 1;
					auto resultlabel = GetLabel(str, index);
					auto c = new std::string;
					*c = resultlabel;
					CommandResult val;
					val.resultType = result.resultType;
					val.value = c;
					args.push_back(val);
				}
				else
				{
					auto resultlabel = GetLabel2(str, index);
					auto c = new std::string;
					*c = resultlabel;
					CommandResult val;
					val.resultType = result.resultType;
					val.value = c;
					args.push_back(val);

				}
			}
			else if (result.resultType == ResultType::String)
			{
				index = result.index + 1;
				auto resultlabel = GetString(str, index);
				auto c = new std::string;
				*c = resultlabel;
				CommandResult val;
				val.resultType = result.resultType;
				val.value = c;
				args.push_back(val);
			}
			else if (result.resultType == ResultType::Operador)
			{
				index = result.index;
				auto val2 = GetOperador(str, index);
				auto c = new COperator;
				*c = val2;
				CommandResult val;
				val.resultType = result.resultType;
				val.value = c;
				args.push_back(val);
			}
			else if (result.resultType == ResultType::Number)
			{
				index = result.index;
				auto val = GetNumber(str, index);
				auto c = new std::string;
				*c = val;
				CommandResult val3;
				val3.resultType = result.resultType;
				val3.value = c;
				args.push_back(val3);
			}
			else if (result.resultType == ResultType::Expression)
			{
				index = result.index + 1;
				auto resultlabel = GetExpression2(str, index);
				auto c = new std::vector<std::vector<CommandResult>>;
				*c = resultlabel;
				CommandResult val3;
				val3.resultType = result.resultType;
				val3.value = c;
				args.push_back(val3);

			}
			else if (result.resultType == ResultType::Comment)
			{
				ret.push_back(args);
				args.clear();
				if (result.index != -1)
				{
					index = result.index + 1;
				}
			}
			if (index != -1 && index < str.size() && FindEndExpression(str, index))
			{
				ret.push_back(args);
				args.clear();
				index += 1;
				break;
			}
			result = Next(str, index);
		}
		if (args.size() > 0)
		{
			ret.push_back(args);
			args.clear();
		}
		return ret;
	}
	std::vector<std::vector<CommandResult>> GetArguments(std::string str)
	{
		std::vector<std::vector<CommandResult>> ret;
		std::vector<CommandResult> args;
		auto result = Next(str, 0);
		while (result.index != -1 && result.resultType != ResultType::Undefined)
		{
			auto index = -1;
			if (result.resultType == ResultType::Label)
			{
				index = result.index;
				auto currentchar = str[index];
				if (currentchar == '\'')
				{
					index++;
					auto resultlabel = GetLabel(str, index);
					auto c = new std::string;
					*c = resultlabel;
					CommandResult val;
					val.resultType = result.resultType;
					val.value = c;
					args.push_back(val);
				}
				else
				{
					auto resultlabel = GetLabel2(str, index);
					auto c = new std::string;
					*c = resultlabel;
					CommandResult val;
					val.resultType = result.resultType;
					val.value = c;
					args.push_back(val);

				}
			}
			else if (result.resultType == ResultType::String)
			{
				index = result.index + 1;
				auto resultlabel = GetString(str, index);
				auto c = new std::string;
				*c = resultlabel;
				CommandResult val;
				val.resultType = result.resultType;
				val.value = c;
				args.push_back(val);
			}
			else if (result.resultType == ResultType::Operador)
			{
				index = result.index;
				auto val2 = GetOperador(str, index);
				auto c = new COperator;
				*c = val2;
				CommandResult val;
				val.resultType = result.resultType;
				val.value = c;
				args.push_back(val);
			}
			else if (result.resultType == ResultType::Number)
			{
				index = result.index;
				auto val = GetNumber(str, index);
				auto c = new std::string;
				*c = val;
				CommandResult val3;
				val3.resultType = result.resultType;
				val3.value = c;
				args.push_back(val3);
			}
			else if (result.resultType == ResultType::Expression)
			{
				index = result.index + 1;
				auto resultlabel = GetExpression2(str, index);
				auto c = new std::vector<std::vector<CommandResult>>;
				*c = resultlabel;
				CommandResult val3;
				val3.resultType = result.resultType;
				val3.value = c;
				args.push_back(val3);

			}
			else if (result.resultType == ResultType::Comment)
			{
				ret.push_back(args);
				args.clear();
				if (result.index != -1)
				{
					index = result.index + 1;
				}
			}
			result = Next(str, index);
		}
		if (args.size() > 0)
		{
			ret.push_back(args);
			args.clear();
		}
		return ret;
	}
	std::string CommandResult::ToString()
	{
		return *((std::string*)this->value);
	}
	COperator CommandResult::ToOperador()
	{
		return *((COperator*)this->value);
	}
	std::vector<std::vector<CommandResult>> CommandResult::ToExpression()
	{
		return *((std::vector<std::vector<CommandResult>> *)this->value);
	}
	double CommandResult::ToDouble()
	{
		return std::stod(ToString());
	}
	int CommandResult::ToInt()
	{
		return std::stoi(ToString());
	}
	COperator Op(std::string type)
	{
		if (type == "+")
		{
			return COperator::Add;
		}
		else if (type == "-")
		{
			return COperator::Sub;
		}
		else if (type == "/")
		{
			return COperator::Div;
		}
		else if (type == "*")
		{
			return COperator::Mul;
		}
		else if (type == "%")
		{
			return COperator::Mod;
		}
		else if (type == "&&")
		{
			return COperator::And;
		}
		else if (type == "||")
		{
			return COperator::Or;
		}
		else if (type == ">")
		{
			return COperator::CmpG;
		}
		else if (type == "<")
		{
			return COperator::CmpL;
		}
		else if (type == "==")
		{
			return COperator::CmpE;
		}
		else if (type == "!=")
		{
			return COperator::CmpNE;
		}
		else if (type == ">=")
		{
			return COperator::CmpGE;
		}
		else if (type == "<=")
		{
			return COperator::CmpLE;
		}
		else if (type == "++")
		{
			return COperator::Inc;
		}
		else if (type == "--")
		{
			return COperator::Dec;
		}
		else
		{
			return COperator::None;
		}
	}
}
