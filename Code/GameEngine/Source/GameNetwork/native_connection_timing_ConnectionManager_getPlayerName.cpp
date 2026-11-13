// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// platformsdk
//
// ?getPlayerName@ConnectionManager@@QAE?AVUnicodeString@@H@Z
// retail 0x004D0198, 61 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/native_connection_timing.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <string.h>
#include <windows.h>
#include <new>
#include <stdlib.h>

// TU-scoped extension of the canonical StringInline owning ABI for format().
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

// Retail string headers store ushort length/capacity before the text at +8.
// StringInline supplies the owning ABI; this local view supplies comparison.
struct BFMEAsciiStringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};
static inline int filePathLength(const AsciiString &text)
{
	BFMEAsciiStringHeader *data = *reinterpret_cast<BFMEAsciiStringHeader * const *>(&text);
	return data ? data->length : 0;
}
static inline int compareFilePaths(const AsciiString &left, const AsciiString &right)
{
	int rightLength = filePathLength(right);
	const char *rightText = right.str();
	int leftLength = filePathLength(left);
	const char *leftText = left.str();
	int length = leftLength < rightLength ? leftLength : rightLength;
	int result = memcmp(leftText, rightText, length);
	return result ? result : leftLength - rightLength;
}

typedef std::map<unsigned short, AsciiString> FileCommandMap;
typedef std::map<unsigned short, unsigned char> FileMaskMap;
typedef std::map<unsigned short, int> FileProgressMap;

typedef bool Bool;
typedef unsigned short UnsignedShort;

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_ROUTERFALLBACK = 22
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
#include "../../Include/GameNetwork/NetCommandMsg.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class GameMessage;
class GameMessageArgument;

// The constructor at RVA 0x00674A40 copies a GameMessage's type and arguments.
// Its 0x30-byte allocation and field stores agree with the upstream layout.
Bool DoesCommandRequireACommandID(NetCommandType type);
Bool CommandRequiresDirectSend(NetCommandMsg *msg);
Bool IsCommandSynchronized(NetCommandType type);
UnsignedShort GenerateNextCommandID();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
	public:
	NetCommandRef(NetCommandMsg *message);
	void setRelay(unsigned char value) { relay = value; }
	unsigned char getRelay() { return relay; }
	NetCommandMsg *getCommand() { return msg; }
	NetCommandRef *getNext() { return next; }
	~NetCommandRef();
	NetCommandMsg *msg;
	NetCommandRef *next;
	NetCommandRef *prev;
	unsigned char relay;
	unsigned int m_timeLastSent;
};

#include "../../Include/GameNetwork/NetCommandListClass.h"

// BFME-only type 22 broadcasts router succession order. The role-derived
// name follows producer 0x00666000 and disconnectPlayer consumer 0x00666300.
class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	NetPlayerLeaveCommandMsg();
	void setLeavingPlayerID(unsigned char playerID);
private:
	unsigned char m_leavingPlayerID;
};
class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	NetDestroyPlayerCommandMsg();
	void setPlayerIndex(unsigned int playerID);
private:
	unsigned int m_playerIndex;
};
// Retail copies this address as two dwords and aligns its local copy to eight
// bytes. The storage view expresses that alignment without changing ip/port.
#include "../../Include/Common/NetPacketAddress.h"
#pragma pack(push, 1)
struct TransportMessage
{
	unsigned int crc;
	unsigned char data[0x400];
	int length;
	unsigned int addr;
	unsigned short port;
};
#pragma pack(pop)
class BFMETransport
{
public:
	char unknown[0x20700];
	TransportMessage received[128];
};
// Packet fields remain four-packed: address is at +0x1E4 and sizeof is 0x200.
#pragma pack(push, 4)
#pragma pack(pop)
#include "../../Include/GameNetwork/NetCommandWrapperListClass.h"
class Network;
struct BFMEReceiveNetworkVTable
{
	void *unknown[55];
	Bool (__fastcall *isRouterLeavePending)(Network *network);
};
class Network
{
public:
	Bool isRouterLeavePending() { return m_vtable->isRouterLeavePending(this); }
private:
	BFMEReceiveNetworkVTable *m_vtable;
};
extern Network *TheNetwork;
Bool CommandRequiresAck(NetCommandMsg *msg);

class BFMENetRequestPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestPlayerLeaveCommandMsg();
	int getRequestedPlayerID();
	void setRequestedPlayerID(int player);
private:
	int m_requestedPlayer;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class GameClient;

struct GameClientVTable
{
	void *unknown[26];
	unsigned int (__fastcall *getFrame)(GameClient *gameClient);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
#include "../../Include/GameClient/GameClientClass.h"

extern GameClient *TheGameClient;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;
extern unsigned int g_dword010EAD50;
extern unsigned int g_lastPacketRouterStallFrame;
extern int FRAMES_TO_KEEP;

template <class T> const T &frameMaximum(const T &lhs, const T &rhs)
{
	return rhs > lhs ? rhs : lhs;
}

template <class T> const T &frameMinimum(const T &lhs, const T &rhs)
{
	return rhs < lhs ? rhs : lhs;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameDataManager.h
#include "../../Include/GameNetwork/FrameDataManagerClass.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
class Connection
{
	public:
	void sendNetCommandMsg(NetCommandMsg *msg, unsigned char relay);
	long getLastTimeSent() { return m_lastTimeSent; }
	int m_openState;
	char m_unknown04[0x10];
	UnicodeString m_playerName;
	char m_unknown18[8];
	float m_averageLatency;
	char m_unknown24[0x324];
	long m_lastTimeSent;
	unsigned int m_lastHeardFrom;
};

// Retail's real ConnectionManager, named so these two bodies carry their true
// mangled names; the BFME-native helpers below keep the BFMEConnectionManager
// name because theirs are unknown.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class DisconnectManager;
class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectChatCommandMsg();
	void setText(UnicodeString text);
private:
	UnicodeString m_text;
};
// These BFME-only request/reply messages carry narrow strings at +0x1C/+0x20.
class BFMENetRequestGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	AsciiString getText1C();
};
// BFME adds two C-string accessors after the reference interface's eleven slots.
// Their names describe use here; no claim of recovered retail source names.
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void unknown00(); virtual void unknown04(); virtual void unknown08();
	virtual void unknown0C(); virtual void unknown10(); virtual void unknown14();
	virtual void unknown18(); virtual void unknown1C(); virtual void unknown20();
	virtual void unknown24(); virtual void unknown28();
	virtual const char *getReplyIdentityText();
	virtual const char *getAuthSecretText();
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern "C" char *goastrdup(const char *text) throw();
extern "C" char *GenerateAuthA(char *challenge, char *password, char *response);

class NetChatCommandMsg : public NetCommandMsg
{
public:
	NetChatCommandMsg();
	void setText(UnicodeString text);
	void setPlayerMask(int playerMask);
private:
	UnicodeString m_text;
	int m_playerMask;
};

class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectFrameCommandMsg();
	void setDisconnectFrame(unsigned int frame);
private:
	unsigned int m_disconnectFrame;
};

class NetProgressCommandMsg : public NetCommandMsg
{
public:
	NetProgressCommandMsg();
	void setPercentage(unsigned char percent);
	unsigned char getPercentage();
private:
	unsigned char m_percent;
};
class NetFileCommandMsg : public NetCommandMsg
{
public:
	AsciiString getRealFilename();
	unsigned char *getFileData();
	unsigned int getFileLength();
};
#include "../../Include/Common/File.h"
#include "../../Include/Common/FileSystem.h"
extern FileSystem *TheFileSystem;

// BFME LAN chat passes an IP/port record by address, unlike the ZH scalar IP.
struct BFMEFileTransferAddress
{
	unsigned int ip;
	unsigned short port;
	BFMEFileTransferAddress(unsigned int value, unsigned short portValue) : ip(value), port(portValue) {}
};
#include "../../Include/GameNetwork/LANAPI.h"
extern LANAPI *TheLAN;

class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	NetFileAnnounceCommandMsg();
	void setRealFilename(AsciiString filename);
	void setPlayerMask(unsigned char playerMask);
	void setFileID(unsigned short fileID);
private:
	AsciiString m_filename;
	unsigned short m_fileID;
	unsigned char m_playerMask;
};
class NetFileProgressCommandMsg : public NetCommandMsg
{
public:
	NetFileProgressCommandMsg();
	void setFileID(unsigned short commandID);
	void setProgress(int progress);
private:
	unsigned short m_fileID;
	int m_progress;
};
class ConnectionManager
{
public:
	void sendLocalCommand(NetCommandMsg *msg, unsigned char relay);
	void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay);
	int getNumPlayers();
	void flushConnections();
	void processChat(NetChatCommandMsg *msg);
	void sendDisconnectChat(UnicodeString text);
	UnicodeString getPlayerName(int slot);
	int getFileTransferProgress(int playerID, AsciiString path);
	unsigned short sendFileAnnounce(AsciiString path, unsigned char playerMask);
	friend class BFMEConnectionManager;
	unsigned int getPacketRouterSlot();

private:
	void processDisconnectChat(NetDisconnectChatCommandMsg *msg);
	void processProgress(NetProgressCommandMsg *msg);
	void processFileAnnounce(NetFileAnnounceCommandMsg *msg);
	void processFile(NetFileCommandMsg *msg);
	void processFileProgress(NetFileProgressCommandMsg *msg);
	char m_unknown00[4];
	Connection *m_connections[8];
	char m_unknown24[0x12004];
	unsigned int m_localSlot;
	unsigned int m_packetRouterSlot;
	char m_unknown12030[0x28];
	UnicodeString m_localPlayerName;
	char m_unknown1205C[0x88];
	FrameDataManager *m_frameData[8];
	char m_unknown12104[0x14];
	FileCommandMap m_fileCommandMap;
	FileMaskMap m_fileRecipientMaskMap;
	FileProgressMap m_fileProgressMap[8];
};

// Role-derived local identity: the native manager embeds nine 65536-bit
// command-ID histories. The retail source class name remains unrecovered.
class Gen_00667F30
{
public:
	void bfmeClearRange(UnsignedShort commandID);
};

class BFMECommandIDHistory
{
public:
	Bool accept(UnsignedShort commandID, unsigned int frame);
private:
	unsigned int word(unsigned int id) const { return m_bits[id >> 5]; }
	unsigned int &word(unsigned int id) { return m_bits[id >> 5]; }
	Bool isSet(unsigned int id) const { return (word(id) & (1u << (id & 31))) != 0; }
	void set(unsigned int id) { word(id) |= 1u << (id & 31); }
	unsigned int m_bits[0x800];
};

#include "../../Include/GameNetwork/BFMEConnectionManager.h"

// Retail's real DisconnectManager, for the one body here whose true mangled name
// is known. Protected, to match the IAE in the decorated name.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
public:
	// Public in the reference's header, so QAE in the decorated names.
	void processDisconnectCommand(NetCommandRef *ref, ConnectionManager *conMgr);
	DisconnectManager();
	void init();
protected:
	// Protected there, so IAE.
	void processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
};

// Returns an owning string copy from the local name or a peer connection.
// ILT 0x00012A62 and the named DisconnectManager callers prove the return ABI.
UnicodeString ConnectionManager::getPlayerName(int slot)
{
	if (slot == m_localSlot)
		return m_localPlayerName;
	if (m_connections[slot])
		return m_connections[slot]->m_playerName;
	return UnicodeString::TheEmptyString;
}
