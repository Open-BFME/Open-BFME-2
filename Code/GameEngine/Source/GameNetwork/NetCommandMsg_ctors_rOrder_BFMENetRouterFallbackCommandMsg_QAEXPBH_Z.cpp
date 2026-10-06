// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// The NetCommandMsg subclass constructors.
//
// Each one identifies itself: it stores its class vptr and stamps its own
// NetCommandType into m_commandType at +0x14 -- the offset CommandRequiresAck
// reads and Connection::doSend tests for FRAMEINFO. Reading the stamped constant
// off a constructor names it, which is how this family was recovered.
//
// The base is the reference's, in the reference's field order, with one BFME
// change: m_executionFrame starts at -1 rather than 0. FrameDataManager's
// addNetCommandMsg reads +8 as the execution frame, so -1 is "not yet bound to a
// frame" instead of "frame zero".
//
//   0x00  vptr
//   0x04  m_timestamp
//   0x08  m_executionFrame     (-1)
//   0x0C  m_playerID
//   0x10  m_id                 (UnsignedShort)
//   0x14  m_commandType
//   0x18  m_referenceCount     (1 -- construction implies an attach)
//
// The base assigns m_commandType = NETCOMMANDTYPE_UNKNOWN last; every derived
// constructor overwrites it, so the compiler elides the base's store and nothing
// is written to +0x14 in a subclass constructor. The standalone base body at
// 0x006735D0 is where that store survives, and it writes -1.
//
// BFME de-pooled this graph like the rest of the netcode, so there is no
// MemoryPoolObject base; the vptr comes from the virtual destructor. Declared
// locally rather than through a shim header because any file under
// inputs/reference/shims/ forces the full gate.

typedef int Int;

enum { MAX_SLOTS = 8 };
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum NetCommandType
{
	// -1, not 0. The standalone base constructor at 0x006735D0 stores -1 into
	// m_commandType; every derived constructor overwrites it, so the elided store
	// hides that in the subclasses.
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
	NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg() {}

	void attach();

	UnsignedShort getID() { return m_id; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }

protected:
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	NetCommandType m_commandType;					// this+0x14
	Int m_referenceCount;							// this+0x18
};

// BFME-only type 22: eight ranked player IDs, local player first. Producer
// 0x00666000 sorts peers by a latency/frame-ratio score; disconnectPlayer at
// 0x00666466 selects the next ID in this array when the router departs.
// The packet representation narrows each entry to one byte (-1 becomes 255).
class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	void setPlayerOrder(const Int *players);

	Int m_playerOrder[MAX_SLOTS];						// this+0x1C .. +0x38
};

void BFMENetRouterFallbackCommandMsg::setPlayerOrder(const Int *players)
{
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		m_playerOrder[i] = players[i];
	}
}
