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

extern "C" const void* const __identifier("??_7SourceNamespace_DirectionalLight@FXShaderParameterSourceNamespaceSAS@@6B@")[];

class __declspec(novtable) Rva0014F4A1 : public Rva0014F401
{
public:
	Rva0014F4A1() { *(const void**)this=__identifier("??_7SourceNamespace_DirectionalLight@FXShaderParameterSourceNamespaceSAS@@6B@"); }
	Rva0014F4A1(const Rva0014F4A1 &other);
	virtual ~Rva0014F4A1() {}
	int index;
};

struct __declspec(novtable) Rva00150CD0Entry : public Rva0014F4A1
{
	Rva00150CD0Entry() {}
	virtual ~Rva00150CD0Entry() {}
};
class Rva00150C22Vector {
 Rva00150CD0Entry *start,*finish,*end;
public: void resize(unsigned, Rva00150CD0Entry);
};
typedef _STL::vector<Rva00150CD0Entry> Rva00150CD0Vector;
namespace _STL { template<> void vector<Rva00150CD0Entry>::resize(unsigned int); }
class Rva00150CD0 : public Rva00BC6F24Base { Rva00150CD0Vector values; const void *m_10; int m_14; public: void grow(int count); void rva00150CD0(int count); };
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
template<> void vector<Rva00150CD0Entry>::_M_fill_insert(Rva00150CD0Entry*,unsigned,const Rva00150CD0Entry&);
}
void Rva00150C22Vector::resize(unsigned n,Rva00150CD0Entry value) {
 _STL::vector<Rva00150CD0Entry>*v=reinterpret_cast<_STL::vector<Rva00150CD0Entry>*>(this);
 if (n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

// By-value resize: native 86B ret0C body, 8B stride, erase and fill
// callees read from this target. Inline vtable cleanup keeps EH unwind
// registration while dead stores disappear on the normal return path.

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0015079D reads ?_M_fill_insert@?$vector@URva0015079DElement@@V?$allocator@URva0015079DElement@@@_STL@@@_STL@@QAEXPAURva0015079DElement@@IABU3@@Z
#pragma comment(linker, "/alternatename:?_M_fill_insert@?$vector@URva00150CD0Entry@@V?$allocator@URva00150CD0Entry@@@_STL@@@_STL@@QAEXPAURva00150CD0Entry@@IABU3@@Z=?_M_fill_insert@?$vector@URva0015079DElement@@V?$allocator@URva0015079DElement@@@_STL@@@_STL@@QAEXPAURva0015079DElement@@IABU3@@Z")
//   0x00150659 reads ?erase@?$vector@URva00150659Element@@V?$allocator@URva00150659Element@@@_STL@@@_STL@@QAEPAURva00150659Element@@PAU3@0@Z
#pragma comment(linker, "/alternatename:?erase@?$vector@URva00150CD0Entry@@V?$allocator@URva00150CD0Entry@@@_STL@@@_STL@@QAEPAURva00150CD0Entry@@PAU3@0@Z=?erase@?$vector@URva00150659Element@@V?$allocator@URva00150659Element@@@_STL@@@_STL@@QAEPAURva00150659Element@@PAU3@0@Z")
