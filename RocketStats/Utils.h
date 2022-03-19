#pragma once

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include <functional>

#include <pch.h>
#include <tinyexpr/tinyexpr.h>

using namespace std;


class Utils
{
public:
	static LPSTR ConvertToLPSTR(const std::string& s);

	// Colors
	static float GetAlpha(std::vector<float> color, float opacity = 1.f);
	static ImColor GetImColor(std::vector<float> color, float opacity = 1.f);

	// Strings
	static std::string ljust(std::string str, size_t n, char c);
	static std::string tolower(std::string str);
	static std::string toupper(std::string str);
	static std::string capitalize(std::string str);
	static void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
	static void ReplaceVars(std::string& str, std::map<std::string, std::string>& vars, std::function<void(const std::string&, std::string&)> passe = nullptr);
	static std::string FloatFixer(float a_value, size_t n);
	static std::string FloatFixer(std::string str, size_t n);
	static std::string PointFixer(float a_value, size_t n, size_t md);

	// Arrays
	static std::vector<std::string> Split(const std::string& str, char delim);
	static std::map<std::string, int> SplitKeyInt(const std::string str, size_t offset = 0);
	static size_t FindKeyInt(std::vector<std::map<std::string, int>> vector, std::string key, int value);

	// Operations
	static int EvaluateExpression(std::string str, int percent2pixels);
};