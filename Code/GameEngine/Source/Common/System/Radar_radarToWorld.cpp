// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD
// Radar conversions and event initialization. Native2D8395..2D84F6 and
// named createEvent callers establish the new353B member and50-byte records.
// The visible inline+noinline worldToRadar body keeps its own99B exact and
// exposes output-temp behavior to the caller; the old133B conversion stays exact.
// Frame-rate access reuses the existing30-valued global owner. The writable
// fade multiplier below has target-observed initial0.5 and current usage;
// its descriptive name is not an original identifier claim.

struct ICoord2D
{
	int x;
	int y;
};

#include "Code/Libraries/Include/Lib/Coord3D.h"

#define NULL 0

class BfmeTerrainHeightView
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual float getGroundHeight(float x, float y, Coord3D *normal = NULL);
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

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

class GameClient;extern GameClient *TheGameClient;

extern int g_009BA4E8;
float BfmeRadarEventFadeFraction=0.5f;

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
	bool radarToWorld(const ICoord2D *radar, Coord3D *world);
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);

protected:
 void internalCreateEvent(const Coord3D*,RadarEventType,float,const RGBAColorInt*,const RGBAColorInt*);
private:
	unsigned char m_pad[0x24];
	float m_xSample; // +0x24 (retail-measured)
	float m_ySample; // +0x28 (retail-measured)
 RadarEvent m_events[64];int m_eventCount;
};

// ?radarToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z
bool Radar::radarToWorld(const ICoord2D *radar, Coord3D *world)
{
	if (radar == NULL || world == NULL)
		return false;

	int x = radar->x;
	int y = radar->y;
	if (x < 0)
		x = 0;
	if (x >= 128)
		x = 128 - 1;
	if (y < 0)
		y = 0;
	if (y >= 128)
		y = 128 - 1;

	world->x = x * m_xSample;
	world->y = y * m_ySample;

	BfmeTerrainHeightView *terrain = (BfmeTerrainHeightView *)TheTerrainLogic;
	world->z = terrain->getGroundHeight(world->x, world->y);

	return true;
}

inline __declspec(noinline) bool Radar::worldToRadar(const Coord3D *world, ICoord2D *radar)
{
	if (world == NULL || radar == NULL)
		return false;

	radar->x = (int)(world->x / m_xSample);
	radar->y = (int)(world->y / m_ySample);

	if (radar->x < 0)
		radar->x = 0;
	if (radar->x >= 128)
		radar->x = 128 - 1;
	if (radar->y < 0)
		radar->y = 0;
	if (radar->y >= 128)
		radar->y = 128 - 1;

	return true;
}
// ?TheTerrainLogic@@3PAVBfmeTerrainHeightView@@A: the global at VA 0xdfec50 is ?TheTerrainLogic@@3PAVTerrainLogic@@A.

void Radar::internalCreateEvent(const Coord3D *pos, RadarEventType tag, float scale, const RGBAColorInt *a, const RGBAColorInt *b)
{
 ICoord2D tmp; if(!pos||!a||!b)return; worldToRadar(pos,&tmp);
 m_events[m_eventCount].type=tag;
 m_events[m_eventCount].active=true;
 m_events[m_eventCount].createFrame=reinterpret_cast<ClientFrameSubsystem*>(TheGameClient)->getFrame();
 m_events[m_eventCount].dieFrame=(unsigned int)((float)(unsigned)reinterpret_cast<ClientFrameSubsystem*>(TheGameClient)->getFrame()+(float)g_009BA4E8*scale);
 m_events[m_eventCount].fadeFrame=(unsigned int)((float)m_events[m_eventCount].dieFrame-(float)g_009BA4E8*BfmeRadarEventFadeFraction);
 m_events[m_eventCount].color1=*a;
 m_events[m_eventCount].color2=*b;
 m_events[m_eventCount].worldLoc=*pos;
 m_events[m_eventCount].radarLoc=tmp;
 m_events[m_eventCount].soundPlayed=false;
 m_events[m_eventCount].ref.clearRef();
 if(++m_eventCount>=64)m_eventCount=0;
}

