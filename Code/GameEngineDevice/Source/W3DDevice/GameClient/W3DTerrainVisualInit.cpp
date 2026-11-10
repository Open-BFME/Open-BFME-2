// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ?init@W3DTerrainVisual@@UAEXXZ, retail 0x00091AEA..0x00091CA7 (445 bytes,
// EH): BFME2's W3DTerrainVisual::init. Under the DX8 device lock it runs the
// base init (the shared bare return 0x000B3FD0), creates the height-map
// render object (0x393C bytes, constructor 0x000E3BFE(false); slot 121 with
// (2, 0)) and publishes it as TheTerrainRenderObject, the terrain tracks
// system (0x28 bytes, constructor 0x00084CA5, init 0x00084D01 with the 3D
// scene), TheW3DShadowManager (constructor 0x0009A710, then 0x0009A254), the
// water render object (0x264 bytes, constructor 0x00082329; 0x0007FC38 with
// TheWritableGlobalData's water height, size and type, then placed at its
// water position through render-object slot 22) and the smudge manager
// (constructor 0x000A60F0, slot 1). Unless 0x00DFE7A8 is set or the water
// type is 1 the water object joins the scene (slot 2). Views carry only what
// this body touches; global spellings are the data ledger's.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

class SceneClass;
class RTS3DScene;

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class Rva00091AEARenderObj
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21)
#undef V
	virtual void Set_Position(const Vector3 &position);	// slot 22
};

class Rva00091AEAScene
{
public:
	virtual void v0();
	virtual void v1();
	virtual void Add_Render_Object(Rva00091AEARenderObj *obj);	// slot 2
};

#include "../../../../GameEngine/Include/Common/Rva000B3FD0.h"

// The height-map render object.
class Rva000E3B41
{
public:
	Rva000E3B41(bool flag);
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109)
	V(110) V(111) V(112) V(113) V(114) V(115) V(116) V(117) V(118) V(119)
	V(120)
	virtual void slot121(int a, int b);
	V(122) V(123) V(124) V(125) V(126) V(127) V(128) V(129)
	V(130) V(131) V(132) V(133) V(134) V(135) V(136) V(137)
#undef V
	virtual void reset();				// slot 138
private:
	unsigned char m_pad04[0x393C - 4];
};

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// The terrain tracks system.
class Rva00084CA5
{
public:
	Rva00084CA5();
private:
	unsigned char m_data[0x28];
};

class Rva00084C05System
{
public:
	void init(SceneClass *scene);
};

class TerrainTracksRenderObjClassSystem;
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;

class W3DShadowManager
{
public:
	W3DShadowManager();
	bool rva0009A254();
	void rva0009A2CD();
private:
	unsigned char m_data[0x18];
};

extern W3DShadowManager *TheW3DShadowManager;

enum WaterType { WATER_TYPE_DEFAULT };

// The water render object; its render-object part sits at +4.
class WaterRenderObjClass
{
public:
	WaterRenderObjClass();
	int m_00;
	Rva00091AEARenderObj m_renderObj;		// +0x04
private:
	unsigned char m_pad08[0x264 - 8];
};

class Rva0007FC38
{
public:
	int rva0007FC38(float waterHeight, float waterSizeX, float waterSizeY, SceneClass *scene, WaterType type);
};

extern void *W3DGCData00DE2000;

class W3DSmudgeManager
{
public:
	W3DSmudgeManager();
	virtual void v0();
	virtual void init();				// slot 1
	virtual void reset();				// slot 2
private:
	unsigned char m_pad04[0x44 - 4];
};

class BfmeB991;
// The smudge manager slot three units reach (BaseHeightMapReleaseResources,
// W3DTerrainVisualDestructor, BfmeConv991) and this one assigns. RVA 0x009E612C
// is past .data's raw end (file offset 0x009DCC08), so retail's image holds it
// zero until the rowed body below stores the new W3DSmudgeManager into it - a
// tentative definition, for the same reason as g_Va00DB6218: an explicit "= 0"
// would let MSVC learn the value and fold the guards in BfmeConv991 and
// BaseHeightMapReleaseResources into literals. Only a pointer is declared here,
// so no complete class or destructor is needed.
// Symbol ?g_bfmeB991@@3PAVBfmeB991@@A, defined below.
extern BfmeB991 *g_bfmeB991;
BfmeB991 *g_bfmeB991;

// The timing-log enable byte is owned by Rva003B9EC4.cpp at VA 0x00DFE7A8.
extern unsigned char g_00DFE7A8;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva00091AEAGlobalView
{
	unsigned char m_pad00[0x6C];
	float m_waterPositionX;				// +0x6C
	float m_waterPositionY;				// +0x70
	float m_waterPositionZ;				// +0x74
	float m_waterExtentX;				// +0x78
	float m_waterExtentY;				// +0x7C
	WaterType m_waterType;				// +0x80
};

// TerrainVisual::reset clears the base's +0x0C filename string; its body
// is the shared 8-byte string-release forwarder 0x0004F82B.
class Rva0004F82B
{
public:
	void rva0004F82B();
};

class Rva00083CE9Host
{
public:
	void Reset();
};

class Rva00082B08
{
public:
	void rva00082B08();
};

// Logic height map, at +0x1C in the complete terrain visual and +0x18 from
// the secondary SubsystemInterface receiver (count at +4, slot 0 deletes it).
class Rva00091CA7Counted
{
public:
	virtual void deleteThis();
	void releaseRef() { if (--m_refs == 0) deleteThis(); }
	int m_refs;					// +0x04
};

#include "../../../Include/W3DDevice/GameClient/W3DTerrainVisualClass.h"

void W3DTerrainVisual::init()
{
	BFMEDX8DeviceLock lock;
	// Preserve the secondary SubsystemInterface receiver expected by retail.
	((Rva000B3FD0 *)((char *)this + 4))->rva000B3FD0();

	m_terrainRenderObject = (BaseHeightMapRenderObjClass *)new Rva000E3B41(false);
	((Rva000E3B41 *)m_terrainRenderObject)->slot121(2, 0);
	TheTerrainRenderObject = m_terrainRenderObject;

	Rva00084CA5 *tracks = new Rva00084CA5;
	TheTerrainTracksRenderObjClassSystem = (TerrainTracksRenderObjClassSystem *)tracks;
	((Rva00084C05System *)tracks)->init((SceneClass *)W3DDisplay::m_3DScene);

	TheW3DShadowManager = new W3DShadowManager;
	TheW3DShadowManager->rva0009A254();

	m_waterRenderObject = new WaterRenderObjClass;
	W3DGCData00DE2000 = m_waterRenderObject;
	Rva00091AEAGlobalView *data = (Rva00091AEAGlobalView *)TheWritableGlobalData;
	((Rva0007FC38 *)m_waterRenderObject)->rva0007FC38(data->m_waterPositionZ, data->m_waterExtentX, data->m_waterExtentY,
		(SceneClass *)W3DDisplay::m_3DScene, data->m_waterType);
	data = (Rva00091AEAGlobalView *)TheWritableGlobalData;
	Vector3 position(data->m_waterPositionX, data->m_waterPositionY, data->m_waterPositionZ);
	m_waterRenderObject->m_renderObj.Set_Position(position);

	W3DSmudgeManager *smudge = new W3DSmudgeManager;
	g_bfmeB991 = (BfmeB991 *)smudge;
	smudge->init();

	if (!g_00DFE7A8 && ((Rva00091AEAGlobalView *)TheWritableGlobalData)->m_waterType != 1 && m_waterRenderObject)
		((Rva00091AEAScene *)W3DDisplay::m_3DScene)->Add_Render_Object(&m_waterRenderObject->m_renderObj);
}

// ?reset@W3DTerrainVisual@@UAEXXZ, retail 0x00091CA7..0x00091D0D (102 bytes),
// slot 9 of the W3DTerrainVisual vtable 0x007C8068 (slot 1 is init above).
// Zero Hour's W3DTerrainVisual::reset without the skybox-texture loop: the
// base TerrainVisual::reset, the height-map render object's reset (slot 138),
// TheW3DShadowManager's Reset (0x0009A2CD), the smudge manager's slot 2, the
// terrain tracks system's Reset (rowed 0x00084002) and the water render
// object's reset (rowed 0x00082B08); BFME 2 then releases the counted object at
// +0x18 and clears it. Retail passes ECX=this to 0x0004F82B and 0x0009A2CD,
// whose rows are other spellings, so they are reached through address-named
// member pins.
void W3DTerrainVisual::reset()
{
	((Rva0004F82B *)((char *)this + 4))->rva0004F82B();
	if (m_terrainRenderObject)
		((Rva000E3B41 *)m_terrainRenderObject)->reset();
	if (TheW3DShadowManager)
		TheW3DShadowManager->rva0009A2CD();
	if (g_bfmeB991)
		((W3DSmudgeManager *)g_bfmeB991)->reset();
	if (TheTerrainTracksRenderObjClassSystem)
		((Rva00083CE9Host *)TheTerrainTracksRenderObjClassSystem)->Reset();
	if (m_waterRenderObject)
		((Rva00082B08 *)m_waterRenderObject)->rva00082B08();
	if (m_logicHeightMap)
	{
		((Rva00091CA7Counted *)m_logicHeightMap)->releaseRef();
		m_logicHeightMap = 0;
	}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x0004F82B -> ??1GeometryRecord@@QAE@XZ
#pragma comment(linker, "/alternatename:?rva0004F82B@Rva0004F82B@@QAEXXZ=??1GeometryRecord@@QAE@XZ")
//   0x0009A2CD -> ?Rva0009A2CDRun@@YAXXZ
#pragma comment(linker, "/alternatename:?rva0009A2CD@W3DShadowManager@@QAEXXZ=?Rva0009A2CDRun@@YAXXZ")
