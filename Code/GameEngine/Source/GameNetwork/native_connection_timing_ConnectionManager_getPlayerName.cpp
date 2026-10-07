// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
//
// ?getPlayerName@ConnectionManager@@QAE?AVUnicodeString@@H@Z
// retail 0x004D0198, 61 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/native_connection_timing.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// class-gate: allow AsciiString the donor's own view; the placed body is byte-exact under it
// class-gate: allow UnicodeString the donor's own view; the placed body is byte-exact under it
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <string.h>

// TU-scoped extension of the canonical StringInline owning ABI for format().
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format(UnicodeString pattern, ...);
	const unsigned short *str( void ) const;

	// The empty UnicodeString every retail client copies from.  Retail exports
	// exactly one name for the datum at 0x01336E54,
	// ?TheEmptyString@UnicodeString@@2V1@B (exports.csv:1340), which is what
	// WWLib's UnicodeString::TheEmptyString mangles to when it is const
	// (unicode_string.h:12); MSVC writes the trailing A only for a non-const
	// static member (measured: 'static C M' -> ?M@C@@2VC@@A, 'static const C M'
	// -> ?M@C@@2VC@@B), so the const here is what names retail's symbol and
	// drops the TU-local ?BFMEEmptyPlayerName alias from
	// ConnectionManager::getPlayerName.
	static const UnicodeString TheEmptyString;
};

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

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

typedef bool Bool;
typedef unsigned short UnsignedShort;

void __cdecl operator delete(void *block) throw();

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
class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();
	virtual int getSortNumber();
	virtual void prepareForRelay();
	void attach();
	void detach();

	void setExecutionFrame(unsigned int frame) { m_executionFrame = frame; }
	unsigned int getExecutionFrame() { return m_executionFrame; }
	void setPlayerID(unsigned int playerID) { m_playerID = playerID; }
	unsigned int getPlayerID() { return m_playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	UnsignedShort getID() { return m_id; }
	void setNetCommandType(NetCommandType type) { m_commandType = type; }
	NetCommandType getNetCommandType() { return m_commandType; }

protected:
	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	int m_referenceCount;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	NetFrameCommandMsg() : NetCommandMsg()
	{
		m_frame = 0;
		m_playerFrame = 0;
		m_commandCount = -1;
		m_commandType = NETCOMMANDTYPE_FRAMEINFO;
	}

	void setFrame(unsigned int frame) { m_frame = frame; }
	unsigned int getFrame() { return m_frame; }
	unsigned int getPlayerFrame() { return m_playerFrame; }
	void setPlayerFrame(unsigned int frame) { m_playerFrame = frame; }
	int getCommandCount() { return m_commandCount; }
	void setCommandCount(int count) { m_commandCount = count; }

private:
	unsigned int m_frame;
	unsigned int m_playerFrame;
	int m_commandCount;
};

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	unsigned char getOriginalPlayerID();
	unsigned int getOriginalExecutionFrame() { return m_originalExecutionFrame; }
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	NetAckStage2CommandMsg(NetCommandMsg *msg);
	UnsignedShort getCommandID();
	unsigned char getOriginalPlayerID();
	unsigned int getOriginalExecutionFrame() { return m_originalExecutionFrame; }
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class GameMessage;
class GameMessageArgument;

// The constructor at RVA 0x00674A40 copies a GameMessage's type and arguments.
// Its 0x30-byte allocation and field stores agree with the upstream layout.
class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);

private:
	int m_numArgs;
	int m_argSize;
	int m_type;
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};

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

class NetCommandList
{
public:
	virtual ~NetCommandList();
	NetCommandRef *getFirstMessage() { return m_first; }
	NetCommandRef *findMessage(UnsignedShort id, unsigned char player);
	NetCommandRef *findMessage(UnsignedShort id, unsigned char player, unsigned int frame);
	void removeMessage(NetCommandRef *ref);
private:
	NetCommandRef *m_first;
};

// BFME-only type 22 broadcasts router succession order. The role-derived
// name follows producer 0x00666000 and disconnectPlayer consumer 0x00666300.
class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	BFMENetRouterFallbackCommandMsg() { m_commandType = NETCOMMANDTYPE_ROUTERFALLBACK; }
	void setPlayerOrder(const int *players);
private:
	int m_players[8];
};

class NetKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetKeepAliveCommandMsg();
};

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
struct NetPacketAddress
{
	union
	{
		struct { unsigned int ip; unsigned short port; };
		unsigned __int64 storage;
	};
};
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
class NetPacket
{
public:
	NetPacket(TransportMessage *msg);
	virtual ~NetPacket();
	NetCommandList *getCommandList();
	NetPacketAddress getAddress() { return m_address; }
private:
	unsigned char m_packet[0x1DC];
	int m_packetLength;
	NetPacketAddress m_address;
	int m_numCommands;
	NetCommandRef *m_lastCommand;
	unsigned int m_lastFrame;
	unsigned short m_lastCommandID;
	unsigned char m_lastPlayerID;
	unsigned char m_lastCommandType;
	unsigned char m_lastRelay;
};
#pragma pack(pop)
class NetCommandWrapperList
{
public:
	NetCommandList *getReadyCommands();
	void processWrapper(NetCommandRef *ref);
	int getPercentComplete(unsigned short commandID);
};
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

class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
	unsigned int getLeaveFrame();
	int getLeavingPlayerID();
};

class BFMENetRequestFrameDataCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestFrameDataCommandMsg();
	void setFirstFrame(unsigned int firstFrame);
	void setLastFrame(unsigned int lastFrame);
	unsigned int getFirstFrame();
	unsigned int getLastFrame();
private:
	unsigned int m_firstFrame;
	unsigned int m_lastFrame;
};

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
class GameLogic
{
	public:
	void processProgressComplete(int playerID);
	void processProgress(int playerID, int percentage);
	void timeOutGameStart();
	unsigned int getFrame() { return frame; }
	char unknown[0x3C];
	unsigned int frame;
};

extern GameLogic *TheGameLogic;

class GameClient;

struct GameClientVTable
{
	void *unknown[26];
	unsigned int (__fastcall *getFrame)(GameClient *gameClient);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	unsigned int getFrame() { return vtable->getFrame(this); }

private:
	GameClientVTable *vtable;
};

extern GameClient *TheGameClient;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char unknown[0xCB4];
	unsigned int m_networkRunAheadSlack;
	char unknownCB8[0xF4];
	Bool commandIDFiltering; // retail flag at +0xDAC; INI key not recovered here
};

extern GlobalData *TheWritableGlobalData;
extern unsigned int g_dword010EAD50;
extern unsigned int g_lastPacketRouterStallFrame;
extern int FRAMES_TO_KEEP;

template <class T> const T &frameMaximum(const T &a, const T &b)
{
	return b > a ? b : a;
}

template <class T> const T &frameMinimum(const T &a, const T &b)
{
	return b < a ? b : a;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameDataManager.h
class FrameDataManager
{
public:
	NetCommandList *getFrameCommandList(unsigned int frame);
	Bool getIsQuitting();
	unsigned int getCommandCount(unsigned int frame);
	unsigned int getFrameCommandCount(unsigned int frame);
	NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
	void setFrameCommandCount(unsigned int frame, unsigned int count);
};

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
class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);
	void setText20(AsciiString text);
private:
	AsciiString m_text1C;
	AsciiString m_text20;
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
extern "C" __declspec(dllimport) void __cdecl free(void *memory);

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
class File
{
public:
	enum { WRITE = 2, CREATE = 8, BINARY = 0x40 };
	virtual void unknown00();
	virtual void unknown04();
	virtual void close();
	virtual void unknown0C();
	virtual int write(const void *buffer, int length);
	virtual void unknown14(); virtual void unknown18(); virtual void unknown1C();
	virtual void unknown20(); virtual void unknown24(); virtual void unknown28();
	virtual int size();
};
class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
	File *openFile(const char *filename, int flags);
};
extern FileSystem *TheFileSystem;

// BFME LAN chat passes an IP/port record by address, unlike the ZH scalar IP.
struct BFMEFileTransferAddress
{
	unsigned int ip;
	unsigned short port;
	BFMEFileTransferAddress(unsigned int value, unsigned short portValue) : ip(value), port(portValue) {}
};
class LANAPI
{
public:
	virtual void unknown00();
	virtual void unknown04();
	virtual void unknown08();
	virtual void unknown0C();
	virtual void unknown10();
	virtual void unknown14();
	virtual void unknown18();
	virtual void unknown1C();
	virtual void unknown20();
	virtual void unknown24();
	virtual void unknown28();
	virtual void unknown2C();
	virtual void unknown30();
	virtual void unknown34();
	virtual void unknown38();
	virtual void unknown3C();
	virtual void unknown40();
	virtual void unknown44();
	virtual void unknown48();
	virtual void unknown4C();
	virtual void unknown50();
	virtual void unknown54();
	virtual void unknown58();
	virtual void unknown5C();
	virtual void unknown60();
	virtual void unknown64();
	virtual void unknown68();
	virtual void unknown6C();
	virtual void unknown70();
	virtual void unknown74();
	virtual void unknown78();
	virtual void unknown7C();
	virtual void unknown80();
	virtual void unknown84();
	virtual void unknown88();
	virtual void OnChat(UnicodeString player, const BFMEFileTransferAddress &address,
		UnicodeString message, int format);
};
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
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	unsigned short getWrappedCommandID();
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

class BFMEConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(int playerID);
	Bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);
	Bool hasPacketRouterFrameStall();
	void processRequestFrameDataCommand(void *msg);
	Bool areFrameCommandsComplete(unsigned int frame, Bool debugSpewage);
	int getFrameHeadroom();
	void processInformPlayerLeaveFrameCommand(void *msg);
	void sendFrameInfo();
	Bool processIncomingCommand(void *ref);
	void init();
	void broadcastRouterFallbackPlan();
	Bool isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	void processRequestPlayerLeaveCommand(void *msg);
	void relayCommand(void *ref);
	void update();
	void runRelayPass();
	void destroy();
	void processWrappedCommand(NetCommandRef *ref);
	void sendFileChunk(AsciiString path, unsigned char playerMask, unsigned short commandID);
	void buildPlayerStatusText(void *out);
	void queueLocalCommand(void *msg); // legacy assembly identity; actual ABI is ackCommand below
	void ackCommand(NetCommandRef *ref, NetPacketAddress *source);
	void sendGameCommand(void *msg);
	Bool isDuplicateCommand(NetCommandMsg *msg);
	void sendPlayerLeaveCommands();
	void sendFrameInfoToPlayer(int slot);
	void sendChat(UnicodeString text, int playerMask);
	void sendGameSpyStatsAuthKey(void *key);
	void sendKeepAliveCommand();
	void sendProgressCommand(int percent);
	void sendDisconnectFrameCommand();
	void sendDisconnectScreenOffCommand(int slot);
	void sendRequestPlayerLeaveCommand();
	void sendLoadCompleteCommand();
	void attachPlayersFromGameInfo(void *gameInfo);
	void resolvePlayerFromName(void *msg);
	void processAck(NetCommandMsg *msg);
	void processGameSpyStatsAuthKeyCommand(void *msg);
	void processAckCommand(void *msg);
	void beginPlayerLeave(void *msg);
	void resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame);

private:
	char m_unknown00[4];
	Connection *m_connections[8];
	BFMECommandIDHistory m_commandHistory[9];
	BFMETransport *m_transport;
	int m_localSlot;
	int m_packetRouterSlot;
	unsigned int m_packetRouterFallback[8];
	char m_unknown12050[0xC];
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
	int m_playerState[8];
	unsigned int m_playerClientFrame[8];
	char m_unknown120C0[0x20];
	DisconnectManager *m_disconnectManager;
	FrameDataManager *m_frameData[8];
	NetCommandList *m_pendingCommands;
	NetCommandList *m_pendingRelays;
	NetCommandWrapperList *m_wrapperList;
	unsigned int m_localLeaveStarted;
	char m_unknown12114[4];
	FileCommandMap m_fileCommandMap;
	FileMaskMap m_fileRecipientMaskMap;
	FileProgressMap m_fileProgressMap[8];
};

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

class BFMEDisconnectManager
{
public:
	void update(void *conMgr);
};

struct BFMEPlayerRouterScore
{
	float score;
	int player;
	BFMEPlayerRouterScore *next;
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
