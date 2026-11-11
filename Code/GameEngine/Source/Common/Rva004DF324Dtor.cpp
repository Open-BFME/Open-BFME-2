// cl: /GX- /MD /DNDEBUG
// Opaque dtor at 0x004DF324 (vptr + consts + pool-member call, tail-jmp base).
// Retail: push esi/mov esi,ecx/lea ecx,[esi+0x24]/mov [esi],0xC61588/
// mov [esi+0xC],0xBEFF90/mov [esi+0x10],0xC6157C/call 0x268902/
// mov ecx,esi/pop esi/jmp 0x4DF7C2 (35B). Models the ModuleUpdateDtors2
// precedent (ArrowStormUpdate 49B): single polymorphic base declared-only (its
// dtor resolves to the opaque pin at 0x004DF7C2), two const members assigned
// from secondary-table addresses (DIR32 sites), and an opaque
// PoolMember at +0x24 whose method resolves to the pin at 0x00268902.
// Owner identity unproven (opaque Rva name).

#include "../../Include/Common/PoolMember.h"

// Base dtor resolves to the opaque pin at 0x004DF7C2 (same 12B layout as
// the Rva004DF7C2Derived family TU: vptr + 8 pad).
class ObjectHelper
{
public:
	virtual ~ObjectHelper();

private:
	char m_pad04[8];
};

class Rva004DF324 : public ObjectHelper
{
public:
	virtual ~Rva004DF324();

private:
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x24 - 0x14];
	PoolMember m_mem24;
};

extern "C" char __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@"); // The separate folded table at RVA 0x007EFF90 remains debt.

// Retail's secondary table at RVA 0x0086157C has three entries before the
// primary table at 0x00861588. Keep the existing inventory symbol, but own
// the complete initialized table instead of a zero-filled integer stand-in.
// These declarations take the rowed entry addresses; they are never called
// through the erased signatures here. The module's class identity is unknown.
extern "C" {
void __identifier("?Rva004A6563Get@@YAHXZ")();
void __identifier("?getDisabledTypesToProcess@Rva004DF396@@UBE?AV?$BitFlags@$0L@@@XZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
extern const void *const s_10[3] = {
	(const void *)&__identifier("?Rva004A6563Get@@YAHXZ"),
	(const void *)&__identifier("?getDisabledTypesToProcess@Rva004DF396@@UBE?AV?$BitFlags@$0L@@@XZ"),
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")
};
}

Rva004DF324::~Rva004DF324()
{
	m_p0C = &__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = &s_10;
	m_mem24.Rva00268902();
}
