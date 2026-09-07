// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// The +0xAC native-network predicate is the small bridge used by the
// frame-pacing query. It asks the connection manager whether its two router
// frame counters are equal; this source only exposes the retail predicate.

class BFMEConnectionManager
{
public:
	bool isPacketRouter(void);
};

class NetworkInterface
{
public:
	int isPacketRouter(void);

private:
	void *m_vtable;
	char m_unknown04[8];
	BFMEConnectionManager *m_connectionManager;
};

int NetworkInterface::isPacketRouter(void)
{
	BFMEConnectionManager *manager = m_connectionManager;
	if (manager != 0)
	{
		if (manager->isPacketRouter())
			return 1;
	}
	return 0;
}
