// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??1RunOffMapBehaviorModuleData@@UAE@XZ at retail 0x00255EA8 (48B).
// Virtual dtor over vtable 0x00BF3298 (slot 0 deleting dtor at 0x00255E8C).
// Layout from the rowed ctor TU at 0x00254ECE (RunToLocation@8 and float@C
// 10.0f, RequiresSpecificTrigger@10, WaypointName AsciiString@14, DieOnMap@18,
// news 0x1C, INI table 0xC42F70). Destruction is the AsciiString at +0x14 via
// the folded 0x00036410 teardown then the Snapshot base vtable 0x00BBB554
// restored inline with no base call (GettingBuilt/Building precedent).

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();
private:
	char *m_data;
};

class __declspec(novtable) RunOffMapBehaviorModuleData : public Snapshot
{
public:
	virtual ~RunOffMapBehaviorModuleData();
private:
	int m_unused04;
	float m_runToLocation;
	float m_unnamed0C;
	bool m_requiresSpecificTrigger;
	AsciiString m_runOffMapWaypointName;
	bool m_dieOnMap;
};

RunOffMapBehaviorModuleData::~RunOffMapBehaviorModuleData()
{
}
