// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?ReleaseResources@BaseHeightMapRenderObjClass@@UAEXXZ, retail 0x00066808
// (292B): BaseHeightMapRenderObjClass::ReleaseResources. Body: Open-BFME-1
// GameEngineDevice/.../BaseHeightMapReleaseResources_Bfme.cpp (retail
// 0x0006C5FC0-era 300B there, donor revision 575ba2b04), re-laid onto BFME 2's
// member offsets and rowed callees: each guarded member release below calls
// the ledger-named body at its address (retail calls the bodies directly,
// the donor reaches them through ILT thunks). The receiver is the render
// object subobject at +0xC4 of the complete object, whose vtable slot 133
// (+0x214) rebuilds the height map reference and whose slot 129 (+0x204) is
// tail-called last. Fields are named by offset: only the accesses retail
// makes are modelled.

class WorldHeightMap
{
public:
	virtual void anchor();

	int m_refCount;
	int m_xExtent;											// +0x08
	int m_yExtent;											// +0x0C
};

class Rva0074011F
{
public:
	void rva0074011F();
};

class BaseHeightMapRenderObjClass;

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};
class Vector3;
class W3DBibBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void addBibDrawable(Vector3 corners[4], DrawableID id, bool highlight);
	void removeHighlighting();
	void clearAllBibs();
	void removeBib(ObjectID id);
	void removeBibDrawable(DrawableID id);
	void addBib(Vector3 corners[4], ObjectID id, bool highlight);
protected:
	void freeBibBuffers();
	void allocateBibBuffers();
public:
	W3DBibBuffer();
	~W3DBibBuffer();
	char data[68048]; // +0x00
};

class W3DRoadBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void loadRoads();
protected:
	void freeRoadBuffers();
	void allocateRoadBuffers();
public:
	W3DRoadBuffer();
	~W3DRoadBuffer();
	void clearAllRoads();
	void setMap(WorldHeightMap*);
	char data[80]; // +0x00
};

#include "../../../Include/W3DDevice/GameClient/W3DFloorBuffer.h"

// 0x000B3FD0 is the one-byte empty body the toolchain folds many empties into.
#include "../../../../GameEngine/Include/Common/Rva000B3FD0.h"

#include "../../../Include/W3DDevice/GameClient/Rva00083E5C.h"

class Rva000731AE
{
public:
	void rva000731AE();
};

class Rva00073C7A
{
public:
	void rva00073C7A();
};

#include "../../../Include/W3DDevice/GameClient/Rva000728E2.h"

class W3DSnowManager
{
public:
	void ReleaseResources();
	bool ReAcquireResources();
};

class TerrainTracksRenderObjClassSystem
{
public:
	void ReAcquireResources();
};

#include "../../../Include/W3DDevice/GameClient/W3DShadowManager.h"

#include "../../../Include/W3DDevice/GameClient/W3DShroudClass.h"

class W3DTaint
{
public:
	bool ReAcquireResources();
	~W3DTaint();
	W3DTaint();
	void init(WorldHeightMap*,float,float);
	char data[80]; // +0x00
};

class RenderInfoClass;
#include "../../../Include/W3DDevice/GameClient/W3DBuffBuffer.h"

#include "../../../Include/W3DDevice/GameClient/W3DBridgeBufferClass.h"

// 0x000ABA2F ignores ECX: a free body.
void rva000ABA2F();

void Rva0009A3DECleanup();
void Rva000A98BACleanup();

// Retail enters 0x0009A3DE with the manager in ECX (the body ignores it), so
// the call is a member call on the manager spelled through the free body.
class Rva0009A3DECall
{
public:
	void invoke()
	{
		union { void (*entry)(); void (Rva0009A3DECall::*method)(); } call;
		call.entry = Rva0009A3DECleanup;
		(this->*call.method)();
	}
};

class TerrainTracksRenderObjClassSystem;
class W3DShadowManager;
class SnowManager;
class DisplayStringManager;
class BfmeB991;
class Display;

extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
extern W3DShadowManager *TheW3DShadowManager;
extern BfmeB991 *g_bfmeB991;
extern SnowManager *TheSnowManager;
extern DisplayStringManager *TheDisplayStringManager;
extern Display *TheDisplay;

#define SLOT_ROW(n) virtual void slot##n##0(); virtual void slot##n##1(); virtual void slot##n##2(); virtual void slot##n##3(); virtual void slot##n##4(); \
	virtual void slot##n##5(); virtual void slot##n##6(); virtual void slot##n##7(); virtual void slot##n##8(); virtual void slot##n##9();

class BfmeB991
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void releaseResources();
	virtual void reacquireResources();
};

class DisplayStringManager
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8();
	virtual void releaseResources();
};

#include "../../../../GameEngine/Include/GameClient/Display.h"

#include "../../../../GameEngine/Include/GameClient/View.h"

extern View *TheTacticalView;

// The complete object's table as ReAcquireResources reaches it: slot 130
// first, slot 131 rebuilds the height data from the map, slot 137 (true)
// once a map is present.
class CompleteObjectReacquire
{
public:
	SLOT_ROW(0) SLOT_ROW(1) SLOT_ROW(2) SLOT_ROW(3) SLOT_ROW(4) SLOT_ROW(5) SLOT_ROW(6) SLOT_ROW(7) SLOT_ROW(8) SLOT_ROW(9)
	SLOT_ROW(10) SLOT_ROW(11) SLOT_ROW(12)
	virtual void slot130();
	virtual void initHeightData131(int x, int y, WorldHeightMap *map, void *unused);
	virtual void slot132(); virtual void slot133(); virtual void slot134(); virtual void slot135();
	virtual void slot136();
	virtual void slot137(bool on);
};

class CompleteObject
{
public:
	SLOT_ROW(0) SLOT_ROW(1) SLOT_ROW(2) SLOT_ROW(3) SLOT_ROW(4) SLOT_ROW(5) SLOT_ROW(6) SLOT_ROW(7) SLOT_ROW(8) SLOT_ROW(9)
	SLOT_ROW(10) SLOT_ROW(11)
	virtual void slot120(); virtual void slot121(); virtual void slot122(); virtual void slot123();
	virtual void slot124(); virtual void slot125(); virtual void slot126(); virtual void slot127();
	virtual void slot128();
	virtual void tail129();
	virtual void slot130(); virtual void slot131(); virtual void slot132();
	virtual void rebuildMap133();
};

class BaseHeightMapRenderObjClass
{
public:
	virtual void ReleaseResources();
	virtual void ReAcquireResources();

private:
	unsigned char m_pad04[0x36FC - 4];
	WorldHeightMap *m_map;
	unsigned char m_pad3700[0x3798 - 0x3700];
	W3DBibBuffer *m_bibBuffer;
	W3DFloorBuffer *m_floorBuffer;
	Rva000B3FD0 *m_cleanupBody;
	unsigned char m_pad37A4[4];
	W3DRoadBuffer *m_roadBuffer;
	Rva0074011F *m_release37AC;
	Rva0074011F *m_release37B0;
	void *m_shroud;
	void *m_shroudSecondary;
	bool m_37BC;											// +0x37BC
};

void BaseHeightMapRenderObjClass::ReleaseResources()
{
	if (m_release37B0)
		m_release37B0->rva0074011F();
	if (m_bibBuffer)
		m_bibBuffer->freeBibBuffers();
	if (m_release37AC)
		m_release37AC->rva0074011F();
	if (m_floorBuffer)
		m_floorBuffer->rva000E473F();
	if (m_cleanupBody)
		m_cleanupBody->rva000B3FD0();

	if (m_map)
		++m_map->m_refCount;
	WorldHeightMap *pMap = m_map;
	CompleteObject *complete = (CompleteObject *)((unsigned char *)this - 0xC4);
	complete->rebuildMap133();
	m_map = pMap;

	if (TheTerrainTracksRenderObjClassSystem)
		((Rva00083E5C *)TheTerrainTracksRenderObjClassSystem)->rva00083E5C();
	if (TheW3DShadowManager)
		((Rva0009A3DECall *)TheW3DShadowManager)->invoke();
	if (m_shroud) {
		((Rva000731AE *)m_shroud)->rva000731AE();
		((Rva000728E2 *)m_shroud)->rva000728E2();
	}
	if (m_shroudSecondary) {
		((Rva00073C7A *)m_shroudSecondary)->rva00073C7A();
		((Rva000728E2 *)m_shroudSecondary)->rva000728E2();
	}
	if (g_bfmeB991)
		g_bfmeB991->releaseResources();
	if (TheSnowManager)
		((W3DSnowManager *)TheSnowManager)->ReleaseResources();
	if (TheDisplayStringManager)
		TheDisplayStringManager->releaseResources();
	Rva000A98BACleanup();
	if (m_roadBuffer)
		m_roadBuffer->freeRoadBuffers();
	if (TheDisplay)
		TheDisplay->slot31();
	complete->tail129();
}

// ?ReAcquireResources@BaseHeightMapRenderObjClass@@UAEXXZ, retail 0x00066962
// (312B): Zero Hour's BaseHeightMapRenderObjClass::ReAcquireResources order
// (terrain tracks, shadows, shroud, height data, bib/bridge buffers, snow,
// roads, two tactical-view redraws) with BFME 2's additions read from retail:
// a complete-object slot 130 first, the taint, buff and floor buffers, the
// 0x00DE612C manager's slot 4, the free 0x000ABA2F and a TheDisplay slot-32
// tail call; the height data rebuild is skipped while +0x37BC is set.
void BaseHeightMapRenderObjClass::ReAcquireResources()
{
	CompleteObjectReacquire *complete = (CompleteObjectReacquire *)((unsigned char *)this - 0xC4);
	complete->slot130();
	if (TheTerrainTracksRenderObjClassSystem)
		TheTerrainTracksRenderObjClassSystem->ReAcquireResources();
	if (TheW3DShadowManager)
		TheW3DShadowManager->ReAcquireResources();
	if (m_shroud)
		((W3DShroud *)m_shroud)->ReAcquireResources();
	if (m_shroudSecondary)
		((W3DTaint *)m_shroudSecondary)->ReAcquireResources();
	if (m_map && !m_37BC)
		complete->initHeightData131(m_map->m_xExtent, m_map->m_yExtent, m_map, 0);
	if (m_release37B0)
		((W3DBuffBuffer *)m_release37B0)->allocateBuffBuffers();
	if (m_bibBuffer)
		m_bibBuffer->allocateBibBuffers();
	if (m_floorBuffer)
		m_floorBuffer->allocateFloorBuffers();
	if (m_release37AC)
		((W3DBridgeBuffer *)m_release37AC)->allocateBridgeBuffers();
	if (g_bfmeB991)
		g_bfmeB991->reacquireResources();
	if (TheSnowManager)
		((W3DSnowManager *)TheSnowManager)->ReAcquireResources();
	if (m_roadBuffer)
	{
		m_roadBuffer->allocateRoadBuffers();
		m_roadBuffer->loadRoads();
	}
	if (m_map)
		complete->slot137(true);
	if (TheTacticalView)
	{
		TheTacticalView->forceRedraw();
		TheTacticalView->forceRedraw();
	}
	rva000ABA2F();
	if (TheDisplay)
		TheDisplay->slot32();
}
