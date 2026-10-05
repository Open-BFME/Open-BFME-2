// cl: /Ireference/shims/moduledata /O1 /MD /EHsc
//
// ??1Rva002D3573@@UAE@XZ retail 0x002D3573 76B.
// MI dtor: primary GameEngineDeletingBase (size 0xC) at +0 with vtable
// 0x00802AA8, secondary Snapshot at +0xC with vtable 0x00802A94 restored to
// base 0x007BB554 via inline Snapshot dtor, member Rva000AD6F4 at +0x10
// cleared via pinned ?clear@Rva000AD6F4@@QAEXXZ at 0x000AD6F4, then rowed
// ??1GameEngineDeletingBase@@UAE@XZ at 0x001B4E74. Neighbours
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

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

#include "Common/Snapshot.h"

class Rva002D3573 : public GameEngineDeletingBase, public Snapshot
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
