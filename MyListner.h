#include <sharkbitParser.h>
#include <string.h>
#include <algorithm>

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

	void enterPointerVarDecl(sharkbitParser::PointerVarDeclContext* ctx) override
	{

	}

	void exitPointerVarDecl(sharkbitParser::PointerVarDeclContext* ctx) override
	{
		VariableGuts * varGuts;
		try
		{
			varGuts = variableContainer[ctx->ID()->getText()];

			if (varType != varGuts->type)
			{
				cerr << "ERROR: Cannot assign pointer of" << varType << " to " << VariableGuts::varTypeToString(varGuts->type);
			}

			std::string* ptr = &varGuts->value;
			std::stringstream ss;
			ss << ptr;
			varValue = ss.str();

			if (varType != VariableGuts::NONE)
			{
				VariableGuts varGuts(varType, varValue, isConst, true);
				variableContainer.add(varName, varGuts);
			}
		}
		catch (std::out_of_range& e)
		{
			cerr << "Variable " << ctx->ID()->getText() << " is not difined.";
		}
	}

	void enterIdDecl(sharkbitParser::IdDeclContext* ctx) override
	{
		varName = ctx->ID()->getText();
	}

	void enterVarDeclInit(sharkbitParser::VarDeclInitContext* ctx) override
	{
		varName = ctx->ID()->getText();
	}

	void exitVarDeclInit(sharkbitParser::VarDeclInitContext* ctx) override
	{
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

	void enterAssignPointer(sharkbitParser::AssignPointerContext* ctx) override
	{

	}

	void exitAssignPointer(sharkbitParser::AssignPointerContext* ctx) override
	{
		VariableGuts* varGuts;
		try
		{
			varGuts = variableContainer[ctx->ID()->getText()];

			if (varType != varGuts->type)
			{
				cerr << "ERROR: Cannot assign pointer of" << varType << " to " << VariableGuts::varTypeToString(varGuts->type);
			}

			std::string* value = varGuts->getValueFromPointer();
			*value = varValue;

		}
		catch (std::out_of_range& e)
		{
			cerr << "Variable " << ctx->ID()->getText() << " is not difined.";
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
		if (ctx->DOUBLE() != nullptr)
		{
			varType = VariableGuts::DOUBLE;
		}
		varType = VariableGuts::NONE;
	}

	void enterMutaable(sharkbitParser::MutaableContext* ctx) override 
	{
		if (ctx->children.size() == 1)
		{
			std::string name = ctx->ID()->getText();

			math.MathExp(variableContainer[name]->value);
		}
		if (ctx->children.size() == 2)
		{
			std::string pointedValue = ctx->ID()->getText();
			VariableGuts * varGuts = variableContainer[pointedValue];

			auto* str = varGuts->getValueFromPointer();

			if (str == nullptr)
			{
				cerr << "Variable \"" << varName << "\" is not a pointer.";
				return;
			}

			std::string value = *str;
			math.MathExp(value);
		}
	}

	void enterConstSpec(sharkbitParser::ConstSpecContext* ctx) override
	{
		if (ctx->CONST() != nullptr)
		{
			isConst = true;
		}
	}

	void enterCompop(sharkbitParser::CompopContext* ctx) override {

		math.compop_def(ctx->getText());
	}

	void enterRelExp(sharkbitParser::RelExpContext* ctx) override {
		math.RemoveMathExpResults();
	}

	void exitRelExp(sharkbitParser::RelExpContext* ctx) override {
		bool a = math.CompareResults();
		int b = 5;
	}

	void exitMathExp(sharkbitParser::MathExpContext*) override {
		varValue = math.getResult();
		math.StoreMathExpResult();
		math.ClearInput();
	}

	void enterMathOp(sharkbitParser::MathOpContext* ctx) override {
		math.oper_def(ctx->getText());
	}

	void exitCoutDecl(sharkbitParser::CoutDeclContext* ctx) override {
		cout << math.getResult();
	}

	void enterStmt(sharkbitParser::StmtContext* ctx) override { 
		

	}

	void enterConstant(sharkbitParser::ConstantContext* ctx) override {
		VariableGuts::VariableType declaredVarType;
		try {
			declaredVarType = variableContainer.getVarialbeType(varName);
		}
		catch (std::out_of_range& e)
		{
			declaredVarType = VariableGuts::NONE;
		}
		if (ctx->INTNUMBER() != nullptr) {
			if (varType == VariableGuts::INT || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::INT))
			{
				math.MathExp(ctx->INTNUMBER()->getText());
				return;
			}
			else
			{
				cerr << "ERROR: Cannot assign 'int' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
				assingable = false;
				return;
			}
		}

		if (ctx->STRING_CONST() != nullptr) {
			if (varType == VariableGuts::STRING || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::STRING))
			{
				// TODO:
				std::string str = ctx->STRING_CONST()->getText();
				str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
				math.setResult(str); 
				return;
			}
			else
			{
				cerr << "ERROR: Cannot assign 'string' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
				assingable = false;
				return;
			}
		}

		if (ctx->CHAR_CONST() != nullptr) {
			if (varType == VariableGuts::CHAR || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::CHAR))
			{
				std::string str = ctx->CHAR_CONST()->getText();
				str.erase(std::remove(str.begin(), str.end(), '\''), str.end());
				math.setResult(str);
			}
			else
			{
				cerr << "ERROR: Cannot assign 'char' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
				assingable = false;
				return;
			}
		}

		if (ctx->DOUBNUMBER() != nullptr) {
			if (varType == VariableGuts::DOUBLE || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::DOUBLE))
			{
				math.setResult(ctx->DOUBNUMBER()->getText());
				return;
			}
			else
			{
				cerr << "ERROR: Cannot assign 'double' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
				assingable = false;
				return;
			}
		}

		if (ctx->FALSE() != nullptr) {
			if (varType == VariableGuts::BOOL || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::BOOL))
			{
				math.setResult(ctx->FALSE()->getText());
				return;
			}
			else
			{
				cerr << "ERROR: Cannot assign 'bool' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
				assingable = false;
				return;
			}
		}

		if (ctx->TRUE() != nullptr) {
			if (varType == VariableGuts::BOOL || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::BOOL))
			{
				math.setResult(ctx->TRUE()->getText());
				return;
			}
			else
			{
				cerr << "ERROR: Cannot assign 'bool' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
				assingable = false;
				return;
			}
		}
		/*
		if (ctx->IP_CONST() != nullptr) {
		if (varType == VariableGuts::IP || (varType == VariableGuts::NONE && declaredVarType == VariableGuts::IP))
		{
			math.setResult(ctx->IP_CONST()->getText());
			return;
		}
		else
		{
			cerr << "ERROR: Cannot assign 'string' to variable typed: " << VariableGuts::varTypeToString(declaredVarType);
			assingable = false;
			return;
		}
	}
	*/
	}
};
