#include <map>
#include <string.h>
#include "VariableGuts.h"


class VariableContainer
{
public:
	std::map<std::string, VariableGuts> contrainer;


	bool add(std::string varName, VariableGuts varGuts)
	{
		if (!contrainer.count(varName))
		{
			contrainer.insert({ varName, varGuts });
			return true;
		}
		else
		{
			std::cout << "ERROR: there is already var with that name";
			return false;
		}
	}

	VariableGuts getCopyOf(std::string varName)
	{
		std::map<std::string, VariableGuts>::iterator it = contrainer.find(varName);

		if (it == contrainer.end()) {
			throw std::out_of_range("Variable not found exception, " + varName);
			std::cout << "ERROR: No variable called: " << varName;
		}
		else {
			return it->second;
		}

	}
	VariableGuts * operator[](std::string varName)
	{
		std::map<std::string, VariableGuts>::iterator it = contrainer.find(varName);

		if (it == contrainer.end()) {
			throw std::out_of_range("Variable not found exception.\n");
			std::cout << "ERROR: No variable called: " << varName;
		}
		else {
			VariableGuts * ret =  &it->second;
			return ret;
		}

	}
};