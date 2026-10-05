// ?_M_fill_insert@?$vector@URva00150CD0Entry@@V?$allocator@URva00150CD0Entry@@@_STL@@@_STL@@QAEXPAURva00150CD0Entry@@IABU3@@Z
// partial score=0.78 date=2026-10-05
// cl: /O1 -GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>
extern const void* const g_00BC6F24[];
extern const void* const g_00BC6F2C[];
extern const void* const g_00BD385C[];
class __declspec(novtable) Rva00BC6F24Base {
public:
 // ?Rva00BC6F24Base::Rva00BC6F24Base present-unmatched
 Rva00BC6F24Base() { *(const void**)this=g_00BC6F24; }
 // ?Rva00BC6F24Base::~Rva00BC6F24Base present-unmatched
 virtual ~Rva00BC6F24Base() { *(const void**)this=g_00BC6F24; }
};
class __declspec(novtable) Rva00BC6F2CBase:public Rva00BC6F24Base {
public:
 // ?Rva00BC6F2CBase::Rva00BC6F2CBase present-unmatched
 Rva00BC6F2CBase() { *(const void**)this=g_00BC6F2C; }
 // ?Rva00BC6F2CBase::~Rva00BC6F2CBase present-unmatched
 virtual ~Rva00BC6F2CBase() { *(const void**)this=g_00BC6F2C; }
 int index;
};
struct __declspec(novtable) Rva00150CD0Entry:public Rva00BC6F2CBase {
public:
 // ?Rva00150CD0Entry::Rva00150CD0Entry present-unmatched
 Rva00150CD0Entry(const Rva00150CD0Entry&);
 Rva00150CD0Entry&operator=(const Rva00150CD0Entry&);
 Rva00150CD0Entry() { *(const void**)this=g_00BD385C; }
 // ?Rva00150CD0Entry::~Rva00150CD0Entry present-unmatched
 virtual ~Rva00150CD0Entry() { *(const void**)this=g_00BD385C; }
};
class Rva00150C22Vector {
 Rva00150CD0Entry *start,*finish,*end;
public: void resize(unsigned, Rva00150CD0Entry);
};
typedef _STL::vector<Rva00150CD0Entry> Rva00150CD0Vector;
namespace _STL { template<> void vector<Rva00150CD0Entry>::resize(unsigned int); }
class Rva00150CD0 { unsigned int vptr; Rva00150CD0Vector values; public: void grow(int count); };
void Rva00150CD0::grow(int count) {
 if ((unsigned)count >= values.size()) {
  int old=values.size();
  values.resize(count);
  for (;old<count;++old) values[old].index=old;
 }
}

// Target: Ghidra extent and native ret4 boundary; vector member +4;
// signed growth loop writes each new element index at +4. Storage stride
// 8 is established by native pointer arithmetic. Application identity unknown.
// STLport4.5.3 supplies size/operator[]; resize declaration targets the
// unique native wrapper 0x00150C22 decoded from this body.

// 0x00150C22: 41B native resize wrapper constructs an 8-byte by-value
// entry. All three vtable writes come from this target; index remains
// uninitialized until the grow loop fills it. No application name inferred.
namespace _STL { template<> void vector<Rva00150CD0Entry>::resize(unsigned n) {
 reinterpret_cast<Rva00150C22Vector*>(this)->resize(n,Rva00150CD0Entry());
} }

namespace _STL {
template<> Rva00150CD0Entry* vector<Rva00150CD0Entry>::erase(Rva00150CD0Entry*,Rva00150CD0Entry*);

}
void Rva00150C22Vector::resize(unsigned n,Rva00150CD0Entry value) {
 _STL::vector<Rva00150CD0Entry>*v=reinterpret_cast<_STL::vector<Rva00150CD0Entry>*>(this);
 if (n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

// By-value resize: native 86B ret0C body, 8B stride, erase and fill
// callees read from this target. Inline vtable cleanup keeps EH unwind
// registration while dead stores disappear on the normal return path.

template void _STL::vector<Rva00150CD0Entry>::_M_fill_insert(Rva00150CD0Entry*,unsigned,const Rva00150CD0Entry&);
