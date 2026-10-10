// ?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ
// partial score=0.92 date=2026-10-10
// ?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ
// partial score=0.95395 date=2026-10-09
// ?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// NetPacket.cpp: the NetPacket bodies retail links from this TU (tu_map approved),
// folded from 24 one-function split units that shared these exact flags.
// One NetPacket view replaces the per-unit ones; every field offset below is the
// one each folded body was byte-verified against:
//   +0x004 packet[0x1DC], +0x1E0 len, +0x1E4/+0x1E8 dest, +0x1EC count,
//   +0x1F0 lastCmd, +0x1F4 frame, +0x1F8 timestamp, +0x1FC id,
//   +0x1FE/+0x1FF/+0x200 player/type/relay.
// Field names for +0x1F4/+0x1F8 are inferred from the BFME1 donor's message
// layout and the sibling frame handler, not from target symbols.
// The room checks read NetCommandRef's m_msg/m_relay directly: the inline
// getters inline to the same bytes, but emitting them here adds COMDAT copies
// that lose to ConnectionManager's and would stop this unit linking.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
enum { MAX_PACKET_SIZE = 0x1DC };

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"
// Inline in BFME: the file serializers 0x005913CB/0x005914D4 read each file-name
// character as m_data ? m_data->data[i] : 0, with no call. A TU-local helper, not a
// StringBase<char>::getCharAt specialization: that specialization's COMDAT copy is
// not retail's out-of-line getCharAt and stopped this unit linking. AsciiString
// holds one pointer to its buffer header; the characters start at +8.
static inline char npCharAt(const AsciiString &s, int i)
{
	const char *data = *(const char *const *)&s;
	return data ? data[8 + i] : 0;
}
#include "/mnt/titan_nv3/open-bfme2-agent-fleet/gemini200/writer-006/Code/Libraries/Include/Lib/Coord3D.h"

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *dest, const unsigned char *src);
void *__cdecl operator new(unsigned int size);
void *__cdecl operator new[](unsigned int size);

class NetCommandMsg
{
public:
	NetCommandMsg();
	UnsignedInt getTimestamp() { return m_timestamp; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }
	void setTiming(UnsignedInt timestamp, UnsignedInt frame) { m_timestamp = timestamp; m_executionFrame = frame; }
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	void setNetCommandType(Int type) { m_commandType = type; }
	void detach();
	virtual ~NetCommandMsg();
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

// The 0x2C data-carrying message: the room check at 0x0058D296 charges its
// +0x28 payload length, rva0058EDEF serializes +0x1C/+0x20/+0x28 and the +0x24
// buffer, and the static reader rva0058E20D rebuilds it in the same order
// through the rowed ctor 0x004D58DE and rva004D5925(data, len). One class
// across the three is a structural inference from that shared layout.
class Rva004D58DE : public NetCommandMsg
{
public:
	Rva004D58DE();
	void rva004D5925(unsigned char *data, unsigned int len);
	UnsignedInt get1c() { return m_1c; }
	UnsignedShort get20() { return m_20; }
	unsigned char *getData() { return m_24; }
	UnsignedInt getDataLength() { return m_28; }
	UnsignedInt m_1c;
	UnsignedShort m_20;
	unsigned char *m_24;
	UnsignedInt m_28;
};

// The wrapper getters are out of line under their ledger names. Retail folds
// the same-offset getters of the other message classes onto these (and onto
// NetProgressCommandMsg::getPercentage, Rva004D5767WordField::get), so the
// add* bodies below call them under these names: getData (+0x1C dword),
// getDataLength (+0x20) and getDataOffset (+0x24).
// UnicodeString getter at +0x1C (rowed under its address name).
class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;
};

// UnicodeString getter at +0x24 (rowed under its address name).
class Rva0023E928
{
public:
	UnicodeString rva0023E928() const;
};

// Type-30 message: dwords at +0x1C/+0x20, a UnicodeString at +0x24.
class NetType30CommandMsg : public NetCommandMsg
{
public:
	UnsignedInt get1c() { return m_1c; }
	UnsignedInt get20() { return m_20; }
	UnsignedInt m_1c;
	UnsignedInt m_20;
};

// Its ctor (rowed under the dtor's class name) and the +0x24 text setter.
class Rva004D67D0
{
public:
	Rva004D67D0();
private:
	char m_pad[0x28];
};

class Rva004D05D7
{
public:
	void rva004D05D7(UnicodeString text);
};

// The +0x1C AsciiString getter is rowed as CDDrive::getPath (retail folds the
// same-offset getters); it is called qualified, as the tree's other callers do.
class CDDrive
{
public:
	virtual AsciiString getPath();
};

// GameMessage, as addGameCommand and its room check read it: the type at
// +0x10, the argument count byte at +0x18 and the rowed argument queries.
enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER,
	ARGUMENTDATATYPE_REAL,
	ARGUMENTDATATYPE_BOOLEAN,
	ARGUMENTDATATYPE_OBJECTID,
	ARGUMENTDATATYPE_DRAWABLEID,
	ARGUMENTDATATYPE_TEAMID,
	ARGUMENTDATATYPE_LOCATION,
	ARGUMENTDATATYPE_PIXEL,
	ARGUMENTDATATYPE_PIXELREGION,
	ARGUMENTDATATYPE_TIMESTAMP,
	ARGUMENTDATATYPE_WIDECHAR,
	ARGUMENTDATATYPE_UNKNOWN
};

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
};

union GameMessageArgumentType
{
	Int integer;
	float real;
	Bool boolean;
	UnsignedInt objectID;
	UnsignedInt drawableID;
	UnsignedInt teamID;
	Coord3D location;
	ICoord2D pixel;
	IRegion2D pixelRegion;
	UnsignedInt timestamp;
	unsigned short wChar;
};

class GameMessage
{
public:
	virtual ~GameMessage();
	Int getType() const { return m_type; }
	UnsignedByte getArgumentCount() const { return m_argCount; }
	GameMessageArgumentDataType getArgumentDataType(Int argIndex);
	const GameMessageArgumentType *getArgument(Int argIndex) const;
	UnsignedInt m_04[3];
	Int m_type;
	UnsignedInt m_14;
	UnsignedByte m_argCount;
};

class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg();
	GameMessage *constructGameMessage();
private:
	UnsignedInt m_gameFields[5];
};

// GameMessageParser and its argument-type nodes, rowed under their address
// names (RvaSmallVtableCtors.cpp): a run's type at +8 and count at +0xC, the
// next node at +4; the parser's first node at +4 and its run count at +0xC.
class Rva0054D593
{
public:
	virtual ~Rva0054D593();
	Rva0054D593 *getNext() { return m_next; }
	GameMessageArgumentDataType getType() { return m_type; }
	Int getArgCount() { return m_argCount; }
	Rva0054D593 *m_next;
	GameMessageArgumentDataType m_type;
	Int m_argCount;
};

class Rva0054D54A
{
public:
	Rva0054D54A();
	Rva0054D54A(GameMessage *msg);
	virtual ~Rva0054D54A();
	Rva0054D593 *getFirstArgumentType() { return m_first; }
	Int getNumTypes() { return m_argTypeCount; }
	Rva0054D593 *m_first;
	Rva0054D593 *m_last;
	Int m_argTypeCount;
};

// The parser's addArgType, rowed under its address name on the class view
// RvaSmallVtableCtors.cpp gives it (same object; the type and count travel
// as pointer-sized values).
class Rva0054D5D3
{
public:
	void rva0054D5D3(void *type, void *argCount);
};

// readGameMessageArgumentFromPacket, rowed with four parameters; BFME's
// reader also passes the message type, which the body never reads.
void Rva00590D19Add(Int type, NetGameCommandMsg *msg, const void *data, Int *readOffset, Int msgType);

// AsciiString getter at +0x20 (rowed under its address name).
class Rva002D9BC1AsciiField
{
public:
	AsciiString get() const;
};

// +0x20 word getter and +0x24 byte getter (rowed under their address names).
class Rva004D5973WordField
{
public:
	UnsignedShort get() const;
};

class Rva001DCD01ByteField
{
public:
	UnsignedByte get() const;
};

class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getWrappedCommandID();
	UnsignedInt getChunkNumber();
	UnsignedInt getNumChunks();
	UnsignedInt getTotalDataLength();
	UnsignedInt getDataLength();
	UnsignedInt getDataOffset();
	UnsignedByte *getData();
};

// +0x1C byte getter.
class NetProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getPercentage();
};

// +0x1C word getter.
class Rva004D5767WordField
{
public:
	UnsignedShort get() const;
};

// Frame message addFrameCommand serializes: three dwords after the base.
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt get1c() { return m_1c; }
	UnsignedInt get20() { return m_20; }
	UnsignedInt get24() { return m_24; }
	UnsignedInt m_1c;
	UnsignedInt m_20;
	UnsignedInt m_24;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

// NetCommandRef's accessors, as TU-local helpers: member inlines would emit
// NetCommandRef::getCommand/getRelay/setRelay COMDAT copies, and the first copy in
// link order (ConnectionManager.cpp, from the ZH header whose vtable puts m_msg at
// +4) differs, so these copies lost and stopped this unit linking. Same inlined
// code; internal linkage, so nothing to lose.
static inline NetCommandMsg *ncrCommand(NetCommandRef *ref) { return ref->m_msg; }
static inline UnsignedByte ncrRelay(const NetCommandRef *ref) { return ref->m_relay; }
static inline void ncrSetRelay(NetCommandRef *ref, UnsignedByte relay) { ref->m_relay = relay; }

struct NetPacketAddress
{
	NetPacketAddress() { ip = 0; port = 0; }

	UnsignedInt ip;
	UnsignedShort port;
};

struct TransportMessageHeader
{
	UnsignedInt crc;
};

struct TransportMessage
{
	TransportMessageHeader header;
	UnsignedByte data[0x400];
	Int length;
	UnsignedInt addr;
	UnsignedShort port;
};

// Variable-size arms of GetBufferSizeNeededForCommand, rowed as free size
// helpers under their address names.
struct Rva00591062Host;
int __cdecl Rva00590F47Get(const Rva004D6119 *obj);
int __cdecl Rva00590F76Get(const Rva004D6119 *obj);
int Rva00590FD4Get(CDDrive *p);
int Rva0059100AGet(CDDrive *p);
int Rva00591036Get(CDDrive *p);
int Rva00591062Get(Rva00591062Host *p);
int Rva00590FA5Get(const Rva0023E928 *obj);
// FillBufferWithCommand's serializers rowed in their own units under address names.
void Rva0058C80FWrite(char *buffer, NetCommandRef *msg);
void Rva0058C96CWrite(char *buffer, NetCommandRef *msg);
void Rva0058CA1BWrite(char *buffer, NetCommandRef *msg);
void Rva0058CB27Write(char *buffer, NetCommandRef *msg);
void Rva005910B4Write(char *buffer, NetCommandRef *msg);
void Rva0058CBD9Write(char *buffer, NetCommandRef *msg);
void Rva0058CCF2Write(char *buffer, NetCommandRef *msg);
void Rva0058CD6AWrite(char *buffer, NetCommandRef *msg);
void Rva0058CE23Write(char *buffer, NetCommandRef *msg);
void Rva0058D041Write(UnsignedByte *buffer, NetCommandRef *msg);
void Rva0058CEC5Write(char *buffer, NetCommandRef *msg);
void Rva0058CF83Write(char *buffer, NetCommandRef *msg);

// Readers rowed as free functions under their address names.
class Rva004D64F5;
class Rva004D65DC;
class Rva004D6208;
class Rva004D62A9;
Rva004D64F5 *Rva00592496Read(Int data, UnsignedInt *readOffset);
Rva004D65DC *Rva00592520Read(Int data, UnsignedInt *readOffset);
Rva004D6208 *Rva005922FBRead(Int data, UnsignedInt *readOffset);
Rva004D62A9 *Rva005923C5Read(Int data, UnsignedInt *readOffset);

class NetCommandList {public:NetCommandList();void reset();NetCommandRef *addMessage(NetCommandMsg *);private:char pad[0x10];};
enum NetCommandType;
Bool DoesCommandRequireACommandID(NetCommandType);

class NetPacket
{
public:
	NetCommandList *getCommandList();
	virtual ~NetPacket();
	NetPacket();
	NetPacket(TransportMessage *msg);
	void init();
	void reset();
	Bool addCommand(NetCommandRef *msg);
	Bool rva0058D18C(NetCommandRef *msg);
	Bool rva0058D211(NetCommandRef *msg);
	UnsignedByte rva0059192A(NetCommandRef *msg);
	UnsignedByte rva005919AF(NetCommandRef *msg);
	UnsignedByte rva00591A65(NetCommandRef *msg);
	UnsignedByte rva0059188C(NetCommandRef *msg);
	UnsignedByte rva00591D0D(NetCommandRef *msg);
	Bool rva0058D296(NetCommandRef *msg);
	Bool rva0058D310(NetCommandRef *msg);
	Bool rva0058D58A(NetCommandRef *msg);
	Bool rva0058D601(NetCommandRef *msg);
	Int rva0058E57B();

	static NetCommandMsg *rva0058DA7E(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DB4D(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DC1C(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DCEB(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DD89(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DDF2(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DE5B(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DEC5(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DEF7(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DF29(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0059205C(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *readGameMessage(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva00592123(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva00592208(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058DFB8(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E047(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E0B0(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E20D(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E2D7(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E367(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E3F4(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E481(UnsignedByte *data, Int &readOffset);
	static NetCommandMsg *rva0058E511(UnsignedByte *data, Int &readOffset);
	static NetCommandRef *ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength);
	// The type-17 reader the linker folded into the type-16 body; its own symbol
	// keeps ConstructNetCommandMsgFromRawData's two call blocks apart.
	static NetCommandMsg *rva0058E0B0Type17(UnsignedByte *data, Int &readOffset);

protected:
	static NetCommandMsg *readWrapperMessage(UnsignedByte *data, Int &readOffset);
	Bool isRoomForWrapperMessage(NetCommandRef *msg);
	Bool rva0058D408(NetCommandRef *msg);
	Bool rva0058D461(NetCommandRef *msg);
	Bool rva0058D4BA(NetCommandRef *msg);
	UnsignedByte rva0058D513(NetCommandRef *msg);
	Bool isRoomForFrameMessage(NetCommandRef *msg);
	UnsignedByte rva0058D70B(NetCommandRef *msg);
	Bool isRoomForGameSpyStatsAuthKeyMessage(NetCommandRef *msg);
	Bool isRoomForFileMessage(NetCommandRef *msg);
	Bool isRoomForGameMessage(NetCommandRef *msg, GameMessage *gmsg);
	static UnsignedInt GetGameCommandSize(NetCommandMsg *msg);
	static UnsignedInt GetBufferSizeNeededForCommand(NetCommandMsg *msg);
	static void FillBufferWithGameCommand(UnsignedByte *buffer, NetCommandRef *ref);
	static void FillBufferWithAckCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithKeepAliveCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithProgressMessage(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithRouterFallbackCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithChatCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void rva0059129F(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithFileCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithFileAnnounceCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithRequestGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithCommand(UnsignedByte *buffer, NetCommandRef *msg);
	// Arms whose serializers the linker folded into a sibling's bytes; each
	// needs its own symbol or the compiler would merge the arms. In BFME1's case
	// order these are DisconnectKeepAlive, TimeOutGameStart and RequestFrameData.
	static void rva0058CACAType25(UnsignedByte *buffer, NetCommandRef *msg);
	static void rva0058CCF2Type17(UnsignedByte *buffer, NetCommandRef *msg);
	static void rva0058CF83Type9(UnsignedByte *buffer, NetCommandRef *msg);
	// Fixed-size arms of GetBufferSizeNeededForCommand, by command type; the
	// constants are the ones retail's jump table returns.
	static UnsignedInt GetType0CommandSize(NetCommandMsg *msg) { return 0x10; }
	static UnsignedInt GetType1CommandSize(NetCommandMsg *msg) { return 0x10; }
	static UnsignedInt GetType2CommandSize(NetCommandMsg *msg) { return 0x10; }
	static UnsignedInt GetType3CommandSize(NetCommandMsg *msg) { return 0x20; }
	static UnsignedInt GetType7CommandSize(NetCommandMsg *msg) { return 0x1C; }
	static UnsignedInt GetType8CommandSize(NetCommandMsg *msg) { return 0x1A; }
	static UnsignedInt GetType9CommandSize(NetCommandMsg *msg) { return 0x1C; }
	static UnsignedInt GetType10CommandSize(NetCommandMsg *msg) { return 0x15; }
	static UnsignedInt GetType11CommandSize(NetCommandMsg *msg) { return 0x18; }
	static UnsignedInt GetType12CommandSize(NetCommandMsg *msg) { return 0xC; }
	static UnsignedInt GetType15CommandSize(NetCommandMsg *msg) { return 0xD; }
	static UnsignedInt GetType16CommandSize(NetCommandMsg *msg) { return 0xF; }
	static UnsignedInt GetType17CommandSize(NetCommandMsg *msg) { return 0xF; }
	static UnsignedInt GetType18CommandSize(NetCommandMsg *msg) { return 0x25; }
	static UnsignedInt GetType20CommandSize(NetCommandMsg *msg) { return ((Rva004D58DE *)msg)->getDataLength() + 0x19; }
	static UnsignedInt GetType22CommandSize(NetCommandMsg *msg) { return 0x15; }
	static UnsignedInt GetType23CommandSize(NetCommandMsg *msg) { return 0x17; }
	static UnsignedInt GetType25CommandSize(NetCommandMsg *msg) { return 0xC; }
	static UnsignedInt GetType26CommandSize(NetCommandMsg *msg) { return 0x14; }
	static UnsignedInt GetType27CommandSize(NetCommandMsg *msg) { return 0x14; }
	static UnsignedInt GetType28CommandSize(NetCommandMsg *msg) { return 0x18; }
	Bool addGameCommand(NetCommandRef *msg);
	void writeGameMessageArgumentToPacket(GameMessageArgumentDataType type, GameMessageArgumentType arg);
	Bool addInformPlayerLeaveFrameCommand(NetCommandRef *msg);
	Bool rva0058E8EA(NetCommandRef *msg);
	Bool addDisconnectFrameCommand(NetCommandRef *msg);
	Bool rva0058EDEF(NetCommandRef *msg);
	Bool addFileProgressCommand(NetCommandRef *msg);
	Bool addWrapperCommand(NetCommandRef *msg);
	Bool rva0058F5E3(NetCommandRef *msg);
	Bool addProgressMessage(NetCommandRef *msg);
	Bool addDisconnectVoteCommand(NetCommandRef *msg);
	Bool addDisconnectPlayerCommand(NetCommandRef *msg);
	Bool rva0058FE15(NetCommandRef *msg);
	Bool addDestroyPlayerCommand(NetCommandRef *msg);
	Bool addRouterFallbackCommand(NetCommandRef *msg);
	Bool addPlayerLeaveCommand(NetCommandRef *msg);
	Bool addFrameCommand(NetCommandRef *msg);
	Bool isAckRepeat(NetCommandRef *msg);
	Bool isAckBothRepeat(NetCommandRef *msg);
	Bool isAckStage1Repeat(NetCommandRef *msg);
	Bool addDisconnectChatCommand(NetCommandRef *msg);
	Bool addChatCommand(NetCommandRef *msg);
	Bool rva005936DB(NetCommandRef *msg);
	Bool addFileCommand(NetCommandRef *msg);
	Bool addFileAnnounceCommand(NetCommandRef *msg);
	Bool addRequestGameSpyStatsAuthKeyCommand(NetCommandRef *msg);
	Bool addGameSpyStatsAuthKeyCommand(NetCommandRef *msg);
	Bool rva005939EE(NetCommandRef *msg);
	// ICF twins: retail gives these types their own call blocks to the
	// folded bodies above, so they are distinct symbols pinned to them.
	Bool rva005939EEAckStage1(NetCommandRef *msg);
	Bool rva005939EEAckStage2(NetCommandRef *msg);
	Bool rva0058FE15DisconnectKeepAlive(NetCommandRef *msg);
	Bool rva0058F5E3TimeOutStart(NetCommandRef *msg);
	Bool rva0058E8EARequestFrameData(NetCommandRef *msg);
	Bool addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt ackValue20, UnsignedInt ackValue24);

public:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	NetPacketAddress m_dest;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedInt m_lastTimestamp;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

// Message classes the static readers construct, sized from their rowed ctors.
class Rva004D57AE : public NetCommandMsg
{
public:
	Rva004D57AE();
	void setPlayerIndex(UnsignedInt v);
private:
	UnsignedInt m_playerIndex; // +0x1C: NetCommandMsg is 0x1C bytes
};

class NetAckBothCommandMsg
{
public:
	NetAckBothCommandMsg();
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();
	UnsignedInt get20() { return m_20; }
	UnsignedInt get24() { return m_24; }
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};

class NetAckStage1CommandMsg
{
public:
	NetAckStage1CommandMsg();
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};

class NetAckStage2CommandMsg
{
public:
	NetAckStage2CommandMsg();
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};

class Rva004CEEC3
{
public:
	Rva004CEEC3();
private:
	char m_pad[0x1C];
public:
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
};

class Rva004CEEE8
{
public:
	Rva004CEEE8();
private:
	char m_pad[0x3C];
};

class NetKeepAliveCommandMsg
{
public:
	NetKeepAliveCommandMsg();
private:
	char m_pad[0x1C];
};

class NetDisconnectKeepAliveCommandMsg
{
public:
	NetDisconnectKeepAliveCommandMsg();
private:
	char m_pad[0x1C];
};

class Rva004D580E
{
public:
	Rva004D580E();
private:
	char m_pad[0x24];
};

class Rva004D57F1
{
public:
	Rva004D57F1();
private:
	char m_pad[0x28];
};

class NetDisconnectPlayerCommandMsg
{
public:
	void setDisconnectSlot(UnsignedByte slot);
	void setDisconnectFrame(UnsignedInt frame);
};

// Type-13 and type-14 messages (ZH's NetDisconnectChatCommandMsg and
// NetChatCommandMsg). rva004D6187 is ZH's setText(UnicodeString), rowed with a
// StringBase<unsigned short> parameter whose copy ctor is private here.
class Rva004D60CA
{
public:
	Rva004D60CA();
	void rva004D6187(UnicodeString text);
private:
	char m_pad[0x20];
};

class Rva004D6134
{
public:
	Rva004D6134();
private:
	char m_pad[0x24];
};

class Rva004D582B
{
public:
	Rva004D582B();
private:
	char m_pad[0x20];
};

class Rva004D5795
{
public:
	Rva004D5795();
private:
	char m_pad[0x20];
};

class Rva004D598E
{
public:
	Rva004D598E();
private:
	char m_pad[0x24];
};

class Rva004D59D1
{
public:
	Rva004D59D1();
private:
	char m_pad[0x24];
};

class Rva004D5A10
{
public:
	Rva004D5A10();
private:
	char m_pad[0x24];
};

class Rva004D5A30
{
public:
	Rva004D5A30();
private:
	char m_pad[0x24];
};

class Rva004D59B8
{
public:
	Rva004D59B8();
private:
	char m_pad[0x20];
};

// Setters the readers call through casts of the constructed message.
class Rva004543C6ByteField { public: unsigned char get() const; };
class Rva004D59ACWordSlot
{
public:
	void set(unsigned short value);
};

class Rva004D576CByteSlot
{
public:
	void set(unsigned char value);
};

class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	void setPlayerOrder(const int *players);
	Int m_playerOrder[8]; // +0x1C, per the BFME1 donor
};

class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeavingPlayerID(Int playerID);
	void setLeaveFrame(UnsignedInt frame);
};

enum DozerTask
{
	DOZER_TASK_ZERO = 0
};

class Script
{
public:
	void setActive(bool active);
};

class DozerAIUpdate
{
public:
	virtual void setCurrentTask(DozerTask task);
};

// ---------------------------------------------------------------------------
// ??1NetPacket@@UAE@XZ 0x0058D0E2, ?init@NetPacket@@QAEXXZ 0x0058D10A (86B),
// ?reset@NetPacket@@QAEXXZ 0x0058D160, ??0NetPacket 0x0058E5B4/0x0058E5EC.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/NetPacket_init.cpp
// (NetPacket::init flat stores + NetPacketAddress stack-temp dest assignment).
// Target evidence: flat 86B store run with EBP frame; callers 0x0058D160 reset
// tail-jmps here, ctors 0x0058E5B4/0x0058E5EC call here after vtable 0x00870A28.

NetCommandList *NetPacket::getCommandList()
{
	NetCommandList *retval = new NetCommandList();
	retval->reset();

	UnsignedByte commandType = 0;
	UnsignedInt frame = 0;
	UnsignedInt timestamp = 0;
	UnsignedByte playerID = 0;
	UnsignedByte relay = 0;
	UnsignedInt commandID = 0;
	NetCommandRef *lastCommand = 0;
	Bool commandIDSet = false;
	Int offset;

	Int i = 0;
	while (i < m_packetLen) {
		if (m_packet[i] == 'T') {
			++i;
			memcpy(&commandType, m_packet + i, sizeof(UnsignedByte));
			i += sizeof(UnsignedByte);
			continue;
		} else if (m_packet[i] == 'S') {
			++i;
			memcpy(&timestamp, m_packet + i, sizeof(UnsignedInt));
			i += sizeof(UnsignedInt);
			continue;
		} else if (m_packet[i] == 'F') {
			++i;
			memcpy(&frame, m_packet + i, sizeof(UnsignedInt));
			i += sizeof(UnsignedInt);
			continue;
		} else if (m_packet[i] == 'P') {
			++i;
			memcpy(&playerID, m_packet + i, sizeof(UnsignedByte));
			i += sizeof(UnsignedByte);
			continue;
		} else if (m_packet[i] == 'R') {
			++i;
			memcpy(&relay, m_packet + i, sizeof(UnsignedByte));
			i += sizeof(UnsignedByte);
			continue;
		} else if (m_packet[i] == 'C') {
			++i;
			memcpy(&commandID, m_packet + i, sizeof(UnsignedShort));
			i += sizeof(UnsignedShort);
			commandIDSet = true;
			continue;
		} else if (m_packet[i] == 'D') {
			++i;
			offset = i;

			NetCommandMsg *msg = 0;
			switch (commandType) {
			case 4:
				msg = readGameMessage(m_packet, offset);
				break;
			case 0:
				msg = rva0058DA7E(m_packet, offset);
				break;
			case 1:
				msg = rva0058DB4D(m_packet, offset);
				break;
			case 2:
				msg = rva0058DC1C(m_packet, offset);
				break;
			case 3:
				msg = rva0058DCEB(m_packet, offset);
				break;
			case 23:
				msg = rva0058DD89(m_packet, offset);
				break;
			case 10:
				msg = rva0058DDF2(m_packet, offset);
				break;
			case 11:
				msg = rva0058DE5B(m_packet, offset);
				break;
			case 12:
				msg = rva0058DEC5(m_packet, offset);
				break;
			case 25:
				msg = rva0058DEF7(m_packet, offset);
				break;
			case 26:
				msg = rva0058DF29(m_packet, offset);
				break;
			case 13:
				msg = rva0059205C(m_packet, offset);
				break;
			case 27:
				msg = rva0058DFB8(m_packet, offset);
				break;
			case 14:
				msg = rva00592123(m_packet, offset);
				break;
			case 15:
				msg = rva0058E047(m_packet, offset);
				break;
			case 16:
				msg = rva0058E0B0(m_packet, offset);
				break;
			case 17:
				msg = rva0058E0B0Type17(m_packet, offset);
				break;
			case 18:
				msg = readWrapperMessage(m_packet, offset);
				break;
			case 20:
				msg = rva0058E20D(m_packet, offset);
				break;
			case 19:
				msg = (NetCommandMsg *)Rva005922FBRead((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 21:
				msg = (NetCommandMsg *)Rva005923C5Read((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 22:
				msg = rva0058E2D7(m_packet, offset);
				break;
			case 8:
				msg = rva0058E367(m_packet, offset);
				break;
			case 7:
				msg = rva0058E3F4(m_packet, offset);
				break;
			case 9:
				msg = rva0058E481(m_packet, offset);
				break;
			case 28:
				msg = rva0058E511(m_packet, offset);
				break;
			case 5:
				msg = (NetCommandMsg *)Rva00592496Read((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 6:
				msg = (NetCommandMsg *)Rva00592520Read((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 30:
				msg = rva00592208(m_packet, offset);
				break;
			}

			if (msg == 0) {
				break;
			}

			msg->setTiming(timestamp, frame);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);
			if (DoesCommandRequireACommandID((NetCommandType)commandType)) {
				if (!commandIDSet) {
					++commandID;
				}
				msg->setID((UnsignedShort)commandID);
			}
			commandIDSet = false;

			NetCommandRef *ref = retval->addMessage(msg);
			if (ref != 0) {
				ncrSetRelay(ref,relay);
			}

			if (lastCommand != 0) {
				delete lastCommand;
			}
			lastCommand = new NetCommandRef(msg);

			msg->detach();
		} else if (m_packet[i] == 'Z') {
			++i;
			offset = i;
			if (lastCommand == 0) {
				break;
			}
			NetCommandMsg *msg = 0;
			if (commandType == 1) {
				msg = (NetCommandMsg *)new NetAckStage1CommandMsg();
				NetAckStage1CommandMsg *last = (NetAckStage1CommandMsg *)ncrCommand(lastCommand);
				((Rva004D59ACWordSlot *)msg)->set(((Rva004D5767WordField *)last)->get() + 1);
				((Rva004D576CByteSlot *)msg)->set(((Rva004543C6ByteField *)last)->get());
				((NetAckStage1CommandMsg *)msg)->m_20 = last->m_20;
				((NetAckStage1CommandMsg *)msg)->m_24 = last->m_24;
			} else if (commandType == 2) {
				msg = (NetCommandMsg *)new NetAckStage2CommandMsg();
				NetAckStage2CommandMsg *last = (NetAckStage2CommandMsg *)ncrCommand(lastCommand);
				((Rva004D59ACWordSlot *)msg)->set(((Rva004D5767WordField *)last)->get() + 1);
				((Rva004D576CByteSlot *)msg)->set(((Rva004543C6ByteField *)last)->get());
				((NetAckStage2CommandMsg *)msg)->m_20 = last->m_20;
				((NetAckStage2CommandMsg *)msg)->m_24 = last->m_24;
			} else if (commandType == 0) {
				msg = (NetCommandMsg *)new NetAckBothCommandMsg();
				NetAckBothCommandMsg *last = (NetAckBothCommandMsg *)ncrCommand(lastCommand);
				((Rva004D59ACWordSlot *)msg)->set(((Rva004D5767WordField *)last)->get() + 1);
				((Rva004D576CByteSlot *)msg)->set(((Rva004543C6ByteField *)last)->get());
				((NetAckBothCommandMsg *)msg)->m_20 = last->m_20;
				((NetAckBothCommandMsg *)msg)->m_24 = last->m_24;
			} else {
				break;
			}

			msg->setTiming(timestamp, frame);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);
			if (DoesCommandRequireACommandID((NetCommandType)commandType)) {
				if (!commandIDSet) {
					++commandID;
				}
				msg->setID((UnsignedShort)commandID);
			}
			commandIDSet = false;

			NetCommandRef *ref = retval->addMessage(msg);
			if (ref != 0) {
				ncrSetRelay(ref,relay);
			}

			delete lastCommand;
			lastCommand = new NetCommandRef(msg);

			msg->detach();
		} else {
			rva0058E57B();
			++i;
			continue;
		}
		i = offset;
	}

	if (lastCommand != 0) {
		delete lastCommand;
	}
	return retval;
}
