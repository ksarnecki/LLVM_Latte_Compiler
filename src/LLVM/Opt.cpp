#include "Opt.h"


void Opt::o0ReturnDeadCode(LLVMProgram& program) {
  bool changed = true;
  while(changed) {
    std::map<std::string, int> refCounter;
    changed = false;
    for(int i=0;i<program.getFunctions().Size();i++) {
      LLVMFunction& f = program.getFunctions()[i];
      for(int j=0;j<f.getBlocks().Size();j++) {
        LLVMBlock& b = f.getBlocks()[j];
        LLVMBlock newb(b.getName(), InstrArray());
        for(int k=0;k<b.getBody().Size();k++) {
          Instr& instr = b.getBody()[k];
          newb.getBody().Insert(instr);
          if(instr.isReturnInstr()) {
            break;
          }
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
        } else {
          changed = true;
        }
      }
      f = newf;
    }
  }
}

void Opt::o0CheckPhiEntries(LLVMProgram& program) {
  std::map<std::string, std::vector<std::string> > refs;

  for(int i=0;i<program.getFunctions().Size();i++) {
    LLVMFunction& f = program.getFunctions()[i];
    for(int j=0;j<f.getBlocks().Size();j++) {
      LLVMBlock& b = f.getBlocks()[j];
      for(int k=0;k<b.getBody().Size();k++) {
        Instr& instr = b.getBody()[k];
        if(instr.isBrInstr()) {
          std::string name = instr.asBrInstr().getBlock().c_str();
          if(refs.find(name.c_str())==refs.end()) {
            refs[name.c_str()] = std::vector<std::string>();
          } 
          refs[name.c_str()].push_back(b.getName().c_str());
        }
        if(instr.isBrIfInstr()) {
          std::string name1 = instr.asBrIfInstr().getIfTrueBlock().c_str();
          std::string name2 = instr.asBrIfInstr().getIfFalseBlock().c_str();
          if(refs.find(name1.c_str())==refs.end()) {
            refs[name1.c_str()] = std::vector<std::string>();
          } 
          refs[name1.c_str()].push_back(b.getName().c_str());
          if(refs.find(name2.c_str())==refs.end()) {
            refs[name2.c_str()] = std::vector<std::string>();
          } 
          refs[name2.c_str()].push_back(b.getName().c_str());
        }
      }
    }
  }

  for(int i=0;i<program.getFunctions().Size();i++) {
    LLVMFunction& f = program.getFunctions()[i];
    for(int j=0;j<f.getBlocks().Size();j++) {
      LLVMBlock& b = f.getBlocks()[j];
      for(int k=0;k<b.getBody().Size();k++) {
        Instr& instr = b.getBody()[k];
        if(instr.isPhiInstr()) {
          PhiInstr& phi = instr.asPhiInstr();
          for(int l=0;l<phi.getCaseses().Size();l++) {
            std::vector<std::string> vec = refs[b.getName().c_str()];
            if(std::find(vec.begin(), vec.end(), phi.getCaseses()[l].getLabel().c_str()) == vec.end()) {
              //fprintf(stderr, "Phi bad case %s %s %s\n", phi.getCaseses()[l].getValue().toJSON().c_str(), b.getName().c_str(), phi.getCaseses()[l].getLabel().c_str());
              phi.getCaseses().Delete(l);
              l--;
            } else {
              //fprintf(stderr, "Phi case ok %s %s\n", b.getName().c_str(), phi.getCaseses()[l].getLabel().c_str());
            }
          }
        }
      }
    }
  }
}

void Opt::o0IfDeadCode(LLVMProgram& program) {
  /*for(int i=0;i<program.getFunctions().Size();i++) {
    LLVMFunction& f = program.getFunctions()[i];
    for(int j=0;j<f.getBlocks().Size();j++) {
      LLVMBlock& b = f.getBlocks()[j];
      for(int k=0;k<b.getBody().Size();k++) {
        Instr& instr = b.getBody()[k];
        if(instr.isPhiInstr()) {
          PhiInstr& phi = instr.asPhiInstr();
          for(int l=0;l<phi.getCaseses().Size();l++) {
            std::vector<std::string> vec = refs[b.getName().c_str()];
            if(std::find(vec.begin(), vec.end(), phi.getCaseses()[l].getLabel().c_str()) == vec.end()) {
              //fprintf(stderr, "Phi bad case %s %s %s\n", phi.getCaseses()[l].getValue().toJSON().c_str(), b.getName().c_str(), phi.getCaseses()[l].getLabel().c_str());
              phi.getCaseses().Delete(l);
              l--;
            } else {
              //fprintf(stderr, "Phi case ok %s %s\n", b.getName().c_str(), phi.getCaseses()[l].getLabel().c_str());
            }
          }
        }
      }
    }
  }*/
}

void Opt::o0(LLVMProgram& program) {
  o0ReturnDeadCode(program);
  o0CheckPhiEntries(program);
}
