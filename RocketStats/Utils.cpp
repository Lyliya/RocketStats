#include "Utils.h"

#pragma region Colors
float Utils::GetAlpha(std::vector<float> color, float opacity)
{
    return (((color.size() == 4) ? color[3] : 1.f) * opacity);
}

ImColor Utils::GetImColor(std::vector<float> color, float opacity)
{
    return ImGui::ColorConvertFloat4ToU32({ (float(color[0]) / 255.f), (float(color[1]) / 255.f), (float(color[2]) / 255.f), GetAlpha(color, opacity) });
}
#pragma endregion

#pragma region Strings
std::string Utils::ljust(std::string str, size_t n, char c)
{
    size_t size = str.size();
    if (size >= n)
        return str;

    return str.replace(str.end(), str.end(), (n - size), c);
}

std::string Utils::toupper(std::string str)
{
    std::string upper;
    for (auto& c : str)
        upper += std::toupper(c);

    return upper;
}

void Utils::ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
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
    return Utils::FloatFixer(std::to_string(a_value), n);
}

std::string Utils::FloatFixer(std::string str, size_t n)
{
    size_t pos = str.find('.');
    if (pos != std::string::npos)
    {
        if (n)
            ++pos;

        str = str.substr(0, (pos + n));
    }

    return str;
}

std::string Utils::PointFixer(float a_value, size_t n, size_t md)
{
    std::string str = std::to_string(a_value);
    size_t pos = (str.find('.') + 1);
    size_t len = str.length();

    if (len < n)
    {
        str.insert((len - 1), (n - len), '0');

        len = str.length();
        if ((len - pos) < md)
            str.insert((len - 1), (md - (len - pos)), '0');
    }
    else if (!n)
        str = FloatFixer(str, 0);
    else if (len > n)
        str = FloatFixer(str, std::max((int(n) - int(pos)), int(md)));

    return str;
}
#pragma endregion

#pragma region Arrays
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
#pragma endregion

#pragma region Operations
std::string Utils::ExpressionSanitize(std::string str, int percent2pixels)
{
    char c;
    char lc;
    size_t pos;
    size_t lpos;

    ReplaceAll(str, " ", "");
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

void Utils::ProcessClosingParenthesis(std::vector<int>& vStack, std::vector<char>& opStack)
{
    while (opStack.back() != '(')
        ExecuteOperation(vStack, opStack);

    opStack.pop_back(); // Remove the opening parenthesis
}

int Utils::ProcessInputNumber(std::string& exp, int pos, std::vector<int>& vStack)
{
    int value = 0;
    while (pos < exp.length() && exp[pos] >= '0' && exp[pos] <= '9')
        value = ((10 * value) + (int)(exp[pos++] - '0'));

    vStack.push_back(value);

    return pos;
}

void Utils::ProcessInputOperator(char op, std::vector<int>& vStack, std::vector<char>& opStack)
{
    while (opStack.size() > 0 && OperatorCausesEvaluation(op, opStack.back()))
    {
        if ((op == '+' || op == '-') && (opStack.back() == '+' || opStack.back() == '-'))
        {
            bool positive = (op == opStack.back());
            bool negative = (op != opStack.back());
            if (positive || negative)
            {
                opStack.pop_back();
                opStack.push_back(positive ? '+' : '-');
                return;
            }
        }

        ExecuteOperation(vStack, opStack);
    }

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

void Utils::ExecuteOperation(std::vector<int>& vStack, std::vector<char>& opStack)
{
    char op = opStack.back(); opStack.pop_back();
    int rightOperand = vStack.back(); vStack.pop_back();
    int leftOperand = 0;
    if (vStack.size())
    {
        leftOperand = vStack.back();
        vStack.pop_back();
    }

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
