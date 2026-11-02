// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Split from Rva002B212A.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Native 2B212A..2B21EF (197B), RET8: search the receiver's 36-byte
// records for name and two ranges; increment/refresh a hit or append a
// level-one record. Each field offset and call is target evidence.
// Existing constructor2AF581 and refresh2AABEE independently establish
// string0/count4/value-range8/tag-range14/value20. The legacy unsigned
// vector declaration is an emitter view of the float range's four-byte
// words, as in the verified constructor; the original record name is open.
// The STL vector algorithm comes from vendored STLport4.5.3 at BFME1
// f98983a7d3bb405f1a4ba94bb6a2a168062a819d. ZH Player.cpp has no matching
// named level-record operation; its Player identity is not asserted here.
// The provider's int comparators return only0/1; a byte cast preserves
// those results and reproduces retail's AL tests without retyping providers.
// The owning wrapper gives the constructed ABI record its already-proved
// teardown2AF1EC. Force-inlining construction removes a forwarding call.
#include "ascii_string.h"
#include <vector>
#include <list>
// Suppress this TU's non-retail copy of ??1?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LocomotorTemplate;
namespace _STL { template <> vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LocomotorTemplate;
namespace _STL { template <> _Vector_base<LocomotorTemplate const *,allocator<LocomotorTemplate const *> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVLocomotorTemplate@@@_STL@@QBEXPAPBVLocomotorTemplate@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LocomotorTemplate;
namespace _STL { template <> void allocator<LocomotorTemplate const *>::deallocate(LocomotorTemplate const * *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
struct Rva002AAC9ERange {float const *begin,*end;};
struct AsciiRange002ADD75 {AsciiString const *begin,*end;};
int Rva002AAC9EEqual(const Rva002AAC9ERange *,const Rva002AAC9ERange *);
int Rva002ADD75Equal(const AsciiRange002ADD75 *,const AsciiRange002ADD75 *);
struct BfmeVectorRecord002AF478 {char opaque[36];};
namespace _STL {template <> void vector<BfmeVectorRecord002AF478>::push_back(const BfmeVectorRecord002AF478 &);}
struct Rva002B212AArg {char prefix[0x11C];_STL::vector<unsigned> values;char gap[8];_STL::vector<AsciiString> tags;};
class Rva002B212A {public:
 char prefix[0x3B0];_STL::vector<BfmeVectorRecord002AF478> records;
 void rva002B212A(Rva002B212AArg *,const AsciiString &);
};


// ?rva002ADC03@Player@@QAEXPAVRva004B5A65Owner@@H@Z, native 2ADC03..2ADC82
// (127B), RET8; callers 0x004B5A65 and 0x004B5AC0 (the cost-modifier
// upgrade pair). Finds the entry of the player's +0x6F4 list whose value
// range equals the upgrade's (+0x11C, the rowed comparator above), whose
// first referenced word is the upgrade's +0x118 and whose +0x10 is the
// given value; erases it (the folded list erase 0x00438539), destroys it
// through the folded 16-byte pair destructor 0x000796BC and frees it, then
// marks TheControlBar dirty (+0x28). Address-derived names; the list is
// spelled with the element type its folded erase carries.
class Snapshot;
// Bind the existing Snapshot-pointer erase owner; this donor's allocator
// settings otherwise emit a different COMDAT with the same name.
namespace _STL {
template<> list<Snapshot *>::iterator list<Snapshot *>::erase(iterator);
}

enum LocomotorSetType { LOCOMOTORSET_INVALID = -1 };
class LocomotorTemplate;
// Use the rowed 0x000796BC pair teardown rather than emitting a private copy.
// MSVC still synthesizes the implicit destructor with a member specialization;
// this declaration keeps the same const-key/vector layout and external ABI.
namespace _STL {
template <> struct pair<const LocomotorSetType, vector<const LocomotorTemplate *> > {
 const LocomotorSetType first;
 vector<const LocomotorTemplate *> second;
 ~pair();
};
}
typedef _STL::pair<const LocomotorSetType, _STL::vector<const LocomotorTemplate *> > Rva002ADC03Pair;
struct Rva002ADC03Ref { int m_value; };
struct Rva002ADC03Entry
{
	Rva002ADC03Ref *m_ref;			// +0x00
	Rva002AAC9ERange m_range;		// +0x04
	int m_0C;
	int m_value;					// +0x10
};
class Rva004B5A65Owner
{
public:
	char m_pad000[0x118];
	int m_118;						// +0x118
	Rva002AAC9ERange m_range;		// +0x11C
};
#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
class Player
{
public:
	void rva002ADC03(Rva004B5A65Owner *owner, int value);
	char m_pad000[0x6f4];
	_STL::list<Snapshot *> m_6F4;	// +0x6F4
};
void Player::rva002ADC03(Rva004B5A65Owner *owner, int value)
{
	_STL::list<Snapshot *> &entries = m_6F4;
	_STL::list<Snapshot *>::iterator end = entries.end();
	for (_STL::list<Snapshot *>::iterator it = entries.begin(); it != end; ++it)
	{
		Rva002ADC03Entry *entry = reinterpret_cast<Rva002ADC03Entry *>(*it);
		if ((unsigned char)Rva002AAC9EEqual(&entry->m_range, &owner->m_range) &&
			entry->m_ref->m_value == owner->m_118 && entry->m_value == value)
		{
			entries.erase(it);
			reinterpret_cast<Rva002ADC03Pair *>(entry)->~Rva002ADC03Pair();
			::operator delete(entry);
			TheControlBar->field28 = true;
			return;
		}
	}
}
