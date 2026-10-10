// cl: /O1 /DBFME_ASCII_DTOR_DECL /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
static __forceinline char configCharAt(const AsciiString &text,int index)
{const char *data=*reinterpret_cast<const char *const *>(&text);return data?data[8+index]:0;}
static __forceinline void configAppendChar(AsciiString &text,char c){((StringBase<char> *)&text)->concat(&c,1);}
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


// Retail 382A6E uses the byte allocator for the VIP tree header. Other
// ledger int-tree bindings use the separate pool provider2F0C32; this
// scoped allocator view keeps the native byte-allocator family distinct.
// Its value remains the donor signed32 VIP identifier.
template<class T> class Rva0054E8DCAllocator : public std::allocator<T>
{
public:
 template<class U> struct rebind {typedef Rva0054E8DCAllocator<U> other;};
 Rva0054E8DCAllocator() throw() {}
 Rva0054E8DCAllocator(const Rva0054E8DCAllocator&) throw() {}
 template<class U> Rva0054E8DCAllocator(const Rva0054E8DCAllocator<U>&) throw() {}
};

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
	std::vector<short> m_manglerPorts;

	std::list<AsciiString> m_qmMaps;
	Int m_qmBotID;
	Int m_qmChannel;

	Bool m_restrictGamesToLobby;

	std::set<Int,std::less<Int>,Rva0054E8DCAllocator<Int> > m_vip; // VIP people

	// BFME 2 has no rank-point table: the constructor (0x0054E8DC) puts the
	// VIP set at +0x58 and the leftover config at +0x64, and create news 0x68.

	AsciiString m_leftoverConfig;
};


///////////////////////////////////////////////////////////////////////////////////////

struct Rva00300489 {virtual AsciiString rva00300489() const;};
struct Rva0054E84C {bool rva0054E84C();};
namespace _STL {template<> _List_base<int,allocator<int> >::~_List_base();}
class SectionChecker
{
public:
	typedef std::list<int> SectionList;
	SectionList::iterator end() {return m_bools.end();}
 __forceinline void addVar(const Bool *var,SectionList::iterator position) { m_bools.insert(position,reinterpret_cast<int>(var)); }
	__forceinline Bool isInSection(){return ((Rva0054E84C *)this)->rva0054E84C();}
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

///////////////////////////////////////////////////////////////////////////////////////
// Retail 0x0054F4AF (89 bytes): Zero Hour's factory unchanged. SetUpGameSpy
// (0x00386F7F) passes the config text by value; the 0x68-byte object is built
// by the GameSpyConfig constructor at 0x0054E8DC (pinned).

GameSpyConfigInterface* GameSpyConfigInterface::create(AsciiString config)
{
	return NEW GameSpyConfig(config);
}

// Constructor recovered from BFME1 donor874e38488 with the target rank-point
// table omitted. Retail54E8DC and its parser calls establish the 0x68 layout
// and signed VIP identifiers. Its byte allocator is proven separately from
// existing pool-based int trees; the scoped type does not assert a retail
// allocator spelling. Existing /O1 and retail insert-layout settings reproduce
// the full2795B body including all calls and string literals.
GameSpyConfig::GameSpyConfig( AsciiString config ) :
m_natRetryInterval(1000),
m_natMaxManglerRetries(25),
m_natManglerRetryInterval(300),
m_natKeepaliveInterval(15000),
m_natPortTimeout(10000),
m_natRoundTimeout(10000),
m_pingReps(1),
m_pingTimeout(1000),
m_pingCutoffGood(300),
m_pingCutoffBad(600),
m_restrictGamesToLobby(FALSE),
m_qmBotID(0),
m_qmChannel(0)
{

	AsciiString line;
	Bool inPingServers = FALSE;
	Bool inPingDuration = FALSE;
	Bool inQMMaps = FALSE;
	Bool inQMBot = FALSE;
	Bool inManglers = FALSE;
	Bool inVIP = FALSE;
	Bool inNAT = FALSE;
	Bool inCustom = FALSE;

	SectionChecker sections;
 SectionChecker::SectionList::iterator sectionEnd=sections.end();
	sections.addVar(&inPingServers,sectionEnd);
	sections.addVar(&inPingDuration,sectionEnd);
	sections.addVar(&inQMMaps,sectionEnd);
	sections.addVar(&inQMBot,sectionEnd);
	sections.addVar(&inManglers,sectionEnd);
	sections.addVar(&inVIP,sectionEnd);
	sections.addVar(&inNAT,sectionEnd);
	sections.addVar(&inCustom,sectionEnd);

	while (config.nextToken(&line, "\n"))
	{
		if (configCharAt(line,line.getLength()-1) == '\r')
			line.removeLastChar();	// there is a trailing '\r'

		line.trim();

		if (line.isEmpty())
			continue;

		if (!sections.isInSection() && line.compare("<PingServers>") == 0)
		{
			inPingServers = TRUE;
		}
		else if (inPingServers && line.compare("</PingServers>") == 0)
		{
			inPingServers = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<PingDuration>") == 0)
		{
			inPingDuration = TRUE;
		}
		else if (inPingDuration && line.compare("</PingDuration>") == 0)
		{
			inPingDuration = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<QMMaps>") == 0)
		{
			inQMMaps = TRUE;
		}
		else if (inQMMaps && line.compare("</QMMaps>") == 0)
		{
			inQMMaps = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<Manglers>") == 0)
		{
			inManglers = TRUE;
		}
		else if (inManglers && line.compare("</Manglers>") == 0)
		{
			inManglers = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<QMBot>") == 0)
		{
			inQMBot = TRUE;
		}
		else if (inQMBot && line.compare("</QMBot>") == 0)
		{
			inQMBot = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<VIP>") == 0)
		{
			inVIP = TRUE;
		}
		else if (inVIP && line.compare("</VIP>") == 0)
		{
			inVIP = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<NAT>") == 0)
		{
			inNAT = TRUE;
		}
		else if (inNAT && line.compare("</NAT>") == 0)
		{
			inNAT = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<Custom>") == 0)
		{
			inCustom = TRUE;
		}
		else if (inCustom && line.compare("</Custom>") == 0)
		{
			inCustom = FALSE;
		}
		else if (inVIP)
		{
			line.toLower();
			if (line.getLength())
			{
				Int val = atoi(line.str());
				if (val > 0)
					m_vip.insert(val);
			}
		}
		else if (inPingServers)
		{
			line.toLower();
			m_pingServers.push_back(line);
		}
		else if (inPingDuration)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " ="))
			{
				if (key.compare("reps") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingReps = atoi(val.str());
					}
				}
				else if (key.compare("timeout") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingTimeout = atoi(val.str());
					}
				}
				else if (key.compare("low") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingCutoffGood = atoi(val.str());
					}
				}
				else if (key.compare("med") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingCutoffBad = atoi(val.str());
					}
				}
			}
		}
		else if (inManglers)
		{
			line.trim();
			line.toLower();
			AsciiString hostStr;
			AsciiString portStr;
			line.nextToken(&hostStr, ":");
			line.nextToken(&portStr, ":\n\r");
			if (!hostStr.isEmpty() && !portStr.isEmpty())
			{
				m_manglerHosts.push_back(hostStr);
				m_manglerPorts.push_back(atoi(portStr.str()));
			}
		}
		else if (inQMMaps)
		{
			line.toLower();
			AsciiString mapName;
			mapName.format("%s\\%s\\%s.map", ((const Rva00300489 *)TheMapCache)->Rva00300489::rva00300489().str(), line.str(), line.str());
			mapName = TheGameState->portableMapPathToRealMapPath(TheGameState->realMapPathToPortableMapPath(mapName));
			mapName.toLower();

			const MapMetaData *md = TheMapCache->findMap(mapName);
			if (md)
			{
				m_qmMaps.push_back(mapName);
			}
		}
		else if (inQMBot)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " ="))
			{
				if (key.compare("id") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_qmBotID = atoi(val.str());
					}
				}
			}
		}
		else if (inNAT)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " ="))
			{
				if (key.compare("retryinterval") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natRetryInterval = atoi(val.str());
					}
				}
				else if (key.compare("manglerretries") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natMaxManglerRetries = atoi(val.str());
					}
				}
				else if (key.compare("manglerinterval") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natManglerRetryInterval = atoi(val.str());
					}
				}
				else if (key.compare("keepaliveinterval") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natKeepaliveInterval = atoi(val.str());
					}
				}
				else if (key.compare("porttimeout") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natPortTimeout = atoi(val.str());
					}
				}
				else if (key.compare("roundtimeout") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natRoundTimeout = atoi(val.str());
					}
				}
				else
				{
					DEBUG_LOG(("Unknown key '%s' = '%s' in NAT block of GameSpy Config\n", key.str(), val.str()));
				}
			}
			else
			{
				DEBUG_LOG(("Key '%s' missing val in NAT block of GameSpy Config\n", key.str()));
			}
		}
		else if (inCustom)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " =") && line.nextToken(&val, " ="))
			{
				if (key.compare("restricted") == 0)
				{
					m_restrictGamesToLobby = atoi(val.str());
				}
				else
				{
					DEBUG_LOG(("Unknown key '%s' = '%s' in Custom block of GameSpy Config\n", key.str(), val.str()));
				}
			}
			else
			{
				DEBUG_LOG(("Key '%s' missing val in Custom block of GameSpy Config\n", key.str()));
			}
		}
		else
		{
			m_leftoverConfig.concat(line);
			configAppendChar(m_leftoverConfig,'\n');
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////

