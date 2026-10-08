// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI's structure-placement anchor: setPlacementStart (vftable 0x7FD410
// slot 58), setPlacementEnd (59), isPlacementAnchored (60),
// getPlacementPoints (61) and getPlacementAngle (62).
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp, same names and slot
// order (ZH slots 42-46 between placeBuildAvailable and
// selectDrawable).
// Target evidence for the layout: the anchor flag is the byte at +0x554, the
// start point +0x558 and the end point +0x560 (setPlacementStart writes both
// from the one argument, setPlacementEnd only +0x560); the pending place type
// is +0x53C and the placement icon array +0x544, whose first drawable's angle
// (+0x44, after the cached position at +0x38) is the placement angle, else
// 0.0f from the literal pool.
// BFME 2 difference from ZH: getPlacementPoints projects the first icon's
// position (the interpolated position getter 0x002763E6) through
// TheTacticalView->worldToScreen (0x00050F29) when the pending template
// has the kind-of bit at +0x11F & 0x10 (template kind-of bits at +0x108).

#define NULL 0

struct ICoord2D { int x, y; };
#include "../../../Libraries/Include/Lib/Coord3D.h"

class ThingTemplate
{
public:
	bool hasPlacementProjection() const { return ( m_kindOfBytes[0x17] & 0x10 ) != 0; }
private:
	char m_unknown000[0x108];
	unsigned char m_kindOfBytes[0x18];				// +0x108
};

class Drawable
{
public:
	float getOrientation() const { return m_cachedAngle; }
private:
	char m_unknown00[0x44];
	float m_cachedAngle;							// +0x44
};

// The ledger's name for Drawable's interpolated position getter 0x002763E6.
class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class View
{
public:
	bool worldToScreen( const Coord3D *w, ICoord2D *s );	// 0x00050F29, the inline ZH wrapper over slot 88
};

extern View *TheTacticalView;

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
	V(56) V(57)
#undef V
	virtual void setPlacementStart( const ICoord2D *start );	// slot 58
	virtual void setPlacementEnd( const ICoord2D *end );		// slot 59
	virtual bool isPlacementAnchored( void );				// slot 60
	virtual void getPlacementPoints( ICoord2D *start, ICoord2D *end );	// slot 61
	virtual float getPlacementAngle( void );					// slot 62

protected:
	char m_unknown004[0x53C - 0x4];
	const ThingTemplate *m_pendingPlaceType;		// +0x53C
	char m_unknown540[0x544 - 0x540];
	Drawable **m_placeIcon;							// +0x544
	char m_unknown548[0x554 - 0x548];
	bool m_placeAnchorInProgress;					// +0x554
	ICoord2D m_placeAnchorStart;					// +0x558
	ICoord2D m_placeAnchorEnd;						// +0x560
};

void InGameUI::setPlacementStart( const ICoord2D *start )
{
	if( start )
	{
		m_placeAnchorStart.x = start->x;
		m_placeAnchorStart.y = start->y;
		m_placeAnchorEnd.x = start->x;
		m_placeAnchorEnd.y = start->y;
		m_placeAnchorInProgress = true;
	}
	else
		m_placeAnchorInProgress = false;
}

void InGameUI::setPlacementEnd( const ICoord2D *end )
{
	if( end )
	{
		m_placeAnchorEnd.x = end->x;
		m_placeAnchorEnd.y = end->y;
	}
}

bool InGameUI::isPlacementAnchored( void )
{
	return m_placeAnchorInProgress;
}

void InGameUI::getPlacementPoints( ICoord2D *start, ICoord2D *end )
{
	if( start )
	{
		if( m_pendingPlaceType->hasPlacementProjection() && m_placeIcon[ 0 ] )
		{
			TheTacticalView->worldToScreen( reinterpret_cast<BFMERopeDrawable *>( m_placeIcon[ 0 ] )->getPosition(), start );
		}
		else
			*start = m_placeAnchorStart;
	}
	if( end )
		*end = m_placeAnchorEnd;
}

float InGameUI::getPlacementAngle( void )
{
	if( m_placeIcon[ 0 ] )
		return m_placeIcon[ 0 ]->getOrientation();
	return 0.0f;
}
