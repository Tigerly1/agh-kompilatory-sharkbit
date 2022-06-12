#include <iostream>

#include "antlr4-runtime.h"
#include "sharkbitLexer.h"
#include "sharkbitParser.h"
#include "sharkbitBaseListener.h"
#include "MyVisitor.h"

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
	std::string word = "? 5;";
	//std::string word = "? 3333 ;";

	ANTLRInputStream input(word);
	sharkbit::sharkbitLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	sharkbit::sharkbitParser parser(&tokens);

	/*
	antlr4::tree::ParseTree* tree = parser.program();
	TreeShapeListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
	*/

	
	MyVisitor myVisitor;

	myVisitor.visitProgram(parser.program());


	tokens.fill();
	for (Token* token : tokens.getTokens()) {
		std::cout << token->toString() << std::endl;
	}


	return 0;
}