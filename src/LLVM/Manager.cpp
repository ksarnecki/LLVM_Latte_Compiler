#include "Manager.h"

bool Manager::cmp(const Type& t1, const Type& t2) {
	if(t1.isBasic() && t2.isBasic()) {
		if(t1.asBasic().isInt() && t2.asBasic().isInt())
			return true;
		if(t1.asBasic().isBool() && t2.asBasic().isBool())
			return true;
		if(t1.asBasic().isString() && t2.asBasic().isString())
			return true;
		if(t1.asBasic().isChar() && t2.asBasic().isChar())
			return true;
		if(t1.asBasic().isVoid() && t2.asBasic().isVoid())
			return true;
	} 
	if(t1.isFunction() && t2.isFunction()) {
		//TODO
	}
	return false;
}

bool Manager::bsc(const Type& t) {
	return t.isBasic();
}

bool Manager::txt(const Type& t) {
	if(t.isBasic())
		return t.asBasic().isString() || t.asBasic().isChar();
	return false;
}

bool Manager::cst(const Type& t1, const Type& t2) {
	//TODO
	return cmp(t1, t2);
}


void Manager::addIdent(const Ident& ident, const Type& t, int nesting, Enviroment& env, Store& str) {
	int id = str.Size();
	str.Insert(StoreElement(id, t));
	env.Insert(EnviromentElement(ident, id, nesting));
}

Type Manager::getTypeByIdent(const Ident& ident, Enviroment& env, Store& str) {
	for(int i=0;i<env.Size();i++) {
		if(env[i].getIdent() == ident) {
			for(int j=0;j<str.Size();j++) {
				if(env[i].getStoreId()==str[j].getId())
					return str[j].getType();
			}
			throw Exception("[Manager::getTypeByIdent] internal error");
		}
	}
	return Type::createNull();
}