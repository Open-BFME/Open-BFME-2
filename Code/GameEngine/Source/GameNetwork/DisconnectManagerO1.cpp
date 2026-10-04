// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/disconnectmanager /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// DisconnectManager bodies ported from Open-BFME-1's
// GameNetwork/DisconnectManager.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// init 0x004D3822 (163B), sendPlayerDestruct 0x004D3AE2 (129B), turnOnScreen
// 0x004D4176 (61B) and playerHasAdvancedAFrame 0x004D3BB5 (34B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

// BFME's vote helpers take the live connection manager, overloads absent from the published ZH header.
#define countVotesForPlayer(slot) countVotesForPlayer(slot); \
	Int countVotesForPlayer(Int, ConnectionManager *); \
	Int getVotesNeededToKick(Int, ConnectionManager *)
#include "GameNetwork/DisconnectManager.h"
#undef countVotesForPlayer

#include "Common/Recorder.h"
#define showPlayerControls(slot) showPlayerControls(slot); \
	void _bfme_showPlayerControls(Int, Bool); \
	Bool _bfme_arePlayerControlsShown(Int); \
	void setPlayerTimeoutTime(Int, Int)
#include "GameClient/DisconnectMenu.h"
#undef showPlayerControls
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetworkInterface.h"
#include "GameNetwork/NetworkUtil.h"
#include "GameNetwork/GameSpy/PingThread.h"
#include "GameNetwork/GameSpy/GSConfig.h"

// BFME adds this connection-state query; the published ZH class declaration does not expose it.
class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);
	Bool isPlayerSlotActive(Int slot);
	void sendDisconnectFrameCommand();
	void resendFrameRangeToPlayer(Int playerID, UnsignedInt startFrame, UnsignedInt endFrame);
};

class BFMEDisconnectManager : public DisconnectManager
{
public:
	Bool hasPingSuccessRatioAtLeast(Real ratio);
};

// BFME keeps the packet-router fallback plan at this address in its expanded
// ConnectionManager.  The published header's member is not layout-compatible
// here, so keep this view private to the reconstructed accessor.
class BFMEConnectionRouterLayout
{
private:
	char m_bfmePad0[0x12030];

public:
	UnsignedInt m_packetRouterFallback[MAX_SLOTS];
};

// BFME's NetworkInterface puts voteForPlayerDisconnect at vtable slot 31.
class BFMENetworkVoteFacade
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void voteForPlayerDisconnect(Int slot);
};


extern Int g_bfmeDisconnectPingResult;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


void DisconnectManager::init() {
	m_lastFrame = 0;
	m_lastFrameTime = -1;
	m_lastKeepAliveSendTime = -1;
	*(Int *)((char *)this + 0x258) = 0;
	m_disconnectState = DISCONNECTSTATETYPE_SCREENOFF;
	m_timeOfDisconnectScreenOn = 0;
	m_pingFrame = 0;

	for (Int i = 0; i < MAX_SLOTS; ++i) {
		for (Int j = 0; j < MAX_SLOTS; ++j) {
			m_playerVotes[i][j].vote = FALSE;
			m_playerVotes[i][j].frame = 0;
		}
		m_disconnectFrames[i] = 0;
		m_disconnectFramesReceived[i] = FALSE;
		((UnsignedShort *)((char *)this + 0x272))[i] = 0;
		((UnsignedByte *)((char *)this + 0x282))[i] = 0;
	}

	*(Int *)((char *)this + 0x26c) = 0;
	m_pingsSent = 0;
	m_pingsRecieved = 0;
	*(UnsignedByte *)((char *)this + 0x270) = 0;
}


// BFME does NOT translate the slot here: it votes, sends and applies against the
// slot it was handed, where the reference copy first maps it through
// untranslatedSlotPosition and uses that everywhere. The vote table itself is at
// DisconnectManager+0x30, eight bytes per entry -- the flag at +0x00 and the
// frame at +0x04.
struct BfmePlayerVote
{
	Bool vote;							///< retail this+0x00
	UnsignedInt frame;						///< retail this+0x04
};

struct BfmeDisconnectVoteTable
{
	char m_unreconstructed_00[0x30];
	BfmePlayerVote m_playerVotes[MAX_SLOTS][MAX_SLOTS];		///< retail this+0x30
};

// Both callees are DEFINED earlier in this TU, so MSVC inlines them here where
// retail emits calls. Declaring them on a view -- declared, never defined --
// keeps the calls, and the aliases name the same ILTs the real spellings carry.
class BfmeDisconnectVoteSender
{
public:
	void sendVoteCommand( Int slot, ConnectionManager *conMgr );	///< retail ILT 0x0002ee79
	void applyDisconnectVote( Int slot, UnsignedInt frame, Int fromSlot,
			ConnectionManager *conMgr );				///< retail ILT 0x000215ad
};

// BFME's vote count takes the connection manager as a second argument where the
// reference declares a one-argument form, and BFME null-checks TheDisconnectMenu
// before touching it -- the reference copy dereferences it unconditionally.
class BfmeVoteCounter
{
public:
	Int countVotesForPlayer( Int slot, ConnectionManager *conMgr );	///< retail ILT 0x00003751
};

// The slot and vote-frame accessors are reached through a view: retail calls
// them out of line off the NetCommandMsg spelling, and getSlot returns a byte.
class BfmeDisconnectVoteMsg
{
public:
	UnsignedInt getVoteFrame( void );					///< retail ILT 0x00013F20
	unsigned char getSlot( void );						///< retail ILT 0x000058B7
	Int getPlayerID( void ) const { return m_playerID; }

	unsigned char m_unreconstructed_00[0x0c];
	Int m_playerID;										///< retail this+0x0C
};

// isPlayerInGame is defined further down this same file, so a direct call would
// bind to that definition; retail goes through the thunk, hence the view.
class BfmeDisconnectRoster
{
public:
	Bool isPlayerInGame( Int slot, ConnectionManager *conMgr );	///< retail ILT 0x0003A648
};


// BFME calls a free function to take the disconnect screen down, not
// TheDisconnectMenu->hideScreen(): retail's call site sets up no `this`, and the
// menu pointer is loaded inside the callee at 0x0050E5A0 instead. Its retail
// name is unknown, so this one is descriptive.
extern void HideDisconnectWindow(void);


// BFME's show-screen helper is called with NO receiver: it loads
// TheDisconnectMenu itself and creates the DisconnectScreen.apt layout
// internally, so the reference's TheDisconnectMenu->showScreen() passes a `this'
// retail does not. BFME also makes no hidePacketRouterTimeout call here at all.
extern void bfmeShowDisconnectScreen(void);				///< retail 0x0050e9a0

struct BfmeDisconnectScreenFields
{
	char m_unreconstructed_00[0x0C];
	Int m_disconnectState;						///< retail this+0x0c
	Int m_lastKeepAliveSendTime;					///< retail this+0x10
	char m_unreconstructed_14[0x258 - 0x14];
	Int m_haveNotifiedOtherPlayersOfCurrentFrame;			///< retail this+0x258
	Int m_timeOfDisconnectScreenOn;					///< retail this+0x25c
};

// ?turnOnScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
void DisconnectManager::turnOnScreen(ConnectionManager *conMgr) {
	BfmeDisconnectScreenFields *self = (BfmeDisconnectScreenFields *)this;

	bfmeShowDisconnectScreen();
	self->m_disconnectState = DISCONNECTSTATETYPE_SCREENON;
	self->m_lastKeepAliveSendTime = -1;
	populateDisconnectScreen(conMgr);
	resetPlayerTimeouts(conMgr);

	self->m_haveNotifiedOtherPlayersOfCurrentFrame = FALSE;

	self->m_timeOfDisconnectScreenOn = timeGetTime();
}


// BFME asks TWO more questions per slot before it will hold that slot to the
// frame check. Both are per-slot predicates on the connection manager that the
// reference class does not declare, and both are shape-only names: one reads the
// state word at conMgr+0x12080 and answers whether it is in range, the other
// answers true immediately for the local slot at conMgr+0x12028. The reference
// copy checks only connected-and-in-game, so it holds slots to the frame check
// that retail excludes.
class BfmeSlotStateConnectionManager
{
public:
	Bool _bfme_slotStateInRange( Int slot );			///< retail ILT 0x000486b2
	Bool _bfme_slotIsLocalOrLive( Int slot );			///< retail ILT 0x0001f136
};

struct BfmeDisconnectFrameFields
{
	char m_unreconstructed_000[0x230];
	Int m_disconnectFrames[MAX_SLOTS];				///< retail this+0x230
	Bool m_disconnectFramesReceived[MAX_SLOTS];			///< retail this+0x250
};


// this function assumes that we are the packet router. (or at least that 
// we will be after everyone is getting disconnected)
// BFME: DESTROYPLAYER enum is 11 (0x0b), not ZH's 8; no setExecutionFrame.
// True body @ 0x66B550 (159B); drift 0x9F2463 is a mislocated neighbor.
void DisconnectManager::sendPlayerDestruct(Int slot, ConnectionManager *conMgr) {
	UnsignedShort currentID = 0;
	if (DoesCommandRequireACommandID((NetCommandType)11))
	{
		currentID = GenerateNextCommandID();
	}

	NetDestroyPlayerCommandMsg *netmsg = newInstance(NetDestroyPlayerCommandMsg);	
	netmsg->setPlayerID(conMgr->getLocalPlayerID());
	netmsg->setID(currentID);
	netmsg->setPlayerIndex(slot);
	conMgr->sendLocalCommandDirect(netmsg, 0xff);
	netmsg->detach();
}


UnsignedInt DisconnectManager::getMaxDisconnectFrame() {
	UnsignedInt retval = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_disconnectFrames[i] > retval) {
			retval = m_disconnectFrames[i];
		}
	}
	return retval;
}


void DisconnectManager::playerHasAdvancedAFrame(Int slot, UnsignedInt frame) {
	// if they have advanced beyond the frame they had been previously disconnecting on.
	if (frame >= m_disconnectFrames[slot]) {
		m_disconnectFrames[slot] = frame; // just in case we get a disconnect frame command after this is called.
		m_disconnectFramesReceived[slot] = FALSE;
	}
}


