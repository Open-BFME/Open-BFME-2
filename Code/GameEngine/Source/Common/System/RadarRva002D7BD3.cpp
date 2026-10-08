// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc /Ireference/shims/moduledata
//
// ?rva002D7BD3@Radar@@QAEXXZ @0x002D7BD3 42B Radar invalidate draw cache.
// Evidence: stores 0xFFFF0001 at +0x144C and +0x1450 then 0xFFFF at +0x1454
// and +0x1458 plus 0 at +0x145C; callers 0x002D3297 and 0x002D8867;
// prev newMap and next clearRef share Radar class; no calls or floats.
//
// ??0Radar@@QAE@XZ, retail 0x002D87B9, 207 bytes. Radar constructor.
// Evidence: stores Snapshot vtable 0x7BB554 then Radar vptrs 0xC0363C/+0
// and 0xC03604/+4 matching RadarDtor; second-base baseConstruct 0x001B4E63
// on +4; array m_events[64] at +0x2C via ??_L size 0x50 count 0x40 ctor
// 0x2D7CD9 dtor 0x2D7CE0; zeroes +0x1430/+0x14/+0x18/+0x10/+0x11 floats
// +0x1C/+0x20/+0x24/+0x28 extent +0x1434..+0x1448; calls rowed
// ?rva002D7BD3@Radar@@QAEXXZ and ?clearAllEvents@Radar@@IAEXXZ; trailer
// +0x1460=0. Layout from RadarDtor/Radar_reset/Radar_deleteListResources.
// Same-TU rva body lets MSVC keep ECX across the first call (shape lever).

#include "Common/Snapshot.h"

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) RadarSecondBase
{
public:
	__forceinline RadarSecondBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~RadarSecondBase();
	virtual void unused();
};

class RadarEventRef
{
public:
	void release();
};

class RadarEvent
{
public:
	RadarEvent();
	~RadarEvent();
private:
	char m_pad[0x4C];
	RadarEventRef *m_ref; // +0x4C
};

class Radar : public Snapshot, public RadarSecondBase
{
public:
	Radar();
	virtual ~Radar();
	__declspec(noinline) void rva002D7BD3();
protected:
	void clearAllEvents();
private:
	char m_pad08[0x10 - 0x08];
	bool m_hidden; // +0x10
	bool m_forceOn; // +0x11
	char m_pad12[0x14 - 0x12];
	void *m_objectList; // +0x14
	void *m_localList; // +0x18
	float m_avgTerrain; // +0x1C
	float m_avgWater; // +0x20
	float m_xSample; // +0x24
	float m_ySample; // +0x28
public:
	RadarEvent m_events[64]; // +0x2C
private:
	int m_eventTrailer; // +0x142C
public:
	void *m_radarWindow; // +0x1430
	float m_extent[6]; // +0x1434..+0x144C
public:
	int m_144C; // +0x144C
	int m_1450; // +0x1450
	int m_1454; // +0x1454
	int m_1458; // +0x1458
	unsigned char m_145C; // +0x145C
private:
	char m_pad145D[0x1460 - 0x145D];
	int m_1460; // +0x1460
};

RadarEvent::RadarEvent()
{
	m_ref = 0;
}

void Radar::rva002D7BD3()
{
	m_144C = 0xFFFF0001;
	m_1450 = 0xFFFF0001;
	m_1454 = 0xFFFF;
	m_1458 = 0xFFFF;
	m_145C = 0;
}

Radar::Radar()
{
	m_radarWindow = 0;
	m_objectList = 0;
	m_localList = 0;
	m_hidden = false;
	m_forceOn = false;
	m_avgTerrain = 0.0f;
	m_avgWater = 0.0f;
	m_xSample = 0.0f;
	m_ySample = 0.0f;
	m_extent[0] = 0.0f;
	m_extent[1] = 0.0f;
	m_extent[2] = 0.0f;
	m_extent[3] = 0.0f;
	m_extent[4] = 0.0f;
	m_extent[5] = 0.0f;
	rva002D7BD3();
	m_1460 = 0;
	clearAllEvents();
}
