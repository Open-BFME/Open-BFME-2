// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Four singleton/global forwarder bodies (18B + 13B + 16B + 16B). Each pushes
// its operand from a stack slot (/O1), loads a global pointer into ecx and
// calls one thiscall method on it (thiscall is callee-cleanup, hence no
// caller cleanup after the call):
// 0x00224BC9 (member, 18B): g_AptWndMgr (0x00DFE4CC)->method(m_324).
//   The 0x00DFE4CC global is the peer-pinned Apt window manager.
// 0x0039ABFF (const member, 13B): g (0x00DFECC4)->rva00288CFA(this).
//   Wrapper class/signature follow the peer pin (ExperienceTracker const
//   bool member); the callee body ends ret 4, hence the stdcall spelling
//   alongside the peer's QAE pin at the same address.
// 0x003EFE72 (LivingWorldRegion member, 16B, ret 8; `this` unused):
//   ((LivingWorldBuildPlot *)slot)->ConstructBuildingImmediately(template).
//   Both retail callers (LivingWorldLogic::spawnBuilding 0x002B99F8 and
//   0x002B2590) load the region into ECX first.
// 0x00437E9C (free void(int), 16B): g (0x00E032FC)->method(a).
//   Signature/role follow the peer pin (cdecl forwarder, caller passes 1).
// Callee/global identities otherwise unproven; new names address-derived.
// One ledger row per body.
class AsciiString;

#include "../../../Libraries/Source/Apt/AptPlayerClass.h"

// Preserve the existing global pointee spelling; its storage identity is unchanged.
class Rva00224B7DTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00224BC9Owner
{
public:
	bool check();

private:
	unsigned char m_pad[0x324];
	int m_slot;
};

#include "../../Include/Common/Rva00288CFA.h"

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

#include "../../Include/GameLogic/ExperienceTracker.h"

struct Rva003F1BD3TemplateView;
#include "../../Include/GameLogic/LivingWorldBuildPlot.h"

#include "../../Include/Common/Rva0054CBEFTarget.h"

// g_pRva00437E9C is only an alias of the owned global g_Va00E032FC (ledger names column); this unit reads the owner through its own view type.
extern int g_Va00E032FC;
#define g_pRva00437E9C (*(Rva0054CBEFTarget * *)&g_Va00E032FC)

bool Rva00224BC9Owner::check()
{
	return reinterpret_cast<AptPlayer *>(((Rva00224B7DTarget *)g_bfmeAptWindowManager))->RemoveLevel(m_slot);
}

bool ExperienceTracker::rva0039ABFF() const
{
	return reinterpret_cast<Rva00288CFA *>(TheExperienceLevelSystem)->rva00288CFA((int)this);
}

struct Rva0059E647Entry;
class LivingWorldRegion
{
public:
	void rva003EFE72(void *slot, Rva0059E647Entry *buildingTemplate);
};

void LivingWorldRegion::rva003EFE72(void *slot, Rva0059E647Entry *buildingTemplate)
{
	((LivingWorldBuildPlot *)slot)->ConstructBuildingImmediately(
		(const Rva003F1BD3TemplateView *)buildingTemplate);
}

void Rva00437E9C(int value)
{
	g_pRva00437E9C->method(value);
}
