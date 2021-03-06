#include <stdio.h>
#include "Parser.H"
#include "Printer.H"
#include "Absyn.H"
#include "TypeChecker.h"
#include "CodeBuilder.h"
#include "Printer.h"
#include "Opt.h"

int main(int argc, char ** argv) {
  Program *parse_tree = pProgram(stdin);
  if (parse_tree) { 
  	TypeChecker typeChecker;
  	if(!typeChecker.check(parse_tree))
      return -1;
    CodeBuilder cb;
    LLVMProgram program = cb.compile(parse_tree);
    Opt::o0(program);
    Printer::print(program);
    return 0;
  }
  return -1;
}
