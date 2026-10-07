// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?friend_resolveSubUpgradeNames@UpgradeTemplate@@QAEXXZ
//
// UpgradeTemplate::friend_resolveSubUpgradeNames, retail 0x0026F8D6 (102 bytes).
// Identity (target): WorldBuilder debug Upgrade.cpp line 338 names it
// (wb-lead 2/callgraph); its only caller is the 22-byte list walk at
// 0x0026F93C over TheUpgradeCenter's template list (+0x0C head, +0x64 next).
// Retail callees in order: pointer-vector reserve (0x002B712E fold),
// UpgradeCenter::findUpgrade (0x0026F26D), pointer-vector push_back
// (0x004DFCB0 fold), vector<AsciiString>::erase (0x0002CCFC).
// Layout (target-measured): sub-upgrade name vector at +0x10, resolved
// template vector at +0x1C. Structure (inference): names are resolved once
// into templates and the name list is then cleared.
#include "ascii_string.h"
#include <vector>

class ModuleData;
class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class UpgradeTemplate
{
public:
	void friend_resolveSubUpgradeNames();

private:
	unsigned char m_unreconstructed_000[0x10];
	_STL::vector<AsciiString> m_subUpgradeNames; // +0x10
	_STL::vector<const UpgradeTemplate *> m_subUpgrades; // +0x1C
};

void UpgradeTemplate::friend_resolveSubUpgradeNames()
{
	if (!m_subUpgradeNames.empty())
	{
		unsigned int count = m_subUpgradeNames.size();
		reinterpret_cast<_STL::vector<const ModuleData *> *>(&m_subUpgrades)->reserve(count);
		for (unsigned int i = 0; i < count; ++i)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_subUpgradeNames[i]);
			if (upgrade)
				reinterpret_cast<_STL::vector<const ModuleData *> *>(&m_subUpgrades)->push_back(*reinterpret_cast<const ModuleData * const *>(&upgrade));
		}
		m_subUpgradeNames.clear();
	}
}
