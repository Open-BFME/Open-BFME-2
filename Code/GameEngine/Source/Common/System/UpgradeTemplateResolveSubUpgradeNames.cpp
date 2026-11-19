// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
}

class ModuleData;

namespace _STL {
template<> void vector<const ModuleData *>::reserve(unsigned int);
}

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
	void rva0026F93C();

private:
	unsigned char m_pad00[0x0C];
	UpgradeTemplate *m_upgradeTemplates; // +0x0C
};

extern UpgradeCenter *TheUpgradeCenter;

class UpgradeTemplate
{
public:
	void __declspec(noinline) friend_resolveSubUpgradeNames();
	UpgradeTemplate *getNextTemplate() const { return m_nextTemplate; }

private:
	unsigned char m_unreconstructed_000[0x10];
	_STL::vector<AsciiString> m_subUpgradeNames; // +0x10
	_STL::vector<const UpgradeTemplate *> m_subUpgrades; // +0x1C
	unsigned char m_unreconstructed_028[0x64 - 0x28];
	UpgradeTemplate *m_nextTemplate; // +0x64
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

// ?rva0026F93C@UpgradeCenter@@QAEXXZ @0x0026F93C (22B)
void UpgradeCenter::rva0026F93C()
{
	for (UpgradeTemplate *upgradeTemplate = m_upgradeTemplates; upgradeTemplate != 0; upgradeTemplate = upgradeTemplate->getNextTemplate())
		upgradeTemplate->friend_resolveSubUpgradeNames();
}
