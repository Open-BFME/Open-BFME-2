// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/campaignmanagerascii /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ?addRecentLadder@LadderPreferences@@QAEXVLadderPref@@@Z
// retail 0x005E03F6, 121 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/UserPreferences.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// PIN STATUS 2026-09-06 -- python3 tools/pin_status.py game/GameEngine/Source/Common/UserPreferences.cpp
// 47 of 71 definitions here carry a byte-verified `matched`
// targets/game/reverse/functions.csv row naming this source; 6 more are matched only
// from a split-out TU; 18 carry no ledger row at all.  Those 18 are unverified
// Zero Hour reference bodies and are not known to match BFME.  3 free functions
// are counted but not classified.  Check a body before porting behaviour off it.
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: UserPreferences.cpp
// Author: Matthew D. Campbell, April 2002
// Description: Saving/Loading of user preferences
///////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/GameSpyMiscPreferences.h"
#include "Common/UserPreferences.h"
#include "Common/LadderPreferences.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/Registry.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/IgnorePreferences.h"
#include "Common/QuotedPrintable.h"
#include "Common/MultiplayerSettings.h"
#include "GameClient/MapUtil.h"
#include "GameClient/ChallengeGenerals.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE TYPES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

class BfmeGameSpyInfoLocalProfileView
{
public:
	// BFME added seven slots before this method, so the inherited ZH view calls +0x54 instead of retail's +0x70.
	virtual void unused00() = 0, unused01() = 0, unused02() = 0, unused03() = 0;
	virtual void unused04() = 0, unused05() = 0, unused06() = 0, unused07() = 0;
	virtual void unused08() = 0, unused09() = 0, unused10() = 0, unused11() = 0;
	virtual void unused12() = 0, unused13() = 0, unused14() = 0, unused15() = 0;
	virtual void unused16() = 0, unused17() = 0, unused18() = 0, unused19() = 0;
	virtual void unused20() = 0, unused21() = 0, unused22() = 0, unused23() = 0;
	virtual void unused24() = 0, unused25() = 0, unused26() = 0, unused27() = 0;
	virtual Int getLocalProfileID() = 0;
};

class BfmeUserPreferencesVirtualView
{
public:
	virtual void unused00() = 0;
	virtual Bool load( const UnicodeString &fname ) = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual AsciiString getAsciiString( AsciiString key, AsciiString defaultValue ) const = 0;
	virtual void setAsciiString( AsciiString key, AsciiString val ) = 0;
};

struct BfmeAsciiStringDataView
{
	UnsignedInt m_refCount;
	UnsignedShort m_length;
};

struct BfmeAsciiStringView
{
	BfmeAsciiStringDataView *m_data;
	Bool isEmpty() const { return !m_data || m_data->m_length == 0; }
	const char *str() const { return m_data ? reinterpret_cast<const char *>( m_data ) + 8 : ""; }
};

//-----------------------------------------------------------------------------
// PRIVATE DATA ///////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC DATA ////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

// BFME's preference getters read the mapped value's characters in place instead
// of copying an AsciiString out, and they carry no unwind frame: the key is a
// plain object driven by explicit init/destroy calls rather than one with a
// destructor, and the map pointer is formed only after the key is built, which
// is why retail keeps plain `this` in esi across the constructor and only then
// does `add esi,4`. The map's header node doubles as its end sentinel.
struct CustomAsciiStringShim
{
	void *m_data;
	void init( const char *s );
	void destroy( void );
};

struct CustomStringDataShim
{
	UnsignedByte m_header[8];					///< characters follow at +8
};

struct CustomMapNodeShim
{
	UnsignedByte m_unreconstructed_00[0x14];
	CustomStringDataShim *m_value;				///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;
	CustomMapNodeShim *find( CustomAsciiStringShim *key );
};

static AsciiString intAsStr(Int val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

static AsciiString boolAsStr(Bool val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

static AsciiString realAsStr(Real val)
{
	AsciiString ret;
	ret.format("%g", val);
	return ret;
}

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// UserPreferences Class 
//-----------------------------------------------------------------------------

// Body in UserPreferences_write.asm (exact 162B retail).

//-----------------------------------------------------------------------------
// QuickMatchPreferences base class 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CustomMatchPreferences base class 
//-----------------------------------------------------------------------------

// BFME bounds the answer with the playable-side flag at PlayerTemplate+0xBD and
// nothing else -- none of the reference's starting-building, old-faction or
// disabled-general checks are in retail's body.
struct BfmePlayerTemplatePlayable
{
	UnsignedByte m_unreconstructed_00[0xBD];
	Bool m_isPlayableSide;
};

static const char superweaponRestrictionKey[] = "SuperweaponRestrict";

static const char startingCashKey[] = "StartingCash";

static const char limitFactionsKey[] = "LimitArmies";

static const char useStatsKey[] = "UseStats";

//-----------------------------------------------------------------------------
// GameSpyMiscPreferences base class 
//-----------------------------------------------------------------------------

// BFME reaches both preference accessors virtually -- getPref at slot 6 (+0x18)
// and setPref at slot 7 (+0x1c). They are one apart, which is what cross-checks
// the two slot numbers against each other.
class BfmeGameSpyMiscPrefsVtbl
{
public:
	virtual void _gsp0( void ) = 0;
	virtual void _gsp1( void ) = 0;
	virtual void _gsp2( void ) = 0;
	virtual void _gsp3( void ) = 0;
	virtual void _gsp4( void ) = 0;
	virtual void _gsp5( void ) = 0;
	virtual AsciiString getPref( AsciiString key, AsciiString defaultValue ) = 0;
	virtual void setPref( AsciiString key, AsciiString value ) = 0;
};

//-----------------------------------------------------------------------------
// IgnorePreferences base class 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// LadderPreferences base class 
//-----------------------------------------------------------------------------

void LadderPreferences::addRecentLadder( LadderPref ladder )
{
	for (LadderPrefMap::iterator it = m_ladders.begin(); it != m_ladders.end(); ++it)
	{
		if (it->second == ladder)
		{
			m_ladders.erase(it);
			break;
		}
	}

	m_ladders[ladder.lastPlayDate] = ladder;
}
