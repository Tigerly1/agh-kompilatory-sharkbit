1. program → declList
2. declList → declList decl | decl
3. decl → coutDecl | varDecl | funDecl
4. varDecl → constSpec typeDec varDeclInit SEMICOLON
5. varDeclInit → varDeclId | varDeclId ASSIGN mathExp
6. varDeclId → ID | ID LS RS
7. coutDecl -> COUT ID SEMICOLON
8. constSpec → CONST | Ø
9. typeSpec → INT | BOOL | DOUBLE | STRING | IP | PROTOCOL | ADDRESS | FILE | PORT | CHAR | list
10. list -> LIST LESStypeSpecGREATER
11. typeDec -> typeSpec PointerDec
12. PionterDec -> POINTER | Ø
13. funDecl → function ID typeDec LR parms RR stmt
14. parms → parmList | Ø
15. parmList → parmList SEMICOLON parmTypeList | parmTypeList
16. parmTypeList → typeDec parmIdList
17. parmIdList → parmIdList COMMA parmId | parmId
18. parmId → ID | ID LS RS
19. stmt → expStmt | compoundStmt | selectStmt | iterStmt | returnStmt | breakStmt
20. expStmt → simpleExp SEMICOLON | SEMICOLON
21. compoundStmt → LC localDecls stmtList RC
22. localDecls → localDecls VarDecl | Ø
23. stmtList → stmtList stmt | Ø
24. selectStmt → IF (simpleExp)stmt | IF (simpleExp) stmt else stmt
25. iterStmt → WHILE LR simpleExp RR stmt | FOR LR ID IN iterRange RR stmt
26. iterRange → simpleExp TO simpleExp | simpleExp TO simpleExp BY simpleExp
27. returnStmt → RETURN SEMICOLON | RETURN simpleExp SEMICOLON
28. breakStmt → BREAK SEMICOLON
29. simpleExp → mathExp | logicalExp
30. logicalExp → logicalExp AND unaryRelExp | unaryRelExp
31. unaryRelExp → NOT unaryRelExp | relExp
32. relExp → mathExp compop mathExp| mathExp
33. compop → LESS | GREATER | LEQ | GEQ | GEQ | DIFF
34. mathExp → factor mathOp mathExp | factor
35. mathOp → ADD | SUBSTRACTION | MULTIPLY | DIVIDE | MOD
36. factor → immutable | mutable
37. mutable → ID | ID LS NUMCONST RS
38. immutable → LR exp RR | call | constant
39. call → ID LR args RR
40. args → argList | Ø
41. argList → argList COMMA SimpleExp | SimpleExp
42. constant → NULL | INTNUMBER  | CHAR | STRING | TRUE | FALSE | DOUBNUMBER
