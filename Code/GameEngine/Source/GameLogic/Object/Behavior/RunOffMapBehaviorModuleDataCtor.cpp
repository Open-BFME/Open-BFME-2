// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0RunOffMapBehaviorModuleData@@QAE@XZ, retail 0x00254ECE (86 bytes).
// The module-data half of RunOffMapBehavior: vtable 0x00BF3298,
// RunToLocation@8 plus an unnamed float@C (both 10.0f via the retail literal
// at 0xBC2428) plus RequiresSpecificTrigger@10 plus DieOnMap@18 (both false)
// plus RunOffMapWaypointName@14 (empty via the rowed AsciiString copy-set at
// 0x366F0). Field identity is the rowed buildFieldParse proc (table 0xC42F70:
// RunToLocation/RequiresSpecificTrigger/RunOffMapWaypointName/DieOnMap) plus
// the rowed poolkey 0x4621B2 plus factory 0x254F24 (news 0x1C, sole caller).
// The empty UpdateModuleData base (inline-empty ctor plus declared-only dtor)
// is load-bearing for the EH state machine (SpawnUnit precedent). /arch:SSE
// for movss float stores; /EHsc for the __EH_prolog frame.

class AsciiString
{
public:
	AsciiString() : m_data(0)
	{
	}
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData()
	{
	}
	~UpdateModuleData();
};

extern const AsciiString emptyRunOffMapWaypointName;

class RunOffMapBehaviorModuleData : public UpdateModuleData
{
public:
	RunOffMapBehaviorModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	float m_runToLocation;
	float m_unnamed0C;
	bool m_requiresSpecificTrigger;
	AsciiString m_runOffMapWaypointName;
	bool m_dieOnMap;
};

// ??0RunOffMapBehaviorModuleData@@QAE@XZ @0x254ECE
RunOffMapBehaviorModuleData::RunOffMapBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BF3298))
{
	m_dieOnMap = false;
	m_runToLocation = 10.0f;
	m_unnamed0C = 10.0f;
	m_requiresSpecificTrigger = false;
	m_runOffMapWaypointName = emptyRunOffMapWaypointName;
}
