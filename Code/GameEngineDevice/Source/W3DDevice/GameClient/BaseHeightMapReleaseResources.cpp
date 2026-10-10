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
};

class Rva0074011F
{
public:
	void rva0074011F();
};

class BaseHeightMapRenderObjClass;

class W3DBibBuffer
{
	friend class BaseHeightMapRenderObjClass;
protected:
	void freeBibBuffers();
};

class W3DRoadBuffer
{
	friend class BaseHeightMapRenderObjClass;
protected:
	void freeRoadBuffers();
};

class W3DFloorBuffer
{
public:
	void rva000E473F();
};

// 0x000B3FD0 is the one-byte empty body the toolchain folds many empties into.
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva00083E5C
{
public:
	void rva00083E5C();
};

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

class Rva000728E2
{
public:
	void rva000728E2();
};

class W3DSnowManager
{
public:
	void ReleaseResources();
};

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
};

class DisplayStringManager
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8();
	virtual void releaseResources();
};

class Display
{
public:
	SLOT_ROW(0) SLOT_ROW(1) SLOT_ROW(2)
	virtual void slot30();
	virtual void releaseResources();
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
		TheDisplay->releaseResources();
	complete->tail129();
}
