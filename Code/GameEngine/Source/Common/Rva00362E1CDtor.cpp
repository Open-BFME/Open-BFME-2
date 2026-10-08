// Native singleton VA 0x00DFE77C is GameClient.cpp's class GameClient pointer.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/shims/moduledata
// ??1Rva00362E1C@@UAE@XZ @0x00362E1C 87B.
// Virtual dtor: erases this from TheGameClient via rowed rva00239A10, zeroes
// +4, destroys 9 Rva00362D6C at +8 via ??_M, restores Snapshot base to
// g_00BBB554. Same Snapshot/g_00BBB554 recipe as Rva00362D6CDtor. Evidence:
// pin plus caller 0x00362EAE deleting dtor; callees rowed 0x00239A10 0x00036410
// plus ??_M vendor; vtable 0x00817088 then g_00BBB554; neighbours 0x00362E16
// 0x00362E73.
#include "Common/Snapshot.h"

class Rva00239A10
{
public:
	void rva00239A10(void *item);
};

class ClientFrameSubsystem : public Rva00239A10
{
};

extern class GameClient *TheGameClient;

class Rva00362D6C
{
public:
	virtual ~Rva00362D6C();
private:
	char m_pad[0x44 - 4];
};

class Rva00362E1C : public Snapshot
{
public:
	virtual ~Rva00362E1C();
private:
	int m_04;
	Rva00362D6C m_arr[9];
};

Rva00362E1C::~Rva00362E1C()
{
	reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->rva00239A10(this);
	m_04 = 0;
}
