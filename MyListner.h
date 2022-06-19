#include <sharkbitParser.h>
#include <string.h>

#include "sharkbitBaseListener.h";
#include "VariableContainer.h"
#include "Math.h";



using namespace sharkbit;


class MyListner : public sharkbitBaseListener
{
public:
	VariableContainer variableContainer;
	Math math;

	// mutable
	std::string muttable;

	// temporary to save variables
	bool assingable = true;
	std::string varName = "";
	std::string varValue = "";
	VariableGuts::VariableType varType;
	bool isConst = false;
	bool isPointer = false;



	void enterProgram(sharkbitParser::ProgramContext* ctx) override { }

	void enterVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		varName = "";
		varValue = "";
		math.a = "";
		isConst = false;
		isPointer = false;
		assingable = true;
	}

	void exitVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		if (varName == "" || varType == -1)
		{
			return;
		}
		if (assingable)
		{
			VariableGuts varGuts(varType, varValue, isConst);

			variableContainer.add(varName, varGuts);
		}
		// to debug
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
			return;
		}
		if (ctx->BOOL() != nullptr)
		{
			varType = VariableGuts::BOOL;
			return;
		}
		if (ctx->INT() != nullptr)
		{
			varType = VariableGuts::INT;
			return;
		}
		if (ctx->STRING() != nullptr)
		{
			varType = VariableGuts::STRING;
			return;
		}
		if (ctx->IP() != nullptr)
		{
			varType = VariableGuts::IP;
			return;
		}
		if (ctx->CHAR() != nullptr)
		{
			varType = VariableGuts::CHAR;
			return;
		}
	}

	void enterMutaable(sharkbitParser::MutaableContext* ctx) override 
	{
		if (ctx->ID() != nullptr)
		{
			std::string name = ctx->ID()->getText();

			math.MathExp(variableContainer[name].value);
		}
	}

	void enterConstSpec(sharkbitParser::ConstSpecContext* ctx) override
	{
		if (ctx->CONST() != nullptr)
		{
			isConst = true;
		}
	}

	void enterMathExp(sharkbitParser::MathExpContext* ctx) override {
	}

	void exitMathExp(sharkbitParser::MathExpContext*) override {
		varValue = math.getResult();
	}

	void enterMathOp(sharkbitParser::MathOpContext* ctx) override {
		math.oper_def(ctx->getText());

	}

	void enterConstant(sharkbitParser::ConstantContext* ctx) override {

		if (ctx->INTNUMBER() != nullptr) {
			if (varType != VariableGuts::INT)
			{
				cout << "ERROR: Cannot assign this value to this variable " << varName;
				assingable  = false;
				return;
			}
			math.MathExp(ctx->INTNUMBER()->getText());
		}
	}
};
