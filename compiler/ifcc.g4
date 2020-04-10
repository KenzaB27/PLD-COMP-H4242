grammar ifcc;

axiom: program;

program: elements+;
elements: function ;

function: TYPE 'main' '()' block;

block: '{' codelines '}';

codelines: codeline*;

codeline:
	instructionLine		# CodeLine_InstructionLine
	| structure 		# CodeLine_Structure;

blockOrLine:
	block				# BlockImplementation
	| instructionLine	# InstructionIsBlock;

instructionLine:
	assignement ';'		# InstructionLine_Assignement
	| instruction ';'	# InstructionLine_Instruction
	| returnCode ';'	# InstructionLine_ReturnCode
	| breakCode ';'		# InstructionLine_BreakCode;

structure:
	  ifCode		# Structure_IfCode
	| whileCode		# Structure_While
	| forCode		# Structure_For
	| block			# Structure_Block;

ifCode:
	'if' '(' expression ')' blockOrLine elseIfCode*? elseCode?;
elseIfCode: 'else' 'if' '(' expression ')' blockOrLine;
elseCode: 'else' blockOrLine;

whileCode: 'while' '(' expression ')' blockOrLine;

forCode:
	'for' '(' instructionLine expression ';' instruction ')' blockOrLine;

breakCode: 'break';

returnCode: 'return' expression?;

assignement:
	TYPE identifier AFFECT expression	# AssignAndDeclare
	| TYPE identifier					# Declare;

AFFECT: '=' | '+=' | '-=' | '*=' | '/=';

instruction:
	IDENTIFIER AFFECT instruction	# AssignInstruction
	| IDENTIFIER AFFECT expression	# AssignExpression
	| IDENTIFIER '++'				# PostIncrement
	| '++' IDENTIFIER				# PreIncrement
	| IDENTIFIER '--'				# PostDecrement
	| '--' IDENTIFIER				# PreDecrement;

expression:
	 IDENTIFIER DPLUS				# ExprPostIncrement
	| DPLUS IDENTIFIER				# ExprPreIncrement
	| IDENTIFIER DMOINS				# ExprPostDecrement
	| DMOINS IDENTIFIER				# ExprPreDecrement
	| OP2 expression				# ExprSign
	| OP3 expression				# ExprNeg
	| expression OP1 expression		# Op1
	| expression OP2 expression		# Op2
	| expression OPShift expression # OpShift
	| expression OPGL expression	# OpGreaterless
	| expression OPEN expression	# OpEqualNotEqual
	| expression '&' expression		# OpAndBitwise
	| expression '^' expression		# OpXorBitwise
	| expression '|' expression		# OpOrBitwise
	| expression '&&' expression	# OpAnd
	| expression '||' expression	# OpOr
	| '(' expression ')'			# ExprParentheses
	| CONST							# ExprConst
	| IDENTIFIER 					# ExprIdentifier;

OP1: '*' | '/' | '%';
OP2: [+-];
OP3: [!];
DPLUS: '++';
DMOINS: '--';
OPShift: '<<' | '>>';
OPGL: '>' | '<' | '>=' | '<=';
OPEN: '==' | '!=';
 
identifier:
	IDENTIFIER					# SingleIdentifier
	| identifier ',' identifier	# MultipleIdentifiers;

COMMENT: '/*' .*? '*/' -> skip;
DIRECTIVE: '#' .*? '\n' -> skip;
TYPE: 'int';


CONST: [0-9]+;
IDENTIFIER: [a-zA-Z][a-zA-Z_0-9]*;

WS: [ \t\r\n] -> channel(HIDDEN);
