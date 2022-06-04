# MathCPP

My first library for Math dynamic.


## Performance

Example 1:
```cpp
void Test2()
{
	auto lib = LoadLibrary(L"MathLib.dll");
	auto Evaluate = (MathAPI_Evaluate)GetProcAddress(lib, "MathLib_Evaluate");
	const char* str = "2 * pi";
	for (size_t i = 0; i < 10; i++)
	{
		auto a = std::chrono::high_resolution_clock::now();
		auto result = Evaluate(str);
		auto b = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count();
		std::cout << str << " = " << result << std::endl;
		std::cout << duration << " ns" << std::endl;
	}
}
```

![image](https://user-images.githubusercontent.com/41791247/171986700-d7508e56-81a7-4f85-8a8d-cd863fc4a1d2.png)

Example 2:
```cpp
void Test2()
{
	auto lib = LoadLibrary(L"MathLib.dll");
	auto Evaluate = (MathAPI_Evaluate)GetProcAddress(lib, "MathLib_Evaluate");
	const char* str = "#sin(2.2 * 2) + #cos(pi / 3)";
	for (size_t i = 0; i < 10; i++)
	{
		auto a = std::chrono::high_resolution_clock::now();
		auto result = Evaluate(str);
		auto b = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count();
		std::cout << str << " = " << result << std::endl;
		std::cout << duration << " ns" << std::endl;
	}
}
```
![bandicam 2022-06-04 03-13-36-515](https://user-images.githubusercontent.com/41791247/171987138-0024190a-118d-45d2-8010-3e73084aeb93.jpg)


