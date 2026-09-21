// cl: /O1 /MD /GX /DNDEBUG /Oy-
//
// ??0BaseUpgradeModuleData@@QAE@XZ, retail 0x004B3698, 98 bytes. EH ctor
// over the rowed OpenContainModuleData base (0x253487, frameless and
// therefore not unwindable): base call, xor-zero, lea of
// BuildingTemplateName at +0x118, the distinctive vtable literal 0x00C57150
// (via ??_7 pin: slot0 is the scalar-deleting dtor shape at 0x4B3769, slot1
// the shared ret stub 0x4B3FD0), single state-0 store, the two compact null
// stores, the lea of PlacementPrefix at +0x11C plus its null, the NONE
// literal homed in edi (0x00BBB50C), the two StringBase::set calls through
// the rowed 0x55F5, the and-zero of PlacementIndex at +0x120, then the
// standard EH epilogue with the return-this move between the restores.
// Size 0x124 matches the rowed factory at 0x24FE37 (sole raw caller). Class
// identity is the table 0x00C57208 (BuildingTemplateName at +0x118,
// PlacementPrefix at +0x11C, PlacementIndex at +0x120) beside the rowed
// BaseUpgrade pool key and the rowed chained proc. Supersedes the 0.98 bank
// (its 94B size under-claimed the true 98B body; the full emission matches).

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
