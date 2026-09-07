// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 UDP local-address getter, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameNetwork/udp.cpp).
// Retail BFME2 keeps the same fields: cached IP at +0x4, cached port at +0x8.

class UDP
{
public:
	int getLocalAddr(unsigned int &addr, unsigned short &port);

private:
	unsigned char m_pre[0x04];
	unsigned int m_ip;		// +0x04
	unsigned short m_port;	// +0x08
};

// ?getLocalAddr@UDP@@QAEHAAIAAG@Z
int UDP::getLocalAddr(unsigned int &addr, unsigned short &port)
{
	addr = m_ip;
	port = m_port;
	return 0;
}
