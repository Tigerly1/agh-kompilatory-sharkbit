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
	std::string varName = "";
	std::string varValue = "";
	VariableGuts::VariableType varType;
	bool isConst = false;



	void enterProgram(sharkbitParser::ProgramContext* ctx) override { }

	void enterVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		varName = "";
		varValue = "";
		math.a = "";
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

	void enterMutaable(sharkbitParser::MutaableContext* ctx) override 
	{
		if (ctx->ID() != nullptr)
		{
			std::string name = ctx->ID()->getText();

			if (math.get_a().empty()) {
				math.init_a(variableContainer[name].value);
			}
			else {
				math.init_b(variableContainer[name].value);
			}
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
			if (math.get_a().empty()) {
				math.init_a(ctx->INTNUMBER()->getText());
			}
			else {
				math.init_b(ctx->INTNUMBER()->getText());
			}
		}
	}
};
