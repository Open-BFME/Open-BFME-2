// cl: /Ireference/shims/zh_ascii_outofline -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/gameinfo -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: GameInfo.cpp //////////////////////////////////////////////////////
// game setup state info
// Author: Matthew D. Campbell, December 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/CRCDebug.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameState.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "Common/Xfer.h"
#include "GameNetwork/FileTransfer.h"
#include "GameNetwork/GameInfo.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "GameNetwork/GameSpy/StagingRoomGameInfo.h"
#include "GameNetwork/LANAPI.h"						// for testing packet size
#include "GameNetwork/LANAPICallbacks.h"	// for testing packet size
#include "strtok_r.h"

// UnicodeString is StringBase<WideChar>, and retail inlined its one-line
// forwarders away: the call sites below encode the StringBase<WideChar> bodies
// directly, not the ZH UnicodeString spellings (which resolve to the NARROW
// StringBase<char> bodies).
#include "string_base.h"

// ?set@?$StringBase@G@@QAEXABV1@@Z at 0x00888530
// ?set@UnicodeString@@QAEXABV0@@Z present-unmatched
inline void UnicodeString::set( const UnicodeString &stringSrc )
{
	reinterpret_cast<StringBase<WideChar> &>( *this ).set(
		reinterpret_cast<const StringBase<WideChar> &>( stringSrc ) );
}

// ??0?$StringBase@G@@AAE@ABV0@@Z at 0x00888400 -- private, which is what
// mangles it AAE.
inline UnicodeString::UnicodeString( const UnicodeString &stringSrc )
{
	((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
		*(const StringBase<WideChar> *)&stringSrc );
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


GameInfo *TheGameInfo = NULL;

// GameSlot ----------------------------------------

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/LANGameSlot_copy.cpp
// ??0GameSlot@@ present-unmatched
GameSlot::GameSlot()
{
	reset();
}

// GameSlot::reset is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotCtor.cpp (0x003FF50C).

// GameSlot::saveOffOriginalInfo is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotHumanSaveoff.cpp (0x003FF0D4).

static Int getSlotIndex(const GameSlot *slot)
{
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if (TheGameInfo->getConstSlot(i) == slot)
			return i;
	}
	return -1;
}

static Bool isSlotLocalAlly(const GameSlot *slot)
{
	Int slotIndex = getSlotIndex(slot);
	Int localIndex = TheGameInfo->getLocalSlotNum();
	const GameSlot *localSlot = TheGameInfo->getConstSlot(localIndex);

	// if either doesn't exist, not an ally
	if (slotIndex < 0 || localIndex < 0)
		return FALSE;

	// if slot is us, ally
	if (slotIndex == localIndex)
		return TRUE;

	// if slot is same team as us, ally
	if (slot->getTeamNumber() == localSlot->getTeamNumber() && slot->getTeamNumber() >= 0)
		return TRUE;

	// if we're an observer, we see all
	if (localSlot->getOriginalPlayerTemplate() == PLAYERTEMPLATE_OBSERVER)
		return TRUE;

	// nope
	return FALSE;
}

// GameSlot::getApparentPlayerTemplateDisplayName is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FFBB4).

// GameSlot::getApparentPlayerTemplate is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF813).

// GameSlot::getApparentColor is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF838).

// GameSlot::getApparentStartPos is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF870).


// GameSlot::unAccept is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF895).

// GameSlot::setMapAvailability is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF8A0).

// GameSlot::setState is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotSetState.cpp (0x003FFC28).

// GameSlot::isHuman is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotHumanSaveoff.cpp (0x003FF0F1).

// GameSlot::isOccupied is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoPlayerCounts.cpp (0x003FF0FB).

// GameSlot::isAI is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoPlayerCounts.cpp (0x003FF127).
// ?isPlayer@GameSlot@@ present-unmatched
// Implemented in GameSlotIsPlayerAsciiThunk.cpp to avoid an MSVC 7.1
// overload interaction between naked by-value string methods.

// ?isPlayer@GameSlot@@ present-unmatched
Bool GameSlot::isPlayer( UnsignedInt ip ) const
{
	return (m_state == SLOT_PLAYER && m_IP == ip);
}

// ?isOpen@GameSlot@@QBE_NXZ present-unmatched
Bool GameSlot::isOpen( void ) const
{
	return m_state == SLOT_OPEN;
}

// GameInfo ----------------------------------------

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameInfo_ctor.cpp
// ??0GameInfo@@QAE@XZ present-unmatched
GameInfo::GameInfo()
{
	for (int i=0; i<MAX_SLOTS; ++i)
	{
		m_slot[i] = NULL;
	}
	reset();
}

// init is owned by the BFME2 init recovery; the former unrowed
// donor body here used BFME1 GameInfo/GameSlot layouts.


// GameInfo::reset is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoReset.cpp (0x003FFF8F).

// GameInfo::isPlayerPreorder is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoMarkPreorder.cpp (0x003FF1DA).

// GameInfo::markPlayerAsPreorder is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoMarkPreorder.cpp (0x003FF1FE).


// GameInfo::clearSlotList is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoClearSlotList.cpp (0x003FFDB7).

// GameInfo::getNumPlayers is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoPlayerCounts.cpp (0x003FF218).

// GameInfo::getNumNonObserverPlayers is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoPlayerCounts.cpp (0x003FF23D).

// ?getMaxPlayers@GameInfo@@QBEHXZ present-unmatched
Int GameInfo::getMaxPlayers( void ) const
{
	if (!TheMapCache)
		return -1;

	AsciiString lowerMap = m_mapName;
	lowerMap.toLower();
	MapCache::iterator it = TheMapCache->find(lowerMap);
	if (it == TheMapCache->end())
		return -1;
	MapMetaData data = it->second;
	return data.m_numPlayers;
}

// ?enterGame@GameInfo@@UAEXXZ present-unmatched
void GameInfo::enterGame( void )
{
	DEBUG_ASSERTCRASH(!m_inGame && !m_inProgress, ("Entering game at a bad time!"));
	reset();
	m_inGame = true;
	m_inProgress = false;
}

// ?leaveGame@GameInfo@@UAEXXZ present-unmatched
void GameInfo::leaveGame( void )
{
	DEBUG_ASSERTCRASH(m_inGame && !m_inProgress, ("Leaving game at a bad time!"));
	reset();
}

// ?startGame@GameInfo@@UAEXH@Z present-unmatched
void GameInfo::startGame( Int gameID )
{
	DEBUG_ASSERTCRASH(m_inGame && !m_inProgress, ("Starting game at a bad time!"));
	m_gameID = gameID;
	closeOpenSlots();
	m_inProgress = true;
}

// GameInfo::endGame is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoEndGame.cpp (0x003FF296).

// setSlot is owned by the BFME2 init recovery; the former unrowed
// donor body here used BFME1 GameInfo/GameSlot layouts.


GameSlot* GameInfo::getSlot( Int slotNum )
{
	DEBUG_ASSERTCRASH( slotNum >= 0 && slotNum < MAX_SLOTS, ("GameInfo::getSlot - Invalid slot number"));

	// BFME spells this differently from Zero Hour, and the difference is visible
	// in the image: a null check on the array itself, which the compiler keeps as
	// lea/test even though it can never fire, and && where Zero Hour has ||. With
	// && the guard is unreachable for every slotNum, so out-of-range indices read
	// past the array instead of returning NULL. Reproduced as retail has it.
	if (m_slot == NULL)
		return NULL;

	if (slotNum < 0 && slotNum >= MAX_SLOTS)
		return NULL;

	return m_slot[slotNum];
}

const GameSlot* GameInfo::getConstSlot( Int slotNum ) const
{
	DEBUG_ASSERTCRASH( slotNum >= 0 && slotNum < MAX_SLOTS, ("GameInfo::getSlot - Invalid slot number"));
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return NULL;

	return m_slot[slotNum];
}

// GameInfo::getLocalSlotNum is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF2D6).

// GameInfo::getSlotNum is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoGetSlotNum.cpp (0x0040009A).

// ?amIHost@GameInfo@@UBE_NXZ present-unmatched
Bool GameInfo::amIHost( void ) const
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for game slot while not in game"));
	if (!m_inGame)
		return false;

	return getConstSlot(0)->isPlayer(m_localIP);
}

// GameInfo::setMap is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoSetMap.cpp (0x00400126).

// ?setMapContentsMask@GameInfo@@UAEXH@Z present-unmatched
void GameInfo::setMapContentsMask( Int mask )
{
	m_mapMask = mask;
}

// GameInfo::setMapCRC is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoSetMapCRC.cpp (0x00400E9F).

// GameInfo::setMapSize is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameInfoSetMapSize.cpp (0x00400F5A).

// setSeed is owned by the BFME2 init recovery; the former unrowed
// donor body here used BFME1 GameInfo/GameSlot layouts.


// GameInfo::setSlotPointer is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF332).

// ?setSuperweaponRestriction@GameInfo@@QAEXG@Z present-unmatched
void GameInfo::setSuperweaponRestriction( UnsignedShort restriction )
{
  m_superweaponRestriction = restriction;
}

// ?setStartingCash@GameInfo@@QAEXABVMoney@@@Z present-unmatched
void GameInfo::setStartingCash( const Money & startingCash )
{
  m_startingCash = startingCash;
}

// GameInfo::isColorTaken is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp (0x003FF34A).

Bool GameInfo::isStartPositionTaken(Int positionIdx, Int slotToIgnore ) const
{
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot && slot->getStartPos() == positionIdx && i != slotToIgnore)
			return true;
	}
	return false;
}

void GameInfo::resetAccepted( void )
{
	GameSlot *slot = getSlot(0);
	if (slot)
		slot->setAccept();
	for(int i = 1; i< MAX_SLOTS; i++)
	{
		slot = getSlot(i);
		if (slot)
			slot->unAccept();
	}
}

void GameInfo::resetStartSpots()
{
	GameSlot *slot = NULL;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		slot = getSlot(i);
		if (slot != NULL)
		{
			slot->setStartPos(-1);
		}
	}
}
