// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ??0Rva00221088@@QAE@XZ @0x00221088 71B
// Subsystem ctor: baseConstruct then own vtable then setName StrategicHUD.
// Evidence: retail EH_prolog baseConstruct row StringBase PBD row setName row
// caller 0x002210F5 vtable VA 0xbe6b5c string StrategicHUD.
// Precedent Rva00222061Ctor Shell-pattern base for EH after baseConstruct.
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

class SubsystemInterface
{
public:
	void setName(AsciiString name);
};

class Rva00221088 : public BFME2NativeNetworkBase
{
public:
	Rva00221088();
	virtual ~Rva00221088();
	void rva001B5384();
private:
	char m_pad0C[4];
};

Rva00221088::Rva00221088()
{
	((SubsystemInterface *)this)->setName("StrategicHUD");
}

// ?rva002210CF@@YAXXZ @0x002210CF 94B, contiguous after the ctor: the
// StrategicHUD subsystem as a function-local static (guard bit, ctor above,
// atexit cleanup registered), then a one-time call of its 0x001B5384 setup
// behind a separate flag. Address-derived names; the global and its cleanup
// thunk are viewed as g_Va00DFE49C / rva007B76FA elsewhere.
void rva002210CF()
{
	static Rva00221088 s_strategicHud;
	static bool s_setUp;
	if (!s_setUp)
	{
		s_strategicHud.rva001B5384();
		s_setUp = true;
	}
}
