grammar sharkbit;


program :
declList;
declList :
declList decl | decl;
decl :
coutDecl | varDecl | funDecl | varDeclInit | pointerVarDecl | assignPointer | call;
varDecl :
constSpec typeSpec varDeclInit SEMICOLON;
pointerVarDecl:
constSpec typeSpec POINTER idDecl ASSIGN POINTER_ADDRESS ID SEMICOLON;
idDecl:
ID;
varDeclInit :
ID | ID ASSIGN mathExp ;
assignPointer:
POINTED_VALUE ID ASSIGN mathExp SEMICOLON;
coutDecl :
COUT mathExp SEMICOLON;
constSpec :
CONST | ;
typeSpec :
INT | BOOL | DOUBLE | STRING | IP | PROTOCOL | ADDRESS | FILE | PORT | CHAR | list | ;
list:
LIST LESS typeSpec GREATER;
funDecl :
FUNCTION ID typeSpec LR parms RR stmt;
parms :
parmList | ;
parmList :
parmList COMMA parmTypeList | parmTypeList;
parmTypeList :
typeSpec parmIdList;
parmIdList :
parmIdList COMMA parmId | parmId;
parmId :
ID | ID LS RS;
stmt :
expStmt | compoundStmt | selectStmt | iterStmt | returnStmt | breakStmt | varDecl |  coutDecl ;
expStmt :
simpleExp SEMICOLON | SEMICOLON;
compoundStmt :
LC  stmtList  RC;
stmtList :
stmtList stmt | ;
selectStmt :
IF LR simpleExp RR stmt | IF LR simpleExp RR stmt ELSE stmt;
iterStmt :
WHILE LR simpleExp RR stmt | FOR LR ID IN iterRange RR stmt;
iterRange :
simpleExp TO simpleExp | simpleExp TO simpleExp BY simpleExp;
returnStmt :
RETURN SEMICOLON | RETURN simpleExp SEMICOLON;
breakStmt :
BREAK SEMICOLON;
simpleExp :
mathExp | logicalExp;
logicalExp :
logicalExp AND unaryRelExp | unaryRelExp;
unaryRelExp :
NOT unaryRelExp | relExp;
relExp :
mathExp compop mathExp| mathExp;
compop :
LESS | GREATER | LEQ | GEQ | EQ | DIFF;
mathExp :
factor mathOp mathExp | factor;
mathOp :
ADD | SUBSTRACTION | MULTIPLY | DIVIDE | MOD;
factor :
immutable | mutaable;
mutaable :
ID | ID LS INTNUMBER RS | POINTED_VALUE ID;
immutable :
call | constant; //math exp nie wiadomo
call :
ID LR args RR | WRITE_MEMORY LR args RR;
args :
argList | ;
argList :
argList COMMA simpleExp | simpleExp;
constant :
NONE | INTNUMBER | CHAR_CONST | STRING_CONST | TRUE | FALSE | DOUBNUMBER | IP_CONST;

DOUBLE: 'double';
INT: 'int';
STRING: 'string';
BREAK: 'break';
IF: 'if';
ELSE: 'else';
RETURN: 'return';
CHAR: 'char';
CONST: 'const';
FOR: 'for';
VOID: 'void';
WHILE: 'while';
LIST: 'list';
BOOL: 'bool';
IP: 'ip';
ADDRESS: 'address';
FUNCTION: 'function';
FILE: 'file';
PROTOCOL: 'protocol';
POINTER: 'pointer';
AND: 'and';
TRUE: 'true';
FALSE: 'false';
ADD: '+';
SUBSTRACTION: '-';
MULTIPLY: '*';
DIVIDE: '/';
MOD: '%';
ASSIGN: '=';
COMMENT: '#';
COUT: '?';
QUOTE: '\'';
DOUBLEQUOTE: '"';
LS: '[';
RS: ']';
LC: '{';
RC: '}';
LR: '(';
RR: ')';
POINTED_VALUE: '^';
POINTER_ADDRESS: '&';
SEMICOLON: ';';
DECYPHER: 'decypher';
FIND_ADD: 'findAddresses';
GET_PROC: 'getProcess';
SEND_PACKET: 'sendPacket';
WRITE_MEMORY: 'writeMemory';
NONE: 'none';
LESS: '<';
GREATER: '>';
LEQ: '<=';
GEQ: '>=';
EQ: '==';
DIFF: '!=';
COMMA: ',';
DOT: '.' ;
NOT: 'not';
TO: 'to';
BY: 'by';
IN: 'in';
ID: [A-Za-z][a-zA-Z0-9]*;
STRING_CONST: '"'[A-Za-z]*'"';
DOUBNUMBER: [0-9]+'.'[0-9]*;
INTNUMBER: [0-9]+;
CHAR_CONST: '\''[A-Za-z0-9]'\'';
PORT: 'port';
WS: [ \t\r\n]+ -> skip;