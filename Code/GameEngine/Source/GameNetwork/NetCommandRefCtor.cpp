// cl: /DNDEBUG /MD
// ??0NetCommandRef@@QAE@PAVNetCommandMsg@@@Z, retail 0x0058B88A 36 bytes.
// NetCommandRef ctor via BFME1 donor Code/GameEngine/Source/GameNetwork/NetCommandRef_dtor.cpp
// (NetCommandRef::NetCommandRef) and ZH GeneralsMD NetCommandRef.cpp.
// Evidence: new 0x14 at caller 0x0058B2C6 then call here with msg in ecx;
// layout m_msg+0 m_next+4 m_prev+8 m_relay+0xC m_timeLastSent+0x10;
// callee attach at 0x004D55B8 inc +0x18 (m_referenceCount).
class NetCommandMsg
{
public:
	void attach();
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
	unsigned int m_timeLastSent;
};

NetCommandRef::NetCommandRef(NetCommandMsg *msg)
{
	m_next = 0;
	m_prev = 0;
	m_msg = msg;
	m_msg->attach();
	m_timeLastSent = (unsigned int)-1;
	m_relay = 0;
}
