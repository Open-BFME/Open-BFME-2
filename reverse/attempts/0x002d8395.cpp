// ?internalCreateEvent@Radar@@IAEXPBUCoord3D@@W4RadarEventType@@MPBURGBAColorInt@@2@Z
// partial score=0.98 date=2026-10-09
// Zero Hour Radar.cpp internalCreateEvent at BF1 committed2f243e26d.
// Existing matched createEvent88A4 and existing internalCreateEvent pin prove name/ABI.
// Target stride50 events2C nextFree142C, frame slot7C, clearRef2D7CC6.
// Whole353B extent; typed donor structure fixes SIB coordinate stores.
// Only tmp.x load is delayed until after worldLoc copy instead of before.
// cl: /I. /O1 /G7 /DNDEBUG /MD
// ?internalCreateEvent@Radar@@IAEXPBUCoord3D@@W4RadarEventType@@MPBURGBAColorInt@@2@Z @0x002D8395 353B: Radar add-event with worldToRadar and client frame scaling. Evidence: caller pair 0x002D893B 0x002D88A4; callees worldToRadar 0x002D77C9 clearRef 0x002D7CC6 ftol2; member offsets match Radar_reset event layout stride 0x50 trailer +0x142C.
#include <math.h>

#include "Code/Libraries/Include/Lib/Coord3D.h"

struct ICoord2D
{
	int x;
	int y;
};

struct RGBAColorInt { unsigned int v[4]; };
enum RadarEventType { RADAR_EVENT_INVALID = 11 };

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

struct RadarEvent {
 RadarEventType type; bool active;
 unsigned int createFrame, dieFrame, fadeFrame;
 RGBAColorInt color1,color2; Coord3D worldLoc; ICoord2D radarLoc;
 bool soundPlayed; RadarEventRefSlot ref;
};

class Radar
{
public:
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
	protected:
 void internalCreateEvent(const Coord3D *pos, RadarEventType tag, float scale, const RGBAColorInt *a, const RGBAColorInt *b);
private:
	char m_pad[0x2C];
public:
	RadarEvent m_events[64];
private:
	int m_eventCount;
};

void Radar::internalCreateEvent(const Coord3D *pos, RadarEventType tag, float scale, const RGBAColorInt *a, const RGBAColorInt *b)
{
 ICoord2D tmp; if(!pos||!a||!b)return; worldToRadar(pos,&tmp);
 m_events[m_eventCount].type=tag;
 m_events[m_eventCount].active=true;
 m_events[m_eventCount].createFrame=TheGameClient->getFrame();
 m_events[m_eventCount].dieFrame=(unsigned int)((float)(unsigned)TheGameClient->getFrame()+(float)g_00DBA4E8*scale);
 m_events[m_eventCount].fadeFrame=(unsigned int)((float)m_events[m_eventCount].dieFrame-(float)g_00DBA4E8*g_00DBCEB8);
 m_events[m_eventCount].color1=*a;
 m_events[m_eventCount].color2=*b;
 m_events[m_eventCount].worldLoc=*pos;
 m_events[m_eventCount].radarLoc=tmp;
 m_events[m_eventCount].soundPlayed=false;
 m_events[m_eventCount].ref.clearRef();
 if(++m_eventCount>=64)m_eventCount=0;
}
