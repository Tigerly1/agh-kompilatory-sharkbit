#include <sharkbitVisitor.h>
#include <sharkbitBaseVisitor.h>
#include <sharkbitParser.h>
#include <string.h>

using namespace std;

#include <sharkbitVisitor.h>
#include <sharkbitBaseVisitor.h>
#include <sharkbitParser.h>
#include <string.h>
#include <vector>

using namespace sharkbit;

class Math
{
public:
    string a;
    string b;
    string result;
    string operators;
    string compop;
    vector<string> mathExpResults;

    void MathExp(string number) {
        if (get_a().empty()) {
            init_a(number);
        }
        else {
            init_b(number);
        }
    }

    void init_a(string a_a) {
        a = a_a;

        result = a;
    }
    string get_a() {
        return a;
    }
    void init_b(string b_b) {
        b = b_b;
        this->start_math();
    }
    string get_b() {
        return b;
    }
    void oper_def(string op) {
        operators = op;
    };

    void compop_def(string compop_def) {
        this->compop = compop_def;
    }
    void StoreMathExpResult() {
        this->mathExpResults.push_back(this->result);
    }
    void RemoveMathExpResults() {
        this->mathExpResults.clear();
    }
    
    void start_math() {
        int res;
        if (operators == "+") res = std::stoi(a) + std::stoi(b);
        else if (operators == "-") res = std::stoi(a) - std::stoi(b);
        else if (operators == "/")  res = std::stoi(a) / std::stoi(b);
        else if (operators == "*")  res = std::stoi(a) * std::stoi(b);
        else if (operators == "%") res = std::stoi(a) % std::stoi(b);
        this->result = to_string(res);
        a = this->result;
    }
    bool CompareResults() {
        bool result;
        if (!this->compop.empty()) {
            if (this->compop == "<") {}
            else if (this->compop == "<=") result = std::stoi(this->mathExpResults.at(0)) <= std::stoi(this->mathExpResults.at(1));
            else if (this->compop == ">=") result = std::stoi(this->mathExpResults.at(0)) >= std::stoi(this->mathExpResults.at(1));
            else if (this->compop == "==") result = std::stoi(this->mathExpResults.at(0)) == std::stoi(this->mathExpResults.at(1));
            else if (this->compop == ">") result = std::stoi(this->mathExpResults.at(0)) > std::stoi(this->mathExpResults.at(1));
            else if (this->compop == "!=") result = std::stoi(this->mathExpResults.at(0)) != std::stoi(this->mathExpResults.at(1));
        }
        return result;
    }

    void ClearInput() {
        this->a = "";
        this->b = "";
    }
    string getResult() {
        return result;
    }
};