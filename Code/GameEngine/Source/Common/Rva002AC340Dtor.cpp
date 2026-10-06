// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Rva002AC340@@MAE@XZ @0x002AC366 (60B): Rva002AC340 dtor.
// Stores own vtable 0x007FDD6C, frees the BfmeE16 vector buffer at +8 via
// rowed _free 0x00030830, then restores Snapshot base vtable 0x00BBB554
// through the TU-local inline Snapshot base. Same class as rowed ctor 0x002AC340 (vtable
// 0x007FDD6C int at +4 vector at +8). Callers at 0x002AC3A5 0x002B1323 plus
// unwinds at 0x00775DE0 0x00775F6C. Follows PillageModuleDataDtor pattern.
#include <vector>
#include "Common/Snapshot.h"

struct BfmeE16 { float x, y, z, w; };

class Rva002AC340 : public Snapshot
{
public:
	Rva002AC340();
protected:
	virtual ~Rva002AC340();
private:
	int m_int;
	_STL::vector<BfmeE16> m_vec;
};

Rva002AC340::~Rva002AC340()
{
}
