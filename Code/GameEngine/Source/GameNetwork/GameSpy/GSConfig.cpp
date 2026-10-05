// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/GameSpy/GSConfig.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// GameSpyConfig::getManglerLocation 0x0054E7EA (66B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: GSConfig.cpp
// Author: Matthew D. Campbell, Sept 2002
// Description: GameSpy online config
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////
// BFME 2's shared AsciiString (out-of-line compare/set/release, as retail
// calls them) instead of the Zero Hour header's inline bodies, so this unit
// emits no private copies of shared-class methods.
#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameState.h"
#include "GameClient/MapUtil.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/RankPointValue.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////

extern GameSpyConfigInterface *TheGameSpyConfig;

class GameSpyConfig : public GameSpyConfigInterface
{
public:
	GameSpyConfig( AsciiString config );
	~GameSpyConfig() {}

	// Pings
	std::list<AsciiString> getPingServers(void)	{ return m_pingServers; }
	Int getNumPingRepetitions(void)							{ return m_pingReps; }
	Int getPingTimeoutInMs(void)								{ return m_pingTimeout; }
	virtual Int getPingCutoffGood( void )				{	return m_pingCutoffGood; }
	virtual Int getPingCutoffBad( void )				{ return m_pingCutoffBad;	}

	// QM
	// Retail505D10 is a string getter, not this list-return reference method.
	std::list<AsciiString> getQMMaps(void)			{ return m_qmMaps; }
	Int getQMBotID(void)												{ return m_qmBotID; }
	Int getQMChannel(void)											{ return m_qmChannel; }
	void setQMChannel(Int channel)							{ m_qmChannel = channel; }

	// Player Info
	Int getPointsForRank(Int rank);
	virtual Bool isPlayerVIP(Int id);
	
	virtual Bool getManglerLocation(Int index, AsciiString& host, UnsignedShort& port);

	// Ladder / Any other external parsing
	AsciiString getLeftoverConfig(void)					{ return m_leftoverConfig; }
	
	// NAT Timeouts
	virtual Int getTimeBetweenRetries() { return m_natRetryInterval; }
	virtual Int getMaxManglerRetries() { return m_natMaxManglerRetries; }
	virtual time_t getRetryInterval() { return m_natManglerRetryInterval; }
	virtual time_t getKeepaliveInterval() { return m_natKeepaliveInterval; }
	virtual time_t getPortTimeout() { return m_natPortTimeout; }
	virtual time_t getRoundTimeout() { return m_natRoundTimeout; }

	// Custom match
	virtual Bool restrictGamesToLobby() { return m_restrictGamesToLobby; }

protected:
	std::list<AsciiString> m_pingServers;
	Int m_pingReps;
	Int m_pingTimeout;
	Int m_pingCutoffGood;
	Int m_pingCutoffBad;

	Int m_natRetryInterval;
	Int m_natMaxManglerRetries;
	time_t m_natManglerRetryInterval;
	time_t m_natKeepaliveInterval;
	time_t m_natPortTimeout;
	time_t m_natRoundTimeout;

	std::vector<AsciiString> m_manglerHosts;
	std::vector<UnsignedShort> m_manglerPorts;

	std::list<AsciiString> m_qmMaps;
	Int m_qmBotID;
	Int m_qmChannel;

	Bool m_restrictGamesToLobby;

	std::set<Int> m_vip; // VIP people

	Int m_rankPoints[MAX_RANKS];

	AsciiString m_leftoverConfig;
};


///////////////////////////////////////////////////////////////////////////////////////

class SectionChecker
{
public:
	typedef std::list<const Bool *> SectionList;
	void addVar(const Bool *var) { m_bools.push_back(var); }
	Bool isInSection();
protected:
	 SectionList m_bools;
};


///////////////////////////////////////////////////////////////////////////////////////

Bool GameSpyConfig::getManglerLocation(Int index, AsciiString& host, UnsignedShort& port)
{
	if (index < 0 || index >= m_manglerHosts.size())
	{
		return FALSE;
	}

	host = m_manglerHosts[index];
	port = m_manglerPorts[index];
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////
