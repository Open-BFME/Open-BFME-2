// cl: /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0007E12F@Rva0007E12F@@QAEXXZ retail 0x0007E12F 76B lock DX8 thread then
// clear embedded reset-texture ref at +0xF8 and release Rva00083E5C holder
// at +0x100 via its 43B dual release. Evidence: chain calls 0x00083E5C;
// callers at 0x00066939 0x0008221E.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva00083E5C.h"
class Rva0007E12F
{
public:
	void rva0007E12F();
private:
	char _pad00[0xF8];
	BfmeResetTextureRef m_f8;
	char _padFC[4];
	Rva00083E5C *m_100;
};
void Rva0007E12F::rva0007E12F()
{
	BFMEDX8DeviceLock guard;
	if (m_f8.pointer != 0)
		m_f8.clear();
	Rva00083E5C *p = m_100;
	if (p != 0)
		p->rva00083E5C();
}
