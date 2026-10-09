// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /EHsc
//
// ??1Rva002D3573@@UAE@XZ retail 0x002D3573 76B.
// MI dtor: primary SubsystemInterface (size 0xC) at +0 with vtable
// 0x00802AA8, secondary Snapshot at +0xC with vtable 0x00802A94 restored to
// base 0x007BB554 via inline Snapshot dtor, member Rva000AD6F4 at +0x10
// cleared via pinned ?clear@Rva000AD6F4@@QAEXXZ at 0x000AD6F4, then rowed
// ??1SubsystemInterface@@UAE@XZ at 0x001B4E74. Neighbours
// Rva002D352CMaxStore.cpp and RadarWindowOverride.cpp give the System TU and
// /O1 flags; EH shape follows Rva005C3549Dtor (clear in dtor body with /EHsc)
// and RadarDtor (MI with Snapshot restore to g_00BBB554).

class Rva000AD6F4
{
public:
	void clear();
private:
	char m_pad[8];
};

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

#include "Common/Snapshot.h"

class Rva002D3573 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva002D3573();
private:
	Rva000AD6F4 m10;
};

Rva002D3573::~Rva002D3573()
{
	m10.clear();
}
