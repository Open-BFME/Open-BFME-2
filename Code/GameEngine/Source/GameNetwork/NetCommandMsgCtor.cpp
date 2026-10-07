// cl: /DNDEBUG /MD /EHsc
// ??0NetCommandMsg@@QAE@XZ, retail 0x004D5593, 37 bytes. Base message ctor:
// m_executionFrame=-1 (+8), m_timestamp=-1 (+4), m_id=0 (+0x10 word),
// m_playerID=0 (+0xC), m_commandType=UNKNOWN (-1, +0x14), vtable 0x860130,
// m_referenceCount=1 (+0x18). Donor is BFME1
// Code/GameEngine/Source/GameNetwork/NetCommandMsg_ctors.cpp
// (NetCommandMsg::NetCommandMsg, same field order; BFME2 starts timestamp at
// -1 rather than 0). Called by 33 derived ctors (0x004D55D6 NetGameCommandMsg
// shape, Ack family at 0x004D565D/0x004D568F, 30 become ready on landing).
// Vtable 0x860130 slot0 is the deleting dtor at 0x004CEEA6 rowed below.
// ??_GNetCommandMsg@@MAEPAXI@Z, retail 0x004CEEA6, 29 bytes. Deleting dtor:
// reinstalls vtable 0x860130 then frees via rowed ??3@YAXPAX@Z at 0x0002FD60.
// Abbuts the word getter at 0x004CEEA1 (prev ret) and the next body at
// 0x004CEEC3; same TU emits it byte-exact from the inline empty dtor.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 0x19
};

class MemoryPool;
class AsciiString;

class NetCommandMsg
{
public:
	NetCommandMsg();
	UnsignedInt getTimestamp() { return m_timestamp; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
protected:
	virtual ~NetCommandMsg() {}
private:
	virtual MemoryPool *getObjectMemoryPool();
public:
	virtual Int getSortNumber();
	virtual AsciiString getContentsAsAsciiString();
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

// ??0NetCommandMsg@@QAE@XZ
NetCommandMsg::NetCommandMsg()
{
	m_executionFrame = (UnsignedInt)-1;
	m_timestamp = (UnsignedInt)-1;
	m_id = 0;
	m_playerID = 0;
	m_commandType = NETCOMMANDTYPE_UNKNOWN;
	m_referenceCount = 1;
}

// ??0NetKeepAliveCommandMsg@@QAE@XZ, retail 0x004D57C7, 21 bytes. Calls the
// base above then stamps KEEPALIVE (12, +0x14) and its vtable 0x860244. Donor
// is BFME1 NetCommandMsg_ctors.cpp (NetKeepAliveCommandMsg, no members).
class NetKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetKeepAliveCommandMsg();
};

// ??0NetKeepAliveCommandMsg@@QAE@XZ
NetKeepAliveCommandMsg::NetKeepAliveCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_KEEPALIVE;
}

// ??0NetDisconnectKeepAliveCommandMsg@@QAE@XZ @0x004D57DC 21B: calls base plus stamps DISCONNECTKEEPALIVE (0x19) plus vtable 0x860244 shared via ICF.
// Donor BFME1 NetCommandMsg_ctors.cpp DisconnectKeepAlive (no members).
class NetDisconnectKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectKeepAliveCommandMsg();
};

NetDisconnectKeepAliveCommandMsg::NetDisconnectKeepAliveCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_DISCONNECTKEEPALIVE;
}

// ??0Rva004D5795@@QAE@XZ @0x004D5795 25B: calls base plus vtable 0x860224 plus byte 0 at +0x1c plus type 10 at +0x14.
// Vtable 0x860224 names unknown owner; honest-address ctor with 1-byte derived member.
class Rva004D5795 : public NetCommandMsg
{
public:
	Rva004D5795();
private:
	bool m_1c;
};

Rva004D5795::Rva004D5795() : NetCommandMsg()
{
	m_1c = 0;
	m_commandType = (NetCommandType)10;
}

// ??0Rva004D57AE@@QAE@XZ @0x004D57AE 25B: calls base plus dword 0 at +0x1c via And plus vtable 0x860234 plus type 11 at +0x14.
// Honest-address ctor with 4-byte derived member; And is /O1 size form of =0.
class Rva004D57AE : public NetCommandMsg
{
public:
	Rva004D57AE();
private:
	unsigned int m_1c;
};

Rva004D57AE::Rva004D57AE() : NetCommandMsg()
{
	m_1c = 0;
	m_commandType = (NetCommandType)11;
}

// ??0Rva004D582B@@QAE@XZ @0x004D582B 25B: calls base plus vtable 0x860244 plus type 15 plus byte 0 at +0x1c.
// Honest-address ctor with 1-byte derived member sharing KeepAlive vtable via ICF.
class Rva004D582B : public NetCommandMsg
{
public:
	Rva004D582B();
private:
	bool m_1c;
};

Rva004D582B::Rva004D582B() : NetCommandMsg()
{
	m_commandType = (NetCommandType)15;
	m_1c = 0;
}

// ??0Rva004D59B8@@QAE@XZ @0x004D59B8 25B: calls base plus dword 0 at +0x1c via And plus vtable 0x860244 plus type 28 at +0x14.
// Honest-address ctor with 4-byte derived member sharing KeepAlive vtable via ICF.
class Rva004D59B8 : public NetCommandMsg
{
public:
	Rva004D59B8();
private:
	unsigned int m_1c;
};

Rva004D59B8::Rva004D59B8() : NetCommandMsg()
{
	m_1c = 0;
	m_commandType = (NetCommandType)28;
}

// ??0Rva004D57F1@@QAE@XZ @0x004D57F1 29B: calls base plus dword 0 at +0x24 via And plus vtable 0x860244 plus type 26 plus byte 0 at +0x1c.
// Honest-address ctor with 4-byte plus 1-byte derived members sharing KeepAlive vtable via ICF.
class Rva004D57F1 : public NetCommandMsg
{
public:
	Rva004D57F1();
private:
	bool m_1c;
	char m_pad1D[0x24 - 0x1D];
	unsigned int m_24;
};

Rva004D57F1::Rva004D57F1() : NetCommandMsg()
{
	m_24 = 0;
	m_commandType = (NetCommandType)26;
	m_1c = 0;
}

// ??0Rva004D580E@@QAE@XZ @0x004D580E 29B: calls base plus dword 0 at +0x20 via And plus vtable 0x860244 plus type 27 plus byte 0 at +0x1c.
// Honest-address ctor with 4-byte plus 1-byte derived members sharing KeepAlive vtable via ICF; same recipe as Rva004D57F1 above with m_20.
// Callers at 0x004D3A3D 0x0058DFDC.
class Rva004D580E : public NetCommandMsg
{
public:
	Rva004D580E();
private:
	bool m_1c;
	char m_pad1D[0x20 - 0x1D];
	unsigned int m_20;
};

Rva004D580E::Rva004D580E() : NetCommandMsg()
{
	m_20 = 0;
	m_commandType = (NetCommandType)27;
	m_1c = 0;
}

// ??0NetWrapperCommandMsg@@QAE@XZ @0x004D5844 45B: calls base plus six dword 0 at +0x1c/+0x20/+0x24/+0x28/+0x2c/+0x30 plus word 0 at +0x34 plus vtable 0x860254 plus type 18 (WRAPPER).
// Real name via vtable 0x860254 and sibling dtor ??1NetWrapperCommandMsg@@MAE@XZ at 0x004D5871; same /O1 recipe as ctors above.
// Callers at 0x0058E108 0x00594762.
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	NetWrapperCommandMsg();
protected:
	virtual ~NetWrapperCommandMsg();
private:
	virtual MemoryPool *getObjectMemoryPool();
private:
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned int m_30;
	unsigned short m_34;
};

NetWrapperCommandMsg::NetWrapperCommandMsg() : NetCommandMsg()
{
	m_30 = 0;
	m_1c = 0;
	m_28 = 0;
	m_2c = 0;
	m_20 = 0;
	m_24 = 0;
	m_34 = 0;
	m_commandType = (NetCommandType)18;
}

// ??0Rva004D59D1@@QAE@XZ @0x004D59D1 29B: calls base plus dword 0 at +0x1c via And plus dword -1 at +0x20 via Or plus vtable 0x860274 plus type 8.
// Honest-address ctor; same /O1 And/Or recipe as siblings above; unblocks 0x0058E367.
// Callers at 0x004D1E37 0x0058E38C.
class Rva004D59D1 : public NetCommandMsg
{
public:
	Rva004D59D1();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

Rva004D59D1::Rva004D59D1() : NetCommandMsg()
{
	m_1c = 0;
	m_20 = (unsigned int)-1;
	m_commandType = (NetCommandType)8;
}

// ??0Rva004D5A10@@QAE@XZ @0x004D5A10 32B: calls base plus dword -1 at +0x1c via Or plus vtable 0x860284 plus type 7 plus dword 1 at +0x20.
// Honest-address ctor; Or/Mov recipe; unblocks 0x004D00BB 0x0058E3F4.
// Callers at 0x004D00E0 0x0058E419.
class Rva004D5A10 : public NetCommandMsg
{
public:
	Rva004D5A10();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

Rva004D5A10::Rva004D5A10() : NetCommandMsg()
{
	m_1c = (unsigned int)-1;
	m_commandType = (NetCommandType)7;
	m_20 = 1;
}

// ??0Rva004D5A30@@QAE@XZ @0x004D5A30 29B: calls base plus dword 0 at +0x1c via And plus dword 0 at +0x20 via And plus vtable 0x860294 plus type 9.
// Honest-address ctor; same /O1 And recipe as siblings above; unblocks 0x0058E481 0x004CFD06.
// Callers at 0x004CFDA2 0x0058E4A5.
class Rva004D5A30 : public NetCommandMsg
{
public:
	Rva004D5A30();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

Rva004D5A30::Rva004D5A30() : NetCommandMsg()
{
	m_1c = 0;
	m_20 = 0;
	m_commandType = (NetCommandType)9;
}

// ??0Rva004D60CA@@QAE@XZ @0x004D60CA 25B: calls base plus dword 0 at +0x1c via And plus vtable 0x860464 plus type 13 at +0x14.
// Honest-address ctor; same /O1 And recipe as siblings above; unblocks 0x004D187B 0x0059205C.
// Callers at 0x004D18A3 0x00592083.
class Rva004D60CA : public NetCommandMsg
{
public:
	Rva004D60CA();
private:
	unsigned int m_1c;
};

Rva004D60CA::Rva004D60CA() : NetCommandMsg()
{
	_ReadWriteBarrier();
	m_1c = 0;
	m_commandType = (NetCommandType)0xd;
}

// ??0Rva004D64F5@@QAE@XZ @0x004D64F5 25B: calls base plus vtable 0x86050C plus dword 0 at +0x1c via And plus type 5 at +0x14.
// Honest-address ctor; same barrier-pinned vptr-first recipe as Rva004D60CA above; unblocks 0x004D342A 0x00592496.
// Callers at 0x004D3548 0x005924BF.
class Rva004D64F5 : public NetCommandMsg
{
public:
	Rva004D64F5();
private:
	unsigned int m_1c;
};

Rva004D64F5::Rva004D64F5() : NetCommandMsg()
{
	_ReadWriteBarrier();
	m_1c = 0;
	m_commandType = (NetCommandType)5;
}

// ??0Rva004D6134@@QAE@XZ @0x004D6134 29B: calls base plus vtable 0x860474 plus dword 0 at +0x1c via And plus dword 0 at +0x20 via And plus type 14 at +0x14.
// Honest-address ctor; same barrier-pinned vptr-first recipe as siblings above; unblocks 0x00592123 0x004D17C5.
// Callers at 0x004D17ED 0x0059214A.
template <class T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};
class Rva004D6134 : public NetCommandMsg
{
public:
	Rva004D6134();
protected:
	virtual ~Rva004D6134();
private:
	StringBase<unsigned short> m_1c;
	unsigned int m_20;
};

Rva004D6134::Rva004D6134() : NetCommandMsg()
{
	_ReadWriteBarrier();
	m_20 = 0;
	m_commandType = (NetCommandType)0xe;
}

// ??1Rva004D6134@@MAE@XZ, retail 0x004D6151, 54 bytes. Protected virtual
// dtor for Rva004D6134 (vtable 0x860474, base NetCommandMsg vtable 0x860130):
// stores derived vptr, destroys wide-string member at +0x1C via the rowed
// releaseBuffer at 0x00036E70, reinstalls base vptr. Member at +0x1C is a
// 4-byte StringBase<ushort> nulled inline in the ctor (And form preserved).
// Caller at 0x004D6AA0 is the deleting dtor at 0x004D6A9D (slot 0).
Rva004D6134::~Rva004D6134()
{
}

// ??0Rva004D65DC@@QAE@XZ @0x004D65DC 29B: calls base plus vtable 0x860530 plus dword 0 at +0x1c via And plus dword 0 at +0x20 via And plus type 6 at +0x14.
// Honest-address ctor; same barrier-pinned vptr-first recipe as siblings above; unblocks 0x00592520 0x004D12B2.
// Callers at 0x004D1346 0x00592549.
class Rva004D65DC : public NetCommandMsg
{
public:
	Rva004D65DC();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

Rva004D65DC::Rva004D65DC() : NetCommandMsg()
{
	_ReadWriteBarrier();
	m_1c = 0;
	m_20 = 0;
	m_commandType = (NetCommandType)6;
}

// Nine more derived ctors, each stamping its NetCommandType (+0x14) and
// vtable after the base call; retail keeps this in ecx across the base ctor
// call, which cl only does because the base is compiled earlier in this TU.
// Types 0, 1, 2 and 4 name the classes as in the BFME1 donor
// game/GameEngine/Source/GameNetwork/NetCommandMsg_ctors.cpp (ACKBOTH,
// ACKSTAGE1, ACKSTAGE2, GAMECOMMAND), each on its own vtable. BFME2 adds a
// dword to the ack messages: +0x20 is copied from the source message's
// m_timestamp (+0x04) and +0x24 from its m_executionFrame (+0x08); the field
// names are inferred from those sources. The NetGameCommandMsg fields follow
// the ZH layout the rowed addArgument 0x004D5A7A reads (+0x28/+0x2C).
typedef unsigned char UnsignedByte;

// ??0NetGameCommandMsg@@QAE@XZ @0x004D55D6 38B: five zeroed dwords +0x1C..+0x2C,
// vtable 0x8601E4, type 4 (GAMECOMMAND).
class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg();
private:
	Int m_numArgs; // +0x1C
	Int m_argSize; // +0x20
	Int m_type; // +0x24
	void *m_argList; // +0x28
	void *m_argTail; // +0x2C
};

NetGameCommandMsg::NetGameCommandMsg() : NetCommandMsg()
{
	m_argSize = 0;
	m_numArgs = 0;
	m_type = 0;
	m_argList = 0;
	m_argTail = 0;
	m_commandType = (NetCommandType)4;
}

// ??0NetAckBothCommandMsg@@QAE@PAVNetCommandMsg@@@Z @0x004D565D 50B and
// ??0NetAckBothCommandMsg@@QAE@XZ @0x004D568F 34B: vtable 0x8601F4, type 0.
class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	NetAckBothCommandMsg(NetCommandMsg *msg);
	NetAckBothCommandMsg();
private:
	UnsignedShort m_commandID; // +0x1C
	UnsignedByte m_originalPlayerID; // +0x1E
	UnsignedInt m_originalTimestamp; // +0x20
	UnsignedInt m_originalExecutionFrame; // +0x24
};

NetAckBothCommandMsg::NetAckBothCommandMsg(NetCommandMsg *msg) : NetCommandMsg()
{
	m_commandID = msg->getID();
	m_commandType = (NetCommandType)0;
	m_originalPlayerID = msg->getPlayerID();
	m_originalExecutionFrame = msg->getExecutionFrame();
	m_originalTimestamp = msg->getTimestamp();
}

NetAckBothCommandMsg::NetAckBothCommandMsg() : NetCommandMsg()
{
	m_commandID = 0;
	m_originalPlayerID = 0;
	m_originalTimestamp = (UnsignedInt)-1;
	m_originalExecutionFrame = (UnsignedInt)-1;
	m_commandType = (NetCommandType)0;
}

// ??0NetAckStage1CommandMsg@@QAE@PAVNetCommandMsg@@@Z @0x004D56B1 53B and
// ??0NetAckStage1CommandMsg@@QAE@XZ @0x004D56E6 38B: vtable 0x860204, type 1.
class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	NetAckStage1CommandMsg(NetCommandMsg *msg);
	NetAckStage1CommandMsg();
private:
	UnsignedShort m_commandID; // +0x1C
	UnsignedByte m_originalPlayerID; // +0x1E
	UnsignedInt m_originalTimestamp; // +0x20
	UnsignedInt m_originalExecutionFrame; // +0x24
};

NetAckStage1CommandMsg::NetAckStage1CommandMsg(NetCommandMsg *msg) : NetCommandMsg()
{
	m_commandID = msg->getID();
	m_commandType = (NetCommandType)1;
	m_originalPlayerID = msg->getPlayerID();
	m_originalExecutionFrame = msg->getExecutionFrame();
	m_originalTimestamp = msg->getTimestamp();
}

NetAckStage1CommandMsg::NetAckStage1CommandMsg() : NetCommandMsg()
{
	m_commandID = 0;
	m_originalPlayerID = 0;
	m_originalTimestamp = (UnsignedInt)-1;
	m_originalExecutionFrame = (UnsignedInt)-1;
	m_commandType = (NetCommandType)1;
}

// ??0NetAckStage2CommandMsg@@QAE@PAVNetCommandMsg@@@Z @0x004D570C 53B and
// ??0NetAckStage2CommandMsg@@QAE@XZ @0x004D5741 38B: vtable 0x860214, type 2;
// the copying ctor stores timestamp before execution frame and the type last.
class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	NetAckStage2CommandMsg(NetCommandMsg *msg);
	NetAckStage2CommandMsg();
private:
	UnsignedShort m_commandID; // +0x1C
	UnsignedByte m_originalPlayerID; // +0x1E
	UnsignedInt m_originalTimestamp; // +0x20
	UnsignedInt m_originalExecutionFrame; // +0x24
};

NetAckStage2CommandMsg::NetAckStage2CommandMsg(NetCommandMsg *msg) : NetCommandMsg()
{
	m_commandID = msg->getID();
	m_originalPlayerID = msg->getPlayerID();
	m_originalTimestamp = msg->getTimestamp();
	m_originalExecutionFrame = msg->getExecutionFrame();
	m_commandType = (NetCommandType)2;
}

NetAckStage2CommandMsg::NetAckStage2CommandMsg() : NetCommandMsg()
{
	m_commandID = 0;
	m_originalPlayerID = 0;
	m_originalTimestamp = (UnsignedInt)-1;
	m_originalExecutionFrame = (UnsignedInt)-1;
	m_commandType = (NetCommandType)2;
}

// ??0Rva004D58DE@@QAE@XZ @0x004D58DE 36B: dword +0x1C, word +0x20, dwords
// +0x24/+0x28 zeroed, vtable 0x860264, type 0x14. Honest-address name: the
// BFME1 donor enum has no entry for 0x14.
class Rva004D58DE : public NetCommandMsg
{
public:
	Rva004D58DE();
private:
	unsigned int m_1c;
	unsigned short m_20;
	unsigned int m_24;
	unsigned int m_28;
};

Rva004D58DE::Rva004D58DE() : NetCommandMsg()
{
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_commandType = (NetCommandType)0x14;
}

// ??0Rva004D598E@@QAE@XZ @0x004D598E 30B: word +0x1C and dword +0x20 zeroed,
// the vtable 0x860244 shared with KeepAlive via ICF, type 0x16. Honest-address
// name as for the other ICF-shared vtable ctors above.
class Rva004D598E : public NetCommandMsg
{
public:
	Rva004D598E();
private:
	unsigned short m_1c;
	unsigned int m_20;
};

Rva004D598E::Rva004D598E() : NetCommandMsg()
{
	m_1c = 0;
	m_20 = 0;
	m_commandType = (NetCommandType)0x16;
}
