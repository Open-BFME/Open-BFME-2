// ?rva002D8395@Radar@@QAEXPBUCoord3D@@HMABUVec16@@1@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD
// ?rva002D8395@Radar@@QAEXPBUCoord3D@@HMABUVec16@@1@Z @0x002D8395 353B: Radar add-event with worldToRadar and client frame scaling. Evidence: caller pair 0x002D893B 0x002D88A4; callees worldToRadar 0x002D77C9 clearRef 0x002D7CC6 ftol2; member offsets match Radar_reset event layout stride 0x50 trailer +0x142C.
#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	int x;
	int y;
};

struct Vec16
{
	int v[4];
};

class ClientFrameSubsystem
{
public:
	virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
	virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
	virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
	virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
	virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
	virtual int v20(); virtual int v21(); virtual int v22(); virtual int v23();
	virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
	virtual int v28(); virtual int v29(); virtual int v30();
	virtual int getFrame();
};

extern ClientFrameSubsystem *TheGameClient;
extern float g_00BC26EC;
extern int g_00DBA4E8;
extern float g_00DBCEB8;

class RadarEventRef
{
public:
	virtual void m_spare0();
	virtual void m_deleter();
	void release();
private:
	int m_refCount;
};

class RadarEventRefSlot
{
public:
	void clearRef();
private:
	RadarEventRef *m_ref;
};

struct RadarEventBody
{
	unsigned char m_state;
	unsigned char m_pad00[3];
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_keep1C;
	int m_20;
	int m_24;
	int m_28;
	int m_keep2C;
	float m_30;
	float m_34;
	float m_38;
	int m_3C;
	int m_40;
	unsigned char m_44;
	unsigned char m_pad44[3];
	RadarEventRefSlot m_ref;
};

struct RadarEvent
{
	int m_tag;
	RadarEventBody m_body;
};

class Radar
{
public:
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
	void rva002D8395(const Coord3D *pos, int tag, float scale, const Vec16 &a, const Vec16 &b);
private:
	char m_pad[0x2C];
public:
	RadarEvent m_events[64];
private:
	int m_eventCount;
};

// ?rva002D8395@Radar@@QAEXPBUCoord3D@@HMABUVec16@@1@Z present-unmatched
void Radar::rva002D8395(const Coord3D *pos, int tag, float scale, const Vec16 &a, const Vec16 &b)
{
	ICoord2D tmp;
	if (pos == 0)
		return;
	if (&a == 0)
		return;
	if (&b == 0)
		return;
	worldToRadar(pos, &tmp);
	m_events[m_eventCount].m_tag = tag;
	m_events[m_eventCount].m_body.m_state = 1;
	m_events[m_eventCount].m_body.m_04 = TheGameClient->getFrame();
	m_events[m_eventCount].m_body.m_08 = (int)((double)(unsigned)TheGameClient->getFrame() + (double)g_00DBA4E8 * scale);
	m_events[m_eventCount].m_body.m_0C = (int)((double)(unsigned)m_events[m_eventCount].m_body.m_08 - (double)g_00DBA4E8 * g_00DBCEB8);
	*(Vec16 *)&m_events[m_eventCount].m_body.m_10 = a;
	*(Vec16 *)&m_events[m_eventCount].m_body.m_20 = b;
	*(Coord3D *)&m_events[m_eventCount].m_body.m_30 = *pos;
	m_events[m_eventCount].m_body.m_3C = tmp.x;
	m_events[m_eventCount].m_body.m_40 = tmp.y;
	m_events[m_eventCount].m_body.m_44 = 0;
	m_events[m_eventCount].m_body.m_ref.clearRef();
	if (++m_eventCount >= 0x40)
		m_eventCount = 0;
}
