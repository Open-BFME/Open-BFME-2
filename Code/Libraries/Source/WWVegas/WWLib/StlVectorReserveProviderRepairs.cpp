// cl: /O1 /G7 /MD /EHsc
// Reference: STLport4.5.3 stl/_vector.c reserve algorithm, at BFME1 donor
// 6583b3c1ff21db4a561285717028fdafc780b7db. PC callers independently establish
// the three pointers at0/4/8, element stride4 (12 at4EE55E), and every helper.
// Upstream recovered the helpers under their proper element views and removed
// nine false pins. The old reserve rows still used unrelated ObjectID/int or
// per-address Record template names. Keep the callers address-named and use
// the verified providers; sharing a helper does not establish a caller type.
// ReserveAccess exposes protected helpers without changing their mangling.
// This is an identity/dependency repair, not additional recovered bytes.
struct Rva002B9062Element { char data[4]; };
struct Rva005EFD53Element { char data[4]; };
struct Rva005334A4Element { char data[4]; };
class ProductionPrerequisite { public: struct PrereqUnitRec { char data[12]; }; };
namespace _STL {
void free(void *);
template<class T> class allocator { public: T *allocate(unsigned int,const void *) const; };
template<class T,class A> class vector {
protected:
 template<class I> T *_M_allocate_and_copy(unsigned int,I,I);
 void _M_clear();
};
}
template<class T> class ReserveAccess : public _STL::vector<T,_STL::allocator<T> > {
public:
 __forceinline T *copy(unsigned int n,T *f,T *l) {return this->_M_allocate_and_copy(n,f,l);}
 __forceinline void clear() {this->_M_clear();}
};
class Rva00081BAFVector
{
    typedef Rva002B9062Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva00081BAFVector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva00081C17Vector
{
    typedef Rva002B9062Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva00081C17Vector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva004F7DF9Vector
{
    typedef Rva002B9062Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva004F7DF9Vector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva004F830BVector
{
    typedef Rva002B9062Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva004F830BVector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva00577F0FVector
{
    typedef Rva002B9062Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva00577F0FVector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva005E2896Vector
{
    typedef Rva002B9062Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva005E2896Vector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva005F122DVector
{
    typedef Rva005EFD53Element Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva005F122DVector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<ReserveAccess<Element> *>(this)->clear();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva004EE540 { public: void rva004EE540(); };
class Rva004EE55EVector
{
    typedef ProductionPrerequisite::PrereqUnitRec Element;
    Element *start, *finish, *end;
public:
    void reserve(unsigned int);
};
void Rva004EE55EVector::reserve(unsigned int n)
{
    if ((unsigned int)(end - start) < n) {
        unsigned int oldSize = finish - start;
        Element *tmp;
        if (start) {
            tmp = reinterpret_cast<ReserveAccess<Element> *>(this)->copy(n, start, finish);
            reinterpret_cast<Rva004EE540 *>(this)->rva004EE540();
        } else {
            tmp = reinterpret_cast<_STL::allocator<Element> *>(&end)->allocate(n, 0);
        }
        finish = tmp + oldSize;
        start = tmp;
        end = tmp + n;
    }
}

class Rva00532844Vector { Rva005334A4Element *start,*finish,*end; public: void reserve(unsigned int); };
void Rva00532844Vector::reserve(unsigned int n) {
 if((unsigned int)(end-start)<n) {
  unsigned int oldSize=finish-start; Rva005334A4Element *tmp;
  if(start) {tmp=reinterpret_cast<ReserveAccess<Rva005334A4Element> *>(this)->copy(n,start,finish); if(start) _STL::free(start);}
  else tmp=reinterpret_cast<_STL::allocator<Rva005334A4Element> *>(&end)->allocate(n,0);
  finish=tmp+oldSize; start=tmp; end=tmp+n;
 }
}
