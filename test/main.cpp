#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>


typedef double(*MathAPI_Evaluate) (const char* str);
typedef void(*MathLib_Free)(void* commands);
typedef double(*MathLib_EvaluateFromCompile) (void* commands);
typedef void*(*MathLib_Compile) (const char* commands);

void StartConsole()
{
	auto handler = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handler, 9);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_MODERN;
	cfi.FontWeight = FW_NORMAL;
	auto facename = L"Lucida Console";
	wcsncpy_s(cfi.FaceName, facename, wcslen(facename)); // Choose your font
	SetCurrentConsoleFontEx(handler, FALSE, &cfi);
	SetConsoleTitle(L"MathCPP");
	setlocale(LC_ALL, "pt_BR.UTF-8");
}
void Test()
{
	auto lib = LoadLibrary(L"MathLib.dll");
	auto Compile = (MathLib_Compile)GetProcAddress(lib, "MathLib_Compile");
	auto EvaluateFromCompile = (MathLib_EvaluateFromCompile)GetProcAddress(lib, "MathLib_EvaluateFromCompile");
	auto Evaluate = (MathAPI_Evaluate)GetProcAddress(lib, "MathLib_Evaluate");

	// (#pow(3,2) /#sin(2*pi/2)) - 3 / 2)
	while (true)
	{
		std::string str;
		std::getline(std::cin, str);
		auto a = std::chrono::high_resolution_clock::now();
		auto result = Evaluate(str.c_str());
		auto b = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count();

		std::cout << str << " = " << result << std::endl;
		std::cout << duration << " ns" << std::endl;

	}
}
int main()
{
	
	StartConsole();

	Test();
	system("pause");
}
