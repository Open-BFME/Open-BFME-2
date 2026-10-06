// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00594D77@FirewallHelperClass@@QAEPAXG@Z @0x00594D77 (37B): search spareSockets[8] at +0x14 by port at +0x18 stride 8; return entry or 0; layout from Rva00594CDDPermuted ctor; neighbours FirewallHelperClass ctor and findEmptyMessage.
struct SpareEntry
{
	void *udp;
	unsigned short port;
	char _pad[2];
};
class FirewallHelperClass
{
public:
	void *rva00594D77(unsigned short port);
private:
	char _pad00[0x14];
	SpareEntry m_spare[8];
};
void *FirewallHelperClass::rva00594D77(unsigned short port)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_spare[i].port == port)
			return &m_spare[i];
	}
	return 0;
}
