#ifndef MANAGER_HEADER
#define MANAGER_HEADER

#include "Absyn.H"
#include "Store.h"
#include "Enviroment.h"
#include "Types.h"

class Manager
{
public:
  static bool cmp(const Type&, const Type&);
  static bool bsc(const Type&);
  static bool cst(const Type&, const Type&);
  static bool txt(const Type&);
  static void addIdent(const Ident&, const Type&, int, Enviroment&, Store&);
  static Type getTypeByIdent(const Ident&, Enviroment&, Store&);
};


#endif
