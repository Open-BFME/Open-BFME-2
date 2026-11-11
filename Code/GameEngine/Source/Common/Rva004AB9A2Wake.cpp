// cl: /O1 /DNDEBUG /MD
//
// ?rva004AB9A2@Rva004AB9A2@@QAEXXZ @0x004AB9A2 51B.
// When the byte at +0x8D is set, register the member at +0x24 with the
// host at g_00DFE1A8, wake on the object at +8, and clear the byte.

class Rva0028572AHost;

class Rva0020D959Host
{
public:
};

class LargeGroupAudio; extern LargeGroupAudio *TheLargeGroupAudio;
// The ledger row at 0x0020D959 is Rva0020DXXX::rva0020D959(int).
#include "../../Include/Common/Rva0020DXXX.h"


class Object;

enum UpdateSleepTime
{
	USLEEP_FOREVER = 0x3FFFFFFF
};

#include "../../Include/GameLogic/Module/UpdateModule.h"
class Rva004AB9A2 : public UpdateModule
{
public:
	void rva004AB9A2();

private:
	char m_pad20[0x24 - 0x20];
	char m_at24;
	char m_pad25[0x8D - 0x25];
	unsigned char m_flag;
};

void Rva004AB9A2::rva004AB9A2()
{
	if (m_flag == 0)
		return;
	((Rva0020DXXX *)(*(Rva0020D959Host * *)&TheLargeGroupAudio))->rva0020D959((int)&m_at24);
	setWakeFrame(getObject(), USLEEP_FOREVER);
	m_flag = 0;
}
