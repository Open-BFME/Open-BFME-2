// cl: /MD /Ireference/shims/moduledata
// ??0Rva00426713@@QAE@XZ @0x00426713 36B evidence: baseConstruct 0x001B4E63 plus primary vtable 0x0083C408 plus secondary 0x0083C3F8 plus g_00BBB554 at +0x0C plus zero at +0x10
#include "Common/Snapshot.h"
extern "C" const void *const __identifier("??_7Rva00426745@@6BSubsystemInterface@@@")[];
extern "C" const void *const __identifier("??_7Rva00426745@@6BRva00426745SnapshotBase@@@")[];

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class __declspec(novtable) Rva00426713 : public SubsystemInterface, public Snapshot
{
public:
	Rva00426713();
private:
	int m_10;
};

Rva00426713::Rva00426713()
{
	_ReadWriteBarrier();
	m_10 = 0;
	*(const void **)this = __identifier("??_7Rva00426745@@6BSubsystemInterface@@@");
	*(const void **)static_cast<Snapshot *>(this) = (const void *)__identifier("??_7Rva00426745@@6BRva00426745SnapshotBase@@@");
}
