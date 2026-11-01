// ?xferUpgradeMask@@YAXPAVXfer@@PAVRva00291440@@@Z
// partial score=0.98 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG /G7
// Native 003064CB..00306629: complete 350-byte upgrade-mask transfer.
// Semantic donor: BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// game/GameEngine/Source/Common/System/XferUpgradeMask.cpp.
// Native storage is 1024 bits, template name/index/next are +8/+38/+64.
// Inline bit operations fix the previous bank's Xfer/bitset register swaps.
// Declaring the zero loop index before comparing count restores immediate0.
// Native001DB0A8 is a folded four-byte +C getter, shared by unrelated classes.
// Address-derived name records only its pointer-return ABI in this consumer;
// no original UpgradeCenter getter name is asserted. UpgradeCenterFindUpgradeByKey
// independently establishes list head at +C; retail REL32 calls corroborate it.
// Natural XferException uses the native 8-byte class and metadata.
// All350 instruction bytes match; compiler trailing INT3 also matches native.
#include "ascii_string.h"
#include <cstring>

class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Rva00291440 {
public:
 unsigned int words[32];
 __forceinline bool testBit(unsigned int bit) const { return (words[bit>>5] & (1u<<(bit&31))) != 0; }
 __forceinline void setBit(unsigned int bit) { words[bit>>5] |= 1u<<(bit&31); }
};
#include "../../../Include/Common/Upgrade.h"


extern UpgradeCenter *TheUpgradeCenter;
// Retail ThrowInfo identifies the 8-byte XferException class and its
// established constructor, copy constructor and destructor providers.
#include "../../../Include/Common/XferException.h"

namespace FXParticleSystem
{
}

// ?Rva003064CBXfer@@YAXPAVXfer@@PAI@Z
void __cdecl xferUpgradeMask(Xfer *xfer, Rva00291440 *bits)
{
	Xfer *transfer = xfer;
	Rva00291440 *m_upgradeMask = bits;
	transfer->Version1();
	if (transfer->IsStoring()) {
		AsciiString upgradeName;
		unsigned int count = 0;
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->rva001DB0A8();
		while (upgradeTemplate) {
			unsigned int bit = upgradeTemplate->field38;
			if (m_upgradeMask->testBit(bit))
				count++;
			upgradeTemplate = upgradeTemplate->m_next;
		}
		*transfer == *reinterpret_cast<unsigned short*>(&count);
		upgradeTemplate = TheUpgradeCenter->rva001DB0A8();
		while (upgradeTemplate) {
			unsigned int bit = upgradeTemplate->field38;
			if (m_upgradeMask->testBit(bit)) {
				((StringBase<char> &)(upgradeName)).set((const StringBase<char> &)(upgradeTemplate->m_name));
				*transfer == upgradeName;
			}
			upgradeTemplate = upgradeTemplate->m_next;
		}
	} else {
		AsciiString upgradeName;
		unsigned short count;
		*transfer == count;
		memset(m_upgradeMask, 0, 0x80);
		unsigned short i=0;
		if (count > i) {
			do {
				*transfer == upgradeName;
				const UpgradeTemplate *up = TheUpgradeCenter->findUpgrade(upgradeName);
				if (!up) {
					throw XferException(0, 0);
				}
				unsigned int bit = up->field38;
				m_upgradeMask->setBit(bit);
				++i;
			} while (i < count);
		}
	}
}
