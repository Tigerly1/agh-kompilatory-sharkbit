#include <string.h>



class VariableGuts{
public:
	enum VariableType
	{
		INT, BOOL, DOUBLE, STRING, IP, PROTOCOL, ADDRESS, FILE, PORT, CHAR, LIST,
	};
	VariableType type;
	std::string value;
	bool isConst;
	bool isPointer;

	VariableGuts(VariableType type, std::string value, bool isConst = false, bool isPointer = false)
	{
		this->type = type;
		this->value = value;
		this->isConst = isConst;
		this->isPointer = isPointer;
	}

	std::string toString()
	{
		return type + " " + value;
	}
};