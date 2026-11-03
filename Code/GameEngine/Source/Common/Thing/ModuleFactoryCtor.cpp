// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /GF
// stlport
// Native0041386B54B: science-bonus schedule record, side-pointer vector+0 and bonus map+0xC.
// Native callbacks002E2612/004138C7 and caller00413B4D establish the24B layout.
#include <vector>
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
// The Sides parser002E2612 stores pointers returned by lookup002E18C3.
// The pointee's original class name is unproven; no pointed-to object is owned.
struct Rva002E18C3Side;
// Callback004138C7 parses and copies this complete twelve-byte value.
// The signed key is the minimum science-purchase-point count.
struct Rva004138C7BonusView {
 int minimum;
 float firstMultiplier;
 float secondMultiplier;
};
#include "../../../Include/Common/INI/FieldParse.h"
void Rva002E2612Parse(INI *, void *, void *, const void *);
void Rva004138C7Parse(INI *, void *, void *, const void *);

#include "../../../Include/Common/INI/INI.h"

// Native table: two named fields and a complete null terminator. The
// callbacks and their existing rowed consumers establish the vector at +0
// and science-bonus map at +0x0C independently of this ctor's old class view.
extern const FieldParse g_00C39AF8[3] = {
 { "Sides", Rva002E2612Parse, 0, 0 },
 { "Bonus", Rva004138C7Parse, 0, 0x0C },
 { 0, 0, 0, 0 }
};

class Rva0041386B
{
public:
	Rva0041386B();
	void rva0041393F(class INI *ini);
private:
	_STL::vector<Rva002E18C3Side *> m_vec00;
	_STL::map<int, Rva004138C7BonusView> m_map0C;
};
typedef char VerifyScienceBonusFields[(sizeof(Rva004138C7BonusView) == 12) ? 1 : -1];
typedef char VerifyScienceBonusRecord[(sizeof(Rva0041386B) == 24) ? 1 : -1];
Rva0041386B::Rva0041386B()
{
}

// ?rva0041393F@Rva0041386B@@QAEXPAVINI@@@Z @0x0041393F 18B: INI-field init
// forwarder. Caller 0x00413B95 passes ecx = Rva0041386B local and INI * in esi;
// retail pushes the FieldParse table 0x00839AF8 then this, then calls rowed
// INI::initFromINI 0x0002DE78 with ecx = INI *. Honest address name; table is
// owned above with both callbacks and its terminator.
void Rva0041386B::rva0041393F(INI *ini)
{
	ini->initFromINI(this, g_00C39AF8);
}
