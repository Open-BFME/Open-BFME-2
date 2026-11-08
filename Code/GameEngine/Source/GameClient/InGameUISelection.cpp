// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI selection: deselectAllDrawables (vftable 0x7FD410 slot 68,
// 0x0029BDBC), isAnySelectedKindOf (slot 78, 0x0029C0D6) and
// isAllSelectedKindOf (slot 79, 0x0029C107).
// deselectAllDrawables is ZH's loop over TheInGameUI's getAllSelectedDrawables
// (slot 73) calling deselectDrawable (slot 67) with the iterator advanced
// first, then the list clear 0x00239380 on +0x20 and the solo-nexus drawable
// id at +0x980 reset. BFME 2 dropped the postMsg argument and its
// MSG_DESTROY_SELECTED_GROUP (plain ret, no stack arguments).
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp, same names and the same
// pair order after isDrawableSelected (ZH slots 57-59, BFME 2 slots 77-79).
// Target evidence: both walk the selected drawable list at +0x20 directly (no
// getAllSelectedDrawables call, unlike ZH), skip null entries and test the
// drawable's template (+0x04) with the out-of-line ThingTemplate kind-of test
// 0x000456AC (kind-of bits at +0x108, bool result tested in al); any-of
// returns true on the first hit, all-of returns false on the first miss.

#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

enum KindOfType { KINDOF_INVALID = -1 };

#include "../../Include/Common/ThingTemplate.h"

#include "../../Include/GameClient/Drawable.h"
// The native callers examine the template query's bool result in AL.
static inline unsigned char drawableIsKindOf( const Drawable *draw, KindOfType t )
{ return (unsigned char)draw->m_template->isKindOf( t ); }

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

// The ledger's address name for the selected-drawable list clear 0x00239380.
class Rva00239380Holder
{
public:
	void rva00239380();
};

enum { INVALID_DRAWABLE_ID = 0 };

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

void InGameUI::deselectAllDrawables( void )
{
	const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();

	for( DrawableListCIt it = selected->begin(); it != selected->end(); )
	{
		Drawable *draw = *it++;
		TheInGameUI->deselectDrawable( draw );
	}

	reinterpret_cast<Rva00239380Holder *>( &m_selectedDrawables )->rva00239380();

	m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;
}

bool InGameUI::isAnySelectedKindOf( KindOfType kindOf ) const
{
	Drawable *draw;

	DrawableListCIt end = m_selectedDrawables.end();
	for( DrawableListCIt it = m_selectedDrawables.begin(); it != end; ++it )
	{
		draw = *it;
		if( draw && drawableIsKindOf( draw, kindOf ) )
			return true;
	}

	return false;
}

bool InGameUI::isAllSelectedKindOf( KindOfType kindOf ) const
{
	Drawable *draw;

	DrawableListCIt end = m_selectedDrawables.end();
	for( DrawableListCIt it = m_selectedDrawables.begin(); it != end; ++it )
	{
		draw = *it;
		if( draw && !drawableIsKindOf( draw, kindOf ) )
			return false;
	}

	return true;
}
