// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

class BFMEConnectionManager
{
public:
	bool isPacketRouter(void);

private:
	char m_padding[0x12028];
	unsigned int m_localSlot;
	unsigned int m_packetRouterSlot;
};

bool BFMEConnectionManager::isPacketRouter(void)
{
	return m_localSlot == m_packetRouterSlot;
}
