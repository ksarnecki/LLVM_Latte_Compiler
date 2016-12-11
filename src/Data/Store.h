#ifndef _STORE_GEN_H_
#define _STORE_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Type ---------------
#include "Types.h"
//----------------------------------

//------------- Register ---------------
#include "Register.h"
//----------------------------------

//------------- BasicObject ---------------
class BasicObject {
  int _type;
  void* _ptr;

  static const int _TypeInt;
  static const int _TypeBool;
  static const int _TypeDouble;
  static const int _TypeChar;
  static const int _TypeString;

  virtual void init(int, void*);
  virtual void clean();
  BasicObject();
public:
  BasicObject(const BasicObject&);
  virtual BasicObject& operator=(const BasicObject&);

  virtual bool isInt() const;
  virtual bool isBool() const;
  virtual bool isDouble() const;
  virtual bool isChar() const;
  virtual bool isString() const;

  virtual const Register& asInt() const;
  virtual Register& asInt();
  virtual const Register& asBool() const;
  virtual Register& asBool();
  virtual const Register& asDouble() const;
  virtual Register& asDouble();
  virtual const Register& asChar() const;
  virtual Register& asChar();
  virtual const Register& asString() const;
  virtual Register& asString();


  virtual ~BasicObject();

  static BasicObject createInt(const Register&);
  static BasicObject createBool(const Register&);
  static BasicObject createDouble(const Register&);
  static BasicObject createChar(const Register&);
  static BasicObject createString(const Register&);

};
//----------------------------------

//------------- FunctionObject ---------------
class FunctionObject {
  AnsiString name;
public:
  FunctionObject(const AnsiString&);
  virtual const AnsiString& getName() const;
  virtual AnsiString& getName();


  virtual ~FunctionObject();

};
//----------------------------------

//------------- Object ---------------
class Object {
  int _type;
  void* _ptr;

  static const int _TypeBasic;
  static const int _TypeFunction;
  static const int _TypeClassObject;
  static const int _TypeNull;

  virtual void init(int, void*);
  virtual void clean();
  Object();
public:
  Object(const Object&);
  virtual Object& operator=(const Object&);

  virtual bool isBasic() const;
  virtual bool isFunction() const;
  virtual bool isClassObject() const;
  virtual bool isNull() const;

  virtual const BasicObject& asBasic() const;
  virtual BasicObject& asBasic();
  virtual const FunctionObject& asFunction() const;
  virtual FunctionObject& asFunction();


  virtual ~Object();

  static Object createBasic(const BasicObject&);
  static Object createFunction(const FunctionObject&);
  static Object createClassObject();
  static Object createNull();

};
//----------------------------------

//------------- StoreElement ---------------
class StoreElement {
  int id;
  Object obj;
public:
  StoreElement(const int&, const Object&);
  virtual const int& getId() const;
  virtual const Object& getObj() const;
  virtual int& getId();
  virtual Object& getObj();


  virtual ~StoreElement();

};
//----------------------------------

//------------- ObjectArray ---------------
#include "DynSet.h"


class ObjectArray : public DynSet<Object> {
public:
  ObjectArray();


  virtual ~ObjectArray();

};
//----------------------------------

//------------- Store ---------------
#include "DynSet.h"


class Store : public DynSet<StoreElement> {
public:
  Store();


  virtual ~Store();

};
//----------------------------------

#endif
