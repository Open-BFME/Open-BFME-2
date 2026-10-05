// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva005C6C7B@@UAE@XZ @0x005C6C7B 14B: virtual dtor holding a
// set<Rva0027EA49> tree (rowed tree dtor 0x005C6BF5) at +0x30; the empty body
// tail-jumps to the member dtor after the vptr store, the shape of the rowed
// Rva00577838 dtor. Tree, key and hint views are copied from
// stlport_rb_tree_dtor_twins.cpp. The scalar deleting dtor 0x005C6D80 calls
// this body. Identity unproven; address-derived holder name.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "ascii_string.h"

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva0027EA49
{
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};
bool operator<(const Rva0027EA49 &a, const Rva0027EA49 &b);
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva0027EA49Tree;

class Rva005C6C7B
{
public:
	virtual ~Rva005C6C7B();
private:
	char m_pad[0x2C];
	Rva0027EA49Tree m_30; // +0x30
};

Rva005C6C7B::~Rva005C6C7B()
{
}
