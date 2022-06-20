# List of tokens
name | token
----- | -----
DOUBLE | double
INT | int
STRING | string
BREAK | break
IF | if
ELSE | else
RETURN | return
CHAR | char
CONST | const
FOR | for
VOID | void 
WHILE | while
LIST | list
BOOL | bool
IP | ip
ADDRESS | address
FUNCTION | function
FILE | file
PROTOCOL | protocol
STRING | string
POINTER | pointer
AND | and
TRUE | true
FALSE | false
ENDLINE | ;
ADD | +
SUBSTRACTION | -
MULTIPLY | *
DIVIDE | /
MOD | %
ASSING | =
COMMENT | #
COUT | ?
QUOTE | '
DOUBLEQUOTE | "
LS | \[
RS | ]
LC | {
RC | }
LR | (
RR | )
POINTED_VALUE | ^
ADDRESS | &
SEMICOLON | ;
PROTOCOL | protocol
DECYPHER | decypher
FIND_ADD | findAddresses
GET_PROC | getProcess
SEND_PACKET | sendPacket
NULL | null
LESS | <
GREATER | <
LEQ | <=
GEQ | >=
EQ | ==
DIFF | !=
COMMA | ,
DOT | .
AND | and
NOT | not 
TO | to
BY | by
IN | in
ID | letter diglet\*
digit | \d
letter | \w


 *diglet -> letter | digit 
 
 *INTNUMBER -> /^[-+]?\d+/
 
 *DOUBNUMBER -> /^[0-9]+(\\.[0-9]+)?/
 
 *CHAR -> /'\w'/
 
 *STRING -> ".\*"
 
