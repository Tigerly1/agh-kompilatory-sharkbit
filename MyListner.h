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

	// temporary to save variables, set to its deafult values
	bool assingable = true;
	std::string varName = "";
	std::string varValue = "";
	VariableGuts::VariableType varType = VariableGuts::NONE;
	bool isConst = false;
	bool isPointer = false;

	void enterVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		varName = "";
		varType = VariableGuts::NONE;
		math.a = "";
		isConst = false;
		isPointer = false;
		assingable = true;
		varType = VariableGuts::NONE;
	}

	void exitVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		if (varName == "")
		{
			return;
		}
		if (assingable)
		{
			if (varType != VariableGuts::NONE)
			{
				VariableGuts varGuts(varType, varValue, isConst);
				variableContainer.add(varName, varGuts);
			}

		}
		// to debug
		int a = 2;
	}

	void enterVarDeclInit(sharkbitParser::VarDeclInitContext* ctx) override
	{
		
	}

	void exitVarDeclInit(sharkbitParser::VarDeclInitContext* ctx) override
	{
		varName = ctx->ID()->getText();

		if (varType == VariableGuts::NONE)
		{
			try
			{
				VariableGuts* varGuts = variableContainer[varName];

				//std::string* value = &variableContainer[varName].value;
				if (varGuts->isConst)
				{
					cerr << "Variable \"" << varName << "\" is const. You cannot change it.\n";
				}
				else
				{
					variableContainer[varName]->value = varValue;
				}
			}
			catch (std::out_of_range& e)
			{
				cerr << e.what() << endl;
			}
		}

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
		varType = VariableGuts::NONE;
	}

	void enterMutaable(sharkbitParser::MutaableContext* ctx) override 
	{
		if (ctx->ID() != nullptr)
		{
			std::string name = ctx->ID()->getText();

			math.MathExp(variableContainer[name]->value);
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
			if (varType != VariableGuts::INT && varType != VariableGuts::NONE)
			{
				cerr << "ERROR: Cannot assign this value to this variable " << varName;
				assingable  = false;
				return;
			}
			math.MathExp(ctx->INTNUMBER()->getText());
		}
	}

	void exitCoutDecl(sharkbitParser::CoutDeclContext* ctx) override {
		cout << math.getResult();
	}
};
