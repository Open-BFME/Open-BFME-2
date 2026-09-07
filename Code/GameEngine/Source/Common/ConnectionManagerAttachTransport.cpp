// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// Replaces the connection manager's transport, releasing the previous
// transport through its reset path and the game allocator before installing
// the new pointer.

class Transport
{
public:
	~Transport(void);
};

void __cdecl operator delete(void *block);

class BFMEConnectionManager
{
public:
	void attachTransport(Transport *transport);

private:
	char unknown[0x12024];
	Transport *m_transport;
};

void BFMEConnectionManager::attachTransport(Transport *transport)
{
	if (m_transport != 0)
	{
		delete m_transport;
		m_transport = 0;
	}
	m_transport = transport;
}
