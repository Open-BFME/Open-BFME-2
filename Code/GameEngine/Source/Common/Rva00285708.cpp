// cl: /MD
// ?rva00285708@Rva00285708Host@@QAEXXZ @ 0x00285708 34B: guarded refresh via global 0xDFE1A8 callee 0x20D925 then stamp TheGameLogic frame. Evidence: rowed registerSubject 0x0020D925 plus TheGameLogic 0x009FE78C plus g_00DFE1A8 0x00DFE1A8 plus sibling Rva002856CF plus sibling Rva0028572A plus callers 0x00285B91 0x00285C30.
#include "../../Include/Common/Rva0020DXXX.h"
class Rva0020D959Host;
class LargeGroupAudio; extern LargeGroupAudio *TheLargeGroupAudio;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva00285708Host
{
public:
	void rva00285708();
private:
	unsigned char m_pad[0x10];
	int m_10;
};
void Rva00285708Host::rva00285708()
{
	if (m_10 != -1)
		return;
	((Rva0020DXXX *)(*(Rva0020D959Host * *)&TheLargeGroupAudio))->registerSubject((int)this);
	m_10 = TheGameLogic->getFrame();
}
