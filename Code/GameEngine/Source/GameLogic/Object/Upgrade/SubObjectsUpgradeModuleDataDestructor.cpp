// cl: /Ireference/shims/bfme2_ascii /Oy- /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1SubObjectsUpgradeModuleData@@UAE@XZ @0x004B5214, 127 bytes.
// Target identity is supported by the audited SubObjectsUpgrade registration,
// the data factory at 0x0025780C, constructor at 0x00257768, and vtable
// 0x00BF41A8 (see deleting-destructor-identity-audit.md). Ghidra confirms the
// retail destructor clears the vector at +0x13C through the helper at
// 0x004C0628, destroys vectors at +0x13C/+0x130/+0x124/+0x118, then restores
// Snapshot's vtable. Member order and replacement-model semantics follow the
// BFME1 donor at the current reference pointer. Retail Ghidra evidence shows
// that BFME2 stores 8-byte replacement-model values in the final vector, so
// this target-specific declaration uses values rather than donor pointers.

extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

#include <vector>


#include "ascii_string.h"

struct Rva00B6CF1
{
	~Rva00B6CF1();

	AsciiString m_source;
	AsciiString m_replacement;
};

class Snapshot
{
public:
	virtual ~Snapshot();

private:
	unsigned char m_pad[0x118 - 4];
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}

class SubObjectsUpgradeModuleData : public Snapshot
{
public:
	virtual ~SubObjectsUpgradeModuleData();

private:
	_STL::vector<AsciiString> m_showSubObjectNames;
	_STL::vector<AsciiString> m_hideSubObjectNames;
	_STL::vector<AsciiString> m_upgradeSubObjectNames;
	_STL::vector<Rva00B6CF1> m_replacementModels;
	unsigned int m_defaultConditionState;
	unsigned int m_defaultAnimationState;
	unsigned char m_showOnlySelected;
	unsigned char m_hideOnlySelected;
};

SubObjectsUpgradeModuleData::~SubObjectsUpgradeModuleData()
{
	m_replacementModels.clear();
}
