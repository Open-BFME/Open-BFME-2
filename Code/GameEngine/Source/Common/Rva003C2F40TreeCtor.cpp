// cl: -DNDEBUG -MD -EHsc /O1 -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME: ??0Rva003C2F40Owner@@QAE@XZ at retail 0x002BAE57.
// The native constructor installs the vtable at 0x007FE408, whose name slot
// returns "DelayedSplineCameraEventModule", then constructs the map at +0x0c.
// The placeholder base/owner hierarchy below still needs native vtable and
// destructor reconciliation; its historical VNI label was unsupported.

// stlport
#define _STLP_USE_STATIC_LIB 1
#include <memory>

// The native call at 0x002BAE75 reaches the existing 25-byte map constructor
// at 0x005011C1. Several int-keyed maps share that body. Use its rowed
// provider spelling, without asserting that this event's mapped values are
// BfmePod24.
//
// The native destructor 0x002BAEAB destroys the same +0x0c member through
// the tree destructor 0x002B80CE, whose clear 0x002B70B3 is the
// map<int,AsciiString> specialization (stlport_int_ascii_tree_dtor.cpp).
// The map's twelve bytes are therefore that tree, and its implicit
// destructor calls the existing provider's spelling.
struct BfmePod24;
class AsciiString;
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class P> struct _Select1st;
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	~_Rb_tree();
private:
	char m_storage[12];
};
template <class K, class V, class C, class A> class map
{
public:
	map();
	// Inline only. An emitted ??1map<int,BfmePod24> COMDAT here would jump
	// to the AsciiString tree, unlike the other units' copies, and this unit
	// precedes them in link order.
	__declspec(dllimport) __forceinline ~map() {}
private:
	_Rb_tree<int, pair<const int, AsciiString>,
		_Select1st<pair<const int, AsciiString> >, less<int>,
		allocator<pair<const int, AsciiString> > > m_tree;
};
}
typedef _STL::map<int, BfmePod24, _STL::less<int>,
	_STL::allocator<_STL::pair<const int, BfmePod24> > > Rva003C2F40Tree;

#define BFME_SNAPSHOT_CONSTRUCTOR_ONLY
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

// Constructor unwind and the existing complete destructor both reach the
// Snapshot destructor at 0x0049B47C. Preserve the two words before the map;
// the event's own remaining virtual slots still need owner reconciliation.
// No user-declared destructor: retail's 0x002BAEAB stores no vptr, which is
// the implicit virtual destructor this unit's vftable (via ??_G) emits.
class Rva003C2F40Owner : public Snapshot
{
public:
	Rva003C2F40Owner();
	unsigned m_bfme04;
	char m_bfme08;
	char m_padding09[3];
	Rva003C2F40Tree m_tree;
};
// ??0Rva003C2F40Owner@@QAE@XZ
Rva003C2F40Owner::Rva003C2F40Owner()
{
}
