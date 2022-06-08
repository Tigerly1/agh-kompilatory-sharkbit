#include <iostream>

#include "antlr4-runtime.h"
#include "sharkbitLexer.h"
#include "sharkbitParser.h"
#include "sharkbitBaseListener.h"

using namespace antlr4;

class TreeShapeListener : public sharkbit::sharkbitBaseListener {
public:
	void enterProgram(sharkbit::sharkbitParser::ProgramContext* ctx) override  {
		// Do something when entering the key rule.
		std::cout << ctx->parent;
		std::cout << "DZIAŁA KURWA AAA AA AAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	}
};


int main(int argc, const char* argv[]) {

	std::string word = "int main = 5;";
	ANTLRInputStream input(word);
	sharkbit::sharkbitLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	sharkbit::sharkbitParser parser(&tokens);
	antlr4::tree::ParseTree* tree = parser.program();
	TreeShapeListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
	tokens.fill();
	for (Token* token : tokens.getTokens()) {
		std::cout << token->toString() << std::endl;
	}

	return 0;
}