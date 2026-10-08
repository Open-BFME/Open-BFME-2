// ??1Rva0034C5E0@@UAE@XZ
// partial score=0.94 date=2026-09-27
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ob2 /Ireference/shims/moduledata
// stlport
// ??1Rva0034C5E0@@UAE@XZ @ 0x0035822E (88B).
// Dtor of small Snapshot-derived class owning an unsigned-void* RB-tree at +0x0C and AsciiString at +0x04.
// Evidence: vptr 0x008150E4 then null-checked tree dtor 0x00357C6A plus operator delete 0x0002FD60
// then StringBase teardown 0x00036410 then base vptr 0x007BB554; layout from rowed ctor 0x00356FDC
// (+0x04 zero +0x08 one +0x0C zero) and caller deleting dtor 0x00358317 slot 0 of 0x008150E4.
#include <map>

#include "Common/Snapshot.h"

#include "ascii_string.h"

namespace _STL
{
template <>
class _Rb_tree<unsigned, pair<const unsigned, void *>, _Select1st<pair<const unsigned, void *> >, less<unsigned>, allocator<pair<const unsigned, void *> > >
{
public:
	~_Rb_tree();

private:
	void *m_header;
	char m_pad[8];
};
}

typedef _STL::_Rb_tree<unsigned, _STL::pair<const unsigned, void *>, _STL::_Select1st<_STL::pair<const unsigned, void *> >, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > RvaTree00357C6A;

class Rva0034C5E0 : public Snapshot
{
public:
	virtual ~Rva0034C5E0();

private:
	AsciiString m_str;
	int m_val;
	RvaTree00357C6A *m_tree;
};

Rva0034C5E0::~Rva0034C5E0()
{
	RvaTree00357C6A *tree = m_tree;
	if (tree)
	{
		tree->~RvaTree00357C6A();
		::operator delete(tree);
	}
	m_tree = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1BfmeOwnedStringState@@QAE@XZ=??1Rva0034C5E0@@UAE@XZ")
