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

enum KindOfType { KINDOF_INVALID = -1 };

class ThingTemplate
{
public:
	bool isKindOf( KindOfType t ) const;
};

class Drawable
{
public:
	bool isKindOf( KindOfType t ) const { return m_template->isKindOf( t ); }
private:
	virtual void r0();
	const ThingTemplate *m_template;				// +0x04
};

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

// The ledger's address name for the selected-drawable list clear 0x00239380.
class Rva00239380Holder
{
public:
	void rva00239380();
};

typedef unsigned int DrawableID;
enum { INVALID_DRAWABLE_ID = 0 };

class InGameUI
{
public:
#define V(n) virtual void r##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66)
#undef V
	virtual void deselectDrawable( Drawable *draw );				// slot 67
	virtual void deselectAllDrawables( void );						// slot 68
	virtual void r69();
	virtual void r70();
	virtual void r71();
	virtual void r72();
	virtual const DrawableList *getAllSelectedDrawables( void ) const;	// slot 73
	virtual void r74();
	virtual void r75();
	virtual void r76();
	virtual void r77();
	virtual bool isAnySelectedKindOf( KindOfType kindOf ) const;	// slot 78
	virtual bool isAllSelectedKindOf( KindOfType kindOf ) const;	// slot 79

protected:
	char m_unknown004[0x20 - 0x4];
	DrawableList m_selectedDrawables;				// +0x20
	char m_unknown024[0x980 - 0x24];
	DrawableID m_soloNexusSelectedDrawableID;		// +0x980
};

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
		if( draw && draw->isKindOf( kindOf ) )
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
		if( draw && !draw->isKindOf( kindOf ) )
			return false;
	}

	return true;
}
