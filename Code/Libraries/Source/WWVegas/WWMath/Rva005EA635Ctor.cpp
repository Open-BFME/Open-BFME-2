// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva005EA635@@QAE@XZ @0x005EA635 86B ctor with AsciiString temp plus base plus vtable
// Constructs AsciiString DynamicAutoResolveDialog passes to base Rva00221635 then installs vtable g_00C781B8 and +8=10; base needs dtor for EH states per lever
#include "ascii_string.h"
#include "../../../../GameEngine/Include/Common/Rva00221635.h"
class Rva005EA635 : public Rva00221635
{
public:
	virtual void g0();
	Rva005EA635();
private:
	int m_val;
};
Rva005EA635::Rva005EA635() : Rva00221635(AsciiString("DynamicAutoResolveDialog"))
{
	m_val = 10;
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??0Rva00221635@@QAE@ABVAsciiString@@@Z=??0Rva00221635@@QAE@H@Z")
#pragma comment(linker, "/alternatename:?f0@Rva00221635@@UAEXXZ=??_GRva005E9F7B@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?g0@Rva005EA635@@UAEXXZ=?rva005E9F80@Rva005E9F80@@UAEXPAVINI@@@Z")
