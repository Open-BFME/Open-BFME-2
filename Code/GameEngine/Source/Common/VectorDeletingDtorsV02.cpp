// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V02: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot
//   0x003A6E82  0x0049B47C  0x30  0x00C1BBD0#0
//   0x00001F64  0x00001F18  0x0C  0x00BBB59C#0
//   0x001F3574  0x0049B47C  0x08  0x00BE1548#0
//   0x001F36C3  0x0049B47C  0x48  0x00BE15A4#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
#include <new>

// Complete-destructor providers exist for this collector; unresolved owners
// remain byte-verified in the corresponding _Unresolved unit.

namespace FXParticleSystem
{
template <int CATEGORY> class CategoryModuleTemplate;
}

#include "../../Include/GameClient/TerrainFireEmissionInfo.h"
namespace FXParticleSystem
{
}

namespace FXParticleSystem
{
template <>
class CategoryModuleTemplate<8>
{
public:
	CategoryModuleTemplate();
	virtual ~CategoryModuleTemplate();
private:
	char m_unmodelled_04[0xC - 0x04];
};
}

#include "../../Include/GameClient/EmissionVolumeInfo.h"

#include "../../Include/GameClient/WindModuleInfo.h"
namespace FXParticleSystem
{
}

// ?<bfmeVectorDeleteAnchorV02> absent-from-retail
void bfmeVectorDeleteAnchorV02()
{
	new FXParticleSystem::TerrainFireEmissionInfo[2];
	new FXParticleSystem::CategoryModuleTemplate<8>[2];
	new FXParticleSystem::EmissionVolumeInfo[2];
	new FXParticleSystem::WindModuleInfo[2];
}
