// ??1Rva004D060B@@QAE@XZ
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ??1Rva004D060B@@QAE@XZ @0x004D060B 66B
// Dtor: wide string at +0x14 via releaseBuffer 0x36E70 plus iface ptr at +0x18
// via virtual slot0 with 0 then operator delete 0x2FD60. Evidence: deleting
// dtor caller at 0x004D064D plus array delete loop at 0x004D06AE plus EH prolog.
//
// Retail orders the four blocks as member load, xor, cmp, EH-state store:
//   mov ecx,[esi+0x18] ; xor eax,eax ; cmp ecx,eax ; mov [ebp-4],eax ; je +5
// so the null is compared BEFORE the store that publishes it. /EHa anchors
// `xor eax,eax` with its `mov [ebp-4],eax` as one state-variable
// initialisation at frame entry and always emits that pair first, which sinks
// the member load between them. /EHsc breaks the pair: the store is then
// scheduled after the compare, exactly as retail has it.
//
// The member load must also be the first source-level statement, with the null
// materialised only inside the inner scope that deletes it; spelling the delete
// as a named local initialized to 0 lets cl hoist the pair back to frame entry.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"
class Rva004D060BIface
{
public:
	virtual void *Get(int v);
};
class Rva004D060B
{
public:
	~Rva004D060B();
private:
	unsigned char m_pad[0x14];
	StringBase<unsigned short> m_text;
	Rva004D060BIface *m_ptr;
};

// ??1Rva004D060B@@QAE@XZ
Rva004D060B::~Rva004D060B()
{
	Rva004D060BIface *p = m_ptr;
	{
		void *block;
		if (p)
			block = p->Get(0);
		else
			block = 0;
		::operator delete(block);
	}
}