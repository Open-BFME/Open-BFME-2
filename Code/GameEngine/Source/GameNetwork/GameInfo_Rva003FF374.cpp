// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/gameinfo -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
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

// ?reset@GameSlot@@UAEXXZ present-unmatched
void GameSlot::reset()
{
	m_state = SLOT_CLOSED; // decent default
	m_isAccepted = false;
	m_hasMap = true;
	m_color = -1;
	m_startPos = -1;
	m_playerTemplate = -1;
	m_teamNumber = -1;
	m_connectInfo.m_nat = FirewallHelperClass::FIREWALL_TYPE_SIMPLE;
	m_lastFrameInGame = 0;
	m_disconnected = FALSE;
	m_connectInfo.m_port = 0;
	m_isMuted = FALSE;
	m_origPlayerTemplate = -1;
	m_origStartPos = -1;
	m_origColor = -1;
}

void GameSlot::saveOffOriginalInfo( void )
{
	DEBUG_LOG(("GameSlot::saveOffOriginalInfo() - orig was color=%d, pos=%d, house=%d\n",
		m_origColor, m_origStartPos, m_origPlayerTemplate));
	m_origPlayerTemplate = m_playerTemplate;
	m_origStartPos = m_startPos;
	m_origColor = m_color;
	DEBUG_LOG(("GameSlot::saveOffOriginalInfo() - color=%d, pos=%d, house=%d\n",
		m_color, m_startPos, m_playerTemplate));
}

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

UnicodeString GameSlot::getApparentPlayerTemplateDisplayName( void ) const
{
	if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomPlayerTemplate() &&
		m_origPlayerTemplate == PLAYERTEMPLATE_RANDOM && !isSlotLocalAlly(this))
	{
		return TheGameText->fetch("GUI:Random");
	}
	else if (m_origPlayerTemplate == PLAYERTEMPLATE_OBSERVER)
	{
		return TheGameText->fetch("GUI:Observer");
	}
	DEBUG_LOG(("Fetching player template display name for player template %d (orig is %d)\n",
		m_playerTemplate, m_origPlayerTemplate));
	if (m_playerTemplate < 0)
	{
		return TheGameText->fetch("GUI:Random");
	}
	return ThePlayerTemplateStore->getNthPlayerTemplate(m_playerTemplate)->getDisplayName();
}

Int GameSlot::getApparentPlayerTemplate( void ) const
{
	if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomPlayerTemplate() &&
		!isSlotLocalAlly(this))
	{
		return m_origPlayerTemplate;
	}
	return m_playerTemplate;
}

Int GameSlot::getApparentColor( void ) const
{
	if (TheMultiplayerSettings && m_origPlayerTemplate == PLAYERTEMPLATE_OBSERVER)
		return TheMultiplayerSettings->getColor(PLAYERTEMPLATE_OBSERVER)->getColor();

	if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomColor() &&
		!isSlotLocalAlly(this))
	{
		return m_origColor;
	}
	return m_color;
}

Int GameSlot::getApparentStartPos( void ) const
{
	if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomStartPos() &&
		!isSlotLocalAlly(this))
	{
		return m_origStartPos;
	}
	return m_startPos;
}


void GameSlot::unAccept( void )
{
	if (isHuman())
	{
		m_isAccepted = false;
	}
}

void GameSlot::setMapAvailability( Bool hasMap )
{
	if (isHuman())
	{
		m_hasMap = hasMap;
	}
}

void GameSlot::setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo )
{
	if (!(isAI() &&  (state == SLOT_EASY_AI || state == SLOT_MED_AI || state == SLOT_BRUTAL_AI)))
	{
		m_color = -1;
		m_startPos = -1;
		m_playerTemplate = -1;
		m_teamNumber = -1;

		if (state == SLOT_OPEN && TheGameSpyGame && TheGameSpyGame->getConstSlot(0) == this)
		{
			DEBUG_CRASH(("Game Is Hosed!\n"));
		}
	}
	if (state == SLOT_PLAYER)
	{
		reset();
		m_state = state;
		m_name = name;
	}// state == SLOT_PLAYER
	else
	{
		m_state = state;
		m_isAccepted = true;
		m_hasMap = true;
		switch(state)
		{
		case SLOT_OPEN:
			m_name = TheGameText->fetch("GUI:Open");
			break;
		case SLOT_EASY_AI:
			m_name = TheGameText->fetch("GUI:EasyAI");
			break;
		case SLOT_MED_AI:
			m_name = TheGameText->fetch("GUI:MediumAI");
			break;
		case SLOT_BRUTAL_AI:
			m_name = TheGameText->fetch("GUI:HardAI");
			break;
		case SLOT_CLOSED:
		default:
			m_name = TheGameText->fetch("GUI:Closed");
			break;
		}
	}

	m_connectInfo = *connectInfo;
}

// Various tests
Bool GameSlot::isHuman( void ) const
{
	return m_state == SLOT_PLAYER;
}

Bool GameSlot::isOccupied( void ) const
{
	return m_state == SLOT_PLAYER || m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI || m_state == SLOT_BRUTAL_AI;
}

Bool GameSlot::isAI( void ) const
{
	return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI || m_state == SLOT_BRUTAL_AI;
}
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

// ?init@GameInfo@@QAEXXZ present-unmatched
void GameInfo::init( void )
{
	reset();
}

// byte-exact reconstruction: game/GameEngine/Source/Common/GameInfo_resetMethodThunk.cpp
// ?reset@GameInfo@@UAEXXZ present-unmatched
void GameInfo::reset( void )
{
	m_crcInterval = NET_CRC_INTERVAL;
	m_inGame = false;
	m_inProgress = false;
	m_gameID = 0;
	m_mapName = AsciiString("NOMAP");
	m_mapMask = 0;
	m_seed = GetTickCount(); //GameClientRandomValue(0, INT_MAX - 1);
	m_useStats = TRUE;
	m_surrendered = FALSE;
  m_oldFactionsOnly = FALSE;
	// Added By Sadullah Nader
	// Initializations missing and needed
//	m_localIP = 0; // BGC - actually we don't want this to be reset since the m_localIP is 
										// set properly in the constructor of LANGameInfo which uses this as a base class.
	m_mapCRC = 0;
	m_mapSize = 0;
  m_superweaponRestriction = 0; 
  m_startingCash = TheGlobalData->m_defaultStartingCash;
  
	//

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if (m_slot[i])
			m_slot[i]->reset();
	}

	m_preorderMask = 0;
}

Bool GameInfo::isPlayerPreorder(Int index)
{
	if (index >= 0 && index < MAX_SLOTS)
		return ((m_preorderMask & (1 << index)) != 0);
	return FALSE;
}

void GameInfo::markPlayerAsPreorder(Int index)
{
	if (index >= 0 && index < MAX_SLOTS)
		m_preorderMask |= 1 << index;
}


// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameInfo_clearSlotList_Thunk.cpp
// ?clearSlotList@GameInfo@@QAEXXZ present-unmatched
void GameInfo::clearSlotList( void )
{
	for (int i=0; i<MAX_SLOTS; ++i)
	{
		if (m_slot[i])
			m_slot[i]->setState(SLOT_CLOSED);
	}
}

Int GameInfo::getNumPlayers( void ) const
{
	Int numPlayers = 0;
	for (int i=0; i<MAX_SLOTS; ++i)
	{
		if (m_slot[i] && m_slot[i]->isOccupied())
			numPlayers++;
	}
	return numPlayers;
}

Int GameInfo::getNumNonObserverPlayers( void ) const
{
	Int numPlayers = 0;
	for (int i=0; i<MAX_SLOTS; ++i)
	{
		if (m_slot[i] && m_slot[i]->isOccupied() && m_slot[i]->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
			numPlayers++;
	}
	return numPlayers;
}

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

void GameInfo::endGame( void )
{
	DEBUG_ASSERTCRASH(m_inGame && m_inProgress, ("Ending game without playing one!"));
	m_inGame = false;
	m_inProgress = false;
}

// ?setSlot@GameInfo@@UAEXHAVE-GameSlot@@@Z present-unmatched
void GameInfo::setSlot( Int slotNum, GameSlot slotInfo )
{
	DEBUG_ASSERTCRASH( slotNum >= 0 && slotNum < MAX_SLOTS, ("GameInfo::setSlot - Invalid slot number"));
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return;

	DEBUG_ASSERTCRASH( m_slot[slotNum], ("NULL slot pointer"));
	if (!m_slot[slotNum])
		return;

//	Bool isHuman = slotInfo.isHuman();
//	Bool wasHuman = m_slot[slotNum]->isHuman();

	if (slotNum == 0)
	{
		slotInfo.setAccept();
		slotInfo.setMapAvailability(true);
	}
	*m_slot[slotNum] = slotInfo;

#ifdef DEBUG_LOGGING
	UnsignedInt ip = slotInfo.getIP();
#endif

	DEBUG_LOG(("GameInfo::setSlot - setting slot %d to be player %ls with IP %d.%d.%d.%d\n", slotNum, slotInfo.getName().str(),
							ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff));
}

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

// ?getLocalSlotNum@GameInfo@@UBEHXZ present-unmatched
Int GameInfo::getLocalSlotNum( void ) const
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for local game slot while not in game"));
	if (!m_inGame)
		return -1;

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot == NULL) {
			continue;
		}
		if (slot->isPlayer(m_localIP))
			return i;
	}
	return -1;
}

// byte-exact reconstruction: game/GameEngine/Source/Common/GameInfo_getSlotNum_Thunk.cpp
// ?getSlotNum@GameInfo@@QBEHVAsciiString@@@Z present-unmatched
Int GameInfo::getSlotNum( AsciiString userName ) const
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for game slot while not in game"));
	if (!m_inGame)
		return -1;

	UnicodeString uName;
	uName.translate(userName);
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot->isPlayer( uName ))
			return i;
	}
	return -1;
}

// ?amIHost@GameInfo@@UBE_NXZ present-unmatched
Bool GameInfo::amIHost( void ) const
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for game slot while not in game"));
	if (!m_inGame)
		return false;

	return getConstSlot(0)->isPlayer(m_localIP);
}

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameInfoSetMapThunk.cpp
// ?setMap@GameInfo@@QAEXVAsciiString@@@Z present-unmatched
void GameInfo::setMap( AsciiString mapName )
{
	m_mapName = mapName;
	if (m_inGame && amIHost())
	{
		const MapMetaData *mapData = TheMapCache->findMap( mapName );
		if (mapData)
		{
			m_mapMask = 1;
			AsciiString path = mapName;
			path.removeLastChar();
			path.removeLastChar();
			path.removeLastChar();
			path.concat("tga");
			DEBUG_LOG(("GameInfo::setMap() - Looking for '%s'\n", path.str()));
			File *fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 2;
				fp->close();
				fp = NULL;
			}

			AsciiString newMapName;
			if (mapName.getLength() > 0)
			{
				AsciiString token;
				mapName.nextToken(&token, "\\/");
				// add all the tokens except the last one.
				// that way we don't add the filename, just the
				// directory name, we can do this since the filename
				// is just the directory name with the file extention
				// added onto it.
				while (mapName.find('\\') != NULL)
				{
					if (newMapName.getLength() > 0)
					{
						newMapName.concat('/');
					}
					newMapName.concat(token);
					mapName.nextToken(&token, "\\/");
				}
			}
			newMapName.concat("/map.ini");
			DEBUG_LOG(("GameInfo::setMap() - Looking for '%s'\n", newMapName.str()));
			fp = TheFileSystem->openFile(newMapName.str());
			if (fp)
			{
				m_mapMask |= 4;
				fp->close();
				fp = NULL;
			}

			path = GetStrFileFromMap(m_mapName);
			DEBUG_LOG(("GameInfo::setMap() - Looking for '%s'\n", path.str()));
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 8;
				fp->close();
				fp = NULL;
			}

			path = GetSoloINIFromMap(m_mapName);
			DEBUG_LOG(("GameInfo::setMap() - Looking for '%s'\n", path.str()));
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 16;
				fp->close();
				fp = NULL;
			}

			path = GetAssetUsageFromMap(m_mapName);
			DEBUG_LOG(("GameInfo::setMap() - Looking for '%s'\n", path.str()));
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 32;
				fp->close();
				fp = NULL;
			}

			path = GetReadmeFromMap(m_mapName);
			DEBUG_LOG(("GameInfo::setMap() - Looking for '%s'\n", path.str()));
			fp = TheFileSystem->openFile(path.str());
			if (fp)
			{
				m_mapMask |= 64;
				fp->close();
				fp = NULL;
			}
		}
		else
		{
			m_mapMask = 0;
		}
	}
}

// ?setMapContentsMask@GameInfo@@UAEXH@Z present-unmatched
void GameInfo::setMapContentsMask( Int mask )
{
	m_mapMask = mask;
}

// ?setMapCRC@GameInfo@@QAEXI@Z present-unmatched
void GameInfo::setMapCRC( UnsignedInt mapCRC )
{
	m_mapCRC = mapCRC;
	if (!TheMapCache)
		return;

	// check the map cache
	if (m_inGame && getLocalSlotNum() >= 0)
	{
		//TheMapCache->updateCache();
		AsciiString lowerMap = m_mapName;
		lowerMap.toLower();
		//DEBUG_LOG(("GameInfo::setMapCRC - looking for map file \"%s\" in the map cache\n", lowerMap.str()));
		std::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it == TheMapCache->end())
		{
			/*
			DEBUG_LOG(("GameInfo::setMapCRC - could not find map file.\n"));
			it = TheMapCache->begin();
			while (it != TheMapCache->end())
			{
				DEBUG_LOG(("\t\"%s\"\n", it->first.str()));
				++it;
			}
			*/
			getSlot(getLocalSlotNum())->setMapAvailability(false);
		}
		else if (m_mapCRC != it->second.m_CRC)
		{
			DEBUG_LOG(("GameInfo::setMapCRC - map CRC's do not match (%X/%X).\n", m_mapCRC, it->second.m_CRC));
			getSlot(getLocalSlotNum())->setMapAvailability(false);
		}
		else
		{
			//DEBUG_LOG(("GameInfo::setMapCRC - map CRC's match.\n"));
			getSlot(getLocalSlotNum())->setMapAvailability(true);
		}
	}
}

// ?setMapSize@GameInfo@@QAEXI@Z present-unmatched
void GameInfo::setMapSize( UnsignedInt mapSize )
{
	m_mapSize = mapSize;
	if (!TheMapCache)
		return;

	// check the map cache
	if (m_inGame && getLocalSlotNum() >= 0)
	{
		//TheMapCache->updateCache();
		AsciiString lowerMap = m_mapName;
		lowerMap.toLower();
		std::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it == TheMapCache->end())
		{
			DEBUG_LOG(("GameInfo::setMapSize - could not find map file.\n"));
			getSlot(getLocalSlotNum())->setMapAvailability(false);
		}
		else if (m_mapCRC != it->second.m_CRC)
		{
			DEBUG_LOG(("GameInfo::setMapSize - map CRC's do not match.\n"));
			getSlot(getLocalSlotNum())->setMapAvailability(false);
		}
		else
		{
			//DEBUG_LOG(("GameInfo::setMapSize - map CRC's match.\n"));
			getSlot(getLocalSlotNum())->setMapAvailability(true);
		}
	}
}

// ?setSeed@GameInfo@@UAEXH@Z present-unmatched
void GameInfo::setSeed( Int seed )
{
	m_seed = seed;
}

// ?setSlotPointer@GameInfo@@UAEXHPAVGameSlot@@@Z present-unmatched
void GameInfo::setSlotPointer( Int index, GameSlot *slot )
{
	if (index < 0 || index >= MAX_SLOTS)
		return;

	m_slot[index] = slot;
}

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

Bool GameInfo::isColorTaken(Int colorIdx, Int slotToIgnore ) const
{
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot && slot->getColor() == colorIdx && i != slotToIgnore)
			return true;
	}
	return false;
}

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
