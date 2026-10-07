// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/RTS/ScienceStoreRootPrereqs.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ScienceStore::playerHasRootPrereqsForScience 0x001FFC55 (78B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
//
// ScienceStore::playerHasRootPrereqsForScience, retail 0x000E8040.
//
// The control-bar callers pass TheScienceStore, a Player pointer, and a
// ScienceType to this two-argument member before checking hasScience,
// playerHasPrereqsForScience, and the purchase cost.  Retail constructs a
// temporary STLport map<int,bool> and hands it to the three-argument recursive
// science prerequisite helper at 0x000E7C20.  The helper's original spelling
// is not established by the available headers, so its TU-local declaration is
// deliberately address-derived and pinned to the verified retail body; the
// compiler's call resolver selects the image's incremental thunk at each site.

#include <map>

typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

// Concrete Science memo providers are already owned by verified units.
// Keep these operations out of line instead of emitting conflicting copies.
typedef _STL::pair<const ScienceType, bool> ScienceMemoValue;
typedef _STL::_Rb_tree_base<ScienceMemoValue, _STL::allocator<ScienceMemoValue> > ScienceMemoBase;
typedef _STL::_Rb_tree<ScienceType, ScienceMemoValue, _STL::_Select1st<ScienceMemoValue>, _STL::less<ScienceType>, _STL::allocator<ScienceMemoValue> > ScienceMemoTree;
namespace _STL {
template <> ScienceMemoBase::_Rb_tree_base(const allocator<ScienceMemoValue> &);
template <> ScienceMemoBase::~_Rb_tree_base();
template <> ScienceMemoTree::~_Rb_tree();
template <> void ScienceMemoTree::clear();
}


class Player;

class Player
{
public:
	Bool hasScience( ScienceType st ) const;
};

struct SciencePrereqGroup
{
	ScienceType *m_begin;
	ScienceType *m_end;
	ScienceType *m_capacity;
};

class ScienceInfo
{
public:
	char m_head[ 0x18 ];
	SciencePrereqGroup *m_prereqGroups;
	SciencePrereqGroup *m_prereqGroupsEnd;
};

class ScienceStore
{
public:
	Bool playerHasRootPrereqsForScience( const Player *player, ScienceType st ) const;

private:
	const ScienceInfo *findScienceInfo( ScienceType st ) const;

	Bool rva000E7C20SciencePrereqMemo( const Player *player, ScienceType st,
		void *memo ) const;
};


Bool ScienceStore::playerHasRootPrereqsForScience( const Player *player, ScienceType st ) const
{
	std::map<ScienceType, Bool> memo;
	return rva000E7C20SciencePrereqMemo( player, st, &memo );
}
