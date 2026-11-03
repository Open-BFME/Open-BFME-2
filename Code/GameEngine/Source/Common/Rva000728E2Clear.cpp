// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva000728E2@Rva000728E2@@QAEXXZ, RVA 0x000728E2, 14B. Small clear wrapper:
// if the BfmeResetTextureRef holder at +0x1c is non-null tail-jump to its
// clear (rowed 0x0004D75B). Evidence: 7 callers pass holder owners at
// 0x668B2/0x668CA/0x72D20/0x73134/0x73BAB/0x73C16/0x7441B; sibling 0x728F0
// addresses the same +0x1c holder with +0x20/+0x24 and flag +0x35.
#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"
class Rva000728E2
{
public:
	void rva000728E2();
private:
	char m_pad[0x1c];
	BfmeResetTextureRef m_ref;
};
void Rva000728E2::rva000728E2()
{
	if (m_ref.pointer)
		m_ref.clear();
}
