// ?Rva0058D041Write@@YAXPAEPAVNetCommandRef@@@Z
// partial score=0.97 date=2026-10-01
// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva0058D041Write@@YAXPAEPAVNetCommandRef@@@Z @0x0058D041 161B.
// NetPacket wrapper serialize T S F R P C D plus getData pointer.
// Evidence: leaf lane plus donor TSRFPCD markers plus caller 0x00592BC5.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);

class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }
	UnsignedInt getTimestamp() { return m_timestamp; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetCommandRef
{
public:
	__declspec(dllimport) __forceinline NetCommandMsg *getCommand() { return m_msg; }
	__declspec(dllimport) __forceinline UnsignedByte getRelay() const { return m_relay; }
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte *getData();
};

void Rva0058D041Write(UnsignedByte *dst, NetCommandRef *ref)
{
	NetWrapperCommandMsg *cmd = (NetWrapperCommandMsg *)ref->getCommand();
	dst[0] = 0x54;
	dst[1] = (UnsignedByte)cmd->getNetCommandType();
	dst[2] = 0x53;
	UnsignedInt ts = cmd->getTimestamp();
	memcpy(dst + 3, &ts, 4);
	dst[7] = 0x46;
	UnsignedInt fr = cmd->getExecutionFrame();
	memcpy(dst + 8, &fr, 4);
	dst[12] = 0x52;
	dst[13] = ref->getRelay();
	dst[14] = 0x50;
	dst[15] = (UnsignedByte)cmd->getPlayerID();
	dst[16] = 0x43;
	UnsignedShort nid = cmd->getID();
	memcpy(dst + 17, &nid, 2);
	dst[19] = 0x44;
	void *data = cmd->getData();
	memcpy(dst + 20, &data, 4);
}
