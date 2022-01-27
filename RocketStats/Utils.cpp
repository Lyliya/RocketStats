#include "Utils.h"

void Utils::ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
    //while (replace(str, from, to));
    if (from.empty())
        return;

    std::string::size_type start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Utils::ReplaceVars(std::string& str, std::map<std::string, std::string>& vars, std::function<void(const std::string&, std::string&)> passe)
{
    int i;
    int len = (int)str.length();
    int end = -1;

    for (i = (len - 1); i >= 0; --i)
    {
        if (end >= 0 && i > 0 && str[i] == '{' && str[i - 1] == '{')
        {
            const std::string key = str.substr((i + 1), ((end - 1) - (i + 1)));
            std::string value = ((vars.find(key) != vars.end()) ? vars[key] : "");

            if (passe != nullptr)
                passe(key, value);

            str.replace((i - 1), ((end + 1) - (i - 1)), value);
            end = -1;
        }
        else if (str[i] == '}' && i < (len - 1) && str[i + 1] == '}')
            end = (i + 1);
    }
}

std::string Utils::FloatFixer(float a_value, size_t n)
{
    std::string str = std::to_string(a_value);

    size_t pos = str.find('.');
    if (pos != std::string::npos)
    {
        if (n)
            ++pos;

        str = str.substr(0, (pos + n));
    }

    return str;
}

std::vector<std::string> Utils::Split(const std::string& str, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
        result.push_back(item);

    return result;
}

std::map<std::string, int> Utils::SplitKeyInt(const std::string str, size_t offset)
{
    std::map<std::string, int> result;
    std::vector<std::string> values = Split(str.substr(offset), ' ');

    for (const auto& value : values)
    {
        size_t value_assign = value.find('=');
        if (value_assign != std::string::npos)
        {
            std::string key = value.substr(0, value_assign);
            result.insert(std::make_pair(value.substr(0, value_assign), std::stoi(value.substr(value_assign + 1))));
        }
    }

    return result;
}

size_t Utils::FindKeyInt(std::vector<std::map<std::string, int>> vector, std::string key, int value)
{
    size_t index = 0;
    for (auto& map : vector)
    {
        if (map[key] == value)
            return index;

        ++index;
    }

    return std::string::npos;
}

#pragma region Colors
int Utils::OpacityColor(float opacity)
{
    return (int)std::max(0, std::min(255, (int)std::round(opacity * 255)));
}

char* Utils::GetColorAlpha(std::vector<float> color, float opacity)
{
    char result[] = { char(color[0]), char(color[1]), char(color[2]), char(255) };

    if (color.size() == 4)
        result[3] = OpacityColor(float(color[3]) * float(opacity));

    return result;
}
#pragma endregion

#pragma region Operations
std::string Utils::ExpressionSanitize(std::string str, int percent2pixels)
{
    char c;
    char lc;
    size_t pos;
    size_t lpos;

    for (pos = 0, lpos = std::string::npos; pos < str.length(); ++pos)
    {
        c = str[pos];
        if (pos)
            lc = str[pos - 1];

        bool error = ((c == '%' || c == 'p') && (!pos || (lc < '0' || lc > '9')));
        error = (error || (c == 'x' && (!pos || lc != 'p')));

        if (c == '%' && lpos != std::string::npos)
        {
            int percent = (std::stoi(str.substr(lpos, (pos - lpos))) / 100);
            str.replace(lpos, ((pos + 1) - lpos), std::to_string((int)std::round(percent * percent2pixels)));
            lpos = std::string::npos;
        }
        else if (lpos == std::string::npos)
            lpos = pos;

        if (error)
            throw std::invalid_argument("received bad string");
    }

    ReplaceAll(str, "px", "");

    return str;
}

int Utils::EvaluateExpression(std::string exp)
{
    std::vector<int> vStack;
    std::vector<char> opStack;

    opStack.push_back('('); // Implicit opening parenthesis

    int pos = 0;
    while (pos <= exp.length())
    {
        if (pos == exp.length() || exp[pos] == ')')
        {
            ProcessClosingParenthesis(vStack, opStack);
            pos++;
        }
        else if (exp[pos] >= '0' && exp[pos] <= '9')
        {
            pos = ProcessInputNumber(exp, pos, vStack);
        }
        else
        {
            ProcessInputOperator(exp[pos], vStack, opStack);
            pos++;
        }
    }

    int result = vStack.back();
    vStack.pop_back();

    return result; // Result remains on values stacks
}

void Utils::ProcessClosingParenthesis(std::vector<int> vStack, std::vector<char> opStack)
{
    while (opStack.back() != '(')
        ExecuteOperation(vStack, opStack);

    opStack.pop_back(); // Remove the opening parenthesis
}

int Utils::ProcessInputNumber(std::string exp, int pos, std::vector<int> vStack)
{
    int value = 0;
    while (pos < exp.length() && exp[pos] >= '0' && exp[pos] <= '9')
        value = ((10 * value) + (int)(exp[pos++] - '0'));

    vStack.push_back(value);

    return pos;
}

void Utils::ProcessInputOperator(char op, std::vector<int> vStack, std::vector<char> opStack)
{
    while (opStack.size() > 0 && OperatorCausesEvaluation(op, opStack.back()))
        ExecuteOperation(vStack, opStack);

    opStack.push_back(op);
}

bool Utils::OperatorCausesEvaluation(char op, char prevOp)
{
    bool evaluate = false;

    switch (op)
    {
    case '+':
    case '-':
        evaluate = (prevOp != '(');
        break;
    case '*':
    case '/':
        evaluate = (prevOp == '*' || prevOp == '/');
        break;
    case ')':
        evaluate = true;
        break;
    }

    return evaluate;
}

void Utils::ExecuteOperation(std::vector<int> vStack, std::vector<char> opStack)
{
    int rightOperand = vStack.back(); vStack.pop_back();
    int leftOperand = vStack.back(); vStack.pop_back();
    char op = opStack.back(); opStack.pop_back();

    int result = 0;
    switch (op)
    {
    case '+':
        result = (leftOperand + rightOperand);
        break;
    case '-':
        result = (leftOperand - rightOperand);
        break;
    case '*':
        result = (leftOperand * rightOperand);
        break;
    case '/':
        result = (leftOperand / rightOperand);
        break;
    }

    vStack.push_back(result);
}
#pragma endregion