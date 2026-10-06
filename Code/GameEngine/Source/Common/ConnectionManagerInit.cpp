// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// The first BFME2 connection-manager virtual after the two destructors
// reinitializes frame data and clears the announced frame horizon.  This is a
// reset path, not a normal frame-advance writer.

struct FrameDataManager
{
	void reset(void);
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Object;
class GameLogic
{
public:
	char m_pad40[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	char m_padC20[0xC20];
	unsigned int m_C20;
};

extern class GlobalData *TheWritableGlobalData;
extern unsigned int g_007ED97C;

struct ConnSlot
{
	char m_pad[0x34C];
	unsigned long m_34C;
};

class BFMEConnectionManager
{
public:
	void init(void);
	unsigned char rva004CEF58(int slot);
	unsigned char rva004CEFC2(int slot, unsigned int timeoutParam);

private:
	char unknown0[4];
	char unknownConnections[8 * 4];
	char unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	char unknown12030[0x2c];
	int m_frameCeiling;
	int m_playerLatestFrame[8];
	int m_playerState[8];
	int m_playerFlags[8];
	int m_playerFrameCounts[8];
	char unknown120e0[0x24];
	FrameDataManager *m_frameData[8];
	char unknown12124[0x10];
	unsigned char m_initialized;
};

void BFMEConnectionManager::init(void)
{
	FrameDataManager **manager = m_frameData;
	int slotsRemaining = 8;
	do
	{
		if (*manager != 0)
			(*manager)->reset();
		++manager;
	}
	while (--slotsRemaining != 0);

	m_frameCeiling = 0;
	int *frame = (int *)((char *)this + 0x120C0);
	int framesRemaining = 8;
	do
	{
		frame[-24] = 0;
		frame[0] = 0;
		frame[-16] = 0;
		frame[-8] = 1;
		++frame;
	}
	while (--framesRemaining != 0);
	m_initialized = 0;
}

// ?rva004CEF58@BFMEConnectionManager@@QAEEH@Z, retail 0x004CEF58 106B.
// Unlock: timeout check via m_localSlot 0x12028 plus +4 conn array
// plus +0x34C timeGetTime plus m_40 vs g_007ED97C plus m_C20 shift.
// Callers 0x4D3BA2 0x4D42E3 0x4D4758, prev 0x4CEF44 next 0x4CF032.

unsigned char BFMEConnectionManager::rva004CEF58(int slot)
{
	if (slot == m_localSlot)
		return 1;
	ConnSlot *conn = *(ConnSlot **)((char *)this + 4 + slot * 4);
	if (conn == 0)
		return 1;
	if (conn->m_34C == 0)
	{
		conn->m_34C = timeGetTime();
		return 1;
	}
	unsigned long now = timeGetTime();
	unsigned int m40 = TheGameLogic->m_40;
	unsigned int timeout;
	if (m40 < g_007ED97C)
		timeout = TheWritableGlobalData->m_C20 << 2;
	else
		timeout = TheWritableGlobalData->m_C20;
	unsigned long elapsed = now - conn->m_34C;
	return (unsigned char)(timeout >= elapsed);
}

// ?rva004CEFC2@BFMEConnectionManager@@QAEEHI@Z, retail 0x004CEFC2 112B.
// Sibling of 0x4CEF58: same m_localSlot plus conn plus +0x34C time,
// m40 vs g_007ED97C selects param timeout vs m_C20 shift.
// Caller 0x4D4748, prev 0x4CEF58 next 0x4CF032.

unsigned char BFMEConnectionManager::rva004CEFC2(int slot, unsigned int timeoutParam)
{
	if (slot == m_localSlot)
		return 1;
	ConnSlot *conn = *(ConnSlot **)((char *)this + 4 + slot * 4);
	if (conn == 0)
		return 1;
	if (conn->m_34C == 0)
	{
		conn->m_34C = timeGetTime();
		return 1;
	}
	unsigned long now = timeGetTime();
	unsigned int m40 = TheGameLogic->m_40;
	unsigned int timeout;
	if (m40 >= g_007ED97C)
		timeout = timeoutParam;
	else
		timeout = TheWritableGlobalData->m_C20 << 2;
	unsigned long elapsed = now - conn->m_34C;
	return (unsigned char)(timeout >= elapsed);
}

// ?g_007ED97C@@3IA: matched references place it at VA 0xbed97c; also referenced as ?g_007ED97C@@3HA.
unsigned int g_007ED97C = 6u;
#pragma comment(linker, "/alternatename:?g_007ED97C@@3HA=?g_007ED97C@@3IA")
