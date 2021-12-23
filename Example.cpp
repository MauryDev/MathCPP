void MathCompile()
{
	std::cout << "Digite a expressao\n";
	std::string s;
	std::getline(std::cin, s);

	auto test = Light::GetArguments(s);
	for (auto val : test)
	{
		std::cout << s << " = " << std::to_string(MathCPP::Evaluate(val));
	}
	Light::Free(test);

}
