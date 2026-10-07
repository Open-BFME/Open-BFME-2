// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/disconnectmanager /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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


// BFME 2's NetDisconnectPlayerCommandMsg is four bytes longer than Zero
// Hour's: the ZH declaration is renamed out of the way while the headers are
// read and the BFME 2 layout is declared after them (see below).
#define NetDisconnectPlayerCommandMsg NetDisconnectPlayerCommandMsgZH
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

#undef NetDisconnectPlayerCommandMsg

// BFME 2 layout of NetDisconnectPlayerCommandMsg. Target facts:
// sendDisconnectCommand (0x004D3D5C) allocates it with `push 0x28`; its
// constructor (0x004D57F1) writes the command type 0x1A at +0x14, clears the
// slot byte at +0x1C and the frame dword at +0x24; setDisconnectSlot
// (0x0006EDE3, folded) stores a byte at +0x1C and setDisconnectFrame
// (0x005739F6, folded) a dword at +0x24. Zero Hour packs the frame directly
// after the slot at +0x20, so BFME 2 holds a further dword at +0x20 that none
// of these touch; its meaning is unknown.
class NetDisconnectPlayerCommandMsg : public NetCommandMsg
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(NetDisconnectPlayerCommandMsg, "NetDisconnectPlayerCommandMsg")
public:
	NetDisconnectPlayerCommandMsg();

	UnsignedByte getDisconnectSlot();
	void setDisconnectSlot(UnsignedByte slot);

	UnsignedInt getDisconnectFrame();
	void setDisconnectFrame(UnsignedInt frame);

protected:
	UnsignedByte m_disconnectSlot;		// +0x1C
	UnsignedInt m_unknown20;			// +0x20, not touched by the constructor
	UnsignedInt m_disconnectFrame;		// +0x24
};

// BFME adds this connection-state query; the published ZH class declaration does not expose it.
class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);
	Int isPlayerSlotActive(Int slot);
	UnsignedByte rva004CEF58(Int slot);
	void sendDisconnectFrameCommand();
	void resendFrameRangeToPlayer(Int playerID, UnsignedInt startFrame, UnsignedInt endFrame);
};

class BFMEDisconnectManager : public DisconnectManager
{
public:
	Bool hasPingSuccessRatioAtLeast(Real ratio);
	Bool hasPlayerConnectionTimedOut(Int slot, void *connectionManager);
	Int rva004D3E5D(ConnectionManager *conMgr);
	Int rva004D3E93(Int slot, ConnectionManager *conMgr);
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

// Zero Hour's translatedSlotPosition / untranslatedSlotPosition. BFME 2 calls
// both with no `this` and cleans their two stack arguments itself (cdecl), so
// they are free functions here under their ledger names. They must be DEFINED
// in this unit: MSVC 7.1 /O1 cleans a call to a cdecl function it has only
// declared with `pop ecx` twice, but with `add esp,8` once it has seen the
// body, and every retail call to 0x004D39DE / 0x004D39F0 uses `add esp,8`.
int Rva004D39DEGet(int a, int b)
{
	return (a < b) ? a : ((a == b) ? -1 : a - 1);
}

int rva0066b3e0(int a, int b)
{
	if (a == -1)
		return b;
	if (a >= b)
		a++;
	return a;
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


// BFME 2 keeps the disconnect notify time at GlobalData+0xC24 (retail
// 0x004D3AB2 reads it there); the member name is carried from Open-BFME-1's
// hasPlayerTimedOut, the ZH header's offset is not BFME 2's.
struct BfmeDisconnectTimeoutGlobals
{
	char m_unreconstructed_000[0xC24];
	UnsignedInt m_networkDisconnectScreenNotifyTime;	///< retail TheWritableGlobalData+0xc24
};

Bool DisconnectManager::hasPlayerTimedOut(Int slot) {
	if (slot == -1) {
		return FALSE;
	}

	if (((const BfmeDisconnectTimeoutGlobals *)TheGlobalData)->m_networkDisconnectScreenNotifyTime
		<= (timeGetTime() - m_playerTimeouts[slot])) {
		return TRUE;
	}
	return FALSE;
}


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


void DisconnectManager::sendDisconnectCommand(Int slot, ConnectionManager *conMgr) {
	DEBUG_LOG(("DisconnectManager::sendDisconnectCommand - Sending disconnect command for slot number %d\n", slot));
	DEBUG_ASSERTCRASH((slot >= 0) && (slot < MAX_SLOTS), ("Attempting to send a disconnect command for an invalid slot number"));
	if ((slot < 0) || (slot >= (MAX_SLOTS))) {
		return;
	}

	UnsignedInt disconnectFrame = getMaxDisconnectFrame();

	// Need to do the NetDisconnectPlayerCommandMsg creation and sending here.
	NetDisconnectPlayerCommandMsg *msg = newInstance(NetDisconnectPlayerCommandMsg);
	msg->setDisconnectSlot(slot);
	msg->setDisconnectFrame(disconnectFrame);
	msg->setPlayerID(conMgr->getLocalPlayerID());
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}

	conMgr->sendLocalCommand(msg);

	DEBUG_LOG(("DisconnectManager::sendDisconnectCommand - Sending disconnect command for slot number %d for frame %d\n", slot, disconnectFrame));

	msg->detach();
}


void DisconnectManager::playerHasAdvancedAFrame(Int slot, UnsignedInt frame) {
	// if they have advanced beyond the frame they had been previously disconnecting on.
	if (frame >= m_disconnectFrames[slot]) {
		m_disconnectFrames[slot] = frame; // just in case we get a disconnect frame command after this is called.
		m_disconnectFramesReceived[slot] = FALSE;
	}
}

// Target evidence: ConnectionManager's 0x004CF90D forwards (slot, this) here;
// the target indexes the vote table at DisconnectManager+0x30 with 8-byte
// entries and uses the incoming slot directly. The BFME1 donor below provides
// the method's purpose and call order, while target bytes establish BFME2's
// direct-slot behavior in place of untranslatedSlotPosition. The target reads
// the GameLogic frame at +0x40; the BFME1 inline getter reads +0x3C.
// Donor: Open-BFME-1 GameNetwork/DisconnectManager.cpp::voteForPlayerDisconnect.
// Its source is unchanged between checkout 6583b3c1 and fetched official master
// 31950178; the donor structure is guidance and is not treated as target proof.
void DisconnectManager::voteForPlayerDisconnect(Int slot, ConnectionManager *conMgr) {
	if (m_playerVotes[slot][conMgr->getLocalPlayerID()].vote == FALSE) {
		m_playerVotes[slot][conMgr->getLocalPlayerID()].vote = TRUE;
		sendVoteCommand(slot, conMgr);
		applyDisconnectVote(slot,
			reinterpret_cast<GameLogic *>(reinterpret_cast<char *>(TheGameLogic) + 4)->getFrame(),
			conMgr->getLocalPlayerID(), conMgr);
	}
}

// ?countVotesForPlayer@DisconnectManager@@IAEHHPAVConnectionManager@@@Z @ 0x004D3BD7 (91B). Counts voting slots for a player: vote table at +0x30 rows of 8 entries stepped by 8 with flag at +0; skips timed-out and active slots.
// Evidence: callees hasPlayerConnectionTimedOut 0x004D3B7E isPlayerSlotActive 0x004CF0CD rowed; vote table BfmeDisconnectVoteTable; callers 4 unclaimed; unlocks 4.
Int DisconnectManager::countVotesForPlayer(Int slot, ConnectionManager *conMgr) {
	if (slot < 0 || slot >= MAX_SLOTS)
		return 0;
	Int count = 0;
	BfmeDisconnectVoteTable *votes = (BfmeDisconnectVoteTable *)this;
	BFMEDisconnectManager *self = (BFMEDisconnectManager *)this;
	BFMEConnectionManager *bfmeMgr = (BFMEConnectionManager *)conMgr;
	for (Int voter = 0; voter < MAX_SLOTS; ++voter) {
		if (votes->m_playerVotes[slot][voter].vote == TRUE) {
			if (self->hasPlayerConnectionTimedOut(voter, conMgr))
				continue;
			if ((unsigned char)bfmeMgr->isPlayerSlotActive(voter) != 0)
				continue;
			++count;
		}
	}
	return count;
}

// ?rva004D3E93@BFMEDisconnectManager@@QAEHHPAVConnectionManager@@@Z @ 0x004D3E93 (60B). Counts eligible voter slots excluding one.
// Evidence: callees hasPlayerConnectionTimedOut 0x004D3B7E isPlayerInGame 0x004CF0A6 rowed; caller 1 unclaimed; unlocks 1.
// ?rva004D3E5D@BFMEDisconnectManager@@QAEHPAVConnectionManager@@@Z @ 0x004D3E5D (54B).
// Target bytes scan all eight slots, skip those reported timed out by rowed
// hasPlayerConnectionTimedOut (0x004D3B7E), then count those for which rowed
// isPlayerInGame (0x004CF0A6) returns false. The adjacent 0x004D3E93 method
// performs the same walk while excluding one slot. This address-derived
// method label records the call and loop evidence without naming its purpose.
Int BFMEDisconnectManager::rva004D3E5D(ConnectionManager *conMgr) {
	Int count = 0;
	BFMEConnectionManager *bfmeMgr = (BFMEConnectionManager *)conMgr;
	for (Int slot = 0; slot < MAX_SLOTS; ++slot) {
		if (hasPlayerConnectionTimedOut(slot, conMgr))
			continue;
		if (bfmeMgr->isPlayerInGame(slot))
			continue;
		++count;
	}
	return count;
}

Int BFMEDisconnectManager::rva004D3E93(Int excludedSlot, ConnectionManager *conMgr) {
	Int count = 0;
	BFMEConnectionManager *bfmeMgr = (BFMEConnectionManager *)conMgr;
	for (Int slot = 0; slot < MAX_SLOTS; ++slot) {
		if (slot == excludedSlot)
			continue;
		if (hasPlayerConnectionTimedOut(slot, conMgr))
			continue;
		if (bfmeMgr->isPlayerInGame(slot))
			continue;
		++count;
	}
	return count;
}

// Open-BFME-1's isPlayerVotedOut: a slot of -1 is never voted out; otherwise
// the untranslated slot's vote count (0x004D3BD7) is compared against the
// count rva004D3E93 returns for it, which stands where the donor asks
// getVotesNeededToKick. Retail isPlayerInGame (0x004D3F1B) calls this between
// its connection and timeout tests, the donor's order.
Bool DisconnectManager::isPlayerVotedOut(Int slot, ConnectionManager *conMgr) {
	if (slot == -1) {
		return FALSE;
	}
	Int transSlot = rva0066b3e0(slot, conMgr->getLocalPlayerID());
	Int numVotes = countVotesForPlayer(transSlot, conMgr);
	if (numVotes >= ((BFMEDisconnectManager *)this)->rva004D3E93(transSlot, conMgr)) {
		return TRUE;
	}
	return FALSE;
}

Bool DisconnectManager::isPlayerInGame(Int slot, ConnectionManager *conMgr) {
	Int transSlot = rva0066b3e0(slot, conMgr->getLocalPlayerID());
	if ((transSlot < 0) || (transSlot >= MAX_SLOTS) || (conMgr->isPlayerConnected(transSlot) == FALSE)) {
		return FALSE;
	}

	if (isPlayerVotedOut(slot, conMgr) == TRUE) {
		return FALSE;
	}

	if (hasPlayerTimedOut(slot) == TRUE) {
		return FALSE;
	}

	return TRUE;
}

// Open-BFME-1's allOnSameFrame. BFME 2 skips slots the connection manager
// reports active through isPlayerSlotActive and requires its 0x004CEF58
// test to pass before a slot's disconnect frame is compared.
Bool DisconnectManager::allOnSameFrame(ConnectionManager *conMgr) {
	BfmeDisconnectFrameFields *self = (BfmeDisconnectFrameFields *)this;
	BFMEConnectionManager *bfmeMgr = (BFMEConnectionManager *)conMgr;
	Bool retval = TRUE;
	for (Int i = 0; (i < MAX_SLOTS) && (retval == TRUE); ++i) {
		Int transSlot = Rva004D39DEGet(i, conMgr->getLocalPlayerID());
		if (transSlot == -1) {
			continue;
		}
		if ((conMgr->isPlayerConnected(i) == TRUE) && (isPlayerInGame(transSlot, conMgr) == TRUE)
			&& ((UnsignedByte)bfmeMgr->isPlayerSlotActive(i) == FALSE) && bfmeMgr->rva004CEF58(i)) {
			if (self->m_disconnectFramesReceived[i] == FALSE) {
				retval = FALSE;
			}
			if ((self->m_disconnectFramesReceived[i] == TRUE)
				&& (self->m_disconnectFrames[conMgr->getLocalPlayerID()] != self->m_disconnectFrames[i])) {
				retval = FALSE;
			}
		}
	}
	return retval;
}

// Open-BFME-1's applyDisconnectVote: record the vote, recount, and refresh
// the disconnect menu's count for the translated slot when the menu exists.
void DisconnectManager::applyDisconnectVote(Int slot, UnsignedInt frame, Int fromSlot, ConnectionManager *conMgr) {
	m_playerVotes[slot][fromSlot].vote = TRUE;
	m_playerVotes[slot][fromSlot].frame = frame;
	Int numVotes = countVotesForPlayer(slot, conMgr);
	Int transSlot = Rva004D39DEGet(slot, conMgr->getLocalPlayerID());
	if (transSlot != -1 && TheDisconnectMenu) {
		TheDisconnectMenu->updateVotes(transSlot, numVotes);
	}
}


// Open-BFME-1's resetPlayersVotes: drop the votes playerID cast on or
// before frame, then refresh the menu's count as applyDisconnectVote does.
void DisconnectManager::resetPlayersVotes(Int playerID, UnsignedInt frame, ConnectionManager *conMgr) {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_playerVotes[i][playerID].frame <= frame) {
			m_playerVotes[i][playerID].vote = FALSE;
		}
	}

	Int numVotes = countVotesForPlayer(playerID, conMgr);
	Int transSlot = Rva004D39DEGet(playerID, conMgr->getLocalPlayerID());
	if (transSlot != -1 && TheDisconnectMenu) {
		TheDisconnectMenu->updateVotes(transSlot, numVotes);
	}
}

// Open-BFME-1's resetPlayerTimeouts: restart the timeout of every slot that
// translates to a remote player.
void DisconnectManager::resetPlayerTimeouts(ConnectionManager *conMgr) {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		Int slot = Rva004D39DEGet(i, conMgr->getLocalPlayerID());
		if (slot != -1) {
			resetPlayerTimeout(slot);
		}
	}
}

// Open-BFME-1's processDisconnectVote: a vote counts only when its sender is
// still in the game. The donor reads the vote's slot (+0x1c byte) and frame
// (+0x20) through NetDisconnectVoteCommandMsg::getSlot/getVoteFrame; retail's
// linker folded those into the identical getters 0x004C54EC and 0x0030D377,
// which carry the names called here.
void DisconnectManager::processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr) {
	Int transSlot = Rva004D39DEGet(msg->getPlayerID(), conMgr->getLocalPlayerID());

	if (isPlayerInGame(transSlot, conMgr) == FALSE) {
		return;
	}

	applyDisconnectVote(((NetProgressCommandMsg *)msg)->getPercentage(),
		((NetWrapperCommandMsg *)msg)->getDataLength(), msg->getPlayerID(), conMgr);
}
