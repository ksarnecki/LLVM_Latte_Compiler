CC = g++
CCFLAGS = -g
FLEX = flex
BISON = bison
LATEX = latex
DVIPS = dvips

all: TestLatteCPP LatteCPP.ps

clean:
	rm -f *.o LatteCPP.dvi LatteCPP.aux LatteCPP.log LatteCPP.ps TestLatteCPP

distclean:
	 rm -f *.o Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H LatteCPP.l LatteCPP.y LatteCPP.tex LatteCPP.dvi LatteCPP.aux LatteCPP.log LatteCPP.ps TestLatteCPP Makefile

TestLatteCPP: Absyn.o Lexer.o Parser.o Printer.o Test.o
	@echo "Linking TestLatteCPP..."
	${CC} ${CCFLAGS} *.o -o TestLatteCPP
        
Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: LatteCPP.l
	${FLEX} -oLexer.C LatteCPP.l

Parser.C: LatteCPP.y
	${BISON} LatteCPP.y -o Parser.C

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

LatteCPP.dvi: LatteCPP.tex
	${LATEX} LatteCPP.tex

LatteCPP.ps: LatteCPP.dvi
	${DVIPS} LatteCPP.dvi -o LatteCPP.ps

