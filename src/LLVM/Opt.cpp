#include "Opt.h"


void Opt::o0ReturnDeadCode(LLVMProgram& program) {
  std::map<std::string, int> refCounter;

  for(int i=0;i<program.getFunctions().Size();i++) {
    LLVMFunction& f = program.getFunctions()[i];
    for(int j=0;j<f.getBlocks().Size();j++) {
      LLVMBlock& b = f.getBlocks()[j];
      LLVMBlock newb(b.getName(), InstrArray());
      for(int k=0;k<b.getBody().Size();k++) {
        Instr& instr = b.getBody()[k];
        newb.getBody().Insert(instr);
        if(instr.isReturnInstr())
          break;
        if(instr.isBrInstr()) {
          std::string name = instr.asBrInstr().getBlock().c_str();
          if(refCounter.find(name)==refCounter.end()) {
            refCounter[name] = 0;
          } 
          refCounter[name]++;
        }
        if(instr.isBrIfInstr()) {
          std::string name1 = instr.asBrIfInstr().getIfTrueBlock().c_str();
          std::string name2 = instr.asBrIfInstr().getIfFalseBlock().c_str();
          if(refCounter.find(name1)==refCounter.end()) {
            refCounter[name1] = 0;
          } 
          refCounter[name1]++;
          if(refCounter.find(name2)==refCounter.end()) {
            refCounter[name2] = 0;
          } 
          refCounter[name2]++;
        }
      }
      b = newb;
    }
  }

  for(int i=0;i<program.getFunctions().Size();i++) {
    LLVMFunction& f = program.getFunctions()[i];
    LLVMFunction newf = f;
    newf.getBlocks() = LLVMBlockArray();
    for(int j=0;j<f.getBlocks().Size();j++) {
      LLVMBlock& b = f.getBlocks()[j];
      if(j==0 || refCounter.find(b.getName().c_str())!=refCounter.end()) {
        newf.getBlocks().Insert(b);
      }
    }
    f = newf;
  }

}

void Opt::o0(LLVMProgram& program) {
  o0ReturnDeadCode(program);
}
