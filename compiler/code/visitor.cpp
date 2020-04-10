
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

#include "colors.h"


#include "IR/CFG.h"
#include "IR/BasicBlock.h"

#include "AST/DefFunction.h"

#include "AST/Block.h"

#include "AST/CodeLine/CodeLine.h"

#include "AST/CodeLine/InstructionLine/InstructionLine.h"

#include "AST/CodeLine/InstructionLine/Assignement/AssignAndDeclare.h"
#include "AST/CodeLine/InstructionLine/Assignement/Assignement.h"
#include "AST/CodeLine/InstructionLine/Assignement/Declare.h"

#include "AST/CodeLine/InstructionLine/Instruction/Instruction.h"
#include "AST/CodeLine/InstructionLine/Instruction/AssignExpression.h"
#include "AST/CodeLine/InstructionLine/Instruction/AssignInstruction.h"
#include "AST/CodeLine/InstructionLine/Instruction/PostDecrement.h"
#include "AST/CodeLine/InstructionLine/Instruction/PreDecrement.h"
#include "AST/CodeLine/InstructionLine/Instruction/PostIncrement.h"
#include "AST/CodeLine/InstructionLine/Instruction/PreIncrement.h"

#include "AST/CodeLine/InstructionLine/ReturnCode/returnCode.h"
#include "AST/CodeLine/InstructionLine/BreakCode/breakCode.h"

#include "AST/Expression/Expression.h"
#include "AST/Expression/ExpressionIncrDecr.h"
#include "AST/Expression/ExpressionSign.h"
#include "AST/Expression/ExpressionNeg.h"
#include "AST/Expression/ExpressionOP1.h"
#include "AST/Expression/ExpressionOP2.h"
#include "AST/Expression/ExpressionOPBool.h"
#include "AST/Expression/ExpressionOPShift.h"
#include "AST/Expression/ExpressionParentheses.h"
#include "AST/Expression/ExpressionConst.h"
#include "AST/Expression/ExpressionIdentifier.h"

#include "AST/CodeLine/Structure/WhileCode.h"
#include "AST/CodeLine/Structure/ForCode.h"
#include "AST/CodeLine/Structure/IfCode.h"
#include "AST/CodeLine/Structure/ConditionalStruct.h"

/** This class implements the visitors declared in its interface visitor.h
Each of the methods takes the context in which it is called as a parameter and returns a string. The
string corresponds to the assembly lines of the visitor's algorithm.
The goal is to gradually generate the body assembly lines so that at the end of the program's review
we can achieve  a complete assembly code for all the program bu using recursion and polymorphism **/

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitProgram(ifccParser::ProgramContext *ctx)
{
    int size = ctx->elements().size();

#ifdef DEBUG
    cout << size << endl;
    cout << "visitProgram Debut" << endl;
#endif

    SymbolTable *symbolTable = new SymbolTable();
    DefFunction *function = visit(ctx->elements(0));

#ifdef DEBUG
    cout << "return from visit" << endl;
#endif

    cfg = new CFG(function, symbolTable);

#ifdef DEBUG
    cout << "after cfg creation" << endl;
#endif

    cfg->ast->getIR(cfg->getCurrentBlock());

#ifdef DEBUG
    cout << "before gen asm" << endl;
    cout << "number of instruction in bb " + to_string((*(cfg->getCurrentBlock()))->instrs.size()) << endl;
#endif

    cfg->gen_asm(assemblyCode);

#ifdef DEBUG
    cout << "VisitProgram Ended" << endl;
    cout << returnAssembly() << endl;
#endif
    return 0;
}

antlrcpp::Any Visitor::visitElements(ifccParser::ElementsContext *ctx)
{
#ifdef DEBUG
    cout << "visitElements Debut" << endl;
#endif

    DefFunction *function = visit(ctx->function());
    return function;
}

antlrcpp::Any Visitor::visitFunction(ifccParser::FunctionContext *ctx)
{
#ifdef DEBUG
    cout << "visitFunction Debut" << endl;
#endif
    Block *block = this->visit(ctx->block());
    return new DefFunction(block, MAIN);
}

antlrcpp::Any Visitor::visitBlockImplementation(ifccParser::BlockImplementationContext *ctx)
{
#ifdef DEBUG
    cout << "visitBlockImplementation Debut" << endl;
#endif
    return visit(ctx->block());
}

antlrcpp::Any Visitor::visitInstructionIsBlock(ifccParser::InstructionIsBlockContext *ctx)
{
#ifdef DEBUG
    cout << "visitInstructionIsBlock Debut" << endl;
#endif
    InstructionLine *instr = visit(ctx->instructionLine());
    CodeLine *code = instr;
    vector<CodeLine *> instruction;
    instruction.push_back(code);
    return new Block(instruction);
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *ctx)
{
#ifdef DEBUG
    cout << "visitBlock Debut" << endl;
#endif
    vector<CodeLine *> codeLines = this->visit(ctx->codelines());
    return new Block(codeLines);
}

antlrcpp::Any Visitor::visitCodelines(ifccParser::CodelinesContext *ctx)
{
#ifdef DEBUG
    cout << "visitCodelines Debut" << endl;
#endif
    int size = ctx->codeline().size();
    vector<CodeLine *> codeLines;
    for (int i = 0; i < size; i++)
    {
        codeLines.push_back(this->visit(ctx->codeline(i)));
    }
    return codeLines;
}

antlrcpp::Any Visitor::visitCodeLine_InstructionLine(ifccParser::CodeLine_InstructionLineContext *ctx)
{
#ifdef DEBUG
    cout << "visitCodeLine_InstructionLine Debut" << endl;
#endif
    // TODO rethink this
    InstructionLine *instr = visit(ctx->instructionLine());
    CodeLine *code = instr;
    return code;
}

antlrcpp::Any Visitor::visitCodeLine_Structure(ifccParser::CodeLine_StructureContext *ctx)
{
#ifdef DEBUG
    cout << "visitCodeLine_Structure Debut" << endl;
#endif
    Structure *structure = visit(ctx->structure());
    CodeLine *code = structure;
    return code;
}

antlrcpp::Any Visitor::visitStructure_IfCode(ifccParser::Structure_IfCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitStructure_IfCode Debut" << endl;
#endif
    ConditionalStruct *cond = visit(ctx->ifCode());
    Structure *structure = cond;
    return structure;
}

antlrcpp::Any Visitor::visitStructure_While(ifccParser::Structure_WhileContext *ctx)
{
#ifdef DEBUG
    cout << "visitStructure_IfCode Debut" << endl;
#endif
    WhileCode *whileCode = this->visit(ctx->whileCode());
    Structure *structure = whileCode;
    return structure;
}

antlrcpp::Any Visitor::visitStructure_For(ifccParser::Structure_ForContext *ctx)
{
#ifdef DEBUG
    cout << "visitStructure_For Debut" << endl;
#endif
    ForCode *forCode = this->visit(ctx->forCode());
    Structure *structure = forCode;
    return structure;
}

antlrcpp::Any Visitor::visitStructure_Block(ifccParser::Structure_BlockContext *ctx)
{
#ifdef DEBUG
    cout << "visitStructure_Block Debut" << endl;
#endif
    Block *block = visit(ctx->block());
    Structure *structure = block;
    return structure;
}

antlrcpp::Any Visitor::visitInstructionLine_Assignement(ifccParser::InstructionLine_AssignementContext *ctx)
{
#ifdef DEBUG
    cout << "visitInstructionLine_Assignement Debut" << endl;
#endif
    Assignement *assign = this->visit(ctx->assignement());
    InstructionLine *instrLine = assign;
    return instrLine;
}

antlrcpp::Any Visitor::visitInstructionLine_Instruction(ifccParser::InstructionLine_InstructionContext *ctx)
{
#ifdef DEBUG
    cout << "visitInstructionLine_Instruction Debut" << endl;
#endif
    Instruction *instr = this->visit(ctx->instruction());
    InstructionLine *instrLine = instr;
    return instrLine;
}

antlrcpp::Any Visitor::visitInstructionLine_ReturnCode(ifccParser::InstructionLine_ReturnCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitInstructionLine_ReturnCode Debut" << endl;
#endif
    ReturnCode *returnC = this->visit(ctx->returnCode());
    InstructionLine *instrLine = returnC;
    return instrLine;
}

antlrcpp::Any Visitor::visitInstructionLine_BreakCode(ifccParser::InstructionLine_BreakCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitInstructionLine_BreakCode Debut" << endl;
#endif
    BreakCode *breakC = this->visit(ctx->breakCode());
    InstructionLine *instrLine = breakC;
    return instrLine;
}

antlrcpp::Any Visitor::visitIfCode(ifccParser::IfCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitIfCode Debut" << endl;
#endif
    Expression *expression = visit(ctx->expression());
    Block *block = visit(ctx->blockOrLine());
    int size = ctx->elseIfCode().size();
    vector<IfCode *> elseIfCodes;
    for (int i = 0; i < size; i++)
    {
        elseIfCodes.push_back(visit(ctx->elseIfCode(i)));
    }
    Block *elseCode;
    if (ctx->elseCode() != NULL)
    {
        elseCode = visit(ctx->elseCode());
    }
    else
    {
        elseCode = nullptr;
    }
    return new ConditionalStruct(expression, block, elseIfCodes, elseCode);
}

antlrcpp::Any Visitor::visitElseCode(ifccParser::ElseCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitElseCode Debut" << endl;
#endif
    return visit(ctx->blockOrLine());
}

antlrcpp::Any Visitor::visitElseIfCode(ifccParser::ElseIfCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitElseIfCode Debut" << endl;
#endif
    Expression *expression = visit(ctx->expression());
    Block *block = visit(ctx->blockOrLine());
    return new IfCode(expression, block);
}

antlrcpp::Any Visitor::visitWhileCode(ifccParser::WhileCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitWhileCode Debut" << endl;
#endif
    Expression *expression = this->visit(ctx->expression());
    Block *block = this->visit(ctx->blockOrLine());
    return new WhileCode(expression, block);
}

antlrcpp::Any Visitor::visitForCode(ifccParser::ForCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitForCode Debut" << endl;
#endif
    InstructionLine *initialisation = visit(ctx->instructionLine());
    Expression *condition = visit(ctx->expression());
    Instruction *iteration = visit(ctx->instruction());
    Block *block = visit(ctx->blockOrLine());
    return new ForCode(initialisation, condition, iteration, block);
}

antlrcpp::Any Visitor::visitReturnCode(ifccParser::ReturnCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitReturnCode Debut" << endl;
#endif
    Expression *expression = this->visit(ctx->expression());
    return new ReturnCode(expression);
}

antlrcpp::Any Visitor::visitBreakCode(ifccParser::BreakCodeContext *ctx)
{
#ifdef DEBUG
    cout << "visitBreakCode Debut" << endl;
#endif
    return new BreakCode();
}

antlrcpp::Any Visitor::visitAssignAndDeclare(ifccParser::AssignAndDeclareContext *ctx)
{
#ifdef DEBUG
    cout << "visitAssignAndDeclare Debut" << endl;
#endif
    string affect = ctx->AFFECT()->getText();
    if ( affect != "=")
    {
        //error :  += -= *= /= not allowed in declaration
        std::cerr << BOLD(FRED("ERROR :" ))<<"'"<< affect  <<"' operation not allowed in declaration." << endl;
        exit(0);
    }
    vector<string> identifiers;
    string identifier = this->visit(ctx->identifier());
    istringstream ids(identifier);
    string id;
    while (getline(ids, id, ','))
    {
        identifiers.push_back(id);
    }

    Expression *expr = this->visit(ctx->expression());
    return (Assignement *)new AssignAndDeclare(identifiers, expr);
}

antlrcpp::Any Visitor::visitDeclare(ifccParser::DeclareContext *ctx)
{
#ifdef DEBUG
    cout << "visitDeclare Debut" << endl;
#endif
    vector<string> identifiers;
    string identifier = this->visit(ctx->identifier());
    istringstream ids(identifier);
    string id;
    while (getline(ids, id, ','))
    {
        identifiers.push_back(id);
    }
    return (Assignement *)new Declare(identifiers);
}

antlrcpp::Any Visitor::visitAssignInstruction(ifccParser::AssignInstructionContext *ctx)
{
#ifdef DEBUG
    cout << "visitAssignInstruction Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    string affect = ctx->AFFECT()->getText();
    Instruction *instruction = this->visit(ctx->instruction());
    return (Instruction *)new AssignInstruction(identifier, affect, instruction);
}

antlrcpp::Any Visitor::visitAssignExpression(ifccParser::AssignExpressionContext *ctx)
{
#ifdef DEBUG
    cout << "visitAssignExpression Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    string affect = ctx->AFFECT()->getText();
    Expression *expression = this->visit(ctx->expression());
    return (Instruction *)new AssignExpression(identifier, affect, expression);
}

antlrcpp::Any Visitor::visitPostIncrement(ifccParser::PostIncrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitPostIncrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Instruction *)new PostIncrement(identifier);
}

antlrcpp::Any Visitor::visitPreIncrement(ifccParser::PreIncrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitPreIncrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Instruction *)new PreIncrement(identifier);
}

antlrcpp::Any Visitor::visitPostDecrement(ifccParser::PostDecrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitPostDecrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Instruction *)new PostDecrement(identifier);
}

antlrcpp::Any Visitor::visitPreDecrement(ifccParser::PreDecrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitPreDecrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Instruction *)new PreDecrement(identifier);
}

antlrcpp::Any Visitor::visitOp2(ifccParser::Op2Context *ctx)
{
#ifdef DEBUG
    cout << "visitOp2 Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    string op2 = ctx->OP2()->getText();
    return optimizeAS(expr1, op2, expr2);
}

antlrcpp::Any Visitor::visitOp1(ifccParser::Op1Context *ctx)
{
#ifdef DEBUG
    cout << "visitOp1 Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    string op1 = ctx->OP1()->getText();
    return optimizeMDM(expr1, op1, expr2);
}

antlrcpp::Any Visitor::visitExprPreIncrement(ifccParser::ExprPreIncrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprPreIncrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Expression *)new ExpressionIncrDecr(identifier, ExpressionIncrDecr::PREINCREMENT);
}

antlrcpp::Any Visitor::visitExprPostIncrement(ifccParser::ExprPostIncrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprPostIncrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Expression *)new ExpressionIncrDecr(identifier, ExpressionIncrDecr::POSTINCREMENT);
}

antlrcpp::Any Visitor::visitExprPreDecrement(ifccParser::ExprPreDecrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprPreDecrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Expression *)new ExpressionIncrDecr(identifier, ExpressionIncrDecr::PREDECREMENT);
}

antlrcpp::Any Visitor::visitExprPostDecrement(ifccParser::ExprPostDecrementContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprPostDecrement Debut" << endl;
#endif
    string identifier = ctx->IDENTIFIER()->getText();
    return (Expression *)new ExpressionIncrDecr(identifier, ExpressionIncrDecr::POSTDECREMENT);
}

antlrcpp::Any Visitor::visitExprIdentifier(ifccParser::ExprIdentifierContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprIdentifier Debut" << endl;
#endif
    string name = ctx->IDENTIFIER()->getText();
    return (Expression *)new ExpressionIdentifier(name);
}

antlrcpp::Any Visitor::visitOpShift(ifccParser::OpShiftContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpShift Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    string opShift = ctx->OPShift()->getText();
    return (Expression *)new ExpressionOPShift(expr1, opShift, expr2);
}

antlrcpp::Any Visitor::visitOpGreaterless(ifccParser::OpGreaterlessContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpGreaterless Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    string opGL = ctx->OPGL()->getText();
    return (Expression *)new ExpressionOPBool(expr1, opGL, expr2);
}

antlrcpp::Any Visitor::visitOpEqualNotEqual(ifccParser::OpEqualNotEqualContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpEqualNotEqual Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    string OPEN = ctx->OPEN()->getText();
    return (Expression *)new ExpressionOPBool(expr1, OPEN, expr2);
}

antlrcpp::Any Visitor::visitOpXorBitwise(ifccParser::OpXorBitwiseContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpOrBitwise Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    return (Expression *)new ExpressionOPBool(expr1, "^", expr2);
}

antlrcpp::Any Visitor::visitOpOrBitwise(ifccParser::OpOrBitwiseContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpOrBitwise Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    return (Expression *)new ExpressionOPBool(expr1, "|", expr2);
}

antlrcpp::Any Visitor::visitOpOr(ifccParser::OpOrContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpOr Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    return (Expression *)new ExpressionOPBool(expr1, "||", expr2);
}

antlrcpp::Any Visitor::visitOpAnd(ifccParser::OpAndContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpAnd Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    return (Expression *)new ExpressionOPBool(expr1, "&&", expr2);
}

antlrcpp::Any Visitor::visitOpAndBitwise(ifccParser::OpAndBitwiseContext *ctx)
{
#ifdef DEBUG
    cout << "visitOpAndBitwise Debut" << endl;
#endif
    Expression *expr1 = this->visit(ctx->expression(0));
    Expression *expr2 = this->visit(ctx->expression(1));
    return (Expression *)new ExpressionOPBool(expr1, "&", expr2);
}

antlrcpp::Any Visitor::visitExprParentheses(ifccParser::ExprParenthesesContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprParentheses Debut" << endl;
#endif
    Expression *expr = this->visit(ctx->expression());
    return (Expression *)new ExpressionParentheses(expr);
}

antlrcpp::Any Visitor::visitExprNeg(ifccParser::ExprNegContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprNeg Debut" << endl;
#endif
    Expression *expr = this->visit(ctx->expression());
    return (Expression *)new ExpressionNeg(expr);
}

antlrcpp::Any Visitor::visitExprSign(ifccParser::ExprSignContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprSign Debut" << endl;
#endif
    string sign = ctx->OP2()->getText();
    Expression *expr = this->visit(ctx->expression());
    return (Expression *)new ExpressionSign(sign, expr);
}

antlrcpp::Any Visitor::visitExprConst(ifccParser::ExprConstContext *ctx)
{
#ifdef DEBUG
    cout << "visitExprConst Debut" << endl;
#endif
    string value = ctx->CONST()->getText();
    return (Expression *)new ExpressionConst(value);
}

antlrcpp::Any Visitor::visitMultipleIdentifiers(ifccParser::MultipleIdentifiersContext *ctx)
{
#ifdef DEBUG
    cout << "visitMultipleIdentifiers Debut" << endl;
#endif
    /** multiple identifiers management**/
    string id0 = this->visit(ctx->identifier(0));
    string id1 = this->visit(ctx->identifier(1));
    string identifiers = id0 + "," + id1;
    return identifiers;
}

antlrcpp::Any Visitor::visitSingleIdentifier(ifccParser::SingleIdentifierContext *ctx)
{
#ifdef DEBUG
    cout << "visitSingleIdentifier Debut" << endl;
#endif
    return ctx->IDENTIFIER()->getText();
}

string Visitor::returnAssembly()
{
#ifdef DEBUG
    cout << "returnAssembly Debut" << endl;
#endif
    return assemblyCode.str();
}

Expression *Visitor::optimizeAS(Expression *expr1, string op, Expression *expr2)
{   
    ExpressionIdentifier* exprId;
    ExpressionConst *exprConst1, *exprConst2; 
    int val1, val2;
    if((exprConst1 = dynamic_cast<ExpressionConst*>(expr1)) && exprConst1->getName() == "")
    {
        val1 = stoi(exprConst1->getValue());
        if ((exprConst2 = dynamic_cast<ExpressionConst *>(expr2)) && exprConst2->getName() == "")
        {
            val2 = stoi(exprConst2->getValue());
            if (op == "+")
            {
                return (Expression *)new ExpressionConst("", op, to_string(val1 + val2));
            }
            else
            {
                return (Expression *)new ExpressionConst("", op, to_string(val1 - val2));
            }
        }
        else 
        {
            // neutral element of addition / subtraction
            if (val1 == 0)
            {
                if ( op == "+")
                {
                    return expr2;
                }
                return new ExpressionSign("-",expr2);
            }
            else if ((exprId = dynamic_cast<ExpressionIdentifier *>(expr2)))
            {
                op = (op=="-")?"--":op;
                return (Expression *)new ExpressionConst(exprId->getName(), op, to_string(val1));
            }
        }
    }
    else
    {
        if ((exprConst2 = dynamic_cast<ExpressionConst *>(expr2)) && exprConst2->getName() == "")
        {
            val2 = stoi(exprConst2->getValue());
            if(val2 == 0)
            {
                return expr1; 
            }
            else if ((exprId = dynamic_cast<ExpressionIdentifier *>(expr1)))
            {
                return (Expression *)new ExpressionConst(exprId->getName(), op, to_string(val2));
            }
        }
    }
    return (Expression *)new ExpressionOP2(expr1, op, expr2);
}

Expression *Visitor::optimizeMDM(Expression *expr1, string op, Expression *expr2)
{
    ExpressionIdentifier *exprId;
    ExpressionConst *exprConst1, *exprConst2;
    int val1, val2;
    if ((exprConst1 = dynamic_cast<ExpressionConst *>(expr1)) && exprConst1->getName() == "")
    {
        val1 = stoi(exprConst1->getValue());
        if ((exprConst2 = dynamic_cast<ExpressionConst *>(expr2)) && exprConst2->getName() == "")
        {
            val2 = stoi(exprConst2->getValue());
            if (op == "*")
            {
                return (Expression *)new ExpressionConst("", op, to_string(val1 * val2));
            }
            else if ( op == "/")
            {
                return (Expression *)new ExpressionConst("", op, to_string(val1 / val2));
            }
            else
            {
                return (Expression *)new ExpressionConst("", op, to_string(val1 % val2));
            }
        }
        else if (op == "*")
        { 
            // neutral element of multiplication
            if (val1 == 1)
            {

                return expr2;

            }
            else if ((exprId = dynamic_cast<ExpressionIdentifier *>(expr2)))
            {

                return (Expression *)new ExpressionConst(exprId->getName(), op, to_string(val1));
            }
        }
    }
    else
    {
        if ((exprConst2 = dynamic_cast<ExpressionConst *>(expr2)) && exprConst2->getName() == "" && op == "*")
        {
            val2 = stoi(exprConst2->getValue());
            if (val2 == 1)
            {
                return expr1;
            }
            else if ((exprId = dynamic_cast<ExpressionIdentifier *>(expr1)))
            {
                return (Expression *)new ExpressionConst(exprId->getName(), op, to_string(val2));
            }
        }
    }
    return (Expression *)new ExpressionOP1(expr1, op, expr2);
}