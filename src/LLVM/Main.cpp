#include <stdio.h>
#include "Parser.H"
#include "Printer.H"
#include "Absyn.H"
#include "TypeChecker.h"
#include "CodeBuilder.h"
#include "Printer.h"

int main(int argc, char ** argv) {
  Program *parse_tree = pProgram(stdin);
  if (parse_tree) { 
  	TypeChecker typeChecker;
  	typeChecker.check(parse_tree);
    CodeBuilder cb;
    LLVMProgram program = cb.compile(parse_tree);
    Printer::print(program);
    return 0;
  }
  return 1;
}
