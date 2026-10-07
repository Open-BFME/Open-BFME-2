// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4  // BFME renamed it
//
// TeamFactory::removeTeamPrototypeFromList — sibling TU (LocomotorAccessors
// pattern). Retail body @ 0x000EFD50 (149B) keys m_prototypes by
// pair<NameKeyType,NameKeyType> from TeamPrototype AsciiStrings at +0x10/+0x14
// (single-vptr layout; owner-name beside m_name), erases a 0x1C-byte node, and
// calls STLport erase helpers via direct e8. Team.cpp keeps the ZH single-key
// typedef so its other matched symbols stay green; /D_STLP_USE_STATIC_LIB is
// file-local so dllimport-dependent Team.cpp rows are undisturbed.
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
#include "PreRTS.h"
#include "Common/Team.h"
#include "Common/NameKeyGenerator.h"

// ?removeTeamPrototypeFromList@TeamFactory@@QAEXPAVTeamPrototype@@@Z
// ?TeamFactory::removeTeamPrototypeFromList present-unmatched
void TeamFactory::removeTeamPrototypeFromList(TeamPrototype* team)
{
	struct BfmeAsciiString {
		char *m_text;
		const char *str() const { return m_text ? m_text + 8 : ""; }
	};
	struct BfmeTeamPrototypeView {
		void *vftable;
		void *m_factory;
		void *m_owningPlayer;
		UnsignedInt m_id;
		BfmeAsciiString m_name;       // +0x10
		BfmeAsciiString m_ownerName;  // +0x14
	};
	typedef std::pair<NameKeyType, NameKeyType> BfmeTeamPrototypeKey;
	typedef std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > BfmeTeamPrototypeMap;

	BfmeTeamPrototypeView *tp = reinterpret_cast<BfmeTeamPrototypeView *>(team);
	// MSVC evaluates pair ctor args RTL: owner-name key first (+0x14), then name (+0x10).
	BfmeTeamPrototypeKey nk(NAMEKEY(tp->m_name.str()), NAMEKEY(tp->m_ownerName.str()));
	BfmeTeamPrototypeMap *map = reinterpret_cast<BfmeTeamPrototypeMap *>(&m_prototypes);
	BfmeTeamPrototypeMap::iterator it = map->find(nk);
	if (it != map->end())
		map->erase(it);
}
