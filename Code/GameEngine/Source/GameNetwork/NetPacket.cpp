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
#include "../../../Libraries/Include/Lib/Coord3D.h"

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

class NetPacket
{
public:
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
NetPacket::~NetPacket()
{
	if (m_lastCommand != 0) {
		delete m_lastCommand;
		m_lastCommand = 0;
	}
}

void NetPacket::init()
{
	NetPacketAddress dest;
	m_dest = dest;
	m_numCommands = 0;
	m_packetLen = 0;
	m_packet[0] = 0;
	m_lastPlayerID = 0;
	m_lastFrame = 0;
	m_lastTimestamp = 0;
	m_lastCommandID = 0;
	m_lastCommandType = 0;
	m_lastRelay = 0;
	m_lastCommand = 0;
}

void NetPacket::reset()
{
	if (m_lastCommand != 0) {
		delete m_lastCommand;
		m_lastCommand = 0;
	}
	init();
}

// ?rva0058D18C@NetPacket@@QAE_NPAVNetCommandRef@@@Z, retail 0x0058D18C, 133 bytes:
// rva0058D211 with a fixed 9 instead of 5, the room check of the two bodies
// that serialize two dwords (addInformPlayerLeaveFrameCommand, rva0058E8EA).
Bool NetPacket::rva0058D18C(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 9) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D211@NetPacket@@QAE_NPAVNetCommandRef@@@Z, retail 0x0058D211, 133 bytes,
// and its siblings 0x0058D296/0x0058D310/0x0058D58A/0x0058D601.
// NetPacket room check sibling of isRoomForWrapperMessage 0x0058D387: charges
// type/relay/timestamp/frame/player/ID deltas (2/2/5/5/2/3) plus fixed 5 over
// base +0x1E0 and returns room<=0x1DC. Evidence: identical NetPacket tail
// layout +0x1F4/+0x1F8/+0x1FC/+0x1FE/+0x1FF/+0x200 and MAX 0x1DC as the
// sibling; callers 0x0058EB9A 0x0058FFBD. Honest address method of NetPacket.
Bool NetPacket::rva0058D211(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 5) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D296(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	Int base = m_packetLen + ((Rva004D58DE *)cmdMsg)->m_28;
	if ((len + base + 0xB) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D310(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 7) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?isRoomForWrapperMessage@NetPacket 0x0058D387 (129B).
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/NetPacketCommandBodies.cpp.
// Target boundary 0x58D387 is the wrapper-capacity helper: it charges packet
// type, relay, timestamp, player and command-ID data then calls the pinned
// NetWrapperCommandMsg::getDataLength target at 0x0030D377. The +0x1F8 packet
// field is compared with command +0x04 in target bytes; its timestamp meaning
// is inferred from the donor's message layout and the sibling frame handler.
Bool NetPacket::isRoomForWrapperMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	++len;
	len += sizeof(UnsignedShort);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	len += cmdMsg->getDataLength();
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D461@NetPacket@@IAE_NPAVNetCommandRef@@@Z @0x0058D461 (89B).
// NetPacket capacity check sibling of isRoomForWrapperMessage 0x0058D387:
// charges type 2 relay 1+1 timestamp 5 playerID 1+1 plus fixed 1 against
// MAX 0x1DC. No command-ID or data-length steps. Unblocks 0x0058F5E3
// and 0x0058FE15. Same layout and flags as wrapper precedent.
Bool NetPacket::rva0058D461(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
	}
	if ((len + m_packetLen + 1) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D4BA@NetPacket@@IAE_NPAVNetCommandRef@@@Z @0x0058D4BA (89B).
// Same charges as sibling rva0058D461 plus fixed 2. Unblocks 0x0058F7D8.
Bool NetPacket::rva0058D4BA(NetCommandRef *msg)
{
	Int len = 0;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
	}
	if ((len + m_packetLen + 2) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D513@NetPacket@@IAEEPAVNetCommandRef@@@Z 0x0058D513 (119B), the
// frame-message sibling without the execution-frame charge.
UnsignedByte NetPacket::rva0058D513(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	Int total = m_packetLen + len + 6;
	return total <= MAX_PACKET_SIZE;
}

Bool NetPacket::rva0058D58A(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 9) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

Bool NetPacket::rva0058D601(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = msg->m_msg;
	if (m_lastCommandType != (UnsignedInt)cmdMsg->m_commandType) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastTimestamp != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	UnsignedInt lastPlayer = m_lastPlayerID;
	if (lastPlayer != cmdMsg->m_playerID) {
		++len;
		++len;
		needNewCommandID = true;
	}
	UnsignedInt lastID = m_lastCommandID;
	UnsignedInt cmdID = cmdMsg->m_id;
	if (((lastID + 1) != cmdID) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	if ((len + m_packetLen + 2) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?isRoomForFrameMessage@NetPacket 0x0058D686 (133B).
// BFME1 donor: Code/GameEngine/Source/GameNetwork/NetPacket.cpp.
// Same packet-capacity sequence and command fields as BFME1
// isRoomForFrameMessage (0x678180, 128 B), with the target packet's post-frame
// state shifted by four bytes.
Bool NetPacket::isRoomForFrameMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->m_msg);
	if (m_lastCommandType != cmdMsg->m_commandType) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->m_relay) {
		++len;
		++len;
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		++len;
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
		(needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	if (*(UnsignedInt *)((char *)this + 0x1F8) != cmdMsg->m_timestamp) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (*(UnsignedInt *)((char *)this + 0x1F4) != cmdMsg->m_executionFrame) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	++len;
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?rva0058D70B@NetPacket@@IAEEPAVNetCommandRef@@@Z @0x0058D70B 60B.
// NetPacket room check beside isRoomForFrameMessage 0x0058D686: lastCommandType
// vs +0x14 and lastPlayerID vs +0x0C each add 2 then +12 vs 0x1DC.
// Evidence: unlock lane plus sibling TU layout plus caller 0x00591BAB.
UnsignedByte NetPacket::rva0058D70B(NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = msg->m_msg;
	Int len = 0;
	if (m_lastCommandType != cmdMsg->m_commandType) {
		len = 2;
	}
	if (m_lastPlayerID != cmdMsg->m_playerID) {
		++len;
		++len;
	}
	Int total = m_packetLen + len + 12;
	return total <= MAX_PACKET_SIZE;
}

// ?isRoomForGameSpyStatsAuthKeyMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00591DAB, 251 bytes:
// the BFME1 donor's isRoomForGameSpyStatsAuthKeyMessage
// (NetPacket_isRoomForGameSpyStatsAuthKeyMessage.cpp) plus BFME's timestamp
// charge: header bytes, then both strings' lengths and their terminators.
// The inline getters keep len and needNewCommandID in the frame, as retail.
Bool NetPacket::isRoomForGameSpyStatsAuthKeyMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != ncrRelay(msg)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastTimestamp != cmdMsg->getTimestamp()) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	++len;
	len += ((CDDrive *)cmdMsg)->CDDrive::getPath().getLength() + ((Rva002D9BC1AsciiField *)cmdMsg)->get().getLength() + 2;
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?isRoomForFileMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x005917DB, 177 bytes:
// ZH's isRoomForFileMessage plus BFME's timestamp charge, term for term: the
// name's length plus one, the length dword and the file length itself (the
// folded +0x24 getter rowed as NetWrapperCommandMsg::getDataOffset).
Bool NetPacket::isRoomForFileMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != ncrRelay(msg)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastTimestamp != cmdMsg->getTimestamp()) {
		len += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}
	len += sizeof(UnsignedByte);
	len += ((CDDrive *)cmdMsg)->CDDrive::getPath().getLength() + 1;
	len += sizeof(UnsignedInt);
	len += cmdMsg->getDataOffset();
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}

// ?isRoomForGameMessage@NetPacket@@IAE_NPAVNetCommandRef@@PAVGameMessage@@@Z, retail 0x0058D92F, 335 bytes:
// the BFME1 donor's isRoomForGameMessage (NetPacket_addGameCommand.cpp) with
// BFME's timestamp charge first: header bytes, 'D' plus type plus run count,
// then two bytes and the argument data per GameMessageParser run. Retail frees
// the parser with a flag-0 destructor call and the global operator delete,
// which is what ::delete emits.
Bool NetPacket::isRoomForGameMessage(NetCommandRef *msg, GameMessage *gmsg)
{
	Int msglen = 0;
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)(ncrCommand(msg));
	Bool needNewCommandID = false;
	if (m_lastTimestamp != cmdMsg->getTimestamp()) {
		msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastFrame != cmdMsg->getExecutionFrame()) {
		msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (m_lastRelay != ncrRelay(msg)) {
		msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		msglen += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	Rva0054D54A *parser = new Rva0054D54A(gmsg);
	++msglen;
	msglen += sizeof(Int);
	msglen += sizeof(UnsignedByte);
	Rva0054D593 *arg = parser->getFirstArgumentType();
	while (arg != 0) {
		msglen += 2 * sizeof(UnsignedByte);
		GameMessageArgumentDataType type = arg->getType();
		if (type == ARGUMENTDATATYPE_INTEGER) {
			msglen += arg->getArgCount() * sizeof(Int);
		} else if (type == ARGUMENTDATATYPE_REAL) {
			msglen += arg->getArgCount() * sizeof(float);
		} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
			msglen += arg->getArgCount() * sizeof(Bool);
		} else if (type == ARGUMENTDATATYPE_OBJECTID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_TEAMID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_LOCATION) {
			msglen += arg->getArgCount() * (3 * sizeof(float));
		} else if (type == ARGUMENTDATATYPE_PIXEL) {
			msglen += arg->getArgCount() * (2 * sizeof(Int));
		} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
			msglen += arg->getArgCount() * (4 * sizeof(Int));
		} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
			msglen += arg->getArgCount() * sizeof(unsigned short);
		}
		arg = arg->getNext();
	}
	::delete parser;
	parser = 0;
	if (msglen > (MAX_PACKET_SIZE - m_packetLen)) {
		return false;
	}
	return true;
}

// ?GetGameCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z, retail 0x0058C356, 259 bytes:
// the BFME1 donor's GetGameCommandSize (NetPacket_GetBufferSizeNeededForCommand.cpp)
// with BFME's timestamp field in the header charge (0x19 where the donor has
// 0x14). GetBufferSizeNeededForCommand reaches it from its type-4 arm; the
// parser is freed the way isRoomForGameMessage frees it.
UnsignedInt NetPacket::GetGameCommandSize(NetCommandMsg *msg)
{
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)msg;
	UnsignedShort msglen = 0;
	msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte);
	GameMessage *gmsg = cmdMsg->constructGameMessage();
	Rva0054D54A *parser = new Rva0054D54A(gmsg);
	msglen += sizeof(Int);
	msglen += sizeof(UnsignedByte);
	Rva0054D593 *arg = parser->getFirstArgumentType();
	while (arg != 0) {
		msglen += 2 * sizeof(UnsignedByte);
		GameMessageArgumentDataType type = arg->getType();
		if (type == ARGUMENTDATATYPE_INTEGER) {
			msglen += arg->getArgCount() * sizeof(Int);
		} else if (type == ARGUMENTDATATYPE_REAL) {
			msglen += arg->getArgCount() * sizeof(float);
		} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
			msglen += arg->getArgCount() * sizeof(Bool);
		} else if (type == ARGUMENTDATATYPE_OBJECTID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_TEAMID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_LOCATION) {
			msglen += arg->getArgCount() * (3 * sizeof(float));
		} else if (type == ARGUMENTDATATYPE_PIXEL) {
			msglen += arg->getArgCount() * (2 * sizeof(Int));
		} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
			msglen += arg->getArgCount() * (4 * sizeof(Int));
		} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
			msglen += arg->getArgCount() * sizeof(unsigned short);
		}
		arg = arg->getNext();
	}
	::delete parser;
	parser = 0;
	::delete gmsg;
	gmsg = 0;
	return msglen;
}

// ?GetBufferSizeNeededForCommand@NetPacket@@KAIPAVNetCommandMsg@@@Z, retail 0x0059299C, 271 bytes
// with its 31-entry jump table: the BFME1 donor's per-type size dispatcher
// (NetPacket_GetBufferSizeNeededForCommand.cpp). Its callers are
// ConstructBigCommandPacketList's two size queries. The fixed sizes are inline
// helpers, as in the donor, so the table stays a direct dword table; the case
// order is addCommand's except that type 20 precedes type 19.
UnsignedInt NetPacket::GetBufferSizeNeededForCommand(NetCommandMsg *msg)
{
	if (msg == 0) {
		return true;
	}

	switch (msg->getNetCommandType()) {
	case 4:
		return GetGameCommandSize(msg);
	case 1:
		return GetType1CommandSize(msg);
	case 2:
		return GetType2CommandSize(msg);
	case 0:
		return GetType0CommandSize(msg);
	case 3:
		return GetType3CommandSize(msg);
	case 23:
		return GetType23CommandSize(msg);
	case 10:
		return GetType10CommandSize(msg);
	case 11:
		return GetType11CommandSize(msg);
	case 12:
		return GetType12CommandSize(msg);
	case 25:
		return GetType25CommandSize(msg);
	case 26:
		return GetType26CommandSize(msg);
	case 13:
		return Rva00590F47Get((const Rva004D6119 *)msg);
	case 27:
		return GetType27CommandSize(msg);
	case 14:
		return Rva00590F76Get((const Rva004D6119 *)msg);
	case 15:
		return GetType15CommandSize(msg);
	case 16:
		return GetType16CommandSize(msg);
	case 17:
		return GetType17CommandSize(msg);
	case 18:
		return GetType18CommandSize(msg);
	case 20:
		return GetType20CommandSize(msg);
	case 19:
		return Rva00590FD4Get((CDDrive *)msg);
	case 21:
		return Rva0059100AGet((CDDrive *)msg);
	case 22:
		return GetType22CommandSize(msg);
	case 8:
		return GetType8CommandSize(msg);
	case 7:
		return GetType7CommandSize(msg);
	case 9:
		return GetType9CommandSize(msg);
	case 28:
		return GetType28CommandSize(msg);
	case 5:
		return Rva00591036Get((CDDrive *)msg);
	case 6:
		return Rva00591062Get((Rva00591062Host *)msg);
	case 30:
		return Rva00590FA5Get((const Rva0023E928 *)msg);
	}

	return 0;
}

// ?FillBufferWithAckCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x0058C740, 207 bytes:
// the BFME1 donor's FillBufferWithAckCommand (NetPacket.cpp) plus BFME's two
// ack dwords at +0x20/+0x24. As in the donor, each arm reads the ack fields
// through the command reference itself, not its message. The three classes'
// getters are the pinned ICF copies at 0x004D5767/0x004543C6, which is what
// keeps retail's three call blocks apart.
void NetPacket::FillBufferWithAckCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	UnsignedShort offset = 0;

	UnsignedShort commandID = 0;
	UnsignedByte originalPlayerID = 0;
	UnsignedInt ackValue20 = 0;
	UnsignedInt ackValue24 = 0;

	if (cmdMsg->getNetCommandType() == 0) {
		NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg;
		commandID = ackmsg->getCommandID();
		originalPlayerID = ackmsg->getOriginalPlayerID();
		ackValue20 = ackmsg->m_20;
		ackValue24 = ackmsg->m_24;
	} else if (cmdMsg->getNetCommandType() == 1) {
		NetAckStage1CommandMsg *ackmsg = (NetAckStage1CommandMsg *)msg;
		commandID = ackmsg->getCommandID();
		originalPlayerID = ackmsg->getOriginalPlayerID();
		ackValue20 = ackmsg->m_20;
		ackValue24 = ackmsg->m_24;
	} else if (cmdMsg->getNetCommandType() == 2) {
		NetAckStage2CommandMsg *ackmsg = (NetAckStage2CommandMsg *)msg;
		commandID = ackmsg->getCommandID();
		originalPlayerID = ackmsg->getOriginalPlayerID();
		ackValue20 = ackmsg->m_20;
		ackValue24 = ackmsg->m_24;
	}

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'D';
	++offset;
	memcpy(buffer + offset, &commandID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);
	memcpy(buffer + offset, &originalPlayerID, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);
	memcpy(buffer + offset, &ackValue20, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);
	memcpy(buffer + offset, &ackValue24, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);
}

// ?FillBufferWithKeepAliveCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x0058CACA, 93 bytes:
// the BFME1 donor's FillBufferWithKeepAliveCommand (NetPacket.cpp) plus BFME's
// 'S' timestamp field after the relay. FillBufferWithCommand reaches it from
// its type-12 arm; the type-25 arm calls the same (ICF-folded) body.
void NetPacket::FillBufferWithKeepAliveCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'D';
	++offset;
}

// ?rva0058CACAType25@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: FillBufferWithCommand's type-25 arm.
// Its own body is FillBufferWithKeepAliveCommand's, which the retail linker
// folded (ICF) onto 0x0058CACA; defined so the link resolves the arm's call.
void NetPacket::rva0058CACAType25(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'D';
	++offset;
}

// ?rva0058CCF2Type17@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: FillBufferWithCommand's
// type-17 arm. Retail's linker folded its body (ICF) onto 0x0058CCF2, rowed as the
// free serializer Rva0058CCF2Write: T/R/S/P/C/D with no payload. Defined here with
// the same body so the arm's call resolves in the link.
void NetPacket::rva0058CCF2Type17(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;
}

// ?rva0058CF83Type9@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: FillBufferWithCommand's
// type-9 arm. Retail's linker folded its body (ICF) onto 0x0058CF83, rowed as the
// free serializer Rva0058CF83Write: T/S/F/R/P/C/D, then the data pointer value and
// the data length, as retail copies them. Defined here with the same body so the
// arm's call resolves in the link.
void NetPacket::rva0058CF83Type9(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'F';
	++offset;
	UnsignedInt newframe = cmdMsg->getExecutionFrame();
	memcpy(buffer + offset, &newframe, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = ncrRelay(msg);
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;
	// retail walks the buffer pointer for the two payload words
	UnsignedByte *data = cmdMsg->getData();
	buffer += offset;
	memcpy(buffer, &data, sizeof(UnsignedByte *));
	UnsignedInt dataLength = cmdMsg->getDataLength();
	buffer += sizeof(UnsignedByte *);
	memcpy(buffer, &dataLength, sizeof(UnsignedInt));
}

// ?FillBufferWithProgressMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x0058CC8B, 103 bytes:
// the BFME1 donor's FillBufferWithProgressMessage (NetPacket.cpp) plus BFME's
// 'S' timestamp field; FillBufferWithCommand's type-15 arm.
void NetPacket::FillBufferWithProgressMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetProgressCommandMsg *cmdMsg = (NetProgressCommandMsg *)(ncrCommand(msg));
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'D';
	++offset;

	buffer[offset] = cmdMsg->getPercentage();
	++offset;
}

// ?FillBufferWithRouterFallbackCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x0058C8E4, 136 bytes:
// the BFME1 donor's FillBufferWithRouterFallbackCommand
// (NetPacketCommandBodies.cpp) with BFME's 'S' timestamp field and the relay
// and command ID copied as the other serializers copy them; one byte per
// player-order slot, read through a local pointer (which keeps retail's
// indexed loop, as in addRouterFallbackCommand). FillBufferWithCommand's
// type-23 arm.
void NetPacket::FillBufferWithRouterFallbackCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	BFMENetRouterFallbackCommandMsg *cmdMsg = (BFMENetRouterFallbackCommandMsg *)ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;
	const Int *playerOrder = cmdMsg->m_playerOrder;
	for (Int i = 0; i < 8; ++i) {
		buffer[offset + i] = (UnsignedByte)playerOrder[i];
	}
}

// ?FillBufferWithChatCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x00591170, 303 bytes:
// the BFME1 donor's FillBufferWithChatCommand (NetPacket.cpp) with BFME's 'S'
// timestamp field first; the text and player mask are read as
// addChatCommand reads them. FillBufferWithCommand's type-14 arm.
void NetPacket::FillBufferWithChatCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'F';
	++offset;
	UnsignedInt newframe = cmdMsg->getExecutionFrame();
	memcpy(buffer + offset, &newframe, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;
	UnicodeString unitext = ((Rva004D6119 *)cmdMsg)->rva004D6119();
	UnsignedByte length = unitext.getLength();
	Int playerMask = cmdMsg->getDataLength();
	memcpy(buffer + offset, &length, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	memcpy(buffer + offset, unitext.str(), length * sizeof(unsigned short));
	offset += length * sizeof(unsigned short);

	memcpy(buffer + offset, &playerMask, sizeof(Int));
	offset += sizeof(Int);
}

// ?rva0059129F@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x0059129F, 300 bytes:
// FillBufferWithCommand's type-30 arm, the serializer of the message
// rva00592208 reads back: the chat serializer's T/S/F/R/P/C/D header, then the
// +0x24 text as length byte and UTF-16 characters, then the +0x1C and +0x20
// dwords. No identity beyond its address.
void NetPacket::rva0059129F(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetType30CommandMsg *cmdMsg = (NetType30CommandMsg *)ncrCommand(msg);
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'F';
	++offset;
	UnsignedInt newframe = cmdMsg->getExecutionFrame();
	memcpy(buffer + offset, &newframe, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(msg);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;
	UnicodeString unitext = ((Rva0023E928 *)cmdMsg)->rva0023E928();
	UnsignedByte length = unitext.getLength();
	UnsignedInt value1c = cmdMsg->get1c();
	memcpy(buffer + offset, &length, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	memcpy(buffer + offset, unitext.str(), length * sizeof(unsigned short));
	offset += length * sizeof(unsigned short);

	memcpy(buffer + offset, &value1c, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	UnsignedInt value20 = cmdMsg->get20();
	memcpy(buffer + offset, &value20, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);
}

// ?FillBufferWithFileCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x005913CB, 265 bytes:
// FillBufferWithCommand's type-19 (FILE) arm, the serializer addFileCommand
// writes inline: the BFME1 donor's FillBufferWithFileMessage (NetPacket_fill.cpp)
// with BFME's 'S' timestamp after the relay. The name, length and data come
// through the same folded getters addFileCommand uses, including the donor's
// second length call for the dead final offset bump.
void NetPacket::FillBufferWithFileCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
	UnsignedInt offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = ncrRelay(msg);
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;

	AsciiString filename = ((CDDrive *)cmdMsg)->CDDrive::getPath();
	for (Int i = 0; i < filename.getLength(); ++i) {
		buffer[offset] = npCharAt(filename, i);
		++offset;
	}
	buffer[offset] = 0;
	++offset;

	UnsignedInt fileLength = cmdMsg->getDataOffset();
	memcpy(buffer + offset, &fileLength, sizeof(fileLength));
	offset += sizeof(fileLength);

	memcpy(buffer + offset, (UnsignedByte *)cmdMsg->getDataLength(), cmdMsg->getDataOffset());
	offset += cmdMsg->getDataOffset();
}

// ?FillBufferWithFileAnnounceCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x005914D4, 258 bytes:
// FillBufferWithCommand's type-21 (FILE ANNOUNCE) arm: the BFME1 donor's
// FillBufferWithFileAnnounceMessage (NetPacket_fill.cpp) with BFME's 'S'
// timestamp after the relay; the file ID and player mask come through the
// getters addFileAnnounceCommand uses.
void NetPacket::FillBufferWithFileAnnounceCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
	UnsignedInt offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = ncrRelay(msg);
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;

	AsciiString filename = ((CDDrive *)cmdMsg)->CDDrive::getPath();
	for (Int i = 0; i < filename.getLength(); ++i) {
		buffer[offset] = npCharAt(filename, i);
		++offset;
	}
	buffer[offset] = 0;
	++offset;

	UnsignedShort fileID = ((Rva004D5973WordField *)cmdMsg)->get();
	memcpy(buffer + offset, &fileID, sizeof(fileID));
	offset += sizeof(fileID);

	UnsignedByte playerMask = ((Rva001DCD01ByteField *)cmdMsg)->get();
	memcpy(buffer + offset, &playerMask, sizeof(playerMask));
	offset += sizeof(playerMask);
}

// ?FillBufferWithRequestGameSpyStatsAuthKeyCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x005915D6, 187 bytes:
// FillBufferWithCommand's type-5 arm: the BFME1 donor's writer of the same name
// (NetPacket_fillGameSpyStatsAuthKey.cpp) with BFME's 'S' timestamp after the
// relay. Its one string is the +0x1C field addGameSpyStatsAuthKeyCommand reads
// through CDDrive::getPath, copied unguarded through str().
void NetPacket::FillBufferWithRequestGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	UnsignedInt offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = ncrRelay(msg);
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;

	AsciiString text = ((CDDrive *)cmdMsg)->CDDrive::getPath();
	memcpy(buffer + offset, text.str(), text.getLength());
	offset += text.getLength();
	buffer[offset] = 0;
}

// ?FillBufferWithGameSpyStatsAuthKeyCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x00591691, 330 bytes:
// FillBufferWithCommand's type-6 arm: the BFME1 donor's writer of the same name
// with BFME's 'S' timestamp; the key and login are the +0x1C and +0x20 strings
// addGameSpyStatsAuthKeyCommand writes, each copied only when non-empty.
void NetPacket::FillBufferWithGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	UnsignedInt offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = ncrRelay(msg);
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;

	AsciiString key = ((CDDrive *)cmdMsg)->CDDrive::getPath();
	if (key.getLength() != 0) {
		memcpy(buffer + offset, key.str(), key.getLength());
	}
	offset += key.getLength();
	buffer[offset] = 0;
	++offset;

	AsciiString login = ((Rva002D9BC1AsciiField *)cmdMsg)->get();
	if (login.getLength() != 0) {
		memcpy(buffer + offset, login.str(), login.getLength());
	}
	offset += login.getLength();
	buffer[offset] = 0;
}

// ?FillBufferWithCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x00592AAB, 357 bytes
// with its 31-entry jump table: the BFME1 donor's per-type serializer
// dispatcher (NetPacket_FillBufferWithCommand.cpp) in the donor's case order,
// with type 20 ahead of FILE as in GetBufferSizeNeededForCommand, no
// DisconnectScreenOff arm and BFME's type-30 arm last. Its caller is
// ConstructBigCommandPacketList.
void NetPacket::FillBufferWithCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = ncrCommand(msg);
	switch (cmdMsg->getNetCommandType()) {
	case 4:
		FillBufferWithGameCommand(buffer, msg);
		break;
	case 1:
	case 2:
	case 0:
		FillBufferWithAckCommand(buffer, msg);
		break;
	case 3:
		Rva0058C80FWrite((char *)buffer, msg);
		break;
	case 23:
		FillBufferWithRouterFallbackCommand(buffer, msg);
		break;
	case 10:
		Rva0058C96CWrite((char *)buffer, msg);
		break;
	case 11:
		Rva0058CA1BWrite((char *)buffer, msg);
		break;
	case 12:
		FillBufferWithKeepAliveCommand(buffer, msg);
		break;
	case 25:
		rva0058CACAType25(buffer, msg);
		break;
	case 26:
		Rva0058CB27Write((char *)buffer, msg);
		break;
	case 13:
		Rva005910B4Write((char *)buffer, msg);
		break;
	case 27:
		Rva0058CBD9Write((char *)buffer, msg);
		break;
	case 14:
		FillBufferWithChatCommand(buffer, msg);
		break;
	case 15:
		FillBufferWithProgressMessage(buffer, msg);
		break;
	case 16:
		Rva0058CCF2Write((char *)buffer, msg);
		break;
	case 17:
		rva0058CCF2Type17(buffer, msg);
		break;
	case 20:
		Rva0058CD6AWrite((char *)buffer, msg);
		break;
	case 19:
		FillBufferWithFileCommand(buffer, msg);
		break;
	case 21:
		FillBufferWithFileAnnounceCommand(buffer, msg);
		break;
	case 22:
		Rva0058CE23Write((char *)buffer, msg);
		break;
	case 28:
		Rva0058D041Write(buffer, msg);
		break;
	case 8:
		Rva0058CEC5Write((char *)buffer, msg);
		break;
	case 7:
		Rva0058CF83Write((char *)buffer, msg);
		break;
	case 9:
		rva0058CF83Type9(buffer, msg);
		break;
	case 5:
		FillBufferWithRequestGameSpyStatsAuthKeyCommand(buffer, msg);
		break;
	case 6:
		FillBufferWithGameSpyStatsAuthKeyCommand(buffer, msg);
		break;
	case 30:
		rva0059129F(buffer, msg);
		break;
	}
}

// ?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z, retail 0x00592607, 917 bytes:
// the BFME1 donor's (NetPacket.cpp) tagged-field parser with BFME's changes
// read off the image: an 'S' field carries the timestamp, the command ID is
// kept in a dword, the readers are tested in addCommand's order, and an unknown
// type or a reader that fails returns no reference at all.
NetCommandRef *NetPacket::ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength)
{
	Int commandType = 0;
	UnsignedInt commandID = 0;
	UnsignedInt timestamp = 0;
	UnsignedInt frame = 0;
	UnsignedByte playerID = 0;
	UnsignedByte relay = 0;

	Int offset = 0;
	Bool notDone = true;
	NetCommandRef *ref = 0;

	while ((offset < (Int)dataLength) && notDone) {
		if (data[offset] == 'T') {
			++offset;
			memcpy(&commandType, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'R') {
			++offset;
			memcpy(&relay, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'P') {
			++offset;
			memcpy(&playerID, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'C') {
			++offset;
			memcpy(&commandID, data + offset, sizeof(UnsignedShort));
			offset += sizeof(UnsignedShort);
		} else if (data[offset] == 'S') {
			++offset;
			memcpy(&timestamp, data + offset, sizeof(UnsignedInt));
			offset += sizeof(UnsignedInt);
		} else if (data[offset] == 'F') {
			++offset;
			memcpy(&frame, data + offset, sizeof(UnsignedInt));
			offset += sizeof(UnsignedInt);
		} else if (data[offset] == 'D') {
			++offset;
			Int readOffset = offset;
			NetCommandMsg *msg;
			if (commandType == 4) {
				msg = readGameMessage(data, readOffset);
			} else if (commandType == 0) {
				msg = rva0058DA7E(data, readOffset);
			} else if (commandType == 1) {
				msg = rva0058DB4D(data, readOffset);
			} else if (commandType == 2) {
				msg = rva0058DC1C(data, readOffset);
			} else if (commandType == 3) {
				msg = rva0058DCEB(data, readOffset);
			} else if (commandType == 23) {
				msg = rva0058DD89(data, readOffset);
			} else if (commandType == 10) {
				msg = rva0058DDF2(data, readOffset);
			} else if (commandType == 11) {
				msg = rva0058DE5B(data, readOffset);
			} else if (commandType == 12) {
				msg = rva0058DEC5(data, readOffset);
			} else if (commandType == 25) {
				msg = rva0058DEF7(data, readOffset);
			} else if (commandType == 26) {
				msg = rva0058DF29(data, readOffset);
			} else if (commandType == 13) {
				msg = rva0059205C(data, readOffset);
			} else if (commandType == 27) {
				msg = rva0058DFB8(data, readOffset);
			} else if (commandType == 14) {
				msg = rva00592123(data, readOffset);
			} else if (commandType == 15) {
				msg = rva0058E047(data, readOffset);
			} else if (commandType == 16) {
				msg = rva0058E0B0(data, readOffset);
			} else if (commandType == 17) {
				msg = rva0058E0B0Type17(data, readOffset);
			} else if (commandType == 18) {
				msg = readWrapperMessage(data, readOffset);
			} else if (commandType == 20) {
				msg = rva0058E20D(data, readOffset);
			} else if (commandType == 19) {
				msg = (NetCommandMsg *)Rva005922FBRead((Int)data, (UnsignedInt *)&readOffset);
			} else if (commandType == 21) {
				msg = (NetCommandMsg *)Rva005923C5Read((Int)data, (UnsignedInt *)&readOffset);
			} else if (commandType == 22) {
				msg = rva0058E2D7(data, readOffset);
			} else if (commandType == 8) {
				msg = rva0058E367(data, readOffset);
			} else if (commandType == 7) {
				msg = rva0058E3F4(data, readOffset);
			} else if (commandType == 9) {
				msg = rva0058E481(data, readOffset);
			} else if (commandType == 28) {
				msg = rva0058E511(data, readOffset);
			} else if (commandType == 5) {
				msg = (NetCommandMsg *)Rva00592496Read((Int)data, (UnsignedInt *)&readOffset);
			} else if (commandType == 6) {
				msg = (NetCommandMsg *)Rva00592520Read((Int)data, (UnsignedInt *)&readOffset);
			} else if (commandType == 30) {
				msg = rva00592208(data, readOffset);
			} else {
				return 0;
			}
			if (msg == 0) {
				return 0;
			}

			msg->setTiming(timestamp, frame);
			msg->setID(commandID);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);

			ref = new NetCommandRef(msg);
			ncrSetRelay(ref, relay);

			msg->detach();
			msg = 0;

			offset = readOffset;
			notDone = false;
		}
	}

	return ref;
}

// ?FillBufferWithGameCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z, retail 0x0058C488, 696 bytes:
// the BFME1 donor's FillBufferWithGameCommand
// (NetPacket_FillBufferWithGameCommand.cpp) with BFME's 'S' timestamp field
// after the command type. FillBufferWithCommand reaches it from its type-4 arm.
void NetPacket::FillBufferWithGameCommand(UnsignedByte *buffer, NetCommandRef *ref)
{
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)(ncrCommand(ref));
	UnsignedShort offset = 0;
	GameMessage *gmsg = cmdMsg->constructGameMessage();

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'S';
	++offset;
	UnsignedInt newTimestamp = cmdMsg->getTimestamp();
	memcpy(buffer + offset, &newTimestamp, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'F';
	++offset;
	UnsignedInt newframe = cmdMsg->getExecutionFrame();
	memcpy(buffer + offset, &newframe, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = ncrRelay(ref);
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;

	Int newType = gmsg->getType();
	memcpy(buffer + offset, &newType, sizeof(Int));
	offset += sizeof(Int);

	Rva0054D54A *parser = new Rva0054D54A(gmsg);
	UnsignedByte numTypes = parser->getNumTypes();
	memcpy(buffer + offset, &numTypes, sizeof(numTypes));
	offset += sizeof(numTypes);

	Rva0054D593 *argType = parser->getFirstArgumentType();
	while (argType != 0) {
		UnsignedByte type = (UnsignedByte)(argType->getType());
		memcpy(buffer + offset, &type, sizeof(type));
		offset += sizeof(type);

		UnsignedByte argTypeCount = argType->getArgCount();
		memcpy(buffer + offset, &argTypeCount, sizeof(argTypeCount));
		offset += sizeof(argTypeCount);

		argType = argType->getNext();
	}

	Int numArgs = gmsg->getArgumentCount();
	for (Int i = 0; i < numArgs; ++i) {
		GameMessageArgumentDataType type = gmsg->getArgumentDataType(i);
		GameMessageArgumentType arg = *(gmsg->getArgument(i));

		if (type == ARGUMENTDATATYPE_INTEGER) {
			memcpy(buffer + offset, &(arg.integer), sizeof(arg.integer));
			offset += sizeof(arg.integer);
		} else if (type == ARGUMENTDATATYPE_REAL) {
			memcpy(buffer + offset, &(arg.real), sizeof(arg.real));
			offset += sizeof(arg.real);
		} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
			memcpy(buffer + offset, &(arg.boolean), sizeof(arg.boolean));
			offset += sizeof(arg.boolean);
		} else if (type == ARGUMENTDATATYPE_OBJECTID) {
			memcpy(buffer + offset, &(arg.objectID), sizeof(arg.objectID));
			offset += sizeof(arg.objectID);
		} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
			memcpy(buffer + offset, &(arg.drawableID), sizeof(arg.drawableID));
			offset += sizeof(arg.drawableID);
		} else if (type == ARGUMENTDATATYPE_TEAMID) {
			memcpy(buffer + offset, &(arg.teamID), sizeof(arg.teamID));
			offset += sizeof(arg.teamID);
		} else if (type == ARGUMENTDATATYPE_LOCATION) {
			memcpy(buffer + offset, &(arg.location), sizeof(arg.location));
			offset += sizeof(arg.location);
		} else if (type == ARGUMENTDATATYPE_PIXEL) {
			memcpy(buffer + offset, &(arg.pixel), sizeof(arg.pixel));
			offset += sizeof(arg.pixel);
		} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
			memcpy(buffer + offset, &(arg.pixelRegion), sizeof(arg.pixelRegion));
			offset += sizeof(arg.pixelRegion);
		} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
			memcpy(buffer + offset, &(arg.timestamp), sizeof(arg.timestamp));
			offset += sizeof(arg.timestamp);
		} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
			memcpy(buffer + offset, &(arg.wChar), sizeof(arg.wChar));
			offset += sizeof(arg.wChar);
		}
	}

	::delete parser;
	parser = 0;

	::delete gmsg;
	gmsg = 0;
}

// ?writeGameMessageArgumentToPacket@NetPacket@@IAEXW4GameMessageArgumentDataType@@TGameMessageArgumentType@@@Z, retail 0x0058D826, 265 bytes:
// ZH's writeGameMessageArgumentToPacket: copy the argument's member for its
// type. addGameCommand passes the 16-byte argument union by value, which is
// how retail's caller builds the call (four movsd into the outgoing slot).
void NetPacket::writeGameMessageArgumentToPacket(GameMessageArgumentDataType type, GameMessageArgumentType arg)
{
	if (type == ARGUMENTDATATYPE_INTEGER) {
		memcpy(m_packet + m_packetLen, &(arg.integer), sizeof(arg.integer));
		m_packetLen += sizeof(arg.integer);
	} else if (type == ARGUMENTDATATYPE_REAL) {
		memcpy(m_packet + m_packetLen, &(arg.real), sizeof(arg.real));
		m_packetLen += sizeof(arg.real);
	} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
		memcpy(m_packet + m_packetLen, &(arg.boolean), sizeof(arg.boolean));
		m_packetLen += sizeof(arg.boolean);
	} else if (type == ARGUMENTDATATYPE_OBJECTID) {
		memcpy(m_packet + m_packetLen, &(arg.objectID), sizeof(arg.objectID));
		m_packetLen += sizeof(arg.objectID);
	} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
		memcpy(m_packet + m_packetLen, &(arg.drawableID), sizeof(arg.drawableID));
		m_packetLen += sizeof(arg.drawableID);
	} else if (type == ARGUMENTDATATYPE_TEAMID) {
		memcpy(m_packet + m_packetLen, &(arg.teamID), sizeof(arg.teamID));
		m_packetLen += sizeof(arg.teamID);
	} else if (type == ARGUMENTDATATYPE_LOCATION) {
		memcpy(m_packet + m_packetLen, &(arg.location), sizeof(arg.location));
		m_packetLen += sizeof(arg.location);
	} else if (type == ARGUMENTDATATYPE_PIXEL) {
		memcpy(m_packet + m_packetLen, &(arg.pixel), sizeof(arg.pixel));
		m_packetLen += sizeof(arg.pixel);
	} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
		memcpy(m_packet + m_packetLen, &(arg.pixelRegion), sizeof(arg.pixelRegion));
		m_packetLen += sizeof(arg.pixelRegion);
	} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
		memcpy(m_packet + m_packetLen, &(arg.timestamp), sizeof(arg.timestamp));
		m_packetLen += sizeof(arg.timestamp);
	} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
		memcpy(m_packet + m_packetLen, &(arg.wChar), sizeof(arg.wChar));
		m_packetLen += sizeof(arg.wChar);
	}
}

// ?rva0058DA7E@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DA7E 207B.
// Static NetAckBoth factory reading word + byte + two dwords from data+offset.
// Evidence: sibling 0x0058DB4D 207B plus new-0x28 plus rowed
// ??0NetAckBothCommandMsg@@QAE@XZ 0x004D568F plus triple memcpy plus word
// setter 0x004D59AC byte setter 0x004D576C plus direct stores to +0x20 +0x24.
NetCommandMsg *NetPacket::rva0058DA7E(unsigned char *data, int &readOffset)
{
	NetAckBothCommandMsg *msg = new NetAckBothCommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}

// ?rva0058DB4D@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DB4D 207B.
// Static NetAckStage1 factory; rowed ??0NetAckStage1CommandMsg@@QAE@XZ 0x004D56E6.
NetCommandMsg *NetPacket::rva0058DB4D(unsigned char *data, int &readOffset)
{
	NetAckStage1CommandMsg *msg = new NetAckStage1CommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}

// ?rva0058DC1C@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DC1C 207B.
// Static NetAckStage2 factory; rowed ??0NetAckStage2CommandMsg@@QAE@XZ.
NetCommandMsg *NetPacket::rva0058DC1C(unsigned char *data, int &readOffset)
{
	NetAckStage2CommandMsg *msg = new NetAckStage2CommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}

// ?rva0058DCEB@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DCEB 158B.
// Static NetCommandMsg factory reading three 4-byte fields from data+offset.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x28 plus
// Rva004CEEC3 ctor plus triple memcpy-4 direct store to +0x1c +0x20 +0x24.
NetCommandMsg *NetPacket::rva0058DCEB(unsigned char *data, int &readOffset)
{
	Rva004CEEC3 *msg = new Rva004CEEC3();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 4);
	readOffset += 4;
	msg->m_1c = v0;
	unsigned int v1 = 0;
	memcpy(&v1, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v1;
	unsigned int v2 = 0;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v2;
	return (NetCommandMsg *)msg;
}

// ?rva0058DD89@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @ 0x0058DD89 (105B): static
// factory news 0x3C Rva004CEEE8 then reads 8 bytes into local order and calls
// setPlayerOrder. Evidence: sibling factories 0x0058DCEB and 0x0058E047 plus
// rowed Rva004CEEE8 0x004CEEE8 plus rowed setPlayerOrder 0x004D577B. Callers
// 0x00592756 and 0x00594089.
NetCommandMsg *NetPacket::rva0058DD89(unsigned char *data, int &readOffset)
{
	Rva004CEEE8 *msg = new Rva004CEEE8();
	int order[8];
	for (int i = 0; i < 8; ++i, ++readOffset)
		order[i] = data[readOffset];
	((BFMENetRouterFallbackCommandMsg *)msg)->setPlayerOrder(order);
	return (NetCommandMsg *)msg;
}

// ?rva0058DDF2@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058DDF2, 105 bytes:
// the same 1-byte-flag reader as rva0058E047 constructing the rowed Rva004D5795
// message (same 0x20 size) instead of Rva004D582B.
NetCommandMsg *NetPacket::rva0058DDF2(unsigned char *data, int &readOffset)
{
	Rva004D5795 *msg = new Rva004D5795();
	bool flag = false;
	memcpy(&flag, data + readOffset, 1);
	readOffset += 1;
	((Script *)msg)->setActive(flag);
	return (NetCommandMsg *)msg;
}

// ?rva0058DE5B@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z 0x0058DE5B (106B).
NetCommandMsg *NetPacket::rva0058DE5B(UnsignedByte *data, Int &readOffset)
{
	Rva004D57AE *msg = new Rva004D57AE;
	UnsignedInt v = 0;
	memcpy(&v, data + readOffset, sizeof(v));
	readOffset += sizeof(v);
	msg->setPlayerIndex(v);
	return msg;
}

// ?rva0058DEC5@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DEC5 50B.
// Static NetCommandMsg factory constructing KeepAlive with no fields read.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x1c plus
// NetKeepAliveCommandMsg ctor plus uniform factory signature.
NetCommandMsg *NetPacket::rva0058DEC5(unsigned char *data, int &readOffset)
{
	(void)data;
	(void)readOffset;
	NetKeepAliveCommandMsg *msg = new NetKeepAliveCommandMsg();
	return (NetCommandMsg *)msg;
}

// ?rva0058DEF7@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DEF7 50B.
// Static NetCommandMsg factory constructing DisconnectKeepAlive with no fields read.
NetCommandMsg *NetPacket::rva0058DEF7(unsigned char *data, int &readOffset)
{
	(void)data;
	(void)readOffset;
	NetDisconnectKeepAliveCommandMsg *msg = new NetDisconnectKeepAliveCommandMsg();
	return (NetCommandMsg *)msg;
}

// ?rva0058DF29@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058DF29, 143 bytes:
// ZH's readDisconnectPlayerMessage (slot byte, then disconnect frame) on the
// rowed type-26 ctor Rva004D57F1; both setters are the folded 10-byte bodies
// sendDisconnectCommand's pins name. Same shape as rva0058DFB8 below.
NetCommandMsg *NetPacket::rva0058DF29(UnsignedByte *data, Int &readOffset)
{
	Rva004D57F1 *msg = new Rva004D57F1();
	UnsignedByte slot = 0;
	memcpy(&slot, data + readOffset, sizeof(slot));
	readOffset += sizeof(slot);
	((NetDisconnectPlayerCommandMsg *)msg)->setDisconnectSlot(slot);
	UnsignedInt disconnectFrame = 0;
	memcpy(&disconnectFrame, data + readOffset, sizeof(disconnectFrame));
	readOffset += sizeof(disconnectFrame);
	((NetDisconnectPlayerCommandMsg *)msg)->setDisconnectFrame(disconnectFrame);
	return (NetCommandMsg *)msg;
}

// ?rva0059205C@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0059205C, 199 bytes:
// ZH's readDisconnectChatMessage on the rowed type-13 ctor Rva004D60CA: a
// length byte, that many UTF-16 characters, then setText.
NetCommandMsg *NetPacket::rva0059205C(UnsignedByte *data, Int &readOffset)
{
	Rva004D60CA *msg = new Rva004D60CA();
	UnsignedShort text[256];
	UnsignedByte length;
	memcpy(&length, data + readOffset, sizeof(UnsignedByte));
	++readOffset;
	memcpy(text, data + readOffset, length * sizeof(UnsignedShort));
	readOffset += length * sizeof(UnsignedShort);
	text[length] = 0;

	UnicodeString unitext;
	unitext.set(text);
	msg->rva004D6187(unitext);
	return (NetCommandMsg *)msg;
}

// ?rva00592123@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x00592123, 229 bytes:
// ZH's readChatMessage on the rowed type-14 ctor Rva004D6134: the disconnect
// chat text plus a player mask, stored through the folded +0x20 dword setter.
NetCommandMsg *NetPacket::rva00592123(UnsignedByte *data, Int &readOffset)
{
	Rva004D6134 *msg = new Rva004D6134();
	UnsignedShort text[256];
	UnsignedByte length;
	Int playerMask;
	memcpy(&length, data + readOffset, sizeof(UnsignedByte));
	++readOffset;
	memcpy(text, data + readOffset, length * sizeof(UnsignedShort));
	readOffset += length * sizeof(UnsignedShort);
	text[length] = 0;
	memcpy(&playerMask, data + readOffset, sizeof(Int));
	readOffset += sizeof(Int);

	UnicodeString unitext;
	unitext.set(text);
	((Rva004D60CA *)msg)->rva004D6187(unitext);
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(playerMask);
	return (NetCommandMsg *)msg;
}

// ?rva00592208@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x00592208, 243 bytes:
// the type-30 reader, the inverse of rva005936DB: the chat readers' text,
// then the +0x1C and +0x20 dwords, stored after the text is set.
NetCommandMsg *NetPacket::rva00592208(UnsignedByte *data, Int &readOffset)
{
	NetType30CommandMsg *msg = (NetType30CommandMsg *)new Rva004D67D0();
	UnsignedShort text[256];
	UnsignedByte length;
	UnsignedInt field1c;
	UnsignedInt field20;
	memcpy(&length, data + readOffset, sizeof(UnsignedByte));
	++readOffset;
	memcpy(text, data + readOffset, length * sizeof(UnsignedShort));
	readOffset += length * sizeof(UnsignedShort);
	text[length] = 0;
	memcpy(&field1c, data + readOffset, sizeof(UnsignedInt));
	readOffset += sizeof(UnsignedInt);
	memcpy(&field20, data + readOffset, sizeof(UnsignedInt));
	readOffset += sizeof(UnsignedInt);

	UnicodeString unitext;
	unitext.set(text);
	((Rva004D05D7 *)msg)->rva004D05D7(unitext);
	msg->m_1c = field1c;
	msg->m_20 = field20;
	return msg;
}

// ?readGameMessage@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x00591EA6, 438 bytes:
// ZH's readGameMessage with a range check on the message type (an
// out-of-range type frees the message and returns NULL): the argument-type
// runs go into a GameMessageParser, then each argument is read by type.
NetCommandMsg *NetPacket::readGameMessage(UnsignedByte *data, Int &readOffset)
{
	NetGameCommandMsg *msg = new NetGameCommandMsg();

	Int newType;
	memcpy(&newType, data + readOffset, sizeof(newType));
	readOffset += sizeof(newType);
	if (newType <= 0 || newType >= 0x7EE) {
		::delete msg;
		return 0;
	}
	((NetDisconnectPlayerCommandMsg *)msg)->setDisconnectFrame(newType);

	UnsignedByte numArgTypes = 0;
	memcpy(&numArgTypes, data + readOffset, sizeof(numArgTypes));
	readOffset += sizeof(numArgTypes);

	Int totalArgs = 0;
	Rva0054D54A *parser = new Rva0054D54A();
	Int j = 0;
	for (; j < numArgTypes; ++j) {
		UnsignedByte type = (UnsignedByte)ARGUMENTDATATYPE_UNKNOWN;
		memcpy(&type, data + readOffset, sizeof(type));
		readOffset += sizeof(type);

		UnsignedByte argCount = 0;
		memcpy(&argCount, data + readOffset, sizeof(argCount));
		readOffset += sizeof(argCount);

		((Rva0054D5D3 *)parser)->rva0054D5D3((void *)type, (void *)argCount);
		totalArgs += argCount;
	}

	Rva0054D593 *parserArgType = parser->getFirstArgumentType();
	GameMessageArgumentDataType lasttype = ARGUMENTDATATYPE_UNKNOWN;
	Int argsLeftForType = 0;
	if (parserArgType != 0) {
		lasttype = parserArgType->getType();
		argsLeftForType = parserArgType->getArgCount();
	}
	for (j = 0; j < totalArgs; ++j) {
		Rva00590D19Add(lasttype, msg, data, &readOffset, newType);

		--argsLeftForType;
		if (argsLeftForType == 0) {
			if (parserArgType == 0) {
				return 0;
			}

			parserArgType = parserArgType->getNext();
			if (parserArgType != 0) {
				argsLeftForType = parserArgType->getArgCount();
				lasttype = parserArgType->getType();
			}
		}
	}

	::delete parser;
	parser = 0;

	return (NetCommandMsg *)msg;
}

// ?rva0058DFB8@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DFB8 143B.
// Static NetCommandMsg factory reading 1-byte bool plus 4-byte enum from data+offset.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x24 plus
// Rva004D580E ctor plus memcpy-1-4 plus dup_0006ede3 row TYPES wrong
// (object-symbol ?setActive@Script@@QAEX_N@Z) plus dup_00317b9b row TYPES wrong
// (object-symbol ?setCurrentTask@DozerAIUpdate@@UAEXW4DozerTask@@@Z); declared as used.
NetCommandMsg *NetPacket::rva0058DFB8(unsigned char *data, int &readOffset)
{
	Rva004D580E *msg = new Rva004D580E();
	bool flag = false;
	memcpy(&flag, data + readOffset, 1);
	readOffset += 1;
	((Script *)msg)->setActive(flag);
	DozerTask task = DOZER_TASK_ZERO;
	memcpy(&task, data + readOffset, 4);
	readOffset += 4;
	((DozerAIUpdate *)msg)->DozerAIUpdate::setCurrentTask(task);
	return (NetCommandMsg *)msg;
}

// ?rva0058E047@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E047 105B.
// Static NetCommandMsg factory reading 1-byte relay flag from data+offset.
// Evidence: unlock lane plus sibling 0x0058E511 plus new-0x20 plus
// Rva004D582B ctor plus memcpy-1 plus dup_0006EDE3 row TYPES wrong;
// retail calls thiscall bool setter at 0x0006EDE3 whose row is gen-alias
// YAXXZ but object-symbol is ?setActive@Script@@QAEX_N@Z; declared as used.
NetCommandMsg *NetPacket::rva0058E047(unsigned char *data, int &readOffset)
{
	Rva004D582B *msg = new Rva004D582B();
	bool flag = false;
	memcpy(&flag, data + readOffset, 1);
	readOffset += 1;
	((Script *)msg)->setActive(flag);
	return (NetCommandMsg *)msg;
}

// ?rva0058E0B0@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E0B0 50B.
// Static NetCommandMsg factory allocating base message only.
// Evidence: neighbours 0x0058E047 and 0x0058E367 same NetPacket static factory
// shape PAEAAH plus same flags; new-0x1C plus NetCommandMsg base ctor row;
// same two free-function callers as 0x0058E481 family; no payload reads.
NetCommandMsg *NetPacket::rva0058E0B0(unsigned char *data, int &readOffset)
{
	return new NetCommandMsg();
}

// ?rva0058E0B0Type17@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z: the type-17 reader,
// identical to rva0058E0B0 and folded onto 0x0058E0B0 by the retail linker (ICF);
// defined so ConstructNetCommandMsgFromRawData's call resolves in the link.
NetCommandMsg *NetPacket::rva0058E0B0Type17(unsigned char *data, int &readOffset)
{
	return new NetCommandMsg();
}

// ?rva0058E20D@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E20D 202B.
// Static NetPacket factory for Rva004D58DE (0x2C): new via rowed ctor 0x004D58DE,
// dword at +0x1C via 4B memcpy, word at +0x20 via 2B memcpy, dword len via 4B
// memcpy then new[] buffer plus memcpy plus rowed SetData 0x004D5925.
NetCommandMsg *NetPacket::rva0058E20D(unsigned char *data, int &readOffset)
{
	Rva004D58DE *msg = new Rva004D58DE();
	UnsignedInt v0 = 0;
	memcpy(&v0, data + readOffset, 4);
	readOffset += 4;
	msg->m_1c = v0;
	UnsignedInt v1 = 0;
	memcpy(&v1, data + readOffset, 2);
	readOffset += 2;
	msg->m_20 = (UnsignedShort)v1;
	UnsignedInt len = 0;
	memcpy(&len, data + readOffset, 4);
	readOffset += 4;
	unsigned char *buf = new unsigned char[len];
	memcpy(buf, data + readOffset, len);
	readOffset += len;
	msg->rva004D5925(buf, len);
	return (NetCommandMsg *)msg;
}

// ?rva0058E2D7@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058E2D7, 144 bytes.
// Static NetPacket factory reading word then dword: new Rva004D598E (0x24)
// via rowed ctor 0x004D598E, memcpy 2B into v0 then WordSlot set at +0x1C
// via rowed 0x004D59AC, memcpy 4B into v1 then setLeavingPlayerID at +0x20
// via rowed 0x00317B9B.
NetCommandMsg *NetPacket::rva0058E2D7(unsigned char *data, int &readOffset)
{
	Rva004D598E *msg = new Rva004D598E();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	Int v1 = 0;
	memcpy(&v1, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(v1);
	return (NetCommandMsg *)msg;
}

// ?rva0058E367@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E367 141B.
// Static NetCommandMsg factory reading leaving-player ID then leave frame.
// Evidence: BFME1 donor NetPacket_read.cpp readInformPlayerLeaveFrameMessage
// (same new plus setLeavingPlayerID plus setLeaveFrame order); neighbours
// 0x0058E047/0x0058E511 (same NetPacket static factory shape PAEAAH);
// Rva004D59D1 ctor row (type 8 plus vtable 0x860274); setLeaveFrame row.
// Retail defaults playerID to -1 where the donor uses 0 (or -1 proves it).
// The 10B setter at 0x00317B9B is rowed YAXXZ (TYPES wrong); declared as used.
NetCommandMsg *NetPacket::rva0058E367(unsigned char *data, int &readOffset)
{
	Rva004D59D1 *msg = new Rva004D59D1();
	Int playerID = -1;
	memcpy(&playerID, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(playerID);
	UnsignedInt leaveFrame = 0;
	memcpy(&leaveFrame, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeaveFrame(leaveFrame);
	return (NetCommandMsg *)msg;
}

// ?rva0058E3F4@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E3F4 141B.
// Static NetCommandMsg factory reading player index then leaving-player ID.
// Evidence: neighbours 0x0058E367 and 0x0058E481 same NetPacket static factory
// shape PAEAAH; new-0x24 plus Rva004D5A10 ctor row; memcpy plus Rva004D57AE
// setter plus-0x1C; second setter at 0x00317B9B writes plus-0x20; first dword
// defaults -1 like 0x0058E367.
NetCommandMsg *NetPacket::rva0058E3F4(unsigned char *data, int &readOffset)
{
	Rva004D5A10 *msg = new Rva004D5A10();
	UnsignedInt playerIndex = (UnsignedInt)-1;
	memcpy(&playerIndex, data + readOffset, 4);
	readOffset += 4;
	((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
	Int field20 = 0;
	memcpy(&field20, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(field20);
	return (NetCommandMsg *)msg;
}

// ?rva0058E481@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E481 144B.
// Static NetCommandMsg factory reading player index then second dword.
// Evidence: neighbours 0x0058E367 and 0x0058E511; new-0x24 plus Rva004D5A30
// ctor row type 9 vtable 0x860294; memcpy plus Rva004D57AE setter row at
// plus-0x1C; second setter at 0x00317B9B writes plus-0x20.
NetCommandMsg *NetPacket::rva0058E481(unsigned char *data, int &readOffset)
{
	Rva004D5A30 *msg = new Rva004D5A30();
	UnsignedInt playerIndex = 0;
	memcpy(&playerIndex, data + readOffset, 4);
	readOffset += 4;
	((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
	Int field20 = 0;
	memcpy(&field20, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(field20);
	return (NetCommandMsg *)msg;
}

// ?rva0058E511@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E511 106B.
// Static NetCommandMsg factory reading player index from data+offset.
// Evidence: new-0x20 plus Rva004D59B8 ctor plus memcpy plus Rva004D57AE setter.
NetCommandMsg *NetPacket::rva0058E511(unsigned char *data, int &readOffset)
{
	Rva004D59B8 *msg = new Rva004D59B8();
	UnsignedInt playerIndex = 0;
	memcpy(&playerIndex, data + readOffset, 4);
	readOffset += 4;
	((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
	return (NetCommandMsg *)msg;
}

// ?rva0058E57B@NetPacket@@QAEHXZ @0x0058E57B 57B.
// NetPacket thiscall reading m_packetLen at plus-0x1E0: idiv-8 plus remainder
// inc is ceil len-div-8; nested 8-step loops with break on len.
Int NetPacket::rva0058E57B()
{
	Int n = m_packetLen / 8;
	if (m_packetLen % 8 != 0) {
		++n;
	}
	for (Int i = 0; i < n; ++i) {
		for (Int j = 0; j < 8; ++j) {
			if (i * 8 + j >= m_packetLen) {
				break;
			}
		}
	}
	return n;
}

NetPacket::NetPacket()
{
	init();
}

NetPacket::NetPacket(TransportMessage *msg)
{
	init();
	m_dest.ip = msg->addr;
	m_dest.port = msg->port;
	m_packetLen = msg->length;
	memcpy(m_packet, msg->data, sizeof(m_packet));
	m_numCommands = -1;
}

// ?addInformPlayerLeaveFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058E652, 664 bytes:
// addCommand's type-8 arm (dispatcher 0x005944D7, table 0x0059460D), BFME1's
// NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME. Same T/F/R/P/C/D blocks and two-dword
// payload as the BFME1 donor body, plus BFME's S block; payload +0x20 then +0x1C.
Bool NetPacket::addInformPlayerLeaveFrameCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D18C(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058E8EA@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058E8EA, 664 bytes:
// addCommand's arm for types 7 and 9 (BFME1's REQUESTPLAYERLEAVE and
// REQUESTFRAMEDATA, whose identical bodies fold here): T/S/F/R/P/C/D, then the
// +0x1C and +0x20 dwords. Folded, so it keeps its address name.
Bool NetPacket::rva0058E8EA(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D18C(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058E8EARequestFrameData@NetPacket@@IAE_NPAVNetCommandRef@@@Z: addCommand's
// RequestFrameData arm, identical to rva0058E8EA and ICF-folded onto 0x0058E8EA;
// defined so the arm's call resolves in the link.
Bool NetPacket::rva0058E8EARequestFrameData(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D18C(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addDisconnectFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058EB82, 621 bytes:
// addCommand's type-28 arm. BFME2's enum inserts one type after FILE (the
// enum gap moves from 23 to 24 and router fallback from 22 to 23), so this is
// BFME1's DISCONNECTFRAME: ZH's T/F/R/P/C/D plus S, then one dword.
Bool NetPacket::addDisconnectFrameCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D211(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058EDEF@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058EDEF, 649 bytes:
// addCommand's type-20 arm, the type BFME2 inserts: room check rva0058D296,
// T/R/S/P/C/D, then Rva004D58DE's +0x1C dword, +0x20 word, +0x28 length and
// that many bytes of the +0x24 buffer.
Bool NetPacket::rva0058EDEF(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D296(msg)) {
		Rva004D58DE *cmdMsg = (Rva004D58DE *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedInt value = cmdMsg->get1c();
		memcpy(m_packet + m_packetLen, &value, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedShort shortValue = cmdMsg->get20();
		memcpy(m_packet + m_packetLen, &shortValue, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		memcpy(m_packet + m_packetLen, cmdMsg->getData(), dataLength);
		m_packetLen += dataLength;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addFileProgressCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058F078, 594 bytes:
// addCommand's type-22 arm (BFME1's FILEPROGRESS shifted by the inserted
// type): ZH's T/R/P/C/D plus S, then the file ID word and the progress dword.
Bool NetPacket::addFileProgressCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D310(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedShort fileID = ((Rva004D5767WordField *)cmdMsg)->get();
		memcpy(m_packet + m_packetLen, &fileID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		UnsignedInt progress = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &progress, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addWrapperCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058F2CA, 793 bytes:
// addCommand's type-18 arm through isRoomForWrapperMessage: ZH's T/R/P/C/D
// plus S, then the wrapped command ID, chunk number, chunk count, total length,
// data length, data offset and the chunk bytes, in ZH's order.
Bool NetPacket::addWrapperCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForWrapperMessage(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedShort wrappedCommandID = cmdMsg->getWrappedCommandID();
		memcpy(m_packet + m_packetLen, &wrappedCommandID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		UnsignedInt chunkNumber = cmdMsg->getChunkNumber();
		memcpy(m_packet + m_packetLen, &chunkNumber, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt numChunks = cmdMsg->getNumChunks();
		memcpy(m_packet + m_packetLen, &numChunks, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt totalDataLength = cmdMsg->getTotalDataLength();
		memcpy(m_packet + m_packetLen, &totalDataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt dataOffset = cmdMsg->getDataOffset();
		memcpy(m_packet + m_packetLen, &dataOffset, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedByte *data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, data, dataLength);
		m_packetLen += dataLength;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058F5E3@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058F5E3, 501 bytes:
// addCommand's arm for types 16 and 17 (BFME1's LOADCOMPLETE and
// TIMEOUTSTART, which already share one room check there): T/R/S/P/C/D and no
// payload. Folded, so it keeps its address name.
Bool NetPacket::rva0058F5E3(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D461(msg)) {
		NetCommandMsg *cmdMsg = (NetCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058F5E3TimeOutStart@NetPacket@@IAE_NPAVNetCommandRef@@@Z: addCommand's
// TimeOutGameStart arm, identical to rva0058F5E3 and ICF-folded onto 0x0058F5E3;
// defined so the arm's call resolves in the link.
Bool NetPacket::rva0058F5E3TimeOutStart(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D461(msg)) {
		NetCommandMsg *cmdMsg = (NetCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addProgressMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058F7D8, 423 bytes:
// addCommand's type-15 arm: ZH's T/R/P/D plus S, then the percentage byte.
Bool NetPacket::addProgressMessage(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D4BA(msg)) {
		NetProgressCommandMsg *cmdMsg = (NetProgressCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		m_packet[m_packetLen] = cmdMsg->getPercentage();
		++m_packetLen;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addDisconnectVoteCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058F97F, 587 bytes:
// addCommand's type-27 arm (BFME1's DISCONNECTVOTE shifted by the inserted
// type): ZH's T/R/P/C/D plus S, then the slot byte and the +0x20 vote frame.
Bool NetPacket::addDisconnectVoteCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D513(msg)) {
		NetProgressCommandMsg *cmdMsg = (NetProgressCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte percentage = cmdMsg->getPercentage();
		memcpy(m_packet + m_packetLen, &percentage, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		UnsignedInt dataLength = ((NetWrapperCommandMsg *)cmdMsg)->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addDisconnectPlayerCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058FBCA, 587 bytes:
// addCommand's type-26 arm (BFME1's DISCONNECTPLAYER shifted by the inserted
// type): ZH's T/R/P/C/D plus S, then the slot byte and the +0x24 frame.
Bool NetPacket::addDisconnectPlayerCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D513(msg)) {
		NetProgressCommandMsg *cmdMsg = (NetProgressCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte percentage = cmdMsg->getPercentage();
		memcpy(m_packet + m_packetLen, &percentage, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		UnsignedInt dataOffset = ((NetWrapperCommandMsg *)cmdMsg)->getDataOffset();
		memcpy(m_packet + m_packetLen, &dataOffset, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058FE15@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058FE15, 400 bytes:
// addCommand's arm for types 12 and 25 (BFME1's KEEPALIVE and, shifted,
// DISCONNECTKEEPALIVE): T/R/S/P/D and no payload. Folded, so it keeps its
// address name.
Bool NetPacket::rva0058FE15(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D461(msg)) {
		NetCommandMsg *cmdMsg = (NetCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva0058FE15DisconnectKeepAlive@NetPacket@@IAE_NPAVNetCommandRef@@@Z: addCommand's
// DisconnectKeepAlive arm, identical to rva0058FE15 and ICF-folded onto 0x0058FE15;
// defined so the arm's call resolves in the link.
Bool NetPacket::rva0058FE15DisconnectKeepAlive(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D461(msg)) {
		NetCommandMsg *cmdMsg = (NetCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addDestroyPlayerCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0058FFA5, 621 bytes:
// addCommand's type-11 arm: ZH's T/R/F/P/C/D plus S, then the player index.
Bool NetPacket::addDestroyPlayerCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D211(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte * data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, &data, sizeof(UnsignedByte *));
		m_packetLen += sizeof(UnsignedByte *);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addRouterFallbackCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00590212, 534 bytes:
// addCommand's type-23 arm (BFME1's type 22). The loop follows the BFME1 donor
// NetPacket_addRouterFallbackCommand.cpp: keeping the order pointer in a local
// keeps retail's indexed loop instead of a pointer induction.
Bool NetPacket::addRouterFallbackCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D58A(msg)) {
		BFMENetRouterFallbackCommandMsg *cmdMsg = (BFMENetRouterFallbackCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		const Int *playerOrder = cmdMsg->m_playerOrder;
		for (Int i = 0; i < 8; ++i)
			m_packet[m_packetLen + i] = (UnsignedByte)playerOrder[i];
		m_packetLen += 8;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addPlayerLeaveCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00590428, 625 bytes:
// addCommand's type-10 arm: ZH's T/R/F/P/C/D plus S, then the leaving player
// byte (+0x1C, folded onto getPercentage).
Bool NetPacket::addPlayerLeaveCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0058D601(msg)) {
		NetProgressCommandMsg *cmdMsg = (NetProgressCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte percentage = cmdMsg->getPercentage();
		memcpy(m_packet + m_packetLen, &percentage, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		++m_numCommands;
		return true;
	}
	return false;
}

// ?addFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00590699, 651 bytes:
// addCommand's type-3 arm through isRoomForFrameMessage: T/R/P/S/F, an
// unconditional C, then D and three dwords. Unlike ZH there is no repeat path
// and no needNewCommandID flag.
Bool NetPacket::addFrameCommand(NetCommandRef *msg)
{
	if (isRoomForFrameMessage(msg)) {
		NetFrameCommandMsg *cmdMsg = (NetFrameCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = cmdMsg->getTimestamp();
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = cmdMsg->getExecutionFrame();
		}
		m_packet[m_packetLen] = 'C';
		++m_packetLen;
		UnsignedShort newID = cmdMsg->getID();
		memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedInt value1C = cmdMsg->get1c();
		memcpy(m_packet + m_packetLen, &value1C, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt value20 = cmdMsg->get20();
		memcpy(m_packet + m_packetLen, &value20, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt value24 = cmdMsg->get24();
		memcpy(m_packet + m_packetLen, &value24, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		++m_numCommands;
		return true;
	}
	return false;
}

// ?addAckCommand@NetPacket@@IAE_NPAVNetCommandRef@@GEII@Z, retail 0x00591B1B, 498 bytes:
// the shared ack writer behind the folded ack arm rva005939EE. ZH's
// addAckCommand (isAckRepeat 'Z' path, then room check rva0058D70B, T/P/D,
// command ID word and original player byte) with two more dwords, the ack
// message's +0x20/+0x24, where the BFME1 donor has one. The repeat path clears
// m_lastCommand outside the delete test, as in the donor.
Bool NetPacket::addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt ackValue20, UnsignedInt ackValue24)
{
	if (isAckRepeat(msg)) {
		if (m_packetLen >= MAX_PACKET_SIZE) {
			return false;
		}
		m_packet[m_packetLen] = 'Z';
		++m_packetLen;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
		}
		m_lastCommand = 0;
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	if (rva0058D70B(msg)) {
		NetCommandMsg *cmdMsg = ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
		}
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		memcpy(m_packet + m_packetLen, &commandID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		memcpy(m_packet + m_packetLen, &originalPlayerID, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		memcpy(m_packet + m_packetLen, &ackValue20, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		memcpy(m_packet + m_packetLen, &ackValue24, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		++m_numCommands;
		return true;
	}
	return false;
}

// ?rva005939EE@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x005939EE, 49 bytes:
// addCommand's arm for types 0, 1 and 2 (ACKBOTH/ACKSTAGE1/ACKSTAGE2, whose
// identical wrappers fold here; BFME1's NetPacket_ackCommands.cpp shape).
// getCommandID/getOriginalPlayerID are the pinned ack getters (+0x1C word,
// +0x1E byte); the +0x20/+0x24 dwords go through inline getters, which is
// what loads them into registers before the pushes. Folded, so it keeps its
// address name.
Bool NetPacket::rva005939EE(NetCommandRef *msg)
{
	NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)ncrCommand(msg);
	return addAckCommand(msg, ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->get20(), ackmsg->get24());
}

// ?rva005939EEAckStage1@NetPacket@@IAE_NPAVNetCommandRef@@@Z: addCommand's ACKSTAGE1
// arm, identical to rva005939EE and ICF-folded onto 0x005939EE.
Bool NetPacket::rva005939EEAckStage1(NetCommandRef *msg)
{
	NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)ncrCommand(msg);
	return addAckCommand(msg, ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->get20(), ackmsg->get24());
}

// ?rva005939EEAckStage2@NetPacket@@IAE_NPAVNetCommandRef@@@Z: addCommand's ACKSTAGE2
// arm, identical to rva005939EE and ICF-folded onto 0x005939EE.
Bool NetPacket::rva005939EEAckStage2(NetCommandRef *msg)
{
	NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)ncrCommand(msg);
	return addAckCommand(msg, ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->get20(), ackmsg->get24());
}

// ?addDisconnectChatCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x005931D1, 538 bytes:
// addCommand's type-13 arm (DISCONNECTCHAT): T/R/S/P/D, then the text's
// length byte and UTF-16 characters from the +0x1C UnicodeString.
Bool NetPacket::addDisconnectChatCommand(NetCommandRef *msg)
{
	if (rva0059192A(msg)) {
		NetCommandMsg *cmdMsg = ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
		}
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnicodeString unitext = ((Rva004D6119 *)cmdMsg)->rva004D6119();
		UnsignedByte length = unitext.getLength();
		memcpy(m_packet + m_packetLen, &length, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		memcpy(m_packet + m_packetLen, unitext.str(), length * sizeof(unsigned short));
		m_packetLen += length * sizeof(unsigned short);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addChatCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x005933EB, 752 bytes:
// addCommand's type-14 arm (CHAT): ZH's T/F/R/P/C/D plus S, then the
// length byte, the UTF-16 text and the player mask dword.
Bool NetPacket::addChatCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva005919AF(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnicodeString unitext = ((Rva004D6119 *)cmdMsg)->rva004D6119();
		UnsignedByte length = unitext.getLength();
		Int playerMask = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &length, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		memcpy(m_packet + m_packetLen, unitext.str(), length * sizeof(unsigned short));
		m_packetLen += length * sizeof(unsigned short);
		memcpy(m_packet + m_packetLen, &playerMask, sizeof(Int));
		m_packetLen += sizeof(Int);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?rva005936DB@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x005936DB, 787 bytes:
// addCommand's type-30 arm, a BFME2 wide-string message: T/S/F/R/P/C/D,
// then the +0x24 text's length and characters and the +0x1C/+0x20 dwords.
// Not in the BFME1 donor, so it keeps its address name.
Bool NetPacket::rva005936DB(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva00591A65(msg)) {
		NetType30CommandMsg *cmdMsg = (NetType30CommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnicodeString unitext = ((Rva0023E928 *)cmdMsg)->rva0023E928();
		UnsignedByte length = unitext.getLength();
		UnsignedInt value1C = cmdMsg->get1c();
		memcpy(m_packet + m_packetLen, &length, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		memcpy(m_packet + m_packetLen, unitext.str(), length * sizeof(unsigned short));
		m_packetLen += length * sizeof(unsigned short);
		memcpy(m_packet + m_packetLen, &value1C, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		UnsignedInt value20 = cmdMsg->get20();
		memcpy(m_packet + m_packetLen, &value20, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addFileAnnounceCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00592F2B, 678 bytes:
// addCommand's type-21 arm, BFME1's FILEANNOUNCE shifted by the inserted
// type: T/R/S/P/C/D, then the NUL-terminated file name, file ID word and
// player mask byte.
Bool NetPacket::addFileAnnounceCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva0059188C(msg)) {
		NetCommandMsg *cmdMsg = ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		AsciiString filename = ((CDDrive *)cmdMsg)->CDDrive::getPath();
		_mbscpy(m_packet + m_packetLen, (const unsigned char *)filename.str());
		m_packetLen += filename.getLength() + 1;
		UnsignedShort fileID = ((Rva004D5973WordField *)cmdMsg)->get();
		memcpy(m_packet + m_packetLen, &fileID, sizeof(UnsignedShort));
		m_packetLen += sizeof(UnsignedShort);
		UnsignedByte playerMask = ((Rva001DCD01ByteField *)cmdMsg)->get();
		memcpy(m_packet + m_packetLen, &playerMask, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addRequestGameSpyStatsAuthKeyCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00593A1F, 590 bytes:
// addCommand's type-5 arm, named as in the BFME1 donor: T/R/S/P/C/D, then
// the NUL-terminated +0x1C string.
Bool NetPacket::addRequestGameSpyStatsAuthKeyCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (rva00591D0D(msg)) {
		NetCommandMsg *cmdMsg = ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		AsciiString text = ((CDDrive *)cmdMsg)->CDDrive::getPath();
		_mbscpy(m_packet + m_packetLen, (const unsigned char *)text.str());
		m_packetLen += text.getLength() + 1;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addGameSpyStatsAuthKeyCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00593C6D, 680 bytes:
// addCommand's type-6 arm, the BFME1 donor's addGameSpyStatsAuthKeyCommand
// (680 bytes there too) with BFME's S block: T/R/S/P/C/D, then the +0x1C and
// +0x20 strings, each copied with _mbscpy and charged its length plus one.
Bool NetPacket::addGameSpyStatsAuthKeyCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForGameSpyStatsAuthKeyMessage(msg)) {
		NetCommandMsg *cmdMsg = ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		AsciiString key = ((CDDrive *)cmdMsg)->CDDrive::getPath();
		_mbscpy(m_packet + m_packetLen, (const unsigned char *)key.str());
		m_packetLen += key.getLength() + 1;
		AsciiString login = ((Rva002D9BC1AsciiField *)cmdMsg)->get();
		_mbscpy(m_packet + m_packetLen, (const unsigned char *)login.str());
		m_packetLen += login.getLength() + 1;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addFileCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x00592C8C, 671 bytes:
// addCommand's type-19 (FILE) arm behind isRoomForFileMessage: T/R/S/P/C/D, then ZH's
// file name, length dword and file bytes. Retail reaches the length and data
// through folded getters rowed as NetWrapperCommandMsg::getDataOffset (+0x24)
// and getDataLength (+0x20), so the data pointer comes back as an integer.
Bool NetPacket::addFileCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForFileMessage(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)ncrCommand(msg);
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		AsciiString filename = ((CDDrive *)cmdMsg)->CDDrive::getPath();
		_mbscpy(m_packet + m_packetLen, (const unsigned char *)filename.str());
		m_packetLen += filename.getLength() + 1;
		UnsignedInt fileLength = cmdMsg->getDataOffset();
		memcpy(m_packet + m_packetLen, &fileLength, sizeof(fileLength));
		m_packetLen += sizeof(fileLength);
		memcpy(m_packet + m_packetLen, (UnsignedByte *)cmdMsg->getDataLength(), fileLength);
		m_packetLen += fileLength;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		return true;
	}
	return false;
}

// ?addGameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z, retail 0x0059096F, 938 bytes:
// addCommand's type-4 arm, the BFME1 donor's addGameCommand
// (NetPacket_addGameCommand.cpp) with BFME's S block: the null-message early
// return, T/S/F/R/P/C/D behind isRoomForGameMessage, then the message type,
// the parser's runs and each argument. Parser and message are freed with
// ::delete, as in the room check.
Bool NetPacket::addGameCommand(NetCommandRef *msg)
{
	Bool retval = false;
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)(ncrCommand(msg));
	GameMessage *gmsg = cmdMsg->constructGameMessage();
	if (gmsg == 0) {
		return true;
	}
	if (isRoomForGameMessage(msg, gmsg)) {
		Bool needNewCommandID = false;
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastTimestamp != cmdMsg->getTimestamp()) {
			m_packet[m_packetLen] = 'S';
			++m_packetLen;
			UnsignedInt newTimestamp = cmdMsg->getTimestamp();
			memcpy(m_packet + m_packetLen, &newTimestamp, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastTimestamp = newTimestamp;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != ncrRelay(msg)) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = ncrRelay(msg);
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			needNewCommandID = true;
			m_lastPlayerID = cmdMsg->getPlayerID();
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		Int newType = gmsg->getType();
		memcpy(m_packet + m_packetLen, &newType, sizeof(Int));
		m_packetLen += sizeof(Int);
		Rva0054D54A *parser = new Rva0054D54A(gmsg);
		UnsignedByte numTypes = parser->getNumTypes();
		memcpy(m_packet + m_packetLen, &numTypes, sizeof(numTypes));
		m_packetLen += sizeof(numTypes);
		Rva0054D593 *argType = parser->getFirstArgumentType();
		while (argType != 0) {
			UnsignedByte type = (UnsignedByte)(argType->getType());
			memcpy(m_packet + m_packetLen, &type, sizeof(type));
			m_packetLen += sizeof(type);
			UnsignedByte argTypeCount = argType->getArgCount();
			memcpy(m_packet + m_packetLen, &argTypeCount, sizeof(argTypeCount));
			m_packetLen += sizeof(argTypeCount);
			argType = argType->getNext();
		}
		Int numArgs = gmsg->getArgumentCount();
		for (Int i = 0; i < numArgs; ++i) {
			GameMessageArgumentDataType type = gmsg->getArgumentDataType(i);
			GameMessageArgumentType arg = *(gmsg->getArgument(i));
			writeGameMessageArgumentToPacket(type, arg);
		}
		::delete parser;
		parser = 0;
		++m_numCommands;
		if (m_lastCommand != 0) {
			delete m_lastCommand;
			m_lastCommand = 0;
		}
		m_lastCommand = new NetCommandRef(ncrCommand(msg));
		ncrSetRelay(m_lastCommand, ncrRelay(msg));
		retval = true;
	}
	::delete gmsg;
	return retval;
}

// ?addCommand@NetPacket@@QAE_NPAVNetCommandRef@@@Z, retail 0x005944D8, 433 bytes
// including its jump table at 0x0059460D: the BFME1 donor's dispatcher
// (NetPacket_addCommand.cpp). Arms are laid out in source order, read back
// out of the image; types 24 and 29 and a null reference return true.
// Retail's linker folded the ack arms (types 0/1/2), the keep-alive arms
// (12/25), load-complete/time-out-start (16/17) and request-player-leave/
// request-frame-data (7/9), yet each type keeps its own call block, so each
// calls a distinct symbol pinned to the folded body.
Bool NetPacket::addCommand(NetCommandRef *msg)
{
	if (msg == 0) {
		return true;
	}

	switch (ncrCommand(msg)->getNetCommandType()) {
	case 4:
		return addGameCommand(msg);
	case 1:
		return rva005939EEAckStage1(msg);
	case 2:
		return rva005939EEAckStage2(msg);
	case 0:
		return rva005939EE(msg);
	case 3:
		return addFrameCommand(msg);
	case 23:
		return addRouterFallbackCommand(msg);
	case 10:
		return addPlayerLeaveCommand(msg);
	case 11:
		return addDestroyPlayerCommand(msg);
	case 12:
		return rva0058FE15(msg);
	case 25:
		return rva0058FE15DisconnectKeepAlive(msg);
	case 26:
		return addDisconnectPlayerCommand(msg);
	case 13:
		return addDisconnectChatCommand(msg);
	case 27:
		return addDisconnectVoteCommand(msg);
	case 14:
		return addChatCommand(msg);
	case 15:
		return addProgressMessage(msg);
	case 16:
		return rva0058F5E3(msg);
	case 17:
		return rva0058F5E3TimeOutStart(msg);
	case 18:
		return addWrapperCommand(msg);
	case 19:
		return addFileCommand(msg);
	case 20:
		return rva0058EDEF(msg);
	case 21:
		return addFileAnnounceCommand(msg);
	case 22:
		return addFileProgressCommand(msg);
	case 8:
		return addInformPlayerLeaveFrameCommand(msg);
	case 7:
		return rva0058E8EA(msg);
	case 9:
		return rva0058E8EARequestFrameData(msg);
	case 28:
		return addDisconnectFrameCommand(msg);
	case 5:
		return addRequestGameSpyStatsAuthKeyCommand(msg);
	case 6:
		return addGameSpyStatsAuthKeyCommand(msg);
	case 30:
		return rva005936DB(msg);
	}

	return true;
}
