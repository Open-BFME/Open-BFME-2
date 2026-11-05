// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// W3DDisplay::init, retail 0x00046A50 (1594B, slot of W3DDisplay's vtable,
// EH frame). WorldBuilder's debug build names it; Zero Hour's
// W3DDisplay::init and BFME 1's matched W3DDisplayInit_Bfme.cpp
// (0x006ED5B0) are the donors for the order: file system, WWMath, the three
// scenes with white ambient light, the global light pairs, WW3D::Init and its
// static render switches, the 2D renderer, the static LOD level, the render
// device (falling back to 800x600, else throwing ERROR_INVALID_D3D), the
// asset manager, gamma, the shader manager, streaks, the debug display and
// the debug display callback.
// Target-only, from the native body: BFME 2 sizes (scenes 0x108/0x11C/0x818,
// lights 0x120, Render2DClass 0x4C, debug display 0x130), slot numbers, the
// GlobalData offsets, the 0x0061EEE0 helper instance, the LOD level applied
// only for an unset manager, bfmeClearReceiverFlag, SimpleStreakRendererClass
// and the three debug display callbacks. Offsets/slots are readings.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum ErrorCode { ERROR_INVALID_D3D = 0xDEAD0007 };

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/RectClass.h"

class SceneClass
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual void Set_Ambient_Light(const Vector3 &color);	// slot 6
};

class LightClass
{
public:
	enum LightType { POINT = 0, DIRECTIONAL, SPOT };
	LightClass(LightType type);
	unsigned char m_bytes[0x120];
};

class RTS3DInterfaceScene : public SceneClass
{
};

class Rva0006EE6F : public RTS3DInterfaceScene
{
public:
	Rva0006EE6F();
	unsigned char m_bytes[0x108 - 4];
};

class RTS2DScene : public SceneClass
{
public:
	RTS2DScene();
	unsigned char m_bytes[0x11C - 4];
};

class Rva0006E52AObj;
class Rva0006E52A { public: void rva0006E52A(Rva0006E52AObj *, Int); };
class Rva0006E567Obj;
class Rva0006E567 { public: void rva0006E567(Rva0006E567Obj *, Int); };
void Rva001174D0(Int value);

class RTS3DScene : public SceneClass
{
public:
	RTS3DScene();
	unsigned char m_bytes[0x818 - 4];
};

class W3DFileSystem
{
public:
	W3DFileSystem();
	void *m_vtbl;
};
extern W3DFileSystem *TheW3DFileSystem;

class WWMath
{
public:
	static void Init();
	static void Shutdown();
};

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

void Rva00116E40Set(Int value);
void clipCursorToClient();
void BFME_DX8_Thread_Lock(void);
bool BFME_DX8_Thread_Assert(void);

// Native normal and unwind paths use the existing DX8 device guard.
// Its complete destructor at 0x00042F8C tail-calls BFME_DX8_Thread_Assert.
#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

class SortingRendererClass
{
public:
	static void SetMinVertexBufferSize(UnsignedInt count);
};

class SimpleStreakRendererClass
{
public:
	static void Init(Bool enable);
};

#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
	Render2DClass();
	unsigned char m_bytes[0x4C]; // +0x00
};

enum StaticGameLODLevel { STATIC_GAME_LOD_UNKNOWN = -1 };

#include "../../../../GameEngine/Include/Common/GameLODManager.h"

// The setter is still rowed under this owner; keep its existing call identity.
class Rva00202739 { public: Bool rva00202739(Int); };

class Rva0061EEE0
{
public:
	Rva0061EEE0();
	unsigned char m_bytes[0x10];
};
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;

Bool InitializeAssetManager(AsciiString root, AsciiString archive, Bool flag);
void bfmeClearReceiverFlag(Int flag);

class GameFont;
#include "../../../../GameEngine/Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;

#include "../../../../GameEngine/Include/Common/GlobalLanguageClass.h"
extern GlobalLanguage *TheGlobalLanguageData;

class DebugDisplayInterface;
struct _iobuf;
typedef void DebugDisplayCallback(DebugDisplayInterface *dd, void *userData, _iobuf *fp);
void StatDebugDisplay(DebugDisplayInterface *dd, void *userData, _iobuf *fp);
void AnimDebugDisplay(DebugDisplayInterface *dd, void *userData, _iobuf *fp);
void rva000B3FD0DebugDisplay(DebugDisplayInterface *dd, void *userData, _iobuf *fp);

class Rva000747E5
{
public:
	void rva000747E5();
	void rva000748DF(Int font);
	unsigned char m_pad00[0x20];
	Int m_20;
	Int m_24;
};

class Rva0007517F : public Rva000747E5
{
public:
	Rva0007517F();
	unsigned char m_bytes[0x130 - 0x28];
};

#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

extern void *ApplicationHWnd;

class W3DDisplay
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void init();					// slot 12
	virtual void v13();
	virtual void setWidth(UnsignedInt width);		// slot 14
	virtual void setHeight(UnsignedInt height);		// slot 15
	virtual UnsignedInt getWidth();				// slot 16
	virtual UnsignedInt getHeight();			// slot 17
	virtual void setBitDepth(UnsignedInt depth);		// slot 18
	virtual UnsignedInt getBitDepth();			// slot 19
	virtual void setWindowed(Bool windowed);		// slot 20
	virtual Bool getWindowed();				// slot 21
	virtual void v22(); virtual void v23(); virtual void v24();
	virtual void setGamma(Real gamma, Real bright, Real contrast, Bool calibrate);	// slot 25
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44();
	virtual void setTimeOfDay(Int tod);			// slot 45

	static RTS3DScene *m_3DScene;
	static RTS2DScene *m_2DScene;
	static RTS3DInterfaceScene *m_3DInterfaceScene;

	unsigned char m_pad04[0x2C - 4];
	Rva000747E5 *m_debugDisplay;		// +0x2C
	DebugDisplayCallback *m_debugDisplayCallback;	// +0x30
	unsigned char m_pad34[0x144 - 0x34];
	Bool m_initialized;			// +0x144
	unsigned char m_pad145[3];
	LightClass *m_myLight[4];		// +0x148
	LightClass *m_myLight2[4];		// +0x158
	Render2DClass *m_2DRender;		// +0x168
	unsigned char m_pad16c[0x27C - 0x16C];
	Rva0007517F *m_nativeDebugDisplay;	// +0x27C
};

void W3DDisplay::init()
{
	if (m_initialized)
		return;

	TheW3DFileSystem = new W3DFileSystem;
	WWMath::Init();

	m_3DInterfaceScene = new Rva0006EE6F;
	m_3DInterfaceScene->Set_Ambient_Light(Vector3(1.0f, 1.0f, 1.0f));
	m_2DScene = new RTS2DScene;
	m_2DScene->Set_Ambient_Light(Vector3(1.0f, 1.0f, 1.0f));
	m_3DScene = new RTS3DScene;

	Int i;
	for (i = 0; i < TheGlobalData->m_numberGlobalLights; i++)
	{
		m_myLight[i] = new LightClass(LightClass::DIRECTIONAL);
		m_myLight2[i] = new LightClass(LightClass::DIRECTIONAL);
	}
	setTimeOfDay(TheGlobalData->m_timeOfDay);
	for (i = 0; i < TheGlobalData->m_numberGlobalLights; i++)
	{
		((Rva0006E52A *)m_3DScene)->rva0006E52A((Rva0006E52AObj *)m_myLight[i], i);
		((Rva0006E567 *)m_3DScene)->rva0006E567((Rva0006E567Obj *)m_myLight2[i], i);
	}

	if (TheGlobalData->field0B01)
		SortingRendererClass::SetMinVertexBufferSize(1);

	if (WW3D::Init(ApplicationHWnd, 0, false) != true)
		throw ERROR_INVALID_D3D;

	WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS);
	Rva001174D0(0);
	WW3D::Enable_Static_Sort_Lists(true);
	WW3D::Set_Thumbnail_Enabled(false);
	WW3D::Set_Screen_UV_Bias(true);
	Rva00116E40Set(32);

	setWindowed(TheGlobalData->m_windowed);
	m_2DRender = new Render2DClass;

	if (TheGameLODManager && TheGameLODManager->m_1768 == STATIC_GAME_LOD_UNKNOWN)
		((Rva00202739 *)TheGameLODManager)->rva00202739(TheGameLODManager->findStaticLODLevel());

	setWidth(TheGlobalData->m_xResolution);
	setHeight(TheGlobalData->m_yResolution);
	setBitDepth(32);

	{
		BFMEDX8DeviceLock lock;
		if (!WW3D::Set_Render_Device(0, getWidth(), getHeight(), getBitDepth(), getWindowed(), true, false, true))
		{
			TheGlobalData->m_xResolution = 800;
			TheGlobalData->m_yResolution = 600;
			setWidth(TheGlobalData->m_xResolution);
			setHeight(TheGlobalData->m_yResolution);
			if (WW3D::Set_Render_Device(0, getWidth(), getHeight(), getBitDepth(), getWindowed(), true, false, true) != true)
			{
				WW3D::Shutdown();
				WWMath::Shutdown();
				throw ERROR_INVALID_D3D;
			}
		}
		if (getWindowed())
			WW3D::Set_Ext_Swap_Interval(0);
		else
			clipCursorToClient();
	}

	m_2DRender->Set_Coordinate_Range(RectClass(0.0f, 0.0f, (Real)getWidth(), (Real)getHeight()));

	Rva0134FAA0 = (Rva009EB960 *)new Rva0061EEE0;
	InitializeAssetManager(TheGlobalData->m_modDir, TheGlobalData->m_modBIG, TheGlobalData->field0D48 > 0);
	if (TheGlobalData->field11C8)
		bfmeClearReceiverFlag(0);

	if (TheGlobalData->field0BCC != 1.0f)
		setGamma(TheGlobalData->field0BCC, 0.0f, 1.0f, false);

	{
		BFMEDX8DeviceLock lock;
		W3DShaderManager::init();
	}

	SimpleStreakRendererClass::Init(TheGlobalData->m_useShadowMapping);

	m_nativeDebugDisplay = new Rva0007517F;
	m_debugDisplay = m_nativeDebugDisplay;
	if (m_nativeDebugDisplay)
	{
		m_nativeDebugDisplay->rva000747E5();
		GameFont *font;
		if (TheGlobalLanguageData && !TheGlobalLanguageData->m_nativeDebugDisplay.name.isEmpty())
			font = TheFontLibrary->getFont(&TheGlobalLanguageData->m_nativeDebugDisplay.name,
				(Real)TheGlobalLanguageData->m_nativeDebugDisplay.size, TheGlobalLanguageData->m_nativeDebugDisplay.bold);
		else
			font = TheFontLibrary->getFont(&AsciiString("FixedSys"), 8.0f, false);
		m_nativeDebugDisplay->rva000748DF((Int)font);
		m_nativeDebugDisplay->m_24 = 13;
		m_nativeDebugDisplay->m_20 = 9;
	}

	m_initialized = true;

	if (TheGlobalData->field09C3)
		m_debugDisplayCallback = StatDebugDisplay;
	else if (TheGlobalData->field09C4)
		m_debugDisplayCallback = rva000B3FD0DebugDisplay;
	else
		m_debugDisplayCallback = TheGlobalData->field09C8 ? AnimDebugDisplay : 0;
}
