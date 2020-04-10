#include <iostream>

#include "antlr4-runtime.h"
#include "../antlr4-generated/ifccLexer.h"
#include "../antlr4-generated/ifccParser.h"
#include "../antlr4-generated/ifccBaseVisitor.h"

using namespace antlr4;
using namespace std;

class ErrorListener : public BaseErrorListener {
    public:
      ErrorListener() { error = false; }
      bool Error() { return error; }
      virtual void syntaxError(Recognizer *recognizer, Token * offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e);

   protected:
      bool error;

};