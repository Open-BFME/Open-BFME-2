// cl: /Ireference/shims/connectionnotify /Ireference/shims/connectiontransport /Ireference/shims/transport /Ireference/shims/networkutil /Ireference/shims/framecommandreturn /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameNetwork/ConnectionManager.cpp); this unit had no counterpart under Code/.
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


// Retail's _Rb_tree::insert_unique(const value_type&) writes the leftmost fast
// path as `if (__comp && __j == begin())` with `_M_insert(__y, __y, __v)`, not
// as the nested if/else the vendored STLport carries.  The two shapes differ by
// seven bytes here (an inlined arm plus an inverted branch), and the vendored
// header already carries the retail spelling behind this switch.
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

#include "Compression.h"
#include "strtok_r.h"
#include "Common/AudioEventRTS.h"
#include "Common/CRCDebug.h"
#include "Common/Debug.h"
#include "Common/File.h"
#include "Common/GameAudio.h"
#include "Common/LocalFileSystem.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Recorder.h"

#include "GameClient/Diplomacy.h"
#include "GameClient/GameText.h"
#include "GameClient/MessageBox.h"
#include "GameNetwork/ConnectionManager.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/NetCommandWrapperList.h"
#include "GameNetwork/NetworkUtil.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/VictoryConditions.h"
#include "GameClient/DisconnectMenu.h"
#include "GameClient/InGameUI.h"

class Rva004D272EMapHintInsert
{
public:
	typedef FileCommandMap::iterator iterator;
	typedef FileCommandMap::value_type value_type;
	iterator insert(iterator position, const value_type &value);
};

class Rva0046A9ABMapLowerBound
{
public:
	_STL::_Rb_tree_node<FileCommandMap::value_type> *lower_bound(const unsigned short &key) const;
};

class Rva004D5973WordField
{
public:
	unsigned short get() const;
	char m_lead[0x20];
	unsigned short m_value;
};

class Rva001DCD01ByteField
{
public:
	unsigned char get() const;
	char m_lead[0x22];
	unsigned char m_value;
};

class Rva004D632D
{
public:
	AsciiString rva004D632D() const;

private:
	char m_pad[0x1c];
	AsciiString m_str1c;
};

struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};
typedef _STL::map<unsigned short, int, Gen_lt_00940b40> Rva004D2C8EFileProgressMap;

class Rva004D2C8EConnectionManagerLayout
{
public:
	char m_pad[0x12138];
	FileCommandMap s_fileCommandMap;
	FileMaskMap s_fileRecipientMaskMap;
	Rva004D2C8EFileProgressMap s_fileProgressMap[MAX_SLOTS];
};

#pragma optimize("s", on)
template <> AsciiString &FileCommandMap::operator[](const unsigned short &key)
{
	iterator i(((Rva0046A9ABMapLowerBound *)this)->lower_bound(key));
	if (i == end() || key_comp()(key, (*i).first))
		i = ((Rva004D272EMapHintInsert *)this)->insert(
			i, value_type(key, AsciiString()));
	return (*i).second;
}
#pragma optimize("", on)

// Keep the map helpers that the original operator[] instantiation emitted.
// ?Rva004D2941MapInstantiationAnchor present-unmatched
void Rva004D2941MapInstantiationAnchor()
{
	FileCommandMap fileCommandMap;
	FileCommandMap::iterator position = fileCommandMap.lower_bound(0);
	fileCommandMap.insert(position, FileCommandMap::value_type(0, AsciiString()));
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

/**
 * Le destructor.
 */
// ??1ConnectionManager@@ present-unmatched
ConnectionManager::~ConnectionManager(void)
{
	if (m_localUser != NULL) {
		m_localUser->deleteInstance();
		m_localUser = NULL;
	}

//	m_transport = NULL; // Network will delete transports; we just forget them
	if (m_transport != NULL) {
		delete m_transport;
		m_transport = NULL;
	}

	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_frameData[i] != NULL) {
			m_frameData[i]->deleteInstance();
			m_frameData[i] = NULL;
		}
	}

	for (i = 0; i < NUM_CONNECTIONS; ++i) {
		if (m_connections[i] != NULL) {
			m_connections[i]->deleteInstance();
			m_connections[i] = NULL;
		}
	}

	if (TheDisconnectMenu != NULL) {
		// This is done here since TheDisconnectMenu should only be there if we are in a network game.
		delete TheDisconnectMenu;
		TheDisconnectMenu = NULL;
	}

	if (m_disconnectManager != NULL) {
		delete m_disconnectManager;
		m_disconnectManager = NULL;
	}

	if (m_pendingCommands != NULL) {
		m_pendingCommands->deleteInstance();
		m_pendingCommands = NULL;
	}

	if (m_relayedCommands != NULL) {
		m_relayedCommands->deleteInstance();
		m_relayedCommands = NULL;
	}

	if (m_netCommandWrapperList != NULL) {
		m_netCommandWrapperList->deleteInstance();
		m_netCommandWrapperList = NULL;
	}

	s_fileCommandMap.clear();
	s_fileRecipientMaskMap.clear();
	for (i = 0; i < MAX_SLOTS; ++i) {
		s_fileProgressMap[i].clear();
	}
}

/**
 * Le constructor
 */
// ??0ConnectionManager@@ present-unmatched
ConnectionManager::ConnectionManager(void)
{
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		m_frameData[i] = NULL;
	}
	m_transport = NULL;
	m_disconnectManager = NULL;
	m_pendingCommands = NULL;
	m_relayedCommands = NULL;
	m_localAddr = 0;
	m_localPort = 0;
	m_netCommandWrapperList = NULL;
	m_localUser = NULL;
	m_localUser = newInstance(User);
}

/**
 * Initialize the connection manager and any subsystems.
 */
// ConnectionManager::init is defined with its retail-matched body in Code/GameEngine/Source/Common/ConnectionManagerInit2.cpp (0x004D24A2).

/**
 * Reset the connection manager and any subsystems.
 */
// ?reset@ConnectionManager@@ present-unmatched
void ConnectionManager::reset() 
{
//	if (m_transport == NULL) {
//		m_transport = new Transport;
//	}
//	m_transport->reset();
	if (m_transport != NULL) {
		delete m_transport;
		m_transport = NULL;
	}

	for (Int i = 0; i < NUM_CONNECTIONS; ++i) {
		if (m_connections[i] != NULL) {
			m_connections[i]->deleteInstance();
			m_connections[i] = NULL;
		}
	}

	for (i=0; i<MAX_SLOTS; ++i)
	{
		if (m_frameData[i] != NULL) {
			m_frameData[i]->deleteInstance();
			m_frameData[i] = NULL;
		}
	}

	if (m_pendingCommands == NULL) {
		m_pendingCommands = newInstance(NetCommandList);
		m_pendingCommands->init();
	}
	m_pendingCommands->reset();

	if (m_relayedCommands == NULL) {
		m_relayedCommands = newInstance(NetCommandList);
		m_relayedCommands->init();
	}
	m_relayedCommands->reset();

	if (m_netCommandWrapperList == NULL) {
		m_netCommandWrapperList = newInstance(NetCommandWrapperList);
		m_netCommandWrapperList->init();
	}
	m_netCommandWrapperList->reset();

	m_localSlot = -1;
#ifdef MEMORYPOOL_DEBUG
	TheMemoryPoolFactory->debugSetInitFillerIndex(m_localSlot);
#endif
	m_packetRouterSlot = -1;

	for (i = 0; i < TheGlobalData->m_networkFPSHistoryLength; ++i) {
		m_fpsAverages[i] = -1;
	}
	for (i = 0; i < TheGlobalData->m_networkLatencyHistoryLength; ++i) {
		m_latencyAverages[i] = 0.0;
	}

	for (i = 0; i < MAX_SLOTS; ++i) {
		m_packetRouterFallback[i] = -1;
	}

	m_frameMetrics.reset();
}

// ?getPingFrame@ConnectionManager@@ present-unmatched
UnsignedInt ConnectionManager::getPingFrame()
{
	return (m_disconnectManager)?m_disconnectManager->getPingFrame():0;
}

// ?getPingsSent@ConnectionManager@@ present-unmatched
Int ConnectionManager::getPingsSent()
{
	return (m_disconnectManager)?m_disconnectManager->getPingsSent():0;
}

// ?getPingsRecieved@ConnectionManager@@ present-unmatched
Int ConnectionManager::getPingsRecieved()
{
	return (m_disconnectManager)?m_disconnectManager->getPingsRecieved():0;
}

// ?isPlayerConnected@ConnectionManager@@ present-unmatched
Bool ConnectionManager::isPlayerConnected( Int playerID )
{
	return ( playerID == m_localSlot || (m_connections[playerID] && !m_connections[playerID]->isQuitting()) );
}

// ?attachTransport@ConnectionManager@@ present-unmatched
void ConnectionManager::attachTransport(Transport *transport) {
	if (m_transport != NULL) {
		delete m_transport;
		m_transport = NULL;
	}
	m_transport = transport;
}

/**
 * zero out the command counts for the given frames.  Presently this is used for
 * the start of a game since there won't be any commands for the first few frames due to runahead.
 */
// ?zeroFrames@ConnectionManager@@ present-unmatched
void ConnectionManager::zeroFrames(UnsignedInt startingFrame, UnsignedInt numFrames) {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_frameData[i] != NULL) {
//			DEBUG_LOG(("Calling zeroFrames on player %d, starting frame %d, numFrames %d\n", i, startingFrame, numFrames));
			m_frameData[i]->zeroFrames(startingFrame, numFrames);
		}
	}
}

/**
 * Destroy any game messages that are left over due to the run ahead.
 */
// ?destroyGameMessages@ConnectionManager@@ present-unmatched
void ConnectionManager::destroyGameMessages() {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		// Need to destroy these game messages because when the game ends, there are
		// still some game messages left over because of the run ahead aspect of
		// network play.
		if (m_frameData[i] != NULL) {
			m_frameData[i]->destroyGameMessages();
		}
	}
}

// ?doRelay@ConnectionManager@@ present-unmatched
/**
 * ConnectionManager::doRelay()
 * Queries the transport for commands that need to be relayed to another client.
 * Get those commands and relay them to the appropriate Connection(s). We make the
 * assumption that a command will only be relayed once.
 */
// ?doRelay@ConnectionManager@@ present-unmatched
void ConnectionManager::doRelay() {
	static Int numPackets = 0;
	static Int numCommands = 0;

	NetPacket *packet = NULL;

	for (Int i = 0; i < MAX_MESSAGES; ++i) {
		if (m_transport->m_inBuffer[i].length != 0) {
			// This transport buffer has yet to be processed.

			// make a NetPacket out of this data so it can be broken up into individual commands.
			packet = newInstance(NetPacket)(&(m_transport->m_inBuffer[i]));

			//DEBUG_LOG(("ConnectionManager::doRelay() - got a packet with %d commands\n", packet->getNumCommands()));
			//LOGBUFFER( packet->getData(), packet->getLength() );

			// Get the command list from the packet.
			NetCommandList *cmdList = packet->getCommandList();
			NetCommandRef *cmd = cmdList->getFirstMessage();

			// Iterate through the commands in this packet and send them to the proper connections.
			while (cmd != NULL) {
				//DEBUG_LOG(("ConnectionManager::doRelay() - Looking at a command of type %s\n",
					//GetAsciiNetCommandType(cmd->getCommand()->getNetCommandType()).str()));
				if (CommandRequiresAck(cmd->getCommand())) {
					ackCommand(cmd, m_localSlot);
				}
				if (!processNetCommand(cmd)) {
					sendRemoteCommand(cmd);
				}
				cmd = cmd->getNext();

				++numCommands;
			}
			++numPackets;

			// Delete this packet since we won't be needing it anymore.
			packet->deleteInstance();
			packet = NULL;

			cmdList->deleteInstance();
			cmdList = NULL;

			// signal that this has been processed.
			m_transport->m_inBuffer[i].length = 0;
		}
	}

	NetCommandList *cmdList = m_netCommandWrapperList->getReadyCommands();
	NetCommandRef *cmd = cmdList->getFirstMessage();
	while (cmd != NULL) {
		if (CommandRequiresAck(cmd->getCommand())) {
			ackCommand(cmd, m_localSlot);
		}
		if (!processNetCommand(cmd)) {
			sendRemoteCommand(cmd);
		}
		cmd = cmd->getNext();

		++numCommands;
	}
	++numPackets;

	// Delete this packet since we won't be needing it anymore.
	packet->deleteInstance();
	packet = NULL;

	cmdList->deleteInstance();
	cmdList = NULL;
}

/**
 * This is where the non-synchronized network commands should be processed.
 * Return TRUE if the command should not be relayed. Return FALSE if it should be relayed.
 */
// ConnectionManager::processNetCommand is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_processNetCommand.cpp (0x004D2F04).

// ?processFrameResendRequest@ConnectionManager@@ present-unmatched
void ConnectionManager::processFrameResendRequest(NetFrameResendRequestCommandMsg *msg) {
	// first make sure this is a valid slot
	Int playerID = msg->getPlayerID();
	if ((playerID < 0) || (playerID >= MAX_SLOTS)) {	
		return;
	}

	// make sure this player is still in our game.
	if ((m_connections[playerID] == NULL) || (m_connections[playerID]->isQuitting() == TRUE)) {
		return;
	}

	sendFrameDataToPlayer(playerID, msg->getFrameToResend());
}

/**
 * We have received a wrapper for a command too big to fit in a packet.
 */
// ?processWrapper@ConnectionManager@@ present-unmatched
void ConnectionManager::processWrapper(NetCommandRef *ref) 
{
	NetWrapperCommandMsg *wrapperMsg = (NetWrapperCommandMsg *)(ref->getCommand());
	UnsignedShort commandID = wrapperMsg->getWrappedCommandID();
	DEBUG_LOG(("ConnectionManager::processWrapper() - wrapped commandID is %d, commandID is %d\n",
		commandID, wrapperMsg->getID()));
	Int origProgress = 0;
	FileCommandMap::iterator fcIt = s_fileCommandMap.find(commandID);
	if (fcIt != s_fileCommandMap.end())
	{
		origProgress = s_fileProgressMap[m_localSlot][commandID];
	}
	DEBUG_LOG(("ConnectionManager::processWrapper() - origProgress[%d] == %d for command %d\n",
		m_localSlot, origProgress, commandID));

	m_netCommandWrapperList->processWrapper(ref);

	if (fcIt != s_fileCommandMap.end())
	{
		Int newProgress = m_netCommandWrapperList->getPercentComplete(commandID);
		DEBUG_LOG(("ConnectionManager::processWrapper() - newProgress[%d] == %d for command %d\n",
			m_localSlot, newProgress, commandID));
		if (newProgress > origProgress && newProgress < 100)
		{
			DEBUG_LOG(("ConnectionManager::processWrapper() - sending a NetFileProgressCommandMsg\n"));
			s_fileProgressMap[m_localSlot][commandID] = newProgress;

			Int progressMask = 0xff ^ (1 << m_localSlot);
			NetFileProgressCommandMsg *msg = newInstance(NetFileProgressCommandMsg);
			msg->setPlayerID(m_localSlot);
			msg->setID(0);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()))
			{
				msg->setID(GenerateNextCommandID());
			}
			msg->setFileID(commandID);
			msg->setProgress(newProgress);
			sendLocalCommand(msg, progressMask);
			processFileProgress(msg);
			msg->detach();
		}
	}
}

/**
 * A client has sent us their run ahead metrics, lets store them away for future calculations.
 */
// ?processRunAheadMetrics@ConnectionManager@@ present-unmatched
void ConnectionManager::processRunAheadMetrics(NetRunAheadMetricsCommandMsg *msg) 
{
	UnsignedInt player = msg->getPlayerID();
	if ((player >= 0) && (player < MAX_SLOTS) && (isPlayerConnected(player))) {
		m_latencyAverages[player] = msg->getAverageLatency();
		m_fpsAverages[player] = msg->getAverageFps();
		//DEBUG_LOG(("ConnectionManager::processRunAheadMetrics - player %d, fps = %d, latency = %f\n", player, msg->getAverageFps(), msg->getAverageLatency()));
		if (m_fpsAverages[player] > 100) {
			// limit the reported frame rate average to 100.  This is done because if a
			// user alt-tab's out of the game their frame rate climbs to in the neighborhood of
			// 300, that was deemed "ugly" by the powers that be.
			m_fpsAverages[player] = 100;
		}
	}
}

// ConnectionManager::processDisconnectChat is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_processDisconnectChat.cpp (0x004D1023).

// ?processChat@ConnectionManager@@ present-unmatched
void ConnectionManager::processChat(NetChatCommandMsg *msg) 
{
	UnicodeString unitext;
	UnicodeString name;
	UnsignedByte playerID = msg->getPlayerID();
	//DEBUG_LOG(("processChat(): playerID = %d\n", playerID));
	if (playerID == m_localSlot) {
		name = m_localUser->GetName();
		//DEBUG_LOG(("connection is NULL, using %ls\n", name.str()));
	} else if (((m_connections[playerID] != NULL) && (m_connections[playerID]->isQuitting() == FALSE))) {
		name = m_connections[playerID]->getUser()->GetName();
		//DEBUG_LOG(("connection is non-NULL, using %ls\n", name.str()));
	}
	unitext.format(L"[%ls] %ls", name.str(), msg->getText().str());
//	DEBUG_LOG(("ConnectionManager::processChat - got message from player %d (mask %8.8X), message is %ls\n", playerID, msg->getPlayerMask(), unitext.str()));
	
	AsciiString playerName;
	playerName.format("player%d", msg->getPlayerID());
	const Player *player = ThePlayerList->findPlayerWithNameKey( TheNameKeyGenerator->nameToKey( playerName ) );
	if (!player)
	{
		TheInGameUI->message(UnicodeString(L"%ls"), unitext.str());
		return;
	}
	
	Bool fromObserver = !player->isPlayerActive();
	Bool amIObserver = !ThePlayerList->getLocalPlayer()->isPlayerActive();
	Bool canSeeChat = amIObserver || !fromObserver && !TheGameInfo->getConstSlot(playerID)->isMuted();
	
	if ( ((1<<m_localSlot) & msg->getPlayerMask() ) && canSeeChat  )
	{
		RGBColor rgb;
		rgb.setFromInt(player->getPlayerColor());
		TheInGameUI->messageColor(&rgb, UnicodeString(L"%ls"), unitext.str());

		// feedback for received chat messages in-game
		AudioEventRTS audioEvent("GUICommunicatorIncoming");
		TheAudio->addAudioEvent(&audioEvent);
	}
}

// ConnectionManager::processFile is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_fileTransfer.cpp (0x004D2B16).

#pragma optimize("s", on)
void ConnectionManager::processFileAnnounce(NetFileAnnounceCommandMsg *msg) 
{
	DEBUG_LOG(("ConnectionManager::processFileAnnounce() - expecting '%s' (%s) in command %d\n", msg->getPortableFilename().str(), msg->getRealFilename().str(), msg->getFileID()));
	Rva004D2C8EConnectionManagerLayout *layout = (Rva004D2C8EConnectionManagerLayout *)this;
	layout->s_fileCommandMap[((Rva004D5973WordField *)msg)->get()] = ((Rva004D632D *)msg)->rva004D632D();
	layout->s_fileRecipientMaskMap[((Rva004D5973WordField *)msg)->get()] = ((Rva001DCD01ByteField *)msg)->get();
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if ( (1<<i) & ((Rva001DCD01ByteField *)msg)->get() )
		{
			layout->s_fileProgressMap[i][((Rva004D5973WordField *)msg)->get()] = 0;
		}
		else
		{
			layout->s_fileProgressMap[i][((Rva004D5973WordField *)msg)->get()] = 100; // they don't need to get it, so they're already done.
		}
	}
}
#pragma optimize("", on)

// ConnectionManager::processFileProgress is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_fileTransfer.cpp (0x004D2852).

void ConnectionManager::processProgress( NetProgressCommandMsg *msg )
{
	TheGameLogic->processProgress(msg->getPlayerID(), msg->getPercentage());
}

// ?processLoadComplete@ConnectionManager@@ present-unmatched
void ConnectionManager::processLoadComplete( NetCommandMsg *msg )
{
	TheGameLogic->processProgressComplete(msg->getPlayerID());
}

// ?processTimeOutGameStart@ConnectionManager@@ present-unmatched
void ConnectionManager::processTimeOutGameStart( NetCommandMsg *msg )
{
	TheGameLogic->timeOutGameStart();
}

/**
 * Another client has sent us the command count for a new frame.
 */
// ?processFrameInfo@ConnectionManager@@ present-unmatched
void ConnectionManager::processFrameInfo(NetFrameCommandMsg *msg) {
	//stupid frame info, why don't you process yourself?

	UnsignedInt playerID = msg->getPlayerID();

	if ((playerID >= 0) && (playerID < MAX_SLOTS)) {
		if (m_frameData[playerID] != NULL) {
//			DEBUG_LOG(("ConnectionManager::processFrameInfo - player %d, frame %d, command count %d, received on frame %d\n", playerID, msg->getExecutionFrame(), msg->getCommandCount(), TheGameLogic->getFrame()));
			m_frameData[playerID]->setFrameCommandCount(msg->getExecutionFrame(), msg->getCommandCount());
		}
	}
}

/**
 * We just got a stage 1 ack from someone.  So we should remove it from the connection that sent it so
 * it doesn't keep resending it.
 */
// ?processAckStage1@ConnectionManager@@ present-unmatched
void ConnectionManager::processAckStage1(NetCommandMsg *msg) {
#if defined(_DEBUG) || defined(_INTERNAL)
	Bool doDebug = (msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTFRAME) ? TRUE : FALSE;
#endif

	UnsignedByte playerID = msg->getPlayerID();
	NetCommandRef *ref = NULL;

#if defined(_DEBUG) || defined(_INTERNAL)
	if (doDebug == TRUE) {
		DEBUG_LOG(("ConnectionManager::processAck - processing ack for command %d from player %d\n", ((NetAckStage1CommandMsg *)msg)->getCommandID(), playerID));
	}
#endif
	
	if ((playerID >= 0) && (playerID < NUM_CONNECTIONS)) {
		if (m_connections[playerID] != NULL) {
			ref = m_connections[playerID]->processAck(msg);
		}
	} else {
		DEBUG_ASSERTCRASH((playerID >= 0) && (playerID < NUM_CONNECTIONS), ("ConnectionManager::processAck - %d is an invalid player number"));
	}

	if (ref != NULL) {
		if (ref->getCommand()->getNetCommandType() == NETCOMMANDTYPE_FRAMEINFO) {
			m_frameMetrics.processLatencyResponse(((NetFrameCommandMsg *)(ref->getCommand()))->getExecutionFrame());
		}

		ref->deleteInstance();
		ref = NULL;
	}
}

/**
 * We just got a stage 2 ack from someone.  So remove it from the pending commands list so it doesn't
 * get sent in the case of a new packet router.
 */
// ?processAckStage2@ConnectionManager@@ present-unmatched
void ConnectionManager::processAckStage2(NetCommandMsg *msg) {
	UnsignedShort commandID = 0;
	UnsignedByte playerID = 0;
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2) {
		commandID = ((NetAckStage2CommandMsg *)msg)->getCommandID();
		playerID = ((NetAckStage2CommandMsg *)msg)->getOriginalPlayerID();
	} else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		commandID = ((NetAckBothCommandMsg *)msg)->getCommandID();
		playerID = ((NetAckBothCommandMsg *)msg)->getOriginalPlayerID();
	} else {
		return;
	}

	NetCommandRef *ref = m_pendingCommands->findMessage(commandID, playerID);
	if (ref != NULL) {
		//DEBUG_LOG(("ConnectionManager::processAckStage2 - removing command %d from the pending commands list.\n", commandID));
		DEBUG_ASSERTCRASH((m_localSlot == playerID), ("Found a command in the pending commands list that wasn't originated by the local player"));
		m_pendingCommands->removeMessage(ref);
		ref->deleteInstance();
		ref = NULL;
	} else {
		//DEBUG_LOG(("ConnectionManager::processAckStage2 - Couldn't find command %d from player %d in the pending commands list.\n", commandID, playerID));
	}

	ref = m_relayedCommands->findMessage(commandID, playerID);
	if (ref != NULL) {
		//DEBUG_LOG(("ConnectionManager::processAckStage2 - found command ID %d from player %d in the relayed commands list.\n", commandID, playerID));
		UnsignedByte relay = ref->getRelay();
		//DEBUG_LOG(("ConnectionManager::processAckStage2 - relay was %d and is now ", relay));
		relay = relay & ~(1 << msg->getPlayerID());
		//DEBUG_LOG(("%d\n", relay));
		if (relay == 0) {
			//DEBUG_LOG(("ConnectionManager::processAckStage2 - relay is 0, removing command from the relayed commands list.\n"));
			m_relayedCommands->removeMessage(ref);
			NetAckStage2CommandMsg *ackmsg = newInstance(NetAckStage2CommandMsg)(ref->getCommand());
			sendLocalCommand(ackmsg, 1 << ackmsg->getOriginalPlayerID());
			ref->deleteInstance();
			ref = NULL;

			ackmsg->detach();
			ackmsg = NULL;
		} else {
			ref->setRelay(relay);
		}
	}
}

/**
 * We just got a "both" ack from someone.  So process it as both a stage 1 and stage 2 ack.
 */
// ?processAck@ConnectionManager@@ present-unmatched
void ConnectionManager::processAck(NetCommandMsg *msg) {
	if ((msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) || (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH)) {
		processAckStage1(msg);
	}
	if ((msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2) || (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH)) {
		processAckStage2(msg);
	}
}

/**
 * A player has just left our game. Delete their connection and frame data manager.
 * return codes are:
 * PLAYERLEAVECODE_UNKNOWN - player didn't have a valid slot number.
 * PLAYERLEAVECODE_CLIENT - someone in the game that wasn't us or the packet router.
 * PLAYERLEAVECODE_LOCAL - We are leaving the game, we could also be the packet router.
 * PLAYERLEAVECODE_PACKETROUTER - The packet router left the game.
 *
 * If we are leaving and are also the packet router, it will return the PLAYERLEAVECODE_LOCAL return code.
 */
// ?processPlayerLeave@ConnectionManager@@ present-unmatched
PlayerLeaveCode ConnectionManager::processPlayerLeave(NetPlayerLeaveCommandMsg *msg) {
	UnsignedByte playerID = msg->getLeavingPlayerID();
	if ((playerID != m_localSlot) && (m_connections[playerID] != NULL)) {
		DEBUG_LOG(("ConnectionManager::processPlayerLeave() - setQuitting() on player %d on frame %d\n", playerID, TheGameLogic->getFrame()));
		m_connections[playerID]->setQuitting();
	}
	DEBUG_ASSERTCRASH(m_frameData[playerID]->getIsQuitting() == FALSE, ("Player %d is already quitting", playerID));
	if ((playerID != m_localSlot) && (m_frameData[playerID] != NULL) && (m_frameData[playerID]->getIsQuitting() == FALSE)) {
		DEBUG_LOG(("ConnectionManager::processPlayerLeave - setQuitFrame on player %d for frame %d\n", playerID, TheGameLogic->getFrame()+1));
		m_frameData[playerID]->setQuitFrame(TheGameLogic->getFrame() + FRAMES_TO_KEEP + 1);
	}

	if (playerID == m_localSlot)
	{
		// we're leaving, so mark our connections and frame datas to go away.
		for (Int i=0; i<MAX_SLOTS; ++i)
		{
			if (m_connections[i])
			{
				m_connections[i]->clearCommandsExceptFrom(m_localSlot);
				m_connections[i]->setQuitting();
			}
		}
	}

	PlayerLeaveCode code = disconnectPlayer(playerID);
	DEBUG_LOG(("ConnectionManager::processPlayerLeave() - just disconnected player %d with ret code %d\n", playerID, code));
	if (code == PLAYERLEAVECODE_PACKETROUTER)
		resendPendingCommands();

	PopulateInGameDiplomacyPopup();
	return code;
}

// ?getPacketRouterFallbackSlot@ConnectionManager@@ present-unmatched
UnsignedInt ConnectionManager::getPacketRouterFallbackSlot(Int packetRouterNumber) {
	if ((packetRouterNumber >= 0) && (packetRouterNumber < MAX_SLOTS)) {
		return m_packetRouterFallback[packetRouterNumber];
	}
	return MAX_SLOTS;
}

// ConnectionManager::getPacketRouterSlot: defined in ConnectionManagerLocalSlot.cpp (its row's unit).

// ConnectionManager::areAllQueuesEmpty is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_areAllQueuesEmptyTwin_Rva004CF3B9.cpp (0x004CF3B9).

// ?canILeave@ConnectionManager@@ present-unmatched
Bool ConnectionManager::canILeave() {
	return areAllQueuesEmpty();
}

/**
 * The local player is leaving. Tell the local player as well as the other players
 * to remove this player at the specified frame.
 */
// ?handleLocalPlayerLeaving@ConnectionManager@@ present-unmatched
void ConnectionManager::handleLocalPlayerLeaving(UnsignedInt frame) {
	NetPlayerLeaveCommandMsg *msg = newInstance(NetPlayerLeaveCommandMsg);

	msg->setLeavingPlayerID(m_localSlot);
	msg->setExecutionFrame(frame);
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}
	msg->setPlayerID(m_localSlot);

	DEBUG_LOG(("ConnectionManager::handleLocalPlayerLeaving - Local player leaving on frame %d\n", frame));
	DEBUG_ASSERTCRASH(m_packetRouterSlot >= 0, ("ConnectionManager::handleLocalPlayerLeaving, packet router is %d, illegal value.", m_packetRouterSlot));

	sendLocalCommand(msg);

	msg->detach();
}

/**
 * We just got a message that needs to be ack'd, so ack it!
 */
// ?ackCommand@ConnectionManager@@ present-unmatched
void ConnectionManager::ackCommand(NetCommandRef *ref, UnsignedInt localSlot) {
	NetCommandMsg *msg = ref->getCommand();
	NetCommandMsg *ackmsg;
	UnsignedShort commandID;
	UnsignedByte originalPlayerID;
	UnsignedByte sendRelay = 0;

	// Make send relay a bitmask for the connections that the relay will actually be sent to. This is
	// necessary to determine whether or not we have to wait to send a stage 2 ack.
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (((m_connections[i] != NULL) && (m_connections[i]->isQuitting() == FALSE))) {
			sendRelay = sendRelay | (1 << i);
		}
	}

#if defined(_DEBUG) || defined(_INTERNAL)
	Bool doDebug = (msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTFRAME) ? TRUE : FALSE;
#endif

	sendRelay = sendRelay & ref->getRelay();
	if (sendRelay == 0) {
		NetAckBothCommandMsg *bothmsg = newInstance(NetAckBothCommandMsg)(ref->getCommand());
		ackmsg = bothmsg;
		commandID = bothmsg->getCommandID();
		originalPlayerID = bothmsg->getOriginalPlayerID();
#if defined(_DEBUG) || defined(_INTERNAL)
		if (doDebug) {
			DEBUG_LOG(("ConnectionManager::ackCommand - doing ack both for command %d from player %d\n", bothmsg->getCommandID(), bothmsg->getOriginalPlayerID()));
		}
#endif
	} else {
		NetAckStage1CommandMsg *stage1msg = newInstance(NetAckStage1CommandMsg)(ref->getCommand());
		ackmsg = stage1msg;
		commandID = stage1msg->getCommandID();
		originalPlayerID = stage1msg->getOriginalPlayerID();
#if defined(_DEBUG) || defined(_INTERNAL)
		if (doDebug) {
			DEBUG_LOG(("ConnectionManager::ackCommand - doing ack stage 1 for command %d from player %d\n", stage1msg->getCommandID(), stage1msg->getOriginalPlayerID()));
		}
#endif
	}

	ackmsg->setPlayerID(localSlot); // Tell the player who this ack is coming from.

	if (CommandRequiresDirectSend(msg) && CommandRequiresAck(msg)) {
		// Send this ack directly back to the sending player, don't go through the packet router.
		if ((msg->getPlayerID() >= 0) && (msg->getPlayerID() < MAX_SLOTS)) {
			if (m_connections[msg->getPlayerID()] != NULL) {
				m_connections[msg->getPlayerID()]->sendNetCommandMsg(ackmsg, 1 << msg->getPlayerID());
			}
		}
	} else {
		// The local connection may be the packet router, in that case, the connection would be NULL.  So do something about it!
		if ((m_packetRouterSlot >= 0) && (m_packetRouterSlot < MAX_SLOTS)) {
			if (m_connections[m_packetRouterSlot] != NULL) {
//				DEBUG_LOG(("ConnectionManager::ackCommand - acking command %d from player %d to packet router.\n", commandID, m_packetRouterSlot));
				m_connections[m_packetRouterSlot]->sendNetCommandMsg(ackmsg, 1 << m_packetRouterSlot);
			} else if (m_localSlot == m_packetRouterSlot) {
				// we are the packet router, send the ack to the player that sent the command.
				if ((msg->getPlayerID() >= 0) && (msg->getPlayerID() < MAX_SLOTS)) {
					if (m_connections[msg->getPlayerID()] != NULL) {
//						DEBUG_LOG(("ConnectionManager::ackCommand - acking command %d from player %d directly to player.\n", commandID, msg->getPlayerID()));
						m_connections[msg->getPlayerID()]->sendNetCommandMsg(ackmsg, 1 << msg->getPlayerID());
					} else {
	//					DEBUG_ASSERTCRASH(m_connections[msg->getPlayerID()] != NULL, ("Connection to player is NULL"));
					}
				} else {
					DEBUG_ASSERTCRASH((msg->getPlayerID() >= 0) && (msg->getPlayerID() < MAX_SLOTS), ("Command sent by an invalid player ID."));
				}
			} else {
				DEBUG_ASSERTCRASH(m_connections[m_packetRouterSlot] != NULL, ("Connection to packet router is NULL"));
			}
		} else {
			DEBUG_ASSERTCRASH((m_packetRouterSlot >= 0) && (m_packetRouterSlot < MAX_SLOTS), ("I don't know who the packet router is."));
		}
	}

	ackmsg->detach();
}

/**
 * This is where we relay a command from one client to others (including ourselves).
 * This should only be done by the current packet router.
 */
// ?sendRemoteCommand@ConnectionManager@@ present-unmatched
void ConnectionManager::sendRemoteCommand(NetCommandRef *msg) {
	UnsignedByte actualRelay = 0;
	if (msg->getCommand() == NULL) {
		return;
	}

	DEBUG_LOG(("ConnectionManager::sendRemoteCommand - sending net command %d of type %s from player %d, relay is 0x%x\n",
		msg->getCommand()->getID(), GetAsciiNetCommandType(msg->getCommand()->getNetCommandType()).str(), msg->getCommand()->getPlayerID(), msg->getRelay()));

	UnsignedByte relay = msg->getRelay();
	if ((relay & (1 << m_localSlot)) && (m_frameData[msg->getCommand()->getPlayerID()] != NULL)) {
		if (IsCommandSynchronized(msg->getCommand()->getNetCommandType())) {
			DEBUG_LOG(("ConnectionManager::sendRemoteCommand - adding net command of type %s to player %d for frame %d\n", GetAsciiNetCommandType(msg->getCommand()->getNetCommandType()).str(), msg->getCommand()->getPlayerID(), msg->getCommand()->getExecutionFrame()));
			m_frameData[msg->getCommand()->getPlayerID()]->addNetCommandMsg(msg->getCommand());
		}
	}

	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if ((relay & (1 << i)) && ((m_connections[i] != NULL) && (m_connections[i]->isQuitting() == FALSE))) {
			DEBUG_LOG(("ConnectionManager::sendRemoteCommand - relaying command %d to player %d\n", msg->getCommand()->getID(), i));
			m_connections[i]->sendNetCommandMsg(msg->getCommand(), 1 << i);
			actualRelay = actualRelay | (1 << i);
		}
	}

	if ((actualRelay != 0) && (CommandRequiresAck(msg->getCommand()) == TRUE)) {
		NetCommandRef *ref = m_relayedCommands->addMessage(msg->getCommand());
		if (ref != NULL) {
			ref->setRelay(actualRelay);
			//DEBUG_LOG(("ConnectionManager::sendRemoteCommand - command %d added to relayed commands with relay %d\n", msg->getCommand()->getID(), ref->getRelay()));
		}
	}

	// Do some metrics to find the minimum packet arrival cushion.
	if (IsCommandSynchronized(msg->getCommand()->getNetCommandType())) {
//		DEBUG_LOG(("ConnectionManager::sendRemoteCommand - about to call allCommandsReady\n"));
		if (allCommandsReady(msg->getCommand()->getExecutionFrame(), TRUE)) {
			UnsignedInt cushion = msg->getCommand()->getExecutionFrame() - TheGameLogic->getFrame();
			if ((cushion < m_smallestPacketArrivalCushion) || (m_smallestPacketArrivalCushion == -1)) {
				m_smallestPacketArrivalCushion = cushion;
			}
			m_frameMetrics.addCushion(cushion);
//			DEBUG_LOG(("Adding %d to cushion for frame %d\n", cushion, msg->getCommand()->getExecutionFrame()));
		}
	}
}

/**
 * ConnectionManager::update
 * Update the connections. Tell them to do the receive and send.  Also relay
 * commands to their final destinations as necessary.
 */
// ?update@ConnectionManager@@ present-unmatched
void ConnectionManager::update(Bool isInGame) {
//
// 1. do this
// 2. do that
// 3. do something else
// 4. blow something up
// 5. bust some cap
//

	if ((m_localAddr == 0) || (m_localPort == 0)) {
		// we don't have a local address or port yet, this is bad.
		DEBUG_ASSERTCRASH((m_localAddr != 0) && (m_localPort != 0), ("ConnectionManager doesn't have a local address."));
		return;
	}

	m_transport->doRecv();

	if (isInGame) {
		m_disconnectManager->update(this);
	}

	// take the packets from the transport, break them up into commands, and give them to the appropriate connections.
	doRelay();

	// send any necessary keep-alive packets.
	doKeepAlive();

	for (Int i = 0; i < NUM_CONNECTIONS; ++i) {
		if (m_connections[i] != NULL) {
			/*
			if (m_connections[i]->isQueueEmpty() == FALSE) {
//				DEBUG_LOG(("ConnectionManager::update - calling doSend on connection %d\n", i));
			}
			*/

			m_connections[i]->doSend();

			if (m_connections[i]->isQuitting() && m_connections[i]->isQueueEmpty())
			{
				DEBUG_LOG(("ConnectionManager::update - deleting connection for slot %d\n", i));
				m_connections[i]->deleteInstance();
				m_connections[i] = NULL;
			}
		}

		if ((m_frameData[i] != NULL) && (m_frameData[i]->getIsQuitting() == TRUE)) {
			if (m_frameData[i]->getQuitFrame() == TheGameLogic->getFrame()) {
				DEBUG_LOG(("ConnectionManager::update - deleting frame data for slot %d on quitting frame %d\n", i, m_frameData[i]->getQuitFrame()));
				m_frameData[i]->deleteInstance();
				m_frameData[i] = NULL;
			}
		}
	}

	m_transport->doSend();
}

// ?updateRunAhead@ConnectionManager@@ present-unmatched
void ConnectionManager::updateRunAhead(Int oldRunAhead, Int frameRate, Bool didSelfSlug, Int nextExecutionFrame) {
	static time_t lasttimesent = 0;
	time_t curTime = timeGetTime();

	if ((lasttimesent == 0) || ((curTime - lasttimesent) > TheGlobalData->m_networkRunAheadMetricsTime)) {
		if (m_localSlot == m_packetRouterSlot) {
			// We are the packet router, time to compute a new run ahead for this game.
			m_latencyAverages[m_localSlot] = m_frameMetrics.getAverageLatency();

			// since we are now using the display frame rate rather than the logic frame rate to get our average FPS,
			// it doesn't make sense to send the desired logic frame rate if we "slugged" ourself.
//			if (didSelfSlug) {
//				m_fpsAverages[m_localSlot] = frameRate;
//			} else {
				m_fpsAverages[m_localSlot] = m_frameMetrics.getAverageFPS();
//			}
			if (didSelfSlug) {
				//DEBUG_LOG(("ConnectionManager::updateRunAhead - local player run ahead metrics, fps = %d, actual fps = %d, latency = %f, didSelfSlug = true\n", m_fpsAverages[m_localSlot], m_frameMetrics.getAverageFPS(), m_latencyAverages[m_localSlot]));
			} else {
				//DEBUG_LOG(("ConnectionManager::updateRunAhead - local player run ahead metrics, fps = %d, latency = %f, didSelfSlug = false\n", m_fpsAverages[m_localSlot], m_latencyAverages[m_localSlot]));
			}
			Int minFps;
			Int minFpsPlayer;
			getMinimumFps(minFps, minFpsPlayer);
			DEBUG_LOG(("ConnectionManager::updateRunAhead - max latency = %f, min fps = %d, min fps player = %d old FPS = %d\n", getMaximumLatency(), minFps, minFpsPlayer, frameRate));
			if ((minFps >= ((frameRate * 9) / 10)) && (minFps < frameRate)) {
				// if the minimum fps is within 10% of the desired framerate, then keep the current minimum fps.
				minFps = frameRate;
			}
			if (minFps < 5) {
				minFps = 5; // Absolutely do not run below 5 fps.
			}
			if (minFps > TheGlobalData->m_framesPerSecondLimit) {
				minFps = TheGlobalData->m_framesPerSecondLimit; // Cap to 30 FPS.
			}
			DEBUG_LOG(("ConnectionManager::updateRunAhead - minFps after adjustment is %d\n", minFps));
			Int newRunAhead = (Int)((getMaximumLatency() / 2.0) * (Real)minFps);
			newRunAhead += (newRunAhead * TheGlobalData->m_networkRunAheadSlack) / 100; // Add in 10% of slack to the run ahead in case of network hiccups.
			if (newRunAhead < MIN_RUNAHEAD) {
				newRunAhead = MIN_RUNAHEAD; // make sure its at least MIN_RUNAHEAD.
			}

			if (newRunAhead > (MAX_FRAMES_AHEAD / 2)) {
				newRunAhead = MAX_FRAMES_AHEAD / 2; // dont let run ahead get out of hand.
			}

			NetRunAheadCommandMsg *msg = newInstance(NetRunAheadCommandMsg);
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
				msg->setID(GenerateNextCommandID());
			}

			// needs to be set to the greater of getExecutionFrame and TheGameLogic->getFrame() + oldRunAhead
			// This prevents the case of...
			// run ahead starts at 30
			// run ahead changes to 10 at frame 31 (the command was created on frame 1)
			// run ahead changes to 10 at frame 56 (the command was created on frame 46)
			// notice that 56 is within the previous run ahead of 30 which has triggered
			// the frame command count being set for frames 1 through 60 since run ahead
			// didn't change for the first time till frame 31.  This creates an extra command
			// for frame 56 that isn't accounted for in the frame command count that is sent
			// out in the NetFrameCommandMsg.  sheesh.
			if (nextExecutionFrame > (TheGameLogic->getFrame() + oldRunAhead)) {
				msg->setExecutionFrame(nextExecutionFrame);
			} else {
				msg->setExecutionFrame(TheGameLogic->getFrame() + oldRunAhead);
			}

			msg->setRunAhead(newRunAhead);
			msg->setFrameRate(minFps);
			//DEBUG_LOG(("ConnectionManager::updateRunAhead - new run ahead = %d, new frame rate = %d, execution frame %d\n", newRunAhead, minFps, msg->getExecutionFrame()));
			sendLocalCommand(msg, 0xff ^ (1 << minFpsPlayer)); // Send the packet to everyone but the lowest FPS player.

			NetRunAheadCommandMsg *msg2 = newInstance(NetRunAheadCommandMsg);
			msg2->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg2->getNetCommandType())) {
				/*
				 * Ok there needs to be a big friggin comment about this change...
				 * What happens is that the two run ahead commands get sent to different players
				 * using different command ID's.  So player 1 has the run ahead command as command x
				 * and player 2 has the command as command x+1.  This is all good except when it comes
				 * to players being disconnected.  With the new disconnect scheme player 1 could potentially
				 * send his run ahead command to player 2 (or the other way around) to let player 2 catch
				 * up to him.  So if player 2 has his run ahead command as x+1 and now he gets player 1's
				 * command list with the run ahead command listed as command x, he won't see them as being
				 * the same command and will now think he has two different run ahead commands for that frame
				 * and thus his command list will have an extra command and he will never be able to recover.
				 * So to fix this we have to use the same command ID for both run ahead commands.  That way
				 * when the commands are copied places for the disconnect screen they will be seen as the
				 * same command, and all will be good.
				 */
//				msg2->setID(GenerateNextCommandID());
				msg2->setID(msg->getID());
			}
			if (nextExecutionFrame > (TheGameLogic->getFrame() + oldRunAhead)) {
				msg2->setExecutionFrame(nextExecutionFrame);
			} else {
				msg2->setExecutionFrame(TheGameLogic->getFrame() + oldRunAhead);
			}

			// Let the player with the slowest FPS run a little faster than the other computers...
			// just in case they are able to.  Then we might be able to run the game faster which would be good.
			Int newMinFps = (minFps * 11) / 10;
			if (newMinFps == minFps) {
				newMinFps = minFps + 1;
			}
			if (newMinFps > 30) {
				newMinFps = 30; // Cap FPS to 30.
			}
			msg2->setRunAhead(newRunAhead);
			msg2->setFrameRate(newMinFps);

			sendLocalCommand(msg2, 1 << minFpsPlayer);

			msg->detach();
			msg2->detach();
		} else {
			// We are not the packet router, send our metrics info to the packet router.
			NetRunAheadMetricsCommandMsg *msg = newInstance(NetRunAheadMetricsCommandMsg);
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
				msg->setID(GenerateNextCommandID());
			}
			msg->setAverageLatency(m_frameMetrics.getAverageLatency());

			// see above for explanation.
//			if (didSelfSlug) {
//				msg->setAverageFps(frameRate);
//			} else {
				msg->setAverageFps(m_frameMetrics.getAverageFPS());
//			}
			if (didSelfSlug) {
				//DEBUG_LOG(("ConnectionManager::updateRunAhead - average latency = %f, average fps = %d, actual fps = %d, didSelfSlug = true\n", m_frameMetrics.getAverageLatency(), m_frameMetrics.getAverageFPS(), m_frameMetrics.getAverageFPS()));
			} else {
				//DEBUG_LOG(("ConnectionManager::updateRunAhead - average latency = %f, average fps = %d, didSelfSlug = false\n", m_frameMetrics.getAverageLatency(), m_frameMetrics.getAverageFPS()));
			}
			m_connections[m_packetRouterSlot]->sendNetCommandMsg(msg, 1 << m_packetRouterSlot);
			msg->detach();
		}
		lasttimesent = curTime;
	}
}

// ?getMaximumLatency@ConnectionManager@@ present-unmatched
Real ConnectionManager::getMaximumLatency() {
	// This works for 2 player games because the latency for the packet router is always 0.
	Real lat1 = 0.0;
	Real lat2 = 0.0;

	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (isPlayerConnected(i)) {
			if (m_latencyAverages[i] != 0.0) {
				if (m_latencyAverages[i] > lat1) {
					lat2 = lat1;
					lat1 = m_latencyAverages[i];
				} else if (m_latencyAverages[i] > lat2) {
					lat2 = m_latencyAverages[i];
				}
			}
		}
	}

	return (lat1 + lat2);
}

// ?getMinimumFps@ConnectionManager@@ present-unmatched
void ConnectionManager::getMinimumFps(Int &minFps, Int &minFpsPlayer) {
	minFps = -1;
	minFpsPlayer = -1;
//	DEBUG_LOG(("ConnectionManager::getMinimumFps -"));
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if ((m_connections[i] != NULL) || (i == m_localSlot)) {
//			DEBUG_LOG((" %d: %d,", i, m_fpsAverages[i]));
			if (m_fpsAverages[i] != -1) {
				if ((minFps == -1) || (m_fpsAverages[i] < minFps)) {
					minFps = m_fpsAverages[i];
					minFpsPlayer = i;
				}
			}
		}
	}
//	DEBUG_LOG(("\n"));
}

// ?getMinimumCushion@ConnectionManager@@ present-unmatched
UnsignedInt ConnectionManager::getMinimumCushion() {
	return m_frameMetrics.getMinimumCushion();
}

/**
 * The commands for the given frame are all ready, time to send out our command count for that frame.
 */
// ?processFrameTick@ConnectionManager@@ present-unmatched
void ConnectionManager::processFrameTick(UnsignedInt frame) {
	if ((m_frameData[m_localSlot] == NULL) || (m_frameData[m_localSlot]->getIsQuitting() == TRUE)) {
		// if the local frame data stuff is NULL, we must be leaving the game.
		return;
	}
	UnsignedShort commandCount = m_frameData[m_localSlot]->getCommandCount(frame);
	NetFrameCommandMsg *msg = newInstance(NetFrameCommandMsg);
	msg->setExecutionFrame(frame);
	msg->setCommandCount(commandCount);
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}
	msg->setPlayerID(m_localSlot);

	m_frameMetrics.doPerFrameMetrics(frame);

	DEBUG_LOG(("ConnectionManager::processFrameTick - sending frame info for frame %d, ID %d, command count %d\n", frame, msg->getID(), commandCount));

	sendLocalCommand(msg, 0xff & ~(1 << m_localSlot));

	msg->detach();
}

/**
 * Set the local address.
 */
// ?setLocalAddress@ConnectionManager@@ present-unmatched
void ConnectionManager::setLocalAddress(UnsignedInt ip, UnsignedInt port) {
	DEBUG_LOG(("ConnectionManager::setLocalAddress() - local address is %X:%d\n", ip, port));
	m_localAddr = ip;
	m_localPort = port;
}

/**
 * Initialize the transport object
 */
// initTransport is defined in the existing size-optimized region below.

/**
 * This is where the commands from the local client are sent to the other clients in
 * the game.  This is also where the local commands are put into the frame data for
 * future execution.
 */
// ?sendLocalGameMessage@ConnectionManager@@ present-unmatched
void ConnectionManager::sendLocalGameMessage(GameMessage *msg, UnsignedInt frame) {
	UnsignedShort currentID = 0;
	if (DoesCommandRequireACommandID(NETCOMMANDTYPE_GAMECOMMAND)) {
		currentID = GenerateNextCommandID();
	}

	NetCommandMsg *netmsg = newInstance(NetGameCommandMsg)(msg);
	netmsg->setExecutionFrame(frame);
	netmsg->setPlayerID(m_localSlot);
	netmsg->setID(currentID);

	sendLocalCommand(netmsg);

	netmsg->detach();
}

/**
 * This is a NetCommandMsg that originated on the local computer. Send this to everyone specified
 * in the relay field.  Commands sent in this way go through the packet router.
 */
// ?sendLocalCommand@ConnectionManager@@ present-unmatched
void ConnectionManager::sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay /* = 0xff by default*/) {
	if (CommandRequiresDirectSend(msg) || (m_packetRouterSlot < 0) || (m_packetRouterSlot >= MAX_SLOTS) || (m_connections[m_packetRouterSlot] == NULL)) {
		sendLocalCommandDirect(msg, relay);
		return;
	}
	msg->attach();

	DEBUG_LOG(("ConnectionManager::sendLocalCommand - sending net command %d of type %s\n", msg->getID(),
		GetAsciiNetCommandType(msg->getNetCommandType()).str()));

	if (relay & (1 << m_localSlot)) {
		DEBUG_LOG(("ConnectionManager::sendLocalCommand - adding net command of type %s to player %d for frame %d\n", GetAsciiNetCommandType(msg->getNetCommandType()).str(), msg->getPlayerID(), msg->getExecutionFrame()));
		m_frameData[m_localSlot]->addNetCommandMsg(msg);
	}

	// Send the packet to everyone else
	if (m_localSlot == m_packetRouterSlot) {
		// I am the packet router, I need to send this packet to everyone individually.
		for (Int i = 0; i < MAX_SLOTS; ++i) {
			// Send it to all open connections.
			if (((m_connections[i] != NULL) && (m_connections[i]->isQuitting() == FALSE)) && (relay & (1 << i))) {
				// Set the relay mask to only go to this player so he knows not to relay it to anyone else.
				UnsignedByte temprelay = 1 << i;
				m_connections[i]->sendNetCommandMsg(msg, temprelay); // This will create a new copy of netmsg for this connection.
			}
		}
	} else {
		// Send the command to everyone else via the packet router.
		UnsignedByte temprelay = relay & ~(1 << m_localSlot);	// Tell the packet router to relay the message to everyone but myself.
														// Hopefully the packet router is smart enough to not send it
														// to slots that are not in the game.

		m_connections[m_packetRouterSlot]->sendNetCommandMsg(msg, temprelay); // This will create a new copy of netmsg for this connection.

		if (CommandRequiresAck(msg)) {
			NetCommandRef *ref = m_pendingCommands->addMessage(msg);
			//DEBUG_LOG(("ConnectionManager::sendLocalCommand - added command %d to pending commands list.\n", msg->getID()));
			if (ref != NULL) {
				ref->setRelay(temprelay);
			}
		}
	}

	msg->detach(); // detach from the command msg.
}

/**
 * This is a NetCommandMsg that originated on the local computer.  Send this to everyone specified
 * in the relay field.  Commands sent in this way do not go through the packet router.
 */
// sendLocalCommandDirect is defined in the existing size-optimized region below.

Int commandsReadyDebugSpewage = 0;

/**
 * Returns true if all the commands for the given frame are ready to be executed.
 */
// ?allCommandsReady@ConnectionManager@@ present-unmatched
Bool ConnectionManager::allCommandsReady(UnsignedInt frame, Bool justTesting /* = FALSE */) {
	Bool retval = TRUE;
	FrameDataReturnType frameRetVal;
//	retval = FALSE;  // ****for testing purposes only!!!!!!****
	for (Int i = 0; (i < MAX_SLOTS) && retval; ++i) {
		if ((m_frameData[i] != NULL) && (m_frameData[i]->getIsQuitting() == FALSE)) {
/*
			if (!(m_frameData[i]->allCommandsReady(frame, (frame != commandsReadyDebugSpewage) && (justTesting == FALSE)))) {
				if ((frame != commandsReadyDebugSpewage) && (justTesting == FALSE)) {
					DEBUG_LOG(("ConnectionManager::allCommandsReady, frame %d player %d not ready.\n", frame, i));
					commandsReadyDebugSpewage = frame;
				}
				retval = FALSE;
			} else {
//				DEBUG_LOG(("ConnectionManager::allCommandsReady, frame %d player %d is ready.\n", frame, i));
			}
*/

			frameRetVal = m_frameData[i]->allCommandsReady(frame, (frame != commandsReadyDebugSpewage) && (justTesting == FALSE));
			if (frameRetVal == FRAMEDATA_NOTREADY) {
				retval = FALSE;
			} else if (frameRetVal == FRAMEDATA_RESEND) {
				requestFrameDataResend(i, frame);
				retval = FALSE;
			}
		}
	}

	if (frameRetVal == FRAMEDATA_RESEND) {
		// this frame's data is really screwed up, we need to clean it out so it can be resent to us.
		for (i = 0; i < MAX_SLOTS; ++i) {
			if ((m_frameData[i] != NULL) && (i != m_localSlot)) {
				m_frameData[i]->resetFrame(frame, FALSE);
			}
		}
	}

	if ((retval == TRUE) && (justTesting == FALSE)) {
		m_disconnectManager->allCommandsReady(TheGameLogic->getFrame(), this);
		retval = m_disconnectManager->allowedToContinue(); // allow the disconnect manager to keep us on this frame
																											// in case we are waiting for a new packet router or something.
	}

	return retval;
}

// ?handleAllCommandsReady@ConnectionManager@@ present-unmatched
void ConnectionManager::handleAllCommandsReady(void)
{
	m_disconnectManager->allCommandsReady(TheGameLogic->getFrame(), this, FALSE);
}


/**
 * Only call this after making sure that all the commands are there for this frame.
 * After calling this the commands for this frame will be removed from the connection.
 *
 * BGC - To account for the case where the host disconnects without sending the
 *       same commands to all players, we now have to keep around the last 'run ahead'
 *       frames so we can potentially send those commands to the other players in the
 *       game so they can catch up.
 */
// The BFME2 body is defined in ConnectionManagerFrameList.cpp.
// Its target layout and resetFrame ABI differ from the ZH definition.

// ?setFrameGrouping@ConnectionManager@@ present-unmatched
void ConnectionManager::setFrameGrouping(time_t frameGrouping) {
	// Since we are the packet router, we should send more packets per second since we
	// may become the latency bottleneck for sending packets from one player to the next.
	// This is probably ok since the packet router should have the fastest connection of all
	// the players in the game.
	if (m_localSlot == m_packetRouterSlot) {
		frameGrouping = frameGrouping / 2;
	}
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_connections[i] != NULL) {
			m_connections[i]->setFrameGrouping(frameGrouping);
		}
	}
}

/*
// ?determineRouterFallbackPlan@ConnectionManager@@ present-unmatched
void ConnectionManager::determineRouterFallbackPlan() {
	memset(m_packetRouterFallback, 0, sizeof(m_packetRouterFallback));
	Int curnum = 1;
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_connections[i] != NULL) {
			m_packetRouterFallback[i] = curnum;
			if (curnum == 1) {
				m_packetRouterSlot = i;
			}
			++curnum;
		}
	}
}
*/

// ?doKeepAlive@ConnectionManager@@ present-unmatched
void ConnectionManager::doKeepAlive() {
	static Int nextIndex = 0;
	static time_t startTime = 0;

	time_t curTime = timeGetTime();

	if (startTime == 0) {
		startTime = curTime;
		return;
	}

	time_t numSeconds = (curTime - startTime) / 1000;

	while ((nextIndex <= numSeconds) && (nextIndex < MAX_SLOTS)) {
//		DEBUG_LOG(("ConnectionManager::doKeepAlive - trying to send keep alive message to player %d\n", nextIndex));
		if (m_connections[nextIndex] != NULL) {
			NetKeepAliveCommandMsg *msg = newInstance(NetKeepAliveCommandMsg);
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
				msg->setID(GenerateNextCommandID());
			}
//			DEBUG_LOG(("ConnectionManager::doKeepAlive - sending keep alive message to player %d\n", nextIndex));
			sendLocalCommandDirect(msg, 1 << nextIndex);
			msg->detach();
		}
		++nextIndex;
	}
	if (nextIndex == MAX_SLOTS) {
		nextIndex = 0;
		startTime = curTime;
	}
}

// ConnectionManager::disconnectPlayer is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_disconnectPlayer.cpp (0x004D13F8).

// ?quitGame@ConnectionManager@@ present-unmatched
void ConnectionManager::quitGame() {
	// Need to do the NetDisconnectPlayerCommandMsg creation and sending here.
	NetDisconnectPlayerCommandMsg *disconnectMsg = newInstance(NetDisconnectPlayerCommandMsg);
	disconnectMsg->setDisconnectSlot(m_localSlot);
	disconnectMsg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(disconnectMsg->getNetCommandType())) {
		disconnectMsg->setID(GenerateNextCommandID());
	}
	//DEBUG_LOG(("ConnectionManager::disconnectLocalPlayer - about to send disconnect command\n"));
	sendLocalCommandDirect(disconnectMsg, 0xff ^ (1 << m_localSlot));

	//DEBUG_LOG(("ConnectionManager::disconnectLocalPlayer - about to flush connections\n"));
	flushConnections(); // need to do this so our packet actually gets sent before the connections are deleted.
	//DEBUG_LOG(("ConnectionManager::disconnectLocalPlayer - done flushing connections\n"));

	disconnectMsg->detach();

	disconnectLocalPlayer();
}

// ConnectionManager::disconnectLocalPlayer: defined in Network_update.cpp (its row's unit).

/**
 * Takes all the commands that are ready to send and sends them right now.
 */
// ?flushConnections@ConnectionManager@@ present-unmatched
void ConnectionManager::flushConnections() {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_connections[i] != NULL) {
//			DEBUG_LOG(("ConnectionManager::flushConnections - flushing connection to player %d\n", i));
			/*
			if (m_connections[i]->isQueueEmpty()) {
//				DEBUG_LOG(("ConnectionManager::flushConnections - connection queue empty\n"));
			}
			*/
			m_connections[i]->doSend();
		}
	}

	if (m_transport != NULL) {
		m_transport->doSend();
	}
}

// ?resendPendingCommands@ConnectionManager@@ present-unmatched
void ConnectionManager::resendPendingCommands() {
	//DEBUG_LOG(("ConnectionManager::resendPendingCommands()\n"));
	if (m_pendingCommands == NULL) {
		return;
	}

	NetCommandRef *ref = m_pendingCommands->getFirstMessage();
	while (ref != NULL) {
		//DEBUG_LOG(("ConnectionManager::resendPendingCommands - resending command %d\n", ref->getCommand()->getID()));
		sendLocalCommand(ref->getCommand(), ref->getRelay());
		ref = ref->getNext();
	}
}

// ConnectionManager::getLocalPlayerID: defined in ConnectionManagerLocalSlot.cpp (its row's unit).

// ConnectionManager::getPlayerName is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/native_connection_timing_ConnectionManager_getPlayerName.cpp (0x004D0198).

/**
 * Take a user list and make connections and frame data manager objects for each of the players.
 * For now, this is also how we'll determine the packet router fallback plan.
 */
// ?parseUserList@ConnectionManager@@ present-unmatched
void ConnectionManager::parseUserList(const GameInfo *game)
{
	if (!game)
		return;

	Int i;
	Int numUsers = 0;
	m_localSlot = -1;
	DEBUG_LOG(("Local slot is %d\n", game->getLocalSlotNum()));
	for (i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = game->getConstSlot(i);	// badness, but since we cast right back to const, we should be ok
		if (slot->isHuman())
		{
			if (game->getLocalSlotNum() == i)
			{
				m_localSlot = i;
   			m_localUser->setName(slot->getName());
			}

			if (m_localSlot != i)
			{
				m_connections[i] = newInstance(Connection)();
				m_connections[i]->init();
				m_connections[i]->attachTransport(m_transport);
//				UnsignedShort port = (TheNAT)?TheNAT->getSlotPort(i):8088;
				UnsignedShort port = slot->getPort();
				m_connections[i]->setUser(newInstance(User)(slot->getName(), slot->getIP(), port));
				m_frameData[i] = newInstance(FrameDataManager)(FALSE);
				DEBUG_LOG(("Remote user is at %X:%d\n", slot->getIP(), slot->getPort()));
			}
			else
			{
				DEBUG_LOG(("Local user is %d (%X:%d)\n", m_localSlot, slot->getIP(), slot->getPort()));
				m_frameData[i] = newInstance(FrameDataManager)(TRUE);
			}
			m_frameData[i]->init();
			m_frameData[i]->reset();

			m_packetRouterFallback[numUsers] = i;

			++numUsers;

		}
	}
#ifdef MEMORYPOOL_DEBUG
	TheMemoryPoolFactory->debugSetInitFillerIndex(m_localSlot);
#endif

	/*
	if ( numUsers < 2 || m_localSlot == -1 )
	{
		DEBUG_CRASH(("FAILED parseUserList - network game won't work as expected\n"));
		return;
	}

	char * list = strdup(buf);
	char *listPtr = list;
	if (!list)
		return;

	User users[MAX_SLOTS];
	int localUser = -1;
	int i;

	for (i=0; i<MAX_SLOTS; i++)
	{
		users[i].setName("");
	}

	char *userStr, *nameStr, *addrStr, *portStr;
	AsciiString addrAsciiStr;

	char *listPos;

	DEBUG_LOG(("ConnectionManager::parseUserList - looking for local user at %d.%d.%d.%d:%d\n",
		(m_localAddr >> 24) & 0xff,
		(m_localAddr >> 16) & 0xff,
		(m_localAddr >> 8) & 0xff,
		m_localAddr & 0xff,
		m_localPort));

	int numUsers = 0;
	while ( (userStr=strtok_r(listPtr, ",", &listPos)) != NULL )
	{
		listPtr = NULL;
		char *pos = NULL;

		nameStr = strtok_r(userStr, "@", &pos);
		addrStr = strtok_r(NULL, "@:", &pos);
		portStr = strtok_r(NULL, ": ", &pos);

		if (!portStr || numUsers >= MAX_SLOTS)
		{
			DEBUG_LOG(("ConnectionManager::parseUserList - (numUsers = %d) FAILED parseUserList with list [%s]\n", numUsers, buf));
			return;
		}

		addrAsciiStr = addrStr;
		UnsignedInt addr = ResolveIP(addrAsciiStr);
		UnsignedInt port = atoi(portStr);

//		if ((m_localAddr != addr) || (m_localPort != port)) {
		if (loginName.compare(nameStr) != 0) {
			m_connections[numUsers] = newInstance(Connection)();
			m_connections[numUsers]->init();
			m_connections[numUsers]->attachTransport(m_transport);
			m_connections[numUsers]->setUser(newInstance(User)(nameStr, addr, port));

			m_frameData[numUsers] = newInstance(FrameDataManager)(FALSE);

			DEBUG_LOG(("ConnectionManager::parseUserList - User %d is %s\n", numUsers, nameStr));
		} else {
			m_localSlot = numUsers;
			m_localUser.setName(nameStr);

			DEBUG_LOG(("ConnectionManager::parseUserList - User %d is %s\n", numUsers, nameStr));
			DEBUG_LOG(("Local user is %d\n", m_localSlot));

			m_frameData[numUsers] = newInstance(FrameDataManager)(TRUE);
		}
		m_frameData[numUsers]->init();
		m_frameData[numUsers]->reset();

		m_packetRouterFallback[numUsers] = numUsers;

		numUsers++;
	}

	if (numUsers < 2 || m_localSlot == -1)
	{
		DEBUG_LOG(("ConnectionManager::parseUserList - FAILED (local user = %d, num players = %d) with list [%s]\n", m_localSlot, numUsers, buf));
		return;
	}

	if (list != NULL) {
		free(list); // from the strdup above.
		list = NULL;
	}
	*/
}

/**
 * Return the number of incoming bytes per second averaged over 30 sec.
 */
// ?getIncomingBytesPerSecond@ConnectionManager@@ present-unmatched
Real ConnectionManager::getIncomingBytesPerSecond( void )
{
	if (m_transport)
		return m_transport->getIncomingBytesPerSecond();
	else
	  return 0.0;
}

/**
 * Return the number of incoming packets per second averaged over the last 30 sec.
 */
// ?getIncomingPacketsPerSecond@ConnectionManager@@ present-unmatched
Real ConnectionManager::getIncomingPacketsPerSecond( void )
{
	if (m_transport)
		return m_transport->getIncomingPacketsPerSecond();
	else
	  return 0.0;
}

/**
 * Return the number of outgoing bytes per second averaged over the last 30 sec.
 */
// ?getOutgoingBytesPerSecond@ConnectionManager@@ present-unmatched
Real ConnectionManager::getOutgoingBytesPerSecond( void )
{
	if (m_transport)
		return m_transport->getOutgoingBytesPerSecond();
	else
	  return 0.0;
}

/**
 * Return the number of outgoing packets per second averaged over the last 30 sec.
 */
// ?getOutgoingPacketsPerSecond@ConnectionManager@@ present-unmatched
Real ConnectionManager::getOutgoingPacketsPerSecond( void )
{
	if (m_transport) {
		return m_transport->getOutgoingPacketsPerSecond();
	} else {
	  return 0.0;
	}
}

/**
 * Return the number of bytes not from generals clients received per second averaged over the last 30 sec.
 */
// ?getUnknownBytesPerSecond@ConnectionManager@@ present-unmatched
Real ConnectionManager::getUnknownBytesPerSecond( void )
{
	if (m_transport)
		return m_transport->getUnknownBytesPerSecond();
	else
	  return 0.0;
}

/**
 * Return the number ov packets not from generals clients received per second averaged over the last 30 sec.
 */
// ?getUnknownPacketsPerSecond@ConnectionManager@@ present-unmatched
Real ConnectionManager::getUnknownPacketsPerSecond( void )
{
	if (m_transport)
		return m_transport->getUnknownPacketsPerSecond();
	else
	  return 0.0;
}

/**
 * Return the smallest packet arrival cushion since this was last called.
 */
// ?getPacketArrivalCushion@ConnectionManager@@ present-unmatched
UnsignedInt ConnectionManager::getPacketArrivalCushion() {
	UnsignedInt retval = m_smallestPacketArrivalCushion;
	m_smallestPacketArrivalCushion = -1;
	return retval;
}

// ?sendChat@ConnectionManager@@ present-unmatched
void ConnectionManager::sendChat(UnicodeString text, Int playerMask, UnsignedInt executionFrame)
{
	NetChatCommandMsg *msg = newInstance(NetChatCommandMsg);
	msg->setText(text);
	msg->setPlayerMask(playerMask);
	msg->setPlayerID(m_localSlot);
	msg->setID(0);
	msg->setExecutionFrame(executionFrame);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
	{
		msg->setID(GenerateNextCommandID());
	}
	DEBUG_LOG(("Chat message has ID of %d, mask of %8.8X, text of %ls\n", msg->getID(), msg->getPlayerMask(), msg->getText().str()));

	sendLocalCommand(msg, 0xff ^ (1 << m_localSlot));
	processChat(msg);

	msg->detach();
}

// ?sendDisconnectChat@ConnectionManager@@ present-unmatched
void ConnectionManager::sendDisconnectChat(UnicodeString text) {
	NetDisconnectChatCommandMsg *msg = newInstance(NetDisconnectChatCommandMsg);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}
	msg->setText(text);

	sendLocalCommandDirect(msg, 0xff ^ (1 << m_localSlot));
	processDisconnectChat(msg);
}

// ConnectionManager::sendFileAnnounce is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_sendFileAnnounce.cpp (0x004D2D6A).

// ConnectionManager::sendFile is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_sendFile.cpp (0x004D1927).

// ConnectionManager::getFileTransferProgress is defined with its retail-matched body in Code/GameEngine/Source/Common/ConnectionManagerRva004D28C6.cpp (0x004D28C6).


// ?voteForPlayerDisconnect@ConnectionManager@@ present-unmatched
void ConnectionManager::voteForPlayerDisconnect(Int slot) {
	if (m_disconnectManager != NULL) {
		m_disconnectManager->voteForPlayerDisconnect(slot, this);
	}
}

#pragma optimize("s", on)
// Reference leads: ZH ConnectionManager.cpp and BFME1 4adca1fbe7 native_connection_timing.cpp.
// BFME2 captures frame/time together and stamps frame+1; frameData is +12104.
// BFME2 direct-send: native004CF6E4..004CF799; WB ConnectionManager::sendLocalCommandDirect.
struct ConnectionManagerSendLayout {
 char unknown00[4]; Connection* connections[8];
 char unknown24[0x12024-0x24]; Transport* transport; unsigned localSlot; unsigned routerSlot;
 char unknown12030[0x12104-0x12030]; FrameDataManager* frameData[8];
};
template<class T> inline T& connectionField(void* object,unsigned offset) { return *(T*)((char*)object+offset); }
// BFME1 4adca1fbe7 ConnectionManager_initTransport.cpp; native BFME2 size41148h,
// manager transport12024 and address12050; reset provider004D5496.
void ConnectionManager::initTransport() {
 ConnectionManagerSendLayout* layout=(ConnectionManagerSendLayout*)this;
 if(layout->transport) {
  Transport* previous=layout->transport;
  // Native invokes the complete nonvirtual destructor, then releases allocation.
  previous->Transport::~Transport();
  ::operator delete(previous);
  layout->transport=0;
 }
 layout->transport=new Transport;
 layout->transport->Rva004D5496();
 layout->transport->init((const TransportAddress*)((char*)this+0x12050));
}

void ConnectionManager::sendLocalCommandDirect(NetCommandMsg* msg,UnsignedByte relay) {
 ConnectionManagerSendLayout* layout=(ConnectionManagerSendLayout*)this;
 msg->attach();
 if(msg->getExecutionFrame()==0xffffffff) {
  unsigned frame=connectionField<unsigned>(TheGameLogic,0x40);
  unsigned stamp=connectionField<unsigned>(TheGameLogic,0x38);
  msg->SetTimestamp(stamp);
  msg->setExecutionFrame(frame+1);
 } else if(msg->GetTimestamp()==0xffffffff) msg->SetTimestamp(connectionField<unsigned>(TheGameLogic,0x38));
 if(relay & (1 << layout->localSlot)) {
  if(IsCommandSynchronized(msg->getNetCommandType())) {
   if(layout->localSlot<8 && layout->frameData[layout->localSlot]) layout->frameData[layout->localSlot]->addNetCommandMsg(msg);
  }
 }
 for(int i=0;i<8;++i) {
  if(relay & (1 << i)) {
   if(layout->connections[i]) {
    UnsignedByte mask=1 << i;
    layout->connections[i]->sendNetCommandMsg(msg,mask);
   }
  }
 }
 msg->detach();
}

Int ConnectionManager::getNumPlayers()
{
	Int retval = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (isPlayerConnected(i)) {
			++retval;
		}
	}

	return retval;
}

// BFME1 4adca1fbe7315fb2d128d1c87c7b7c7470248a46 native_connection_timing.cpp.
// Native 004CF9DF..004CFAC0; WB 01392F60 notifyOthersOfCurrentFrame.
// The existing BFME2 no-argument identity is shared with updateDisconnectStatus.
class Rva004D59B8 : public NetCommandMsg {
public: Rva004D59B8();
private: unsigned m_disconnectFrame;
};
class Rva004D57AE { public: void setPlayerIndex(unsigned); };
class BFMEConnectionManager { public: void sendDisconnectFrameCommand(); };
void BFMEConnectionManager::sendDisconnectFrameCommand() {
 unsigned frame=connectionField<unsigned>(TheGameLogic,0x40);
 Rva004D59B8* msg=::new Rva004D59B8;
 ConnectionManagerSendLayout* layout=(ConnectionManagerSendLayout*)this;
 msg->setPlayerID(layout->localSlot);
 // Retail folds the +1C frame setter with the already rowed +1C word setter.
 ((Rva004D57AE*)msg)->setPlayerIndex(frame);
 if((unsigned char)DoesCommandRequireACommandID(msg->getNetCommandType())) msg->setID(GenerateNextCommandID());
 ((ConnectionManager*)this)->sendLocalCommandDirect(msg,(unsigned char)~(unsigned char)(1<<layout->localSlot));
 if(connectionField<DisconnectManager*>(this,0x12100)) {
  NetCommandRef* ref=new NetCommandRef(msg);
  ref->setRelay((unsigned char)(1<<layout->localSlot));
  connectionField<DisconnectManager*>(this,0x12100)->processDisconnectCommand(ref,(ConnectionManager*)this);
  ref->NetCommandRef::~NetCommandRef();
  ::operator delete(ref);
 }
 msg->detach();
}

#pragma optimize("", on)

// ?updateLoadProgress@ConnectionManager@@ present-unmatched
void ConnectionManager::updateLoadProgress( Int progress )
{
	NetProgressCommandMsg *msg = newInstance(NetProgressCommandMsg);
	msg->setPercentage( progress );
	msg->setPlayerID( m_localSlot );
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
		msg->setID(GenerateNextCommandID());
	}
	processProgress(msg);
	sendLocalCommand(msg, 0xff ^ (1 << m_localSlot));

	msg->detach();
}

// ?loadProgressComplete@ConnectionManager@@ present-unmatched
void ConnectionManager::loadProgressComplete()
{
	NetCommandMsg *msg = newInstance(NetCommandMsg);
	msg->setPlayerID( m_localSlot );
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
		msg->setID(GenerateNextCommandID());
	}
	msg->setNetCommandType(NETCOMMANDTYPE_LOADCOMPLETE);
	processLoadComplete(msg);
	sendLocalCommand(msg, 0xff ^ (1 << m_localSlot));

	msg->detach();
}

// ?sendTimeOutGameStart@ConnectionManager@@ present-unmatched
void ConnectionManager::sendTimeOutGameStart()
{
	NetCommandMsg *msg = newInstance(NetCommandMsg);
	msg->setPlayerID( m_localSlot );
	msg->setNetCommandType(NETCOMMANDTYPE_TIMEOUTSTART);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
		msg->setID(GenerateNextCommandID());
	}
	processTimeOutGameStart(msg);
	sendLocalCommand(msg, 0xff ^ (1 << m_localSlot));

	msg->detach();
}

// ?isPacketRouter@ConnectionManager@@ present-unmatched
Bool ConnectionManager::isPacketRouter( void )
{
	return m_localSlot == m_packetRouterSlot;
}

// ?getAverageFPS@ConnectionManager@@ present-unmatched
Int ConnectionManager::getAverageFPS( void )
{
	return m_frameMetrics.getAverageFPS();
}

// ?getSlotAverageFPS@ConnectionManager@@ present-unmatched
Int ConnectionManager::getSlotAverageFPS(Int slot) {
	if ((slot < 0) || (slot >= MAX_SLOTS)) {
		return -1;
	}
	if ((m_packetRouterSlot != m_localSlot) && (slot == m_localSlot)) {
		// our framerate data isn't valid for other players unless we are the
		// packet router, so don't fake someone out.
		return -1;
	}
	return m_fpsAverages[slot];
}

#if defined(_DEBUG) || defined(_INTERNAL)
// ?debugPrintConnectionCommands@ConnectionManager@@ present-unmatched
void ConnectionManager::debugPrintConnectionCommands() {
	DEBUG_LOG(("ConnectionManager::debugPrintConnectionCommands - begin commands\n"));
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_connections[i] != NULL) {
			DEBUG_LOG(("ConnectionManager::debugPrintConnectionCommands - commands for connection %d\n", i));
			m_connections[i]->debugPrintCommands();
		}
	}
	DEBUG_LOG(("ConnectionManager::debugPrintConnectionCommands - end commands\n"));
}
#endif

// ?notifyOthersOfCurrentFrame@ConnectionManager@@ present-unmatched
void ConnectionManager::notifyOthersOfCurrentFrame(Int frame) {
	NetDisconnectFrameCommandMsg *msg = newInstance(NetDisconnectFrameCommandMsg);

	msg->setPlayerID(m_localSlot);
	msg->setDisconnectFrame(frame);
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}

	DEBUG_LOG(("ConnectionManager::notifyOthersOfCurrentFrame - sending disconnect frame of %d, command ID = %d\n", frame, msg->getID()));
	sendLocalCommandDirect(msg, 0xff ^ (1 << m_localSlot));
	NetCommandRef *ref = NEW_NETCOMMANDREF(msg);
	ref->setRelay(1 << m_localSlot);
	m_disconnectManager->processDisconnectCommand(ref, this);
	ref->deleteInstance();

	msg->detach();

	DEBUG_LOG(("ConnectionManager::notifyOthersOfCurrentFrame - start screen on debug stuff\n"));
#if defined(_DEBUG) || defined(_INTERNAL)
	debugPrintConnectionCommands();
#endif
}

// ?notifyOthersOfNewFrame@ConnectionManager@@ present-unmatched
void ConnectionManager::notifyOthersOfNewFrame(UnsignedInt frame) {
	NetDisconnectScreenOffCommandMsg *msg = newInstance(NetDisconnectScreenOffCommandMsg);

	msg->setPlayerID(m_localSlot);
	msg->setNewFrame(frame);
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}

	sendLocalCommandDirect(msg, 0xff ^ (1 << m_localSlot));
	NetCommandRef *ref = NEW_NETCOMMANDREF(msg);
	ref->setRelay(1 << m_localSlot);
	m_disconnectManager->processDisconnectCommand(ref, this);
	ref->deleteInstance();

	msg->detach();
}

// ConnectionManager::sendFrameDataToPlayer is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManagerO1.cpp (0x004D04A4).

// ?sendSingleFrameToPlayer@ConnectionManager@@ present-unmatched
void ConnectionManager::sendSingleFrameToPlayer(UnsignedInt playerID, UnsignedInt frame) {
	if ((TheGameLogic->getFrame() - FRAMES_TO_KEEP) > frame) {
		DEBUG_LOG(("ConnectionManager::sendSingleFrameToPlayer - player %d requested frame %d when we are on frame %d, this is too far in the past.\n", playerID, frame, TheGameLogic->getFrame()));
		return;
	}

	UnsignedByte relay = 1 << playerID;

	DEBUG_LOG(("ConnectionManager::sendFrameDataToPlayer - sending data for frame %d\n", frame));
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if ((m_frameData[i] != NULL) && (i != playerID)) { // no need to send his own commands to him.
			NetCommandList *list = m_frameData[i]->getFrameCommandList(frame);
			if (list != NULL) {
				NetCommandRef *ref = list->getFirstMessage();
				while (ref != NULL) {
					DEBUG_LOG(("ConnectionManager::sendFrameDataToPlayer - sending command %d from player %d to player %d using relay 0x%x\n", ref->getCommand()->getID(), i, playerID, relay));
					sendLocalCommandDirect(ref->getCommand(), relay);
					ref = ref->getNext();
				}
			}
			UnsignedInt frameCommandCount = m_frameData[i]->getFrameCommandCount(frame);
			NetFrameCommandMsg *msg = newInstance(NetFrameCommandMsg);
			msg->setExecutionFrame(frame);
			msg->setCommandCount(frameCommandCount);
			if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
				msg->setID(GenerateNextCommandID());
			}
			msg->setPlayerID(i);
			DEBUG_LOG(("ConnectionManager::sendFrameDataToPlayer - sending frame info from player %d to player %d for frame %d with command count %d and ID %d and relay %d\n", i, playerID, msg->getExecutionFrame(), msg->getCommandCount(), msg->getID(), relay));
			sendLocalCommandDirect(msg, relay);
			msg->detach();
		}
	}
}

// ?getNextPacketRouterSlot@ConnectionManager@@ present-unmatched
UnsignedInt ConnectionManager::getNextPacketRouterSlot(UnsignedInt playerID) {
	Int index = 0;
	while ((index < (MAX_SLOTS-1)) && (m_packetRouterFallback[index] != playerID)) {
		++index;
	}
	++index;
	return m_packetRouterFallback[index];
}

// ?requestFrameDataResend@ConnectionManager@@ present-unmatched
void ConnectionManager::requestFrameDataResend(Int playerID, UnsignedInt frame) {
	NetFrameResendRequestCommandMsg *msg = newInstance(NetFrameResendRequestCommandMsg);
	msg->setPlayerID(m_localSlot);
	msg->setFrameToResend(frame);
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}

	if (isPlayerConnected(playerID) == FALSE) {
		playerID = 0;
		while ((playerID < MAX_SLOTS) && (isPlayerConnected(playerID) == FALSE)) {
			++playerID;
		}
	}

	if (playerID < MAX_SLOTS) {
		sendLocalCommandDirect(msg, 1 << playerID);
	}

	msg->detach();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?find@FontCharMap@@QAEPAUFontCharNode@@ABG@Z=??$_M_find@G@?$_Rb_tree@GU?$pair@$$CBGVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBGVAsciiString@@@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGVAsciiString@@@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBGVAsciiString@@@_STL@@@1@ABG@Z")
