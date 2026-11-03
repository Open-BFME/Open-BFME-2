// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
//
// Vector deleting destructors (??_E), batch V05: 78-byte bodies (element size pushed as imm32) that, for
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
//   0x000025B2  0x0000240E  0x9C  0x00BBB5C8#0
//   0x001FC052  0x001FBF4D  0xD4  0x00BE1A28#0
//   0x003A6C0B  0x0049B47C  0x8C  0x00C1BBA0#0
//   0x003A805A  0x0049B47C  0x98  0x00C1BDB0#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
#include <new>

// Complete-destructor providers exist for this collector; unresolved owners
// remain byte-verified in the corresponding _Unresolved unit.

namespace FXParticleSystem
{
class ParticleSystemInfo
{
public:
	ParticleSystemInfo();
	virtual ~ParticleSystemInfo();
private:
	char m_unmodelled_04[0x9C - 0x04];
};
}

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const AsciiString &name = AsciiString());
	virtual ~ParticleSystemTemplate();
private:
	char m_unmodelled_04[0xD4 - 0x04];
};
}

#include "../../Include/GameClient/LightningEmissionInfo.h"
namespace FXParticleSystem
{
}

#include "../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
namespace FXParticleSystem
{
}

// ?<bfmeVectorDeleteAnchorV05> absent-from-retail
void bfmeVectorDeleteAnchorV05()
{
	new FXParticleSystem::ParticleSystemInfo[2];
	new FXParticleSystem::ParticleSystemTemplate[2];
	new FXParticleSystem::LightningEmissionInfo[2];
	new FXParticleSystem::RenderObjectUpdateModuleInfo[2];
}
