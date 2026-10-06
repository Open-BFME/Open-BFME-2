// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058D826@NetPacket@@IAEXHHHHH@Z @0x0058D826 265B.
// NetPacket packet append by kind copying raw stack args via memcpy.
// Evidence: unlock lane plus sibling TU layout plus caller 0x00590C71.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);

class NetPacket
{
public:
	virtual ~NetPacket();
protected:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	UnsignedInt m_destAddress;
	UnsignedShort m_destPort;
	UnsignedShort m_unknown1EA;
	Int m_numCommands;
	NetPacket *m_lastCommand;
	UnsignedInt m_unknown1F4;
	UnsignedInt m_unknown1F8;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
	void rva0058D826(Int a, Int b, Int c, Int d, Int e);
};

void NetPacket::rva0058D826(Int a, Int b, Int c, Int d, Int e)
{
	if (a == 0) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 1) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 2) {
		memcpy(m_packet + m_packetLen, &b, 1);
		m_packetLen += 1;
	} else if (a == 3) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 4) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 5) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 6) {
		memcpy(m_packet + m_packetLen, &b, 12);
		m_packetLen += 12;
	} else if (a == 7) {
		memcpy(m_packet + m_packetLen, &b, 8);
		m_packetLen += 8;
	} else if (a == 8) {
		memcpy(m_packet + m_packetLen, &b, 16);
		m_packetLen += 16;
	} else if (a == 9) {
		memcpy(m_packet + m_packetLen, &b, 4);
		m_packetLen += 4;
	} else if (a == 10) {
		memcpy(m_packet + m_packetLen, &b, 2);
		m_packetLen += 2;
	}
}
