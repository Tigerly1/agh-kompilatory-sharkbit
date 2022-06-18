#include <string.h>



class VariableGuts{
public:
	enum VariableType
	{
		INT, BOOL, DOUBLE, STRING, IP, PROTOCOL, ADDRESS, FILE, PORT, CHAR, LIST
	};
	VariableType type;
	std::string value;
	bool isConst;

	VariableGuts(VariableType type, std::string value, bool isConst = false)
	{
		this->type = type;
		this->value = value;
		this->isConst = isConst;
	}

	std::string toString()
	{
		return type + " " + value;
	}
};