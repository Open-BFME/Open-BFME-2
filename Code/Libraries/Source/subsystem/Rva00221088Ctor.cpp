// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ??0Rva00221088@@QAE@XZ @0x00221088 71B
// Subsystem ctor: baseConstruct then own vtable then setName StrategicHUD.
// Evidence: retail EH_prolog baseConstruct row StringBase PBD row setName row
// caller 0x002210F5 vtable VA 0xbe6b5c string StrategicHUD.
// Precedent Rva00222061Ctor Shell-pattern base for EH after baseConstruct.
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "SubsystemInterface.h"

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
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

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1Rva00221088@@UAE@XZ=??1?$list@URva0036ADF9Element@@V?$allocator@URva0036ADF9Element@@@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?rva001B5384@Rva00221088@@QAEXXZ=?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")
