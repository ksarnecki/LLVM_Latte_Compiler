
#ifndef _LK_DYNSET_H_
#define _LK_DYNSET_H_

#include "Exception.h"

template <class T>
class DSBox {
  T* t;
public:
  DSBox();
  DSBox(const T&);
  virtual DSBox& operator=(const DSBox&); 
  virtual T& getValue();
  virtual const T& getValue() const;
  virtual DSBox<T>* clone() const;
  virtual ~DSBox();
};

template <class T>
class DynSet {
  int len;
  int size;
protected:
  typedef DSBox<T>* DSBoxPtr;
  DSBoxPtr* buf;
  void Free();
  void UpSize();
public:
  DynSet();
  DynSet(const DynSet<T>&);
  virtual DynSet<T>& operator=(const DynSet<T>&);
  virtual DynSet<T>& operator+=(const DynSet<T>&);

  virtual void Insert(const T&);
  virtual const T& operator[](int) const;
  virtual T& operator[](int);
  virtual int Size() const;
  virtual void Delete(int);

  virtual ~DynSet();
};

template <class T>
class UniqueDynSet : public DynSet<T> {
public:
  UniqueDynSet();
  UniqueDynSet(const DynSet<T>&);

  virtual UniqueDynSet<T> Unique() const;
  virtual ~UniqueDynSet();
};

template <class T>
DSBox<T>::DSBox() : t(0) {
}
template <class T>
DSBox<T>::DSBox(const T& _t) : t(new T(_t)) {
}
template <class T>
DSBox<T>& DSBox<T>::operator=(const DSBox<T>& box) {
  if (t!=0)
    delete t;
  t = 0;
  if (box.t!=0)
    t = new T(*box.t);
  return *this;
}
template <class T>
T& DSBox<T>::getValue() {
  if (t==0)
    throw Exception("DSBox::getValue");
  return *t;
}
template <class T>
const T& DSBox<T>::getValue() const {
  if (t==0)
    throw Exception("DSBox::getValue");
  return *t;
}
template <class T>
DSBox<T>* DSBox<T>::clone() const {
  if (t==0)
    throw Exception("DSBox<T>::clone");
  return new DSBox<T>(*t);
}
template <class T>
DSBox<T>::~DSBox() {
  if (t!=0)
    delete t;
}

template <class T>
void DynSet<T>::Free() {
  for (register int i=0;i<len;i++)
    delete buf[i];
  if (size>0 && buf!=0)
    delete[] buf;
  size = len = 0;
  buf = 0;
}
template <class T>
void DynSet<T>::UpSize() {
  size = 2*size+1;
  DSBoxPtr* nbuf = new DSBoxPtr[size];
  for (register int i=0;i<len;i++)
    nbuf[i] = buf[i];
  if (size>0 && buf!=0)
    delete[] buf;
  buf = nbuf;
}
template <class T>
DynSet<T>::DynSet() {
  size = len = 0;
  buf = 0;
}
template <class T>
DynSet<T>::DynSet(const DynSet<T>& ds) {
  size = len = ds.len;
  if (size>0)
    buf = new DSBoxPtr[size];
  else
    buf = 0;
  for (register int i=0;i<len;i++)
    buf[i] = ds.buf[i]->clone();
}
template <class T>
DynSet<T>& DynSet<T>::operator=(const DynSet<T>& ds) {
  Free();
  size = len = ds.len;
  if (size>0)
    buf = new DSBoxPtr[size];
  else
    buf = 0;
  for (register int i=0;i<len;i++)
    buf[i] = ds.buf[i]->clone();
  return *this;
}
template <class T>
DynSet<T>& DynSet<T>::operator+=(const DynSet<T>& ds) {
  for (register int i=0;i<ds.Size();i++)
    Insert(ds[i]);
  return *this;
}
template <class T>  
void DynSet<T>::Insert(const T& t) {
  if (len>=size)
    UpSize();
  buf[len++] = new DSBox<T>(t);
}
template <class T>
const T& DynSet<T>::operator[](int pos) const {
  if (!(pos>=0 && pos<len))
    throw Exception("DynSet<T>::operator[]");
  return buf[pos]->getValue();
}
template <class T>
T& DynSet<T>::operator[](int pos) {
  if (!(pos>=0 && pos<len))
    throw Exception("DynSet<T>::operator[]");
  return buf[pos]->getValue();
}
template <class T>
int DynSet<T>::Size() const {
  return len;
}
template <class T>
void DynSet<T>::Delete(int pos) {
  if (pos<0 || pos>=len)
    throw Exception("DynSet<T>::Delete");
  delete buf[pos];
  if (len>0)
    buf[pos] = buf[len-1];
  len--;
}
template <class T>
DynSet<T>::~DynSet() {
  Free();
}

template <class T>
UniqueDynSet<T>::UniqueDynSet() {
}

template <class T>
UniqueDynSet<T>::UniqueDynSet(const DynSet<T>& _ds) : DynSet<T>(_ds) {
}

template <class T>
UniqueDynSet<T> UniqueDynSet<T>::Unique() const {
  UniqueDynSet<T> q;
  for (register int i=0;i<this->Size();i++) {
    int j = 0;
    while (j<q.Size() && !(q[j]==(*this)[i]))
      j++;
    if (j==q.Size())
      q.Insert((*this)[i]);
  }
  return q;
}

template <class T>
UniqueDynSet<T>::~UniqueDynSet() {
}

#endif
