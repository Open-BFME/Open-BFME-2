// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??1ClearanceTestingSlowDeathBehaviorModuleData@@UAE@XZ, retail 0x00483EE1, 56 bytes.
// SlowDeath-side ModuleData dtor (ctor rowed at 0x483E25). Layout from the ctor
// TU (0x190-byte SlowDeath base plus GeometryInfo member at +0x190 size 0x5C
// plus float tail to 0x208 matching the factory news). Teardown is the
// GeometryInfo word at +0x190 through the rowed 0x50B2A dtor then the base
// through the rowed 0x45E4A5 dtor. BFME1 donor is
// ClearanceTestingSlowDeathBehaviorModuleDataDestructorThunk.cpp. Caller is
// the slot-0 scalar-deleting dtor at 0x483EC5 (vtable 0x00849E98). novtable
// suppresses the derived vtable store retail lacks.

class SlowDeathBehaviorModuleData
{
public:
	virtual ~SlowDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x190 - 4];
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();

private:
	unsigned char m_data[0x5C - 4];
};

class __declspec(novtable) ClearanceTestingSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	virtual ~ClearanceTestingSlowDeathBehaviorModuleData();

private:
	GeometryInfo m_geometry; // +0x190
	unsigned char m_tail[0x208 - 0x190 - 0x5C]; // +0x1EC float tail
};

ClearanceTestingSlowDeathBehaviorModuleData::~ClearanceTestingSlowDeathBehaviorModuleData()
{
}
