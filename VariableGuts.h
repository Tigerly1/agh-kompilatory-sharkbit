#include <string.h>



class VariableGuts{
public:
	enum VariableType
	{
		INT, BOOL, DOUBLE, STRING, IP, PROTOCOL, ADDRESS, FILE, PORT, CHAR, LIST, NONE
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
	static std::string varTypeToString(VariableType type)
	{
		switch (type)
		{
		case INT: return "INT";
		case BOOL: return "BOOL";
		case DOUBLE: return "DOUBLE";
		case STRING: return "STRING";
		case IP: return "IP";
		case PROTOCOL: return "PROTOCOL";
		case ADDRESS: return "ADDRESS";
		case FILE: return "FILE";
		case PORT: return "PORT";
		case CHAR: return "CHAR";
		case LIST: return "LIST";
		case NONE: return "NONE";

		default:
			return "UKNOWN TYPE";
		}
	}
	std::string *getValueFromPointer()
	{
		if (this->isPointer)
		{
			std::stringstream ss(this->value);
			std::uintptr_t temp;
			ss >> std::hex >> temp;

			auto* pp = reinterpret_cast<std::string*>(temp);
			return pp;
		}
		else
		{
			return nullptr;
		}
	}
};