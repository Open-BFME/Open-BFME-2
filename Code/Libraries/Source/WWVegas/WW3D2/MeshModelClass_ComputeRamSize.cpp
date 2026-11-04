// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// MeshModelClass::Compute_Ram_Size: BFME2 RVA 0x001880E0;
// BFME1 donor RVA 0x0096C9B0.
// BFME2 repair: geometry base is 0x8C (retail reads +0x8C/+0x90/+0x98),
// 8 less than BFME1's 0x94; tail layout otherwise identical.

#include "MeshModelClass.h"

#include "MeshMatDescClass.h"

// Call-only view of the existing 0x0016EEE0 owner. The canonical MatInfo
// pointer keeps its MaterialInfoClass type; the original method name is unknown.
class BfmeThingVNQ
{
public:
	int bfmeTotalVNQ();
};

int MeshModelClass::Compute_Ram_Size()
{
	int size = MeshGeometryClass::Compute_Ram_Size();
	if (DefMatDesc != 0)
		size += DefMatDesc->Compute_Ram_Size();
	if (AlternateMatDesc != 0)
		size += AlternateMatDesc->Compute_Ram_Size();
	if (MatInfo != 0)
		size += reinterpret_cast<BfmeThingVNQ *>(MatInfo)->bfmeTotalVNQ();
	return size;
}
