// cl: /Ireference/shims/bfmealloc -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/RTS
// stlport
// readable body of ??1TeamFactory@@UAE@XZ: game/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?addTeamPrototypeToList@TeamFactory@@QAEXPAVTeamPrototype@@@Z: game/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?clear@TeamFactory@@QAEXXZ: game/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?initTeam@TeamFactory@@QAEXABVAsciiString@@0_NPAVDict@@@Z: game/GameEngine/Source/Common/RTS/Team.cpp

// TeamFactory's default constructor, lifted from its MASM dump to C++.
//
// Retail body @ 0x000F2250 (130B):
//   - calls SubsystemInterface::SubsystemInterface() (0x009A1A30, already
//     matched in game/GameEngine/Source/Common/System/SubsystemInterface.cpp)
//     to build the first base (vptr + AsciiString m_name, 8 bytes @ +0x00).
//   - inlines a second, trivial base ctor (no call reaches the bytes) that
//     just stores its own identity vptr @ +0x08 -- this is Snapshot, whose
//     real ctor (Common/System/Snapshot.cpp) is an empty {} body, so the
//     compiler folds it away and only its vptr store survives.
//   - stores TeamFactory's own vtables over both subobjects (+0x00, +0x08),
//     which only happens because TeamFactory overrides virtuals from each
//     base -- forcing a distinct combined vtable per polymorphic subobject.
//   - default-constructs an STLport std::map member @ +0x0c: allocates a
//     0x1c-byte header node (color + parent/left/right + a 12-byte unused
//     value slot), then links left/right back to itself for an empty tree.
//     The 0x1c node size keys the map by a 2-word (8-byte) type, matching
//     TeamFactoryList.cpp's independently-established finding that BFME's
//     m_prototypes is keyed by pair<NameKeyType,NameKeyType> (not the single
//     NameKeyType key ZH's Team.h declares). The exact key/value C++ types
//     don't affect this constructor's bytes (default ctor never compares
//     keys), only their combined size, so plain ints stand in here.
//   - zero-initializes two trailing Int members @ +0x18 / +0x1c
//     (m_uniqueTeamPrototypeID, m_uniqueTeamID). The map's own third
//     (empty, comparator) word @ +0x14 is a real member but is never
//     written -- an empty functor has no state to store.
//
// Object layout: SubsystemInterface(0x08) + Snapshot(0x04) + map(0x0c) +
// 2 Ints(0x08) = 0x20 total.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Modelled first base: only its ABI shape (vptr + one pointer-sized data
// member) and its ctor's mangled name matter here -- the real body lives in
// game/GameEngine/Source/Common/System/SubsystemInterface.cpp (already
// matched), so the ctor below is declared, never defined, and resolves
// there as an external call.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Modelled second base: matches Snapshot's shape. Its ctor is trivial and
// defined right here (inline) so the compiler folds the call away, exactly
// as retail's bytes show -- only the resulting vptr store reaches the
// target function.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// The map's value is anonymous in retail; the ledger already carries its
// _Rb_tree instantiation under the generated payload name gen_dump.py minted
// for it, so use that name and the destructor resolves to the matched row.
// The map is keyed by a two-word key with a plain pointer value, not by an int
// with an eight-byte value: addTeamPrototypeToList @0x000F3DA0 builds the key
// from two NAMEKEY calls before looking it up. Both shapes give the same 0x1C
// node, which is why the constructor, destructor and clear all match either
// way - only a body that uses the key can tell them apart.
// Enough of AsciiString to reproduce str(): retail inlines it as
// `p ? p + 8 : ""` at 0x000F3DAA and 0x000F3DCA.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

enum NameKeyType { NAMEKEY_INVALID = 0 };
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class AsciiString;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
	const AsciiString &keyToName(NameKeyType);
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Dict;
class Player;
class Team;
class TeamFactory;

// getNeutralPlayer is inlined at 0x000F81D3 as a read of this+0x14.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType nk);
	Player *m_pad[5];
	Player *m_neutral;	// +0x14
};
extern PlayerList *ThePlayerList;

// The two AsciiStrings the key is built from sit at +0x10 and +0x14.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	virtual ~TeamPrototype();
	// Seven parameters: 0x000F81FB-0x000F8210 pushes owner and name as two
	// separate strings, in that order, exactly like findTeamPrototype.
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
				Player *pOwner, bool isSingleton, Dict *d, int id);
	char m_pad[0xc];
	AsciiString m_first;
	AsciiString m_second;
	char m_tail[0x278 - 0x18];
};
typedef std::pair<int, int> BfmeTeamPrototypeKey;
// insert_unique is called out of line: bind it to StlSweepR3Rva0039F692.cpp's rowed
// retail specialization instead of emitting a competing (duplicate) copy here.
namespace _STL { template <> pair<_Rb_tree_iterator<pair<const pair<int, int>, TeamPrototype *>, _Nonconst_traits<pair<const pair<int, int>, TeamPrototype *> > >, bool> _Rb_tree<pair<int, int>, pair<const pair<int, int>, TeamPrototype *>, _Select1st<pair<const pair<int, int>, TeamPrototype *> >, less<pair<int, int> >, allocator<pair<const pair<int, int>, TeamPrototype *> > >::insert_unique(const pair<const pair<int, int>, TeamPrototype *> &); }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamFactory();
	virtual ~TeamFactory();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

	void clear(void);
	void addTeamPrototypeToList(TeamPrototype *team);
	// Two parameters, not one: 0x000F8191 pushes both `name` and `owner`
	// before the call, matching the pair-keyed m_prototypes map.
	TeamPrototype *findTeamPrototype(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
	void initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d);

protected:
	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);

private:
	// Keyed by int with an eight-byte value, not by a two-word key: the
	// destructor at 0x000F750B calls
	// _Rb_tree<H, pair<$$CBH, <8 bytes>>>::~_Rb_tree, which names the key type
	// directly. The node is 0x1C either way - 0x10 of links plus a 0xC value -
	// so the constructor's bytes are unchanged.
	std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > m_prototypes;
	int m_uniqueTeamPrototypeID;
	int m_uniqueTeamID;
};

// ??0TeamFactory@@QAE@XZ is defined in TeamFactoryCtor.cpp (rowed 0x003A25B1).

// BFME nulls its singleton in the destructor; the store lands between clear()
// and the map teardown at 0x000F7500.
extern TeamFactory *TheTeamFactory;

// ??1TeamFactory@@UAE@XZ is defined in TeamFactoryDtor.cpp (rowed 0x003A383A).

// clear is defined and verified in TeamFactoryClear.cpp.

// addTeamPrototypeToList itself is rowed in TeamFactoryAddPrototype003A2B78.cpp; this unit
// instantiates the map members it owns (operator[] 0x003A2943 and what it calls out of line).
template TeamPrototype *&std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> >::operator[](const BfmeTeamPrototypeKey &);

// TeamFactory::initTeam is defined with its retail-matched body in Code/GameEngine/Source/Common/RTS/TeamFactoryInitTeam.cpp (0x003A404D).
