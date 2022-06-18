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
    void start_math() {
        if (operators == "+") add();
        else if (operators == "-") substract();
        else if (operators == "/") divide();
        else if (operators == "*") multiply();
    }
    void oper_def(string op) {
        operators = op;
        cout << op;
    };
    void add() {
        int res = std::stoi(a) + std::stoi(b);
        this->result = to_string(res);
        a = this->result;

    };
    void substract() {
        int res = std::stoi(a) - std::stoi(b);
        this->result = to_string(res);
        a = this->result;
    };
    void divide() {
        int res = std::stoi(a) / std::stoi(b);
        this->result = to_string(res);
        a = this->result;
    };
    void multiply() {
        int res = std::stoi(a) * std::stoi(b);
        this->result = to_string(res);
        a = this->result;
    };
    string getResult() {
        return result;
    }

};