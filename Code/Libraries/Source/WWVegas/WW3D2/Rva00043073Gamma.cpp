// cl: /EHsc /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Gamma-setter at 0x00043073 (85B): when the +0x18 flag is clear, takes the
// DX8 device lock, sets the gamma ramp, and releases. The inline unwind guard
// couples the rowed acquire 0x0011F520 with the rowed release 0x00120F50, and
// its try-level state is what carries the /EHsc frame (with the helper-style
// __EH_prolog that /O1 selects); the guard itself emits no code. The fourth
// parameter is the bool Set_Gamma slot and the fifth is a literal 0, which is
// what orders the pushes as push-0 then push-f.
void BFME_DX8_Thread_Lock();
#include "DX8WrapperClass.h"
bool BFME_DX8_Thread_Assert();

struct Rva00043073Guard
{
	Rva00043073Guard() { BFME_DX8_Thread_Lock(); }
	~Rva00043073Guard() { BFME_DX8_Thread_Assert(); }
};

class Rva00043073
{
	char m_pad[0x18];
	unsigned char m_flag18;
public:
	void rva00043073(float gamma, float bright, float contrast, bool calibrate);
};

void Rva00043073::rva00043073(float gamma, float bright, float contrast, bool calibrate)
{
	if (m_flag18 == 0)
	{
		Rva00043073Guard lock;
		DX8Wrapper::Set_Gamma(gamma, bright, contrast, calibrate, 0);
	}
}
