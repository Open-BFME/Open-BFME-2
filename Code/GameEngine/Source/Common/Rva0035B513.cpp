// cl: /DNDEBUG /MD /GX- /Ireference/shims/bfme2_ascii
// stlport
// ?rva0035B513@Rva0035B513@@QAEXPAUBfmeFixedStorage128@@@Z retail 0x0035B513 93B
// Honest upgrade-mask builder: clear a 128-byte bitset, walk the AsciiString
// list at +0x38/+0x3c through TheUpgradeCenter::findUpgrade, set bit
// (index>>5,1<<(index&31)) from UpgradeTemplate+0x38, then copy-construct
// the bitset into the out param.
// Evidence: unlock lane, EBP 0x80 frame with clear80 plus findUpgrade plus
// BfmeFixedStorage128 copy ctor rows, caller at 0x003283C9, ret 4.
#include "ascii_string.h"
#include <new>

#include "../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;

#include "../../Include/Common/Rva001EAE6FHelper.h"

#include "../../Include/Common/BfmeFixedStorage128.h"

class Rva0035B513
{
public:
	BfmeFixedStorage128 *rva0035B513(BfmeFixedStorage128 *out);

private:
	char m_pad[0x38];
	AsciiString *m_first;
	AsciiString *m_last;
};

BfmeFixedStorage128 *Rva0035B513::rva0035B513(BfmeFixedStorage128 *out)
{
	unsigned int tmp[32];
	((Rva001EAE6FHelper *)tmp)->clear80();
	for (AsciiString *asciiString = m_first; asciiString != m_last; ++asciiString) {
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*asciiString);
		if (upgradeTemplate)
			tmp[(static_cast<unsigned int>(upgradeTemplate->field38) >> 5)] |= 1u << (static_cast<unsigned int>(upgradeTemplate->field38) & 31);
	}
	__assume(out != 0);
	new (out) BfmeFixedStorage128((const BfmeFixedStorage128 &)tmp);
	return out;
}
