// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include "IR/CFG.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccVisitor.h"
#include "IR/symbolTable.h"
using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor
{

public:
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override;

    virtual antlrcpp::Any visitProgram(ifccParser::ProgramContext *ctx) override;

    virtual antlrcpp::Any visitElements(ifccParser::ElementsContext *ctx) override;

    virtual antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;

    virtual antlrcpp::Any visitBlockImplementation(ifccParser::BlockImplementationContext *ctx) override;

    virtual antlrcpp::Any visitInstructionIsBlock(ifccParser::InstructionIsBlockContext *ctx) override;

    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

    virtual antlrcpp::Any visitCodelines(ifccParser::CodelinesContext *ctx) override;

    virtual antlrcpp::Any visitCodeLine_InstructionLine(ifccParser::CodeLine_InstructionLineContext *context) override;

    virtual antlrcpp::Any visitCodeLine_Structure(ifccParser::CodeLine_StructureContext *context) override;

    virtual antlrcpp::Any visitStructure_IfCode(ifccParser::Structure_IfCodeContext *context) override;

    virtual antlrcpp::Any visitStructure_While(ifccParser::Structure_WhileContext *context) override;

    virtual antlrcpp::Any visitStructure_For(ifccParser::Structure_ForContext *context) override;

    virtual antlrcpp::Any visitStructure_Block(ifccParser::Structure_BlockContext *context) override;

    virtual antlrcpp::Any visitInstructionLine_Assignement(ifccParser::InstructionLine_AssignementContext *ctx) override;

    virtual antlrcpp::Any visitInstructionLine_Instruction(ifccParser::InstructionLine_InstructionContext *ctx) override;

    virtual antlrcpp::Any visitInstructionLine_ReturnCode(ifccParser::InstructionLine_ReturnCodeContext *ctx) override;

    virtual antlrcpp::Any visitInstructionLine_BreakCode(ifccParser::InstructionLine_BreakCodeContext *ctx) override;

    virtual antlrcpp::Any visitIfCode(ifccParser::IfCodeContext *ctx) override;

    virtual antlrcpp::Any visitElseCode(ifccParser::ElseCodeContext *ctx) override;

    virtual antlrcpp::Any visitElseIfCode(ifccParser::ElseIfCodeContext *ctx) override;

    virtual antlrcpp::Any visitWhileCode(ifccParser::WhileCodeContext *ctx) override;

    virtual antlrcpp::Any visitForCode(ifccParser::ForCodeContext *ctx) override;

    virtual antlrcpp::Any visitReturnCode(ifccParser::ReturnCodeContext *ctx) override;

    virtual antlrcpp::Any visitBreakCode(ifccParser::BreakCodeContext *ctx) override;

    virtual antlrcpp::Any visitAssignAndDeclare(ifccParser::AssignAndDeclareContext *ctx) override;

    virtual antlrcpp::Any visitDeclare(ifccParser::DeclareContext *ctx) override;

    virtual antlrcpp::Any visitAssignInstruction(ifccParser::AssignInstructionContext *ctx) override;

    virtual antlrcpp::Any visitAssignExpression(ifccParser::AssignExpressionContext *ctx) override;

    virtual antlrcpp::Any visitPostIncrement(ifccParser::PostIncrementContext *ctx) override;

    virtual antlrcpp::Any visitPreIncrement(ifccParser::PreIncrementContext *ctx) override;

    virtual antlrcpp::Any visitPostDecrement(ifccParser::PostDecrementContext *ctx) override;

    virtual antlrcpp::Any visitPreDecrement(ifccParser::PreDecrementContext *ctx) override;

    virtual antlrcpp::Any visitOp2(ifccParser::Op2Context *ctx) override;

    virtual antlrcpp::Any visitOp1(ifccParser::Op1Context *ctx) override;

    virtual antlrcpp::Any visitOpShift(ifccParser::OpShiftContext *context) override;

    virtual antlrcpp::Any visitOpGreaterless(ifccParser::OpGreaterlessContext *context) override;

    virtual antlrcpp::Any visitOpEqualNotEqual(ifccParser::OpEqualNotEqualContext *ctx) override;

    virtual antlrcpp::Any visitOpAndBitwise(ifccParser::OpAndBitwiseContext *context) override;

    virtual antlrcpp::Any visitOpXorBitwise(ifccParser::OpXorBitwiseContext *ctx) override;

    virtual antlrcpp::Any visitOpOrBitwise(ifccParser::OpOrBitwiseContext *context) override;

    virtual antlrcpp::Any visitOpAnd(ifccParser::OpAndContext *context) override;

    virtual antlrcpp::Any visitOpOr(ifccParser::OpOrContext *ctx) override;

    virtual antlrcpp::Any visitExprPreIncrement(ifccParser::ExprPreIncrementContext *context) override;

    virtual antlrcpp::Any visitExprPostIncrement(ifccParser::ExprPostIncrementContext *context) override;

    virtual antlrcpp::Any visitExprPreDecrement(ifccParser::ExprPreDecrementContext *context) override;

    virtual antlrcpp::Any visitExprPostDecrement(ifccParser::ExprPostDecrementContext *context) override;

    virtual antlrcpp::Any visitExprIdentifier(ifccParser::ExprIdentifierContext *ctx) override;

    virtual antlrcpp::Any visitExprParentheses(ifccParser::ExprParenthesesContext *ctx) override;

    virtual antlrcpp::Any visitExprNeg(ifccParser::ExprNegContext *ctx) override;

    virtual antlrcpp::Any visitExprSign(ifccParser::ExprSignContext *ctx) override;

    virtual antlrcpp::Any visitExprConst(ifccParser::ExprConstContext *ctx) override;

    virtual antlrcpp::Any visitMultipleIdentifiers(ifccParser::MultipleIdentifiersContext *ctx) override;

    virtual antlrcpp::Any visitSingleIdentifier(ifccParser::SingleIdentifierContext *ctx) override;

    string getVarMultConstAssembly(string codeExpr1, string varName0);

    void downRegisters();

    string returnAssembly();

    Expression *optimizeAS(Expression *expr1, string op, Expression *expr2);

    Expression *optimizeMDM(Expression *expr1, string op, Expression *expr2);
    
    CFG *cfg;

private:
    SymbolTable symbolTable;
    ostringstream assemblyCode;

};
