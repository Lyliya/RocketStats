#pragma once

#include <map>
#include <string>
#include <sstream>
#include <vector>
//#include <utils/parser.h>

using namespace std;


class Utils
{
public:
	static void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
	static std::vector<std::string> Split(const std::string& str, char delim);
	static std::map<std::string, int> SplitKeyInt(const std::string str, size_t offset = 0);
	static size_t FindKeyInt(std::vector<std::map<std::string, int>> vector, std::string key, int value);

	// Operations
	static std::string ExpressionSanitize(std::string str, int percent2pixels);
	static int EvaluateExpression(std::string exp);
	static void ProcessClosingParenthesis(std::vector<int> vStack, std::vector<char> opStack);
	static int ProcessInputNumber(std::string exp, int pos, std::vector<int> vStack);
	static void ProcessInputOperator(char op, std::vector<int> vStack, std::vector<char> opStack);
	static bool OperatorCausesEvaluation(char op, char prevOp);
	static void ExecuteOperation(std::vector<int> vStack, std::vector<char> opStack);
};