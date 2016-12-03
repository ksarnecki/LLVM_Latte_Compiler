CC = g++
CCFLAGS = -g
FLEX = flex
BISON = bison
all: Testgrammar

clean:
	rm -f *.o grammar.dvi grammar.aux grammar.log 
	rm -f grammar.pdf Testgrammar

distclean:
	 rm -f *.o Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H grammar.l grammar.y grammar.tex grammar.dvi grammar.aux grammar.log grammar.ps Testgrammar Makefile

Testgrammar: Absyn.o Lexer.o Parser.o Printer.o Test.o
	@echo "Linking Testgrammar..."
	${CC} ${CCFLAGS} *.o -o Testgrammar

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: grammar.l
	${FLEX} -oLexer.C grammar.l

Parser.C: grammar.y
	${BISON} grammar.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

