// cl: /MD /Ireference/shims/moduledata
// ??0Rva0041AC6A@@QAE@XZ, retail 0x0041AC6A, 32 bytes.
// Evidence: leaf lane, caller at 0x0022FAC5, callee baseConstruct 0x001B4E63,
// vtable g_00C3ADD8 at +0, second vtable g_00C3ADC8 at +0xC overwriting g_00BBB554.
#include "Common/Snapshot.h"
extern "C" const void *const __identifier("??_7Rva0041B790@@6BSubsystemInterface@@@")[];
extern "C" const void *const __identifier("??_7Rva0041B790@@6BSnapshot@@@")[];

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) GameStateMap : public SubsystemInterface, public Snapshot
{
public:
	GameStateMap();
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

GameStateMap::GameStateMap()
{
	_ReadWriteBarrier();
	*(const void **)this = (const void *)__identifier("??_7Rva0041B790@@6BSubsystemInterface@@@");
	*(const void **)static_cast<Snapshot *>(this) = (const void *)__identifier("??_7Rva0041B790@@6BSnapshot@@@");
}
