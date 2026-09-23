// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0CostModifierUpgradeModuleData@@QAE@XZ, retail 0x004B5BAC, 184 bytes.
// CostModifier upgrade data: ObjectFilter at +0x118 builds through the
// opaque 0x3623E5 pin, the Percentage list at +0x11C and the
// ApplyToTheseUpgrades list at +0x130 build through the ICF-folded
// Vector_base at 0x00211E58, UpgradeDiscount/StartsActive/Slaughter at
// +0x128/+0x129/+0x12A default to false, LabelForPalantirString at +0x12C
// nulls then sets ">UNSPECIFIED<" through the rowed StringBase::set at
// 0x000055F5, and two 28B FixedStorage temps copy-constructed from the
// prototype at 0x00DFEFA4 feed the filter through the 0x362087 pin.
// Own table 0x00C582D8 proves every field; the ModuleData factory at
// 0x00250316 news the 0x13C span and calls this ctor as sole caller.
// Shape follows AutoPickUpUpdateModuleDataCtor (filter plus vector plus
// temps) over SubObjectsUpgradeModuleDataCtor (rowed OpenContainModuleData
// base). Levers: (1) the base is virtual-but-empty (rowed TU is novtable
// with a virtual dtor), so it shares the derived vptr at +0 and the base
// call stays this-direct while the pad covers +4..+0x117. (2) The derived
// class is virtual with a declared-only dtor, so the compiler installs
// 0x00C58210 through the ??_7 pin; /O1 sinks that store below the filter
// member-init call (second instance after the V1b probe). (3) The virtual
// base destructor is the fourth EH unwindable, raising the temp-guard
// state from the probed 3 to retail 4. (4) StartsActive at +0x129 is a
// body-last store (the other two bytes stay in the init-list) to reach
// retail trailing position. (5) vector<float> needs its own ICF-fold
// alias pin to 0x00211E58 (int/unsigned/AsciiString precedent).

#include <vector>

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	void set(const T *text);
	~StringBase();

	void *m_data;
};

class AsciiString
{
public:
	AsciiString();
	~AsciiString();

private:
	char *m_data;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

class __declspec(novtable) OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();
}; // Virtual (shares the derived vptr at +0, so the base call stays
	// this-direct) but empty: the rowed folded 0x253487 body runs against
	// this (its vtable store is overwritten by the derived install below
	// and its +8 member setup lands in the pad).

class CostModifierUpgradeModuleData : public OpenContainModuleData
{
public:
	CostModifierUpgradeModuleData();
	virtual ~CostModifierUpgradeModuleData();

private:
	unsigned char m_pad[0x118 - 4]; // +4..+0x117, vptr at +0 is compiler-installed
	Rva003623E5Member m_objectFilter; // +0x118, ObjectFilter
	_STL::vector<float> m_percentages; // +0x11C, Percentage list
	bool m_upgradeDiscount; // +0x128, UpgradeDiscount
	bool m_startsActive; // +0x129, StartsActive
	bool m_slaughter; // +0x12A, Slaughter
	unsigned char m_pad12B; // +0x12B
	StringBase<char> m_labelForPalantirString; // +0x12C, LabelForPalantirString
	_STL::vector<AsciiString> m_applyToTheseUpgrades; // +0x130, ApplyToTheseUpgrades
};

// ??0CostModifierUpgradeModuleData@@QAE@XZ @0x4B5BAC
CostModifierUpgradeModuleData::CostModifierUpgradeModuleData()
	: m_upgradeDiscount(false)
	, m_slaughter(false)
{
	m_objectFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
	m_labelForPalantirString.set(">UNSPECIFIED<");
	m_startsActive = false;
}
