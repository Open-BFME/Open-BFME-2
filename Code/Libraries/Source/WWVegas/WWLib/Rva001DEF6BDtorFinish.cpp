// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva001DEF6B@@QAE@XZ @0x001DEF6B 30B.
//
// Retail bytes: push esi / mov esi,ecx / push [esi+4] / push [esi] / call
// 0x001DEEE0 / mov esi,[esi] / test esi,esi / pop ecx / pop ecx / je +7 /
// push esi / call 0x00030830 _free / pop ecx / pop esi / ret.
//
// The range destroy is called DIRECTLY, not through _Destroy. The 25B loop at
// 0x001DEEE0 is the rowed __destroy_aux for Rva00414BDBElement: it reads only
// [esp+8] and [esp+0xc] (first/last) and strides 0x30, so the __false_type
// argument ICF folded away and a two-argument spelling reproduces it. That
// distinguishes this body from the vector<>::~vector family
// (StlportVectorDtorFamily.cpp), which all call the 24B _Destroy WRAPPER at
// 0x00414508 / 0x0008B632 -- a different body that builds a tag local first.
//
// Element identity: Rva00414BDBElement is the address-derived 0x30-stride
// element already rowed at 0x001DEEE0 and at the vector dtor 0x00414721. The
// owning class of the two-pointer {start,finish} pair is not established here,
// so the honest address-derived name stands.
struct Rva00414BDBElement {
	char m_opaque[48];
	Rva00414BDBElement(const Rva00414BDBElement &);
	Rva00414BDBElement &operator=(const Rva00414BDBElement &);
	~Rva00414BDBElement();
};

namespace _STL {
// The 25B range-destroy loop, rowed as the ICF-folded __destroy_aux
// instantiation at 0x001DEEE0. Only first/last are read.
void __destroy_aux(Rva00414BDBElement *first, Rva00414BDBElement *last);
}

extern "C" void __cdecl free(void *p);

class Rva001DEF6B
{
public:
	~Rva001DEF6B();
private:
	Rva00414BDBElement *m_start;
	Rva00414BDBElement *m_finish;
};

// The emitted call must land on 0x001DEEE0, so bind the plain two-argument
// spelling to the rowed template instantiation.
#pragma comment(linker, "/alternatename:?__destroy_aux@_STL@@YAXPAURva00414BDBElement@@0@Z=??$__destroy_aux@PAURva00414BDBElement@@@_STL@@YAXPAURva00414BDBElement@@0ABU__false_type@0@@Z")

Rva001DEF6B::~Rva001DEF6B()
{
	_STL::__destroy_aux(m_start, m_finish);
	Rva00414BDBElement *s = m_start;
	if (s)
		free(s);
}