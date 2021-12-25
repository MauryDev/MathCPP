void MathCompile()
{
	std::cout << "Digite a expressao\n";
	std::string s;
	std::getline(std::cin, s);
	std::string ex = "(pow $a 0.5)";
	auto test = Light::GetArguments(ex);
	for (auto val : test)
	{
		std::vector<MathCPP::VariableData> data;
		data.push_back(MathCPP::VariableData((char*)"a", std::stod(s)));
		auto res = MathCPP::Evaluate(val, data);
		std::cout << "A" << " = " << std::to_string(res);
	}
	Light::Free(test);

}
