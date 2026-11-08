// cl: /DBFME_ASCII_DTOR_DECL /DNDEBUG /MD /GX- /Oi-
// stlport
//
// ?rva00507877@Rva00507823@@UAEXXZ retail 0x00507877 163B
// Virtual slot 8 offset 0x20 of vtable 0x00864010 class of
// ??1Rva00507823@@UAE@XZ plus slot 8 of 0x00864C38 Made002CCA37 and
// 0x008650B8 Made002CCCF3. Resolves upgrade-name vectors at +0x108 and
// +0x114 via UpgradeCenter findUpgrade 0x0026F26D into bitsets at +0x04
// and +0x84 then erases both vectors via 0x002CCFC. Same UpgradeMuxData
// getUpgradeActivationMasks shape with masks at +0x04 and vectors at
// +0x108 per ctor 0x0050775B clear80 and Vector_base layout. Callers at
// 0x005092B5 and 0x005095FE and 0x005097D1 plus jmp at 0x0050B928.
#include <vector>
#include <string.h>

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


struct UpgradeMaskType
{
	void clear()
	{
		memset(&m_words[0], 0, sizeof(m_words));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (unsigned long)1 << (bit & 31);
	}
	unsigned long m_words[32];
};

#include "../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;	// Upgrade.cpp's global (0x009FEB60)

#include "../../Include/GameLogic/Module/Rva00507823.h"

void Rva00507823::rva00507877()
{
	_STL::vector<AsciiString>::const_iterator it;
	for (it = reinterpret_cast<_STL::vector<AsciiString> &>(m_storage108).begin(); it != reinterpret_cast<_STL::vector<AsciiString> &>(m_storage108).end(); ++it)
	{
		const UpgradeTemplate *theTemplate = TheUpgradeCenter->findUpgrade(*it);
		if (theTemplate)
			reinterpret_cast<UpgradeMaskType &>(m_mask04).set(theTemplate->field38);
	}
	for (it = reinterpret_cast<_STL::vector<AsciiString> &>(m_storage114).begin(); it != reinterpret_cast<_STL::vector<AsciiString> &>(m_storage114).end(); ++it)
	{
		const UpgradeTemplate *theTemplate = TheUpgradeCenter->findUpgrade(*it);
		if (theTemplate)
			reinterpret_cast<UpgradeMaskType &>(m_mask84).set(theTemplate->field38);
	}
	reinterpret_cast<_STL::vector<AsciiString> &>(m_storage108).clear();
	reinterpret_cast<_STL::vector<AsciiString> &>(m_storage114).clear();
}
