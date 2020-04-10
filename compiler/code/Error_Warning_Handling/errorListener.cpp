#include "errorListener.h"
#include "../colors.h"

void ErrorListener::syntaxError(Recognizer *recognizer, Token * offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e)  {
         cerr<<BOLD(FRED("ERROR :"))<<" on position "<<line<<":"<<charPositionInLine << " " << msg <<endl;
         error = true;
}