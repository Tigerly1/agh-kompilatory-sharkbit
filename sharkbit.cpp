#include <iostream>
#include "antlr4-runtime.h"
#include "sharkbitLexer.h"
#include "sharkbitParser.h"
#include "sharkbitBaseListener.h"
#include "MyVisitor.h"
#include "MyListner.h"

using namespace antlr4;
class TreeShapeListener : public sharkbit::sharkbitBaseListener {
public:
	void enterProgram(sharkbit::sharkbitParser::ProgramContext* ctx) override  {
		// Do something when entering the key rule.
		std::cout << ctx->declList() << std::endl;
		//std::cout << "DZIAŁA KURWA AAA AA AAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	}
};


int main(int argc, const char* argv[]) {
    std::string word = "int a = 2; a = 3; const int b = 12; b = 2; d = 3; ";
    ANTLRInputStream input(word);
    sharkbit::sharkbitLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    sharkbit::sharkbitParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();

    MyListner listener;
    listener.enterProgram(parser.program());
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);


    return 0;
}