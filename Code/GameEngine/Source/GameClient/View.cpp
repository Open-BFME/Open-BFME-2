// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/View.cpp); this unit had no counterpart under Code/.
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
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// View.cpp ///////////////////////////////////////////////////////////////////
// A "view", or window, into the World
// Author: Michael S. Booth, February 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameEngine.h"
#include "Common/Xfer.h"
#include "GameClient/View.h"
#include "GameClient/Drawable.h"

UnsignedInt View::m_idNext = 1;

// the tactical view singleton
View *TheTacticalView = NULL;


// ?View::View present-unmatched
View::View( void )
{
	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_currentHeightAboveGround = 0.0f;
	m_defaultAngle = 0.0f;
	m_defaultPitchAngle = 0.0f;
	m_heightAboveGround = 0.0f;
	m_lockDist = 0.0f;
	m_maxHeightAboveGround = 0.0f;
	m_maxZoom = 0.0f;
	m_minHeightAboveGround = 0.0f;
	m_minZoom = 0.0f;
	m_next = NULL;
	m_okToAdjustHeight = TRUE;
	m_originX = 0;
	m_originY = 0;
	m_snapImmediate = FALSE;
	m_terrainHeightUnderCamera = 0.0f;
	m_zoom = 0.0f;
	//
	m_pos.x = 0;
	m_pos.y = 0;
	m_width = 0;
	m_height = 0;
	m_angle = 0.0f;
	m_pitchAngle = 0.0f;
	m_cameraLock = INVALID_ID;
	m_cameraLockDrawable = NULL;
	m_zoomLimited = TRUE;

	// create unique view ID
	m_id = m_idNext++;

	// default field of view
	m_FOV = 50.0f * PI/180.0f;
	
	m_mouseLocked = FALSE;
	
	m_guardBandBias.x = 0.0f;
	m_guardBandBias.y = 0.0f;
}

// ?View::~View present-unmatched
View::~View()
{
}

// ?View::init present-unmatched
void View::init( void )
{
	m_width = DEFAULT_VIEW_WIDTH;
	m_height = DEFAULT_VIEW_HEIGHT;
	m_originX = DEFAULT_VIEW_ORIGIN_X;
	m_originY = DEFAULT_VIEW_ORIGIN_Y;
	m_pos.x = 0;
	m_pos.y = 0;
	m_angle = 0.0f;
	m_cameraLock = INVALID_ID;
	m_cameraLockDrawable = NULL;
	m_zoomLimited = TRUE;
	
	m_maxZoom = 1.3f;
	m_minZoom = 0.2f;
	m_zoom = m_maxZoom;
	m_maxHeightAboveGround = TheGlobalData->m_maxCameraHeight;
	m_minHeightAboveGround = TheGlobalData->m_minCameraHeight;
	m_okToAdjustHeight = FALSE;

	m_defaultAngle = 0.0f;
	m_defaultPitchAngle = 0.0f;
}

// ?View::reset present-unmatched
void View::reset( void )
{
	// Only fixing the reported bug.  Who knows what side effects resetting the rest could have.
	m_zoomLimited = TRUE;
}

/**
 * Prepend this view to the given list, return the new list.
 */
// ?View::prependViewToList present-unmatched
View *View::prependViewToList( View *list )
{
	m_next = list;
	return this;
}

// ?View::zoomIn present-unmatched
void View::zoomIn( void )
{
	setHeightAboveGround(getHeightAboveGround() - 10.0f);
}

// ?View::zoomOut present-unmatched
void View::zoomOut( void )
{
	setHeightAboveGround(getHeightAboveGround() + 10.0f);
}

/**
 * Center the view on the given coordinate.
 */
// Retail 0x0025EA7C..0x0025EAD5 preserves z before replacing x and y;
// initializing those discarded coordinates prevents the 89-byte match.
void View::lookAt( const Coord3D *o ) 
{ 

	/// @todo this needs to be changed to be 3D, this is still old 2D stuff
	Coord3D pos;
	pos.z = getPosition()->z;
	pos.x = o->x - m_width * 0.5f; 
	pos.y = o->y - m_height * 0.5f; 
	setPosition(&pos);
}

/**
 * Shift the view by the given delta.
 */
// ?View::scrollBy present-unmatched
void View::scrollBy( Coord2D *delta ) 
{ 
	// update view's world position
	m_pos.x += delta->x;
	m_pos.y += delta->y;
}

/**
 * Rotate the view around the up axis by the given angle.
 */
void View::setAngle( Real angle )
{
	m_angle = angle; 
}

/**
 * Rotate the view around the horizontal (X) axis to the given angle.
 */
void View::setPitch( Real angle )
{
	m_pitchAngle = angle;

	Real limit = PI/5.0f;

	if (m_pitchAngle < -limit)
		m_pitchAngle = -limit;
	else if (m_pitchAngle > limit)
		m_pitchAngle = limit;
}

/**
 * Set the view angle back to default
 */
// ?View::setAngleAndPitchToDefault present-unmatched
void View::setAngleAndPitchToDefault( void )
{ 
	m_angle = m_defaultAngle;
	m_pitchAngle = m_defaultPitchAngle;
}

/**
 * write the view's current location in to the view location object
 */
// ?View::getLocation present-unmatched
void View::getLocation( ViewLocation *location )
{

	const Coord3D *pos = getPosition();
	location->init( pos->x, pos->y, pos->z, getAngle(), getPitch(), getZoom() );

}


/**
 * set the view's current location from to the view location object
 */
// ?View::setLocation present-unmatched
void View::setLocation( const ViewLocation *location )
{
	if ( location->m_valid )
	{
		setPosition(&location->m_pos);
		setAngle(location->m_angle);
		setPitch(location->m_pitch);
		setZoom(location->m_zoom);
		forceRedraw();
	}

}

//-------------------------------------------------------------------------------------------------
/** project the 4 corners of this view into the world and return each point as a parameter,
		the world points are at the requested Z */
//-------------------------------------------------------------------------------------------------
// ?View::getScreenCornerWorldPointsAtZ present-unmatched
void View::getScreenCornerWorldPointsAtZ( Coord3D *topLeft, Coord3D *topRight,
																					Coord3D *bottomLeft, Coord3D *bottomRight,
																					Real z )
{
	ICoord2D screenTopLeft, screenTopRight, screenBottomLeft, screenBottomRight;
	ICoord2D origin;
	Int viewWidth = getWidth();
	Int viewHeight = getHeight();

	// sanity
	if( topLeft == NULL || topRight == NULL || bottomLeft == NULL || bottomRight == NULL )
		return;

	// setup the screen coords for the 4 corners of the viewable display
	getOrigin( &origin.x, &origin.y );
	screenTopLeft.x     = origin.x;								// upper left
	screenTopLeft.y     = origin.y;								// upper left
	screenTopRight.x    = origin.x + viewWidth;		// upper right
	screenTopRight.y    = origin.y;								// upper right
	screenBottomLeft.x  = origin.x + viewWidth;		// lower right
	screenBottomLeft.y  = origin.y + viewHeight;  // lower right
	screenBottomRight.x = origin.x;								// lower left
	screenBottomRight.y = origin.y + viewHeight;	// lower left

	// project
	screenToWorldAtZ( &screenTopLeft, topLeft, z );
	screenToWorldAtZ( &screenTopRight, topRight, z );
	screenToWorldAtZ( &screenBottomLeft, bottomLeft, z );
	screenToWorldAtZ( &screenBottomRight, bottomRight, z );

}  // end getScreenCornerWorldPointsAtZ

// ------------------------------------------------------------------------------------------------
/** Xfer method for a view */
// ------------------------------------------------------------------------------------------------
// ?View::xfer present-unmatched
void View::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// camera angle
	Real angle = getAngle();
	xfer->xferReal( &angle );
	setAngle( angle );

	// view position
	Coord3D viewPos;
	getPosition( &viewPos );
	xfer->xferReal( &viewPos.x );
	xfer->xferReal( &viewPos.y );
	xfer->xferReal( &viewPos.z );
	lookAt( &viewPos );

}  // end xfer

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?setDesiredSpeed@AIUpdateInterface@@QAEXM@Z=?setHeightAboveGround@View@@UAEXM@Z")

// Native FUN_0065e9de spans 0025E9DE..0025EA2E, ending in RET 28.
// It stores seven scalar floats at +4..+1C and then sets byte +0 to one.
// The original receiver and field meanings remain unknown. ZH ViewLocation
// has a similar initializer, but its six-argument signature is different.
class Rva0025E9DE
{
public:
	void rva0025E9DE(float a, float b, float c, float d, float e, float f, float g);
private:
	bool flag00;
	float value04, value08, value0C, value10, value14, value18, value1C;
};

void Rva0025E9DE::rva0025E9DE(float a, float b, float c, float d, float e, float f, float g)
{
	value04 = a;
	value08 = b;
	value0C = c;
	value10 = d;
	value14 = e;
	value18 = f;
	value1C = g;
	flag00 = true;
}

// Adapted from BFME 1 ViewGetLocationBfme.cpp, donor revision
// 968ca36c3265b295297e6aed45a6bd89ffe59c40. The donor's position-copy
// and seven-float initializer describe this shape; target virtual slots
// are each four bytes later. Native 0x0025EB43..0x0025EBB9 establishes
// position offsets +0x0C/+0x10/+0x14 and slots 100/108/110/124.
// Original target type, method and scalar meanings remain unclaimed.
class Rva0025EB43
{
public:
	#define RVA25EB43_SLOT(n) virtual void slot##n();
	RVA25EB43_SLOT(00) RVA25EB43_SLOT(04) RVA25EB43_SLOT(08) RVA25EB43_SLOT(0C)
	RVA25EB43_SLOT(10) RVA25EB43_SLOT(14) RVA25EB43_SLOT(18) RVA25EB43_SLOT(1C)
	RVA25EB43_SLOT(20) RVA25EB43_SLOT(24) RVA25EB43_SLOT(28) RVA25EB43_SLOT(2C)
	RVA25EB43_SLOT(30) RVA25EB43_SLOT(34) RVA25EB43_SLOT(38) RVA25EB43_SLOT(3C)
	RVA25EB43_SLOT(40) RVA25EB43_SLOT(44) RVA25EB43_SLOT(48) RVA25EB43_SLOT(4C)
	RVA25EB43_SLOT(50) RVA25EB43_SLOT(54) RVA25EB43_SLOT(58) RVA25EB43_SLOT(5C)
	RVA25EB43_SLOT(60) RVA25EB43_SLOT(64) RVA25EB43_SLOT(68) RVA25EB43_SLOT(6C)
	RVA25EB43_SLOT(70) RVA25EB43_SLOT(74) RVA25EB43_SLOT(78) RVA25EB43_SLOT(7C)
	RVA25EB43_SLOT(80) RVA25EB43_SLOT(84) RVA25EB43_SLOT(88) RVA25EB43_SLOT(8C)
	RVA25EB43_SLOT(90) RVA25EB43_SLOT(94) RVA25EB43_SLOT(98) RVA25EB43_SLOT(9C)
	RVA25EB43_SLOT(A0) RVA25EB43_SLOT(A4) RVA25EB43_SLOT(A8) RVA25EB43_SLOT(AC)
	RVA25EB43_SLOT(B0) RVA25EB43_SLOT(B4) RVA25EB43_SLOT(B8) RVA25EB43_SLOT(BC)
	RVA25EB43_SLOT(C0) RVA25EB43_SLOT(C4) RVA25EB43_SLOT(C8) RVA25EB43_SLOT(CC)
	RVA25EB43_SLOT(D0) RVA25EB43_SLOT(D4) RVA25EB43_SLOT(D8) RVA25EB43_SLOT(DC)
	RVA25EB43_SLOT(E0) RVA25EB43_SLOT(E4) RVA25EB43_SLOT(E8) RVA25EB43_SLOT(EC)
	RVA25EB43_SLOT(F0) RVA25EB43_SLOT(F4) RVA25EB43_SLOT(F8) RVA25EB43_SLOT(FC)
	virtual float slot100();
	RVA25EB43_SLOT(104)
	virtual float slot108();
	RVA25EB43_SLOT(10C)
	virtual float slot110();
	RVA25EB43_SLOT(114) RVA25EB43_SLOT(118) RVA25EB43_SLOT(11C) RVA25EB43_SLOT(120)
	virtual float slot124();
	#undef RVA25EB43_SLOT

	void rva0025EB43(Rva0025E9DE *location);
private:
	char m_pad04[8];
	float m_pos[3];
};

void Rva0025EB43::rva0025EB43(Rva0025E9DE *location)
{
	location->rva0025E9DE(m_pos[0], m_pos[1], m_pos[2],
		slot100(), slot108(), slot124(), slot110());
}
