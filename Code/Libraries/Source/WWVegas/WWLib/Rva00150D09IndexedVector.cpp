// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
extern "C" const unsigned char __identifier("??_7Base@@6B@")[];

class __declspec(novtable) Rva00BC6F24Base
{
public:
	Rva00BC6F24Base() { *(const void **)this = __identifier("??_7Base@@6B@"); }
	virtual ~Rva00BC6F24Base();
};

inline Rva00BC6F24Base::~Rva00BC6F24Base()
{
	*(const void **)this = __identifier("??_7Base@@6B@");
}

extern "C" const void* const __identifier("??_7Rva0007E04D@@6B@")[];

class __declspec(novtable) Rva0014F401 : public Rva00BC6F24Base
{
public:
	Rva0014F401() { *(const void**)this=__identifier("??_7Rva0007E04D@@6B@"); }
	Rva0014F401(const Rva0014F401 &other);
	virtual ~Rva0014F401() {}
};

extern "C" const void* const __identifier("??_7SourceNamespace_PointLight@FXShaderParameterSourceNamespaceSAS@@6B@")[];

class __declspec(novtable) Rva0014F4C2 : public Rva0014F401
{
public:
	Rva0014F4C2() { *(const void**)this=__identifier("??_7SourceNamespace_PointLight@FXShaderParameterSourceNamespaceSAS@@6B@"); }
	Rva0014F4C2(const Rva0014F4C2 &other);
	virtual ~Rva0014F4C2() {}
	int index;
};

struct __declspec(novtable) Rva00150D09Entry : public Rva0014F4C2
{
	Rva00150D09Entry() {}
	virtual ~Rva00150D09Entry() {}
};
class Rva00150C4BVector {
 Rva00150D09Entry *start,*finish,*end;
public: void resize(unsigned, Rva00150D09Entry);
};
typedef _STL::vector<Rva00150D09Entry> Rva00150D09Vector;
namespace _STL { template<> void vector<Rva00150D09Entry>::resize(unsigned int); }
class Rva00150D09 : public Rva00BC6F24Base { Rva00150D09Vector values; const void *m_10; int m_14; public: void grow(int count); void rva00150D09(int count); };
void Rva00150D09::grow(int count) {
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
// unique native wrapper 0x00150C4B decoded from this body.

// 0x00150C4B: 41B native resize wrapper constructs an 8-byte by-value
// entry. All three vtable writes come from this target; index remains
// uninitialized until the grow loop fills it. No application name inferred.
namespace _STL { template<> void vector<Rva00150D09Entry>::resize(unsigned n) {
 reinterpret_cast<Rva00150C4BVector*>(this)->resize(n,Rva00150D09Entry());
} }

namespace _STL {
template<> Rva00150D09Entry* vector<Rva00150D09Entry>::erase(Rva00150D09Entry*,Rva00150D09Entry*);
template<> void vector<Rva00150D09Entry>::_M_fill_insert(Rva00150D09Entry*,unsigned,const Rva00150D09Entry&);
}
void Rva00150C4BVector::resize(unsigned n,Rva00150D09Entry value) {
 _STL::vector<Rva00150D09Entry>*v=reinterpret_cast<_STL::vector<Rva00150D09Entry>*>(this);
 if (n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

// By-value resize: native 86B ret0C body, 8B stride, erase and fill
// callees read from this target. Inline vtable cleanup keeps EH unwind
// registration while dead stores disappear on the normal return path.

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0015087B reads ?_M_fill_insert@?$vector@URva0015087BElement@@V?$allocator@URva0015087BElement@@@_STL@@@_STL@@QAEXPAURva0015087BElement@@IABU3@@Z
#pragma comment(linker, "/alternatename:?_M_fill_insert@?$vector@URva00150D09Entry@@V?$allocator@URva00150D09Entry@@@_STL@@@_STL@@QAEXPAURva00150D09Entry@@IABU3@@Z=?_M_fill_insert@?$vector@URva0015087BElement@@V?$allocator@URva0015087BElement@@@_STL@@@_STL@@QAEXPAURva0015087BElement@@IABU3@@Z")
//   0x00150659 reads ?erase@?$vector@URva00150659Element@@V?$allocator@URva00150659Element@@@_STL@@@_STL@@QAEPAURva00150659Element@@PAU3@0@Z
#pragma comment(linker, "/alternatename:?erase@?$vector@URva00150D09Entry@@V?$allocator@URva00150D09Entry@@@_STL@@@_STL@@QAEPAURva00150D09Entry@@PAU3@0@Z=?erase@?$vector@URva00150659Element@@V?$allocator@URva00150659Element@@@_STL@@@_STL@@QAEPAURva00150659Element@@PAU3@0@Z")
