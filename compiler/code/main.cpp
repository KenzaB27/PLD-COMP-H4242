#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <list>
#include <iterator>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"
#include "Error_Warning_Handling/errorListener.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{

  list<string> options;

  for (int i = 1; i < argn; i++)
  {
    options.push_back(argv[i]);
  }

  // We compile a file
  if (find(options.begin(), options.end(), "-S") != options.end())
  {

    // Looking for output file if given
    string inputFile;
    list<string>::iterator i1;
    string ext = ".c";
    for (i1 = options.begin(); i1 != options.end(); ++i1)
    {
      string temp = (string)*i1;
      if (temp.find(ext) != string::npos)
      {
        inputFile = temp;
        break;
      }
    }

    // Looking for output file if given
    string outputFile;
    list<string>::iterator itO = find(options.begin(), options.end(), "-o");
    if (itO != options.end())
    {
      advance(itO, 1);
      outputFile = *itO;
    }
    else
    {
      outputFile = inputFile.substr(0, inputFile.size() - 1) + "s";
    }

    // Compile the file
    stringstream in;
    ifstream lecture(inputFile);
    in << lecture.rdbuf();

    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    //  for (auto token : tokens.getTokens()) {
    //    std::cout << token->toString() << std::endl;
    //  }

    ifccParser parser(&tokens);

    ErrorListener errorlistener;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorlistener);

    tree::ParseTree *tree = parser.axiom();

    if (parser.getNumberOfSyntaxErrors() == 0)
    {
#ifdef DEBUG
      cout << "NO SYNTAX ERROR" << endl;
#endif
      Visitor visitor;
      visitor.visit(tree);
#ifdef DEBUG
      cout << "AFTER VISIT TREE" << endl;
#endif
      string assembly = visitor.returnAssembly(); //The assembly code returned by visitor.h
#ifdef DEBUG
      cout << "Assembly generated : " << endl;
      cout << assembly << endl;
#endif
      std::ofstream outfile;
      outfile.open(outputFile);
      outfile << assembly;
      // cout << assembly;
      outfile.close();
      if (find(options.begin(), options.end(), "-Wall") != options.end())
      {
        visitor.cfg->symbolTable->check_var_usage();
      }
    }
    else
    {
      return 1;
    }
  }
  else if (find(options.begin(), options.end(), "-h") != options.end())
  {
    cout << "Usage of ifcc : " << endl
         << "./ifcc -S [-o outputFile] [-Wall]        :   -Wall for warnings. " << endl
         << "-o outputFile:   -o to choose an output file. " << endl
         << "-S           :   -S to compile only. " << endl;

    return 0;
  }
  else
  {
    cout << "Missing arguments. Type `ifcc -h` to see alist of options" << endl;
    return 1;
  }

  return 0;
}
