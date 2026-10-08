// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs
// Native 0x000532B7..0x0005333F, 136 bytes, RET4: Xfer flag virtual 0x90 then BfmeAudioEventPrefix136(ref 0) release xfer rva002D9FD9 return m_int0C else 1. Evidence: rowed EH_prolog 0x629188 BfmeAudioEventPrefix136 ctor 0x2D97D6 Release 0x50ED3 dtor 0x2D9A43 pin rva002D9FD9 0x2D9FD9; callers 0x5983F 0x59859; ret 0x4 stdcall.
#include "Common/BfmeAudioEventPrefix136.h"

class Xfer
{
public:
	virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03(); virtual void x04();
	virtual void x05(); virtual void x06(); virtual void x07(); virtual void x08(); virtual void x09();
	virtual void x10(); virtual void x11(); virtual void x12(); virtual void x13(); virtual void x14();
	virtual void x15(); virtual void x16(); virtual void x17(); virtual void x18(); virtual void x19();
	virtual void x20(); virtual void x21(); virtual void x22(); virtual void x23(); virtual void x24();
	virtual void x25(); virtual void x26(); virtual void x27(); virtual void x28(); virtual void x29();
	virtual void x30(); virtual void x31(); virtual void x32(); virtual void x33(); virtual void x34();
	virtual void x35();
	virtual void getFlag(unsigned char *flag);
};

// The native state transitions and temporary Release_Ref call prove that
// the null reference argument owns its temporary lifetime through the call.
struct Rva000532B7TemporaryRef : OpaqueRefElement4 {
    __forceinline Rva000532B7TemporaryRef() { referent = 0; }
    __forceinline ~Rva000532B7TemporaryRef() { if (referent) referent->Release_Ref(); }
};
int __stdcall Rva000532B7Get(Xfer *xfer)
{
	unsigned char flag;
	xfer->getFlag(&flag);
	if (flag != 0) {
		BfmeAudioEventPrefix136 prefix(Rva000532B7TemporaryRef(), 0);
		prefix.rva002D9FD9(xfer);
		int result = prefix.m_int0C;
		return result;
	}
	return 1;
}
