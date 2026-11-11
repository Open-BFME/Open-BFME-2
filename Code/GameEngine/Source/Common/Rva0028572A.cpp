// cl: /MD
class Rva0028572AHost;
class Rva0020D959Host
{
public:
};
class LargeGroupAudio; extern LargeGroupAudio *TheLargeGroupAudio;
// The ledger row at 0x0020D959 is Rva0020DXXX::rva0020D959(int).
#include "../../Include/Common/Rva0020DXXX.h"

class Rva0028572AHost
{
public:
	void rva0028572A();
private:
	unsigned char m_pad[0x10];
	int m_10;
};
// ?rva0028572A@Rva0028572AHost@@QAEXXZ
void Rva0028572AHost::rva0028572A()
{
	if (m_10 != -1)
	{
		((Rva0020DXXX *)(*(Rva0020D959Host * *)&TheLargeGroupAudio))->rva0020D959((int)this);
		m_10 = -1;
	}
}
