#include <sharkbitParser.h>
#include <string.h>

#include "sharkbitBaseListener.h";
#include "VariableContainer.h"



using namespace sharkbit;


class MyListner : public sharkbitBaseListener
{
public:
	VariableContainer variableContainer;

	// temporary to save variables
	std::string varName = "";
	std::string varValue = "";
	VariableGuts::VariableType varType;
	bool isConst = false;



	void enterProgram(sharkbitParser::ProgramContext* ctx) override { }

	void enterVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		varName = "";
		varValue = "";
		isConst = false;
	}

	void exitVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		if (varName == "" || varValue == "" || varType == -1)
		{
			return;
		}
		VariableGuts varGuts(varType, varValue, isConst);

		variableContainer.add(varName, varGuts);
		int a = 2;
	}
	void enterVarDeclId(sharkbitParser::VarDeclIdContext* ctx) override 
	{
		varName = ctx->ID()->getText();
	}
	

	void enterTypeSpec(sharkbitParser::TypeSpecContext* ctx) override 
	{
		if (ctx->ADDRESS() != nullptr)
		{
			varType = VariableGuts::ADDRESS;
		}
		if (ctx->BOOL() != nullptr)
		{
			varType = VariableGuts::BOOL;
		}
		if (ctx->INT() != nullptr)
		{
			varType = VariableGuts::INT;
		}
		if (ctx->STRING() != nullptr)
		{
			varType = VariableGuts::STRING;
		}
		if (ctx->IP() != nullptr)
		{
			varType = VariableGuts::IP;
		}
		if (ctx->CHAR() != nullptr)
		{
			varType = VariableGuts::CHAR;
		}
	}

	void enterMathExp(sharkbitParser::MathExpContext* ctx) override 
	{
		// TODO: implement mathExp
		varValue = "2";
	}

	void enterConstSpec(sharkbitParser::ConstSpecContext* ctx) override
	{
		if (ctx->CONST() != nullptr)
		{
			isConst = true;
		}
	}
};
