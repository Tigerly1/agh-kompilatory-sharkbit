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


	//if conditions for proper working of if statement
	bool isInIfStatement = false;
	bool relExpIf = false;
	bool isElse = false;
	// temporary to save variables, set to its deafult values
	 
	bool assingable = true;
	std::string varName = "";
	std::string varValue = "";
	VariableGuts::VariableType varType = VariableGuts::NONE;
	bool isConst = false;
	bool isPointer = false;
	void enterSelectStmt(sharkbitParser::SelectStmtContext* ctx) override {
		isInIfStatement = true;
	}
	void exitSelectStmt(sharkbitParser::SelectStmtContext* ctx) override {
		isInIfStatement = false;
		relExpIf = false;
		isElse = false;
	}
	void enterStmt(sharkbitParser::StmtContext* ctx) override {
	}
	void exitStmt(sharkbitParser::StmtContext* ctx) override {
		if (ctx->parent->children.size() == 7) {
			if (ctx->parent->children[5]->getText() == "else" && relExpIf == false)isElse = true;
		}
	}
	void enterVarDecl(sharkbitParser::VarDeclContext* ctx) override
	{
		if (isInIfStatement && !relExpIf && !isElse) return;
		if(relExpIf)
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
		if (isInIfStatement && !relExpIf && !isElse) return;
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
		if (isInIfStatement && !relExpIf && !isElse) return;
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
		if (isInIfStatement && !relExpIf && !isElse) return;
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
		if (isInIfStatement && !relExpIf && !isElse) return;
		if (ctx->ID() != nullptr)
		{
			std::string name = ctx->ID()->getText();

			math.MathExp(variableContainer[name]->value);
		}
	}

	void enterConstSpec(sharkbitParser::ConstSpecContext* ctx) override
	{
		if (isInIfStatement && !relExpIf && !isElse) return;
		if (ctx->CONST() != nullptr)
		{
			isConst = true;
		}
	}
	void enterCompop(sharkbitParser::CompopContext* ctx) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
		math.compop_def(ctx->getText());
	}
	void enterRelExp(sharkbitParser::RelExpContext* ctx) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
		math.RemoveMathExpResults();
	}
	void exitRelExp(sharkbitParser::RelExpContext* ctx) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
		relExpIf = math.CompareResults();
		int b = 5;
	}
	void exitMathExp(sharkbitParser::MathExpContext*) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
		varValue = math.getResult();
		math.StoreMathExpResult();
		math.ClearInput();
	}

	void enterMathOp(sharkbitParser::MathOpContext* ctx) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
		math.oper_def(ctx->getText());

	}

	void exitCoutDecl(sharkbitParser::CoutDeclContext* ctx) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
		cout << math.getResult();
	}

	void enterConstant(sharkbitParser::ConstantContext* ctx) override {
		if (isInIfStatement && !relExpIf && !isElse) return;
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

};
