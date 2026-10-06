// cl: /DNDEBUG /MD /EHsc
//
// ??1Radar@@UAE@XZ, retail 0x002D7CED, 98 bytes. Radar destructor (MI:
// primary Snapshot, second GameEngineDeletingBase). Evidence: two vptr
// stores (0xC0363C at +0, 0xC03604 at +4) per Radar_reset.cpp comment on
// the ctor near 0x002D7CF0; calls rowed ?deleteListResources@Radar@@IAEXXZ;
// destroys m_events[64] at +0x2C via ??_M (size 0x50 count 0x40, element
// dtor at 0x002D7CE0); calls rowed ??1GameEngineDeletingBase@@UAE@XZ
// on +4 slice; final inline Snapshot store to g_00BBB554. Neighbour TUs
// Radar_reset.cpp / Radar_deleteListResources.cpp give +0x14/+0x18 lists,
// +0xD flag, +0x2C events, +0x142C trailer layout.

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

extern const void *const g_00BBB554[];
inline Snapshot::~Snapshot() { *(const void **)this = g_00BBB554; }

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class RadarEventRef
{
public:
	void release();
};

class RadarEvent
{
public:
	~RadarEvent();
private:
	char m_pad[0x4C];
	RadarEventRef *m_ref; // +0x4C
};

class Radar : public Snapshot, public GameEngineDeletingBase
{
protected:
	void deleteListResources();
public:
	virtual ~Radar();
private:
	char m_pad08[0x2C - 0x8];
public:
	RadarEvent m_events[64]; // +0x2C
private:
	int m_eventTrailer; // +0x142C
};

RadarEvent::~RadarEvent()
{
	if (m_ref)
		m_ref->release();
}

Radar::~Radar()
{
	deleteListResources();
}
