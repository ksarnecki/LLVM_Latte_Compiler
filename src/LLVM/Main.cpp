#include <stdio.h>
#include "Parser.H"
#include "Printer.H"
#include "Absyn.H"
#include "TypeChecker.h"

int main(int argc, char ** argv) {
  Program *parse_tree = pProgram(stdin);
  if (parse_tree) { 
  	TypeChecker typeChecker;
  	typeChecker.check(parse_tree);
    //LlvmBuilder *b = new LlvmBuilder();
    //LLVMProgram llvmProgram = b->compile(parse_tree); 
    //LLVMProgramPrinter::print(llvmProgram);
    return 0;
  }
  return 1;
}
