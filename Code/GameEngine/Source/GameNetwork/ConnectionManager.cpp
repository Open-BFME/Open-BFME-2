// cl: /Ireference/shims/connectionnotify /Ireference/shims/connectiontransport /Ireference/shims/transport /Ireference/shims/networkutil /Ireference/shims/framecommandreturn /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// platformsdk
// dxsdk
// Release through the complete nonvirtual destructor and global delete, as the
// verified sendDisconnectFrameCommand does below. Calling inline deleteInstance
// here emits an /O2 scalar deleting destructor that differs from its owned
// /O1 retail body; these calls must not replace that existing provider.
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameNetwork/ConnectionManager.cpp); this unit had no counterpart under Code/.
// Only its rowed bodies remain. The 51 unrowed Zero Hour methods (update,
// processAck*, updateRunAhead, the Transport/DisconnectManager/FrameMetrics
// getters, ...) matched no retail body, no other object referenced them, and
// they made 40 references no object defines (Zero Hour's NetRunAhead*/
// NetFrameResendRequest/NetDisconnect* messages, FrameMetrics, Transport
// statistics, GameLogic::timeOutGameStart). Retail's ConnectionManager
// methods are rowed in their own units, named in the comments below.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../Include/Common/BfmeVciAnchorElem.h"
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
namespace _STL { template <> pair<unsigned short const, AsciiString>::pair(unsigned short const &, AsciiString const &); }


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
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned short const, unsigned char>, _Nonconst_traits<pair<unsigned short const, unsigned char> > >, bool> _Rb_tree<unsigned short, pair<unsigned short const, unsigned char>, _Select1st<pair<unsigned short const, unsigned char> >, less<unsigned short>, allocator<pair<unsigned short const, unsigned char> > >::insert_unique(pair<unsigned short const, unsigned char> const &); }
namespace _STL { template <> pair<unsigned short const, unsigned char>::pair(unsigned short const &, unsigned char const &); }
namespace _STL { template <> _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, less<unsigned short>, allocator<pair<unsigned short const, int> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, less<unsigned short>, allocator<pair<unsigned short const, int> > >::_M_erase(_Rb_tree_node<pair<unsigned short const, int> > *); }
namespace _STL { template <> void _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, less<unsigned short>, allocator<pair<unsigned short const, int> > >::clear(); }
// bfme link decl-only end

// FileCommandMap::operator[]'s two out-of-line helpers are rows spelled for
// trees whose code is the same: 0x0046A9AB is the map<ushort, uchar> tree's
// _M_lower_bound (StlO1Instantiations.cpp) and 0x004D272E the hinted
// map<int, Rva004D272ERecord>::insert (StlSweepR3Rva004D272E.cpp). The
// subscript reaches them through those types; both stay declared only.
struct Rva004D272ERecord { char bytes[1]; };
typedef _STL::map<int, Rva004D272ERecord> Rva004D272EMap;
namespace _STL {
template <> _Rb_tree_node<pair<unsigned short const, unsigned char> > *
_Rb_tree<unsigned short, pair<unsigned short const, unsigned char>,
	_Select1st<pair<unsigned short const, unsigned char> >, less<unsigned short>,
	allocator<pair<unsigned short const, unsigned char> > >::_M_lower_bound(const unsigned short &) const;
template <> Rva004D272EMap::iterator Rva004D272EMap::insert(Rva004D272EMap::iterator, const Rva004D272EMap::value_type &);
}
static __forceinline const Rva004D272EMap::value_type &asRva004D272EValue(const FileCommandMap::value_type &value)
{
	return *(const Rva004D272EMap::value_type *)&value;
}

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

// The progress-map subscript is provided by ConnectionManagerRva004D28C6.cpp.
namespace _STL { template <> int &Rva004D2C8EFileProgressMap::operator[](const unsigned short &key); }

class Rva004D2C8EConnectionManagerLayout
{
public:
	char m_pad[0x12138];
	FileCommandMap s_fileCommandMap;
	FileMaskMap s_fileRecipientMaskMap;
	Rva004D2C8EFileProgressMap s_fileProgressMap[MAX_SLOTS];
};

#pragma optimize("s", on)
namespace _STL {
template <> pair<unsigned short const, AsciiString>::pair(unsigned short const &a, AsciiString const &b)
    : first(a), second(b) {}
}
template <> AsciiString &FileCommandMap::operator[](const unsigned short &key)
{
	typedef _STL::_Rb_tree_node<value_type> *Node;
	typedef _STL::_Rb_tree_node<Rva004D272EMap::value_type> *RecordNode;
	iterator i((Node)((FileMaskMap *)this)->lower_bound(key)._M_node);
	if (i == end() || key_comp()(key, (*i).first))
		i = iterator((Node)((Rva004D272EMap *)this)->insert(
			Rva004D272EMap::iterator((RecordNode)i._M_node),
			asRva004D272EValue(value_type(key, AsciiString())))._M_node);
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
// ConnectionManager::~ConnectionManager is rowed in ConnectionManager_dtor.cpp; the Zero
// Hour copy here was a non-retail second definition. It was also what emitted the
// rowed map<unsigned short,int> dtor; this anchor keeps it emitted (no retail body).
// ?bfmeAnchorFileProgressMapDtor absent-from-retail
void bfmeAnchorFileProgressMapDtor(FileProgressMap *progress)
{
	progress->~FileProgressMap();
}

/**
 * Le constructor
 */
// ConnectionManager::ConnectionManager is rowed in its home unit; this copy was a duplicate definition.

/**
 * Initialize the connection manager and any subsystems.
 */
// ConnectionManager::init is defined with its retail-matched body in Code/GameEngine/Source/Common/ConnectionManagerInit2.cpp (0x004D24A2).


// ConnectionManager::isPlayerConnected is rowed with BFME2's body in
// ConnectionManager_processPlayerLeave.cpp.


/**
 * This is where the non-synchronized network commands should be processed.
 * Return TRUE if the command should not be relayed. Return FALSE if it should be relayed.
 */
// ConnectionManager::processNetCommand is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_processNetCommand.cpp (0x004D2F04).


/**
 * We have received a wrapper for a command too big to fit in a packet.
 */
// processWrapper is owned by ConnectionManager_fileTransfer.cpp.
// The unrowed donor definition here did not reproduce its native body.
// Keep the existing rowed map operations and their instantiated tree helpers
// as library providers after removing their old donor-only caller.
namespace _STL {
template int &map<unsigned short, int>::operator[](const unsigned short &);
template map<unsigned short, AsciiString>::iterator
map<unsigned short, AsciiString>::find(const unsigned short &);
}


// ConnectionManager::processDisconnectChat is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_processDisconnectChat.cpp (0x004D1023).


// ConnectionManager::processFile is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_fileTransfer.cpp (0x004D2B16).

#pragma optimize("s", on)
void ConnectionManager::processFileAnnounce(NetFileAnnounceCommandMsg *msg) 
{
	DEBUG_LOG(("ConnectionManager::processFileAnnounce() - expecting '%s' (%s) in command %d\n", msg->getPortableFilename().str(), msg->getRealFilename().str(), msg->getFileID()));
	UnsignedShort fileID;
	Rva004D2C8EConnectionManagerLayout *layout = (Rva004D2C8EConnectionManagerLayout *)this;
	layout->s_fileCommandMap[(fileID = ((Rva004D5973WordField *)msg)->get())] = ((Rva004D632D *)msg)->rva004D632D();
	layout->s_fileRecipientMaskMap[(fileID = ((Rva004D5973WordField *)msg)->get())] = ((Rva001DCD01ByteField *)msg)->get();
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if ( (1<<i) & ((Rva001DCD01ByteField *)msg)->get() )
		{
			layout->s_fileProgressMap[i][(fileID = ((Rva004D5973WordField *)msg)->get())] = 0;
		}
		else
		{
			layout->s_fileProgressMap[i][(fileID = ((Rva004D5973WordField *)msg)->get())] = 100; // they don't need to get it, so they're already done.
		}
	}
}
#pragma optimize("", on)

// ConnectionManager::processFileProgress is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_fileTransfer.cpp (0x004D2852).

void ConnectionManager::processProgress( NetProgressCommandMsg *msg )
{
	TheGameLogic->processProgress(msg->getPlayerID(), msg->getPercentage());
}


// ConnectionManager::getPacketRouterSlot: defined in ConnectionManagerLocalSlot.cpp (its row's unit).

// ConnectionManager::areAllQueuesEmpty is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_areAllQueuesEmptyTwin_Rva004CF3B9.cpp (0x004CF3B9).


/**
 * Initialize the transport object
 */
// initTransport is defined in the existing size-optimized region below.

/**
 * This is where the commands from the local client are sent to the other clients in
 * the game.  This is also where the local commands are put into the frame data for
 * future execution.
 */

// sendLocalCommand is implemented by ConnectionManager_processAck.cpp.

/**
 * This is a NetCommandMsg that originated on the local computer.  Send this to everyone specified
 * in the relay field.  Commands sent in this way do not go through the packet router.
 */
// sendLocalCommandDirect is defined in the existing size-optimized region below.


// Owned here: only present in a network game, deleted above; retail .data
// starts it at 0 (VA 0x00A048D0).
DisconnectMenu *TheDisconnectMenu = 0;


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


// ConnectionManager::disconnectPlayer is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_disconnectPlayer.cpp (0x004D13F8).


// ConnectionManager::disconnectLocalPlayer: defined in Network_update.cpp (its row's unit).


// ConnectionManager::resendPendingCommands (0x004D016E) is defined with its retail body in ConnectionManager_rva004D00BB.cpp.

// ConnectionManager::getLocalPlayerID: defined in ConnectionManagerLocalSlot.cpp (its row's unit).

// ConnectionManager::getPlayerName is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/native_connection_timing_ConnectionManager_getPlayerName.cpp (0x004D0198).

// ConnectionManager::parseUserList: defined with its retail-matched body in ConnectionManagerParseUserList.cpp (0x004D1616).


// ConnectionManager::sendDisconnectChat is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_sendChat.cpp (0x004D187B).

// ConnectionManager::sendFileAnnounce is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_sendFileAnnounce.cpp (0x004D2D6A).

// ConnectionManager::sendFile is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManager_sendFile.cpp (0x004D1927).

// ConnectionManager::getFileTransferProgress is defined with its retail-matched body in Code/GameEngine/Source/Common/ConnectionManagerRva004D28C6.cpp (0x004D28C6).


// ConnectionManager::voteForPlayerDisconnect: retail's body is the row at 0x004CF90D
// (VslotSmallBodiesBA.cpp); this unit only declares it.

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

// ConnectionManager::getNumPlayers (0x004CF926) is rowed beside isPlayerConnected
// in ConnectionManager_processPlayerLeave.cpp.

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

// ?updateLoadProgress@ConnectionManager@@QAEXH@Z native 0x004CF940..0x004CF9CD 141B.
// Retail allocates with the plain global operator new (0x0002FDA0, push 0x20) and
// calls the 0x004D582B ctor directly, so this is ::new, not the pooled newInstance.
// 0x004D582B is BFME's NetProgressCommandMsg (base ctor, vtable, type 15 at +0x14,
// byte 0 at +0x1C); its ledger row carries the address-derived class name
// Rva004D582B, so the new-expression is spelled through that view and the result
// cast back. setPercentage folds into the 10-byte +0x1C byte setter at 0x0006EDE3
// whose row is an ICF gen-alias; the only resolvable byte-setter spelling at that
// address is the already pinned setDisconnectSlot view (same fold, same store).
class Rva004D582B : public NetCommandMsg {
public:
	Rva004D582B();
private:
	UnsignedByte m_percent;
};
void ConnectionManager::updateLoadProgress( Int progress )
{
	ConnectionManagerSendLayout *layout = (ConnectionManagerSendLayout *)this;
	Rva004D582B *raw = ::new Rva004D582B();
	NetProgressCommandMsg *msg = (NetProgressCommandMsg *)raw;
	((NetDisconnectPlayerCommandMsg *)msg)->setDisconnectSlot((UnsignedByte)progress);
	msg->setPlayerID( layout->localSlot );
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
		msg->setID(GenerateNextCommandID());
	}
	processProgress(msg);
	sendLocalCommandDirect(msg, (unsigned char)~(unsigned char)(1 << layout->localSlot));

	msg->detach();
}

#pragma optimize("", on)


// ConnectionManager::sendFrameDataToPlayer is defined with its retail-matched body in Code/GameEngine/Source/GameNetwork/ConnectionManagerO1.cpp (0x004D04A4).


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?find@FontCharMap@@QAEPAUFontCharNode@@ABG@Z=??$_M_find@G@?$_Rb_tree@GU?$pair@$$CBGVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBGVAsciiString@@@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGVAsciiString@@@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBGVAsciiString@@@_STL@@@1@ABG@Z")
