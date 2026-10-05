// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
extern const void* const g_00BC6F24[];
extern const void* const g_00BC6F2C[];
extern const void* const g_00BD3854[];
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
struct __declspec(novtable) Rva00150C97Entry:public Rva00BC6F2CBase {
public:
 // ?Rva00150C97Entry::Rva00150C97Entry present-unmatched
 Rva00150C97Entry() { *(const void**)this=g_00BD3854; }
 // ?Rva00150C97Entry::~Rva00150C97Entry present-unmatched
 virtual ~Rva00150C97Entry() { *(const void**)this=g_00BD3854; }
};
class Rva00150BF9Vector {
 Rva00150C97Entry *start,*finish,*end;
public: void resize(unsigned, Rva00150C97Entry);
};
typedef _STL::vector<Rva00150C97Entry> Rva00150C97Vector;
namespace _STL { template<> void vector<Rva00150C97Entry>::resize(unsigned int); }
class Rva00150C97 { unsigned int vptr; Rva00150C97Vector values; public: void grow(int count); };
void Rva00150C97::grow(int count) {
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
// unique native wrapper 0x00150BF9 decoded from this body.

// 0x00150BF9: 41B native resize wrapper constructs an 8-byte by-value
// entry. All three vtable writes come from this target; index remains
// uninitialized until the grow loop fills it. No application name inferred.
namespace _STL { template<> void vector<Rva00150C97Entry>::resize(unsigned n) {
 reinterpret_cast<Rva00150BF9Vector*>(this)->resize(n,Rva00150C97Entry());
} }

namespace _STL {
template<> Rva00150C97Entry* vector<Rva00150C97Entry>::erase(Rva00150C97Entry*,Rva00150C97Entry*);
template<> void vector<Rva00150C97Entry>::_M_fill_insert(Rva00150C97Entry*,unsigned,const Rva00150C97Entry&);
}
void Rva00150BF9Vector::resize(unsigned n,Rva00150C97Entry value) {
 _STL::vector<Rva00150C97Entry>*v=reinterpret_cast<_STL::vector<Rva00150C97Entry>*>(this);
 if (n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

// By-value resize: native 86B ret0C body, 8B stride, erase and fill
// callees read from this target. Inline vtable cleanup keeps EH unwind
// registration while dead stores disappear on the normal return path.
