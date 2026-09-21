// ??0BaseUpgradeModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-21
// ??0BaseUpgradeModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-21
// cl: /O1 /MD /GX /DNDEBUG /Oy-
//
// ??0BaseUpgradeModuleData@@QAE@XZ, retail 0x004B3698, 94 bytes. EH ctor
// over the rowed OpenContainModuleData base (0x253487, frameless and
// therefore not unwindable): base call, xor-zero, lea of
// BuildingTemplateName at +0x118, the distinctive vtable literal 0x00C57150
// (via ??_7 pin, Devastate/UnitCrate precedent: slot0 is the scalar-deleting
// dtor shape at 0x4B3769, slot1 the shared ret stub 0x4B3FD0), single
// state-0 store, the two compact null stores, the lea of PlacementPrefix at
// +0x11C plus its null, the NONE literal homed in edi (0x00BBB50C), the two
// StringBase::set calls through the rowed 0x55F5 (UnitCrate null-plus-set
// precedent), the and-zero of PlacementIndex at +0x120, then the standard
// EH epilogue. Size 0x124 matches the rowed factory at 0x24FE37 (sole raw
// caller). Class identity is the table 0x00C57208 (BuildingTemplateName at
// +0x118, PlacementPrefix at +0x11C, PlacementIndex at +0x120) beside the
// rowed BaseUpgrade pool key and the rowed chained proc.
//
// Shape (v1-auto, 92/94, FIRST-TRY): virtual base with declared-only dtor
// plus two AsciiString members (inline zero-init plus declared-only dtor,
// auto-constructed) plus body sets to "NONE" plus trailing and-zero. States
// 0 and 2 fall out exactly (one per string-group, UnitCrate 0,1 precedent
// for a single string).
//
// SOLE WALL (2 bytes): epilogue restores. Retail pops only esi (5E) and
// abandons the pushed ebx/edi; every variant here pops edi+esi+ebx
// (5F+5E+5B). Refuted: /Oy- on/off, /G6, /G7, /O2 (SEH-inline disaster),
// /Ot (SEH-inline disaster), /Og-, /Ob0 (disaster), /Oi- (identical).
// The prolog pushes and all stores/calls/branches are byte-identical; the
// save/restore mask is a pure codegen quirk needing a new lever (toolchain
// patch-level or unseen shape). Do NOT retry blind flag swaps.

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	unsigned char m_pad[0x118 - 4];
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const char *str);

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

class BaseUpgradeModuleData : public OpenContainModuleData
{
public:
	BaseUpgradeModuleData();
	virtual ~BaseUpgradeModuleData();

private:
	AsciiString m_buildingTemplateName; // +0x118
	AsciiString m_placementPrefix; // +0x11C
	int m_placementIndex; // +0x120
};

// ??0BaseUpgradeModuleData@@QAE@XZ @0x4B3698
BaseUpgradeModuleData::BaseUpgradeModuleData()
{
	m_buildingTemplateName.set("NONE");
	m_placementPrefix.set("NONE");
	m_placementIndex = 0;
}
