#include "sharkbitVisitor.h";
#include <sharkbitParser.h>
#include <string.h>


using namespace sharkbit;

class MyVisitor :sharkbitVisitor
{
public:
	std::any visitProgram(sharkbitParser::ProgramContext* context)override
	{
		std::cout << "program running";

		return visitChildren(context);
	};
    std::any visitDeclList(sharkbitParser::DeclListContext* context)override
    {
        std::cout << "1 running";

        return visitChildren(context);
    };

    std::any visitDecl(sharkbitParser::DeclContext* context) override {
        std::cout << "2 running";

        return visitChildren(context);
    };

    std::any visitVarDecl(sharkbitParser::VarDeclContext* context) override
    {
        auto x = context->children[1]->children[0]->getTreeType();

        //std::cout << x;

        std::cout << "3 running";

        return visitChildren(context);
    };

    std::any visitVarDeclInit(sharkbitParser::VarDeclInitContext* context) override {
        std::cout << "4 running";

        return visitChildren(context);
    };

    std::any visitVarDeclId(sharkbitParser::VarDeclIdContext* context) override {
        std::cout << "5 running";

        return visitChildren(context);
    };

    std::any visitCoutDecl(sharkbitParser::CoutDeclContext* context) override {
        std::cout << "5 running";


        //char semicolon = std::any_cast<char>(visitChildren(context));
        //std::vector<std::any> numint = std::any_cast<std::vector < std::any >> (visitChildren(context));

        //int num_int = std::any_cast<int>(any_math);
        
        //std::cout << std::endl << num_int << std::endl;


        
        //std::vector<std::any> numint = std::any_cast<std::vector < std::any >> (visitChildren(context));


        // ? 5 ;

        auto hehehe = visitChildren(context);


        auto x = context->getText();


        std::vector<int> tokens;
        for (int i = 0; i < 64; i++)
        {
            std::vector a = context->getTokens(i);
            if (!a.empty())
            {
                tokens.push_back(i);
            }
        }


        return true;
    };

    std::any visitConstSpec(sharkbitParser::ConstSpecContext* context) override {
        std::cout << "6 running";


        return visitChildren(context);
    };

    std::any visitTypeSpec(sharkbitParser::TypeSpecContext* context) override {
        std::cout << "7 running";

        auto x = context->INT();


        return visitChildren(context);
    };

    std::any visitList(sharkbitParser::ListContext* context)override {
        std::cout << "8 running";

        return visitChildren(context);
    };

    std::any visitTypeDec(sharkbitParser::TypeDecContext* context) override {
        std::cout << "9 running";

        return visitChildren(context);
    };

    std::any visitPointerDec(sharkbitParser::PointerDecContext* context) override {
        std::cout << "10 running";

        return visitChildren(context);
    };

    std::any visitFunDecl(sharkbitParser::FunDeclContext* context) override {
        std::cout << "11 running";

        return visitChildren(context);
    };

    std::any visitParms(sharkbitParser::ParmsContext* context) override {
        std::cout << "12 running";

        return visitChildren(context);
    };

    std::any visitParmList(sharkbitParser::ParmListContext* context) override{
        std::cout << "13 running";

        return visitChildren(context);
    };

    std::any visitParmTypeList(sharkbitParser::ParmTypeListContext* context) override {
        std::cout << "14 running";

        return visitChildren(context);
    };

    std::any visitParmIdList(sharkbitParser::ParmIdListContext* context) override {
        std::cout << "15 running";

        return visitChildren(context);
    };

    std::any visitParmId(sharkbitParser::ParmIdContext* context) override {
        std::cout << "16 running";

        return visitChildren(context);
    };

    std::any visitStmt(sharkbitParser::StmtContext* context) override {
        std::cout << "17 running";

        return visitChildren(context);
    };

    std::any visitExpStmt(sharkbitParser::ExpStmtContext* context) override {
        std::cout << "18 running";

        return visitChildren(context);
    };

    std::any visitCompoundStmt(sharkbitParser::CompoundStmtContext* context) override {
        std::cout << "19 running";

        return visitChildren(context);
    };

    std::any visitStmtList(sharkbitParser::StmtListContext* context) override {
        std::cout << "20 running";

        return visitChildren(context);
    };

    std::any visitSelectStmt(sharkbitParser::SelectStmtContext* context) override {
        std::cout << "21 running";

        return visitChildren(context);
    };

    std::any visitIterStmt(sharkbitParser::IterStmtContext* context) override {
        std::cout << "22 running";

        return visitChildren(context);
    };

    std::any visitIterRange(sharkbitParser::IterRangeContext* context) override {
        std::cout << "23 running";

        return visitChildren(context);
    };

    std::any visitReturnStmt(sharkbitParser::ReturnStmtContext* context) override {
        std::cout << "24 running";

        return visitChildren(context);
    };

    std::any visitBreakStmt(sharkbitParser::BreakStmtContext* context) override {
        std::cout << "25 running";

        return visitChildren(context);
    };

    std::any visitSimpleExp(sharkbitParser::SimpleExpContext* context) override {
        std::cout << "26 running";

        return visitChildren(context);
    };

    std::any visitLogicalExp(sharkbitParser::LogicalExpContext* context) override {
        std::cout << "27 running";

        return visitChildren(context);
    };

    std::any visitUnaryRelExp(sharkbitParser::UnaryRelExpContext* context) override {
        std::cout << "28 running";

        return visitChildren(context);
    };

    std::any visitRelExp(sharkbitParser::RelExpContext* context) override {
        std::cout << "29 running";

        return visitChildren(context);
    };

    std::any visitCompop(sharkbitParser::CompopContext* context) override {
        std::cout << "30 running";

        return visitChildren(context);
    };

    std::any visitMathExp(sharkbitParser::MathExpContext* context) override
     {
        std::cout << "31 running";
       
        /*if (context->mathOp())

        context->factor +
        
        */ 

        //if (context->children[1]->getText() == "ADD")
        //{
        //auto factor = context->factor();

        //auto mathExp = context->mathExp();
        //}

        //int stop = 1;
        if (context->mathOp() == nullptr)
        {
            //int ret = std::any_cast<int>(visitChildren(context));
            //return ret;
            return visitChildren(context);
        }
        // 5 + 5
        //auto piatka = context->factor()->;
        if (context->mathOp()->ADD() != nullptr)
        {
            std::any x = visitChildren(context);
            return x;
        }
    };

    std::any visitMathOp(sharkbitParser::MathOpContext* context) override {
        std::cout << "32 running";

        return visitChildren(context);
    };

    std::any visitFactor(sharkbitParser::FactorContext* context) override {
        std::cout << "33 running";

        auto x = visitChildren(context);
        int numint = std::any_cast<int>(x);

        return x;
    };

    std::any visitMutaable(sharkbitParser::MutaableContext* context) override {
        std::cout << "34 running";

        return visitChildren(context);
    };

    std::any visitImmutable(sharkbitParser::ImmutableContext* context) override {
        std::cout << "35 running";

        auto x = visitChildren(context);
        int numint = std::any_cast<int>(x);

        return x;
    };

    std::any visitCall(sharkbitParser::CallContext* context) override {
        std::cout << "36 running";

        return visitChildren(context);
    };

    std::any visitArgs(sharkbitParser::ArgsContext* context) override {
        std::cout << "37 running";

        return visitChildren(context);
    };

    std::any visitArgList(sharkbitParser::ArgListContext* context) override  {
        std::cout << "38 running";

        return visitChildren(context);
    };

    std::any visitConstant(sharkbitParser::ConstantContext* context) override {
        std::cout << "39 running";


        if (context->CHAR_CONST() != nullptr)
        {
            return context->CHAR_CONST()->getText()[0];
        }
        auto x = context->INTNUMBER();

        if (context->INTNUMBER() != nullptr)
        {
            std::string intNumber = context->INTNUMBER()->getText();
            int ret = atoi(intNumber.c_str());
            return ret;
        }
        if (context->DOUBNUMBER() != nullptr)
        {
            throw _Notliteral_impl_;
        }

        return nullptr;
    };

};