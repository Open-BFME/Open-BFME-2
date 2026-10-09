// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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

class Vector3
{
public:
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real X, Y, Z;
};

class RectClass
{
public:
	RectClass(Real left, Real top, Real right, Real bottom) : Left(left), Top(top), Right(right), Bottom(bottom) {}
	Real Left, Top, Right, Bottom;
};

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

class RTS3DScene : public SceneClass
{
public:
	RTS3DScene();
	void rva0006E52A(LightClass *light, Int index);
	void rva0006E567(LightClass *light, Int index);
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
	static void rva0069E440();
};

class WW3D
{
public:
	enum PrelitModeEnum { PRELIT_MODE_VERTEX = 0, PRELIT_MODE_LIGHTMAP_MULTI_PASS };
	static Bool Init(void *hwnd, char *defaultpal, Bool lite);
	static Bool Set_Render_Device(Int dev, Int resx, Int resy, Int bits, Int windowed, Bool resize_window, Bool reset_device, Bool restore_assets);
	static void Set_Ext_Swap_Interval(long swap);
	static void rva001174D0(Int value);
	static void Set_Prelit_Mode(PrelitModeEnum mode) { PrelitMode = mode; }
	static void Enable_Static_Sort_Lists(Bool onoff) { AreStaticSortListsEnabled = onoff; }
	static void Set_Thumbnail_Enabled(Bool onoff) { ThumbnailEnabled = onoff; }
	static void Set_Screen_UV_Bias(Bool onoff) { IsScreenUVBiased = onoff; }
private:
	static PrelitModeEnum PrelitMode;
	static Bool AreStaticSortListsEnabled;
	static Bool ThumbnailEnabled;
	static Bool IsScreenUVBiased;
};

void Rva00116E40Set(Int value);
Bool shutdownRenderDevice();
void clipCursorToClient();
void BFME_DX8_Thread_Lock(void);
void BFME_DX8_Thread_Assert(void);

class DX8ThreadLock
{
public:
	DX8ThreadLock() { BFME_DX8_Thread_Lock(); }
	~DX8ThreadLock() { BFME_DX8_Thread_Assert(); }
};

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

class W3DShaderManager
{
public:
	static void init();
};

class Render2DClass
{
public:
	Render2DClass();
	void Set_Coordinate_Range(const RectClass &range);
	unsigned char m_bytes[0x4C];
};

enum StaticGameLODLevel { STATIC_GAME_LOD_UNKNOWN = -1 };

class GameLODManager
{
public:
	StaticGameLODLevel findStaticLODLevel();
	Bool rva00202739(Int level);
	unsigned char m_pad00[0x1768];
	Int m_staticLODLevel;			// +0x1768
};
extern GameLODManager *TheGameLODManager;

class Rva0061EEE0
{
public:
	Rva0061EEE0();
	unsigned char m_bytes[0x10];
};
extern Rva0061EEE0 *TheRva0061EEE0;

Bool InitializeAssetManager(AsciiString root, AsciiString archive, Bool flag);
void bfmeClearReceiverFlag(Int flag);

class GameFont;
class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, Real pointSize, Bool bold);
};
extern FontLibrary *TheFontLibrary;

class GlobalLanguage
{
public:
	unsigned char m_pad00[0xC8];
	AsciiString m_defaultDisplayFont;	// +0xC8
	Int m_defaultDisplayFontSize;		// +0xCC
	Bool m_defaultDisplayFontBold;		// +0xD0
};
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

class GlobalData
{
public:
	unsigned char m_pad00[0x2C];
	Bool m_windowed;			// +0x2C
	unsigned char m_pad2d[3];
	UnsignedInt m_xResolution;		// +0x30
	UnsignedInt m_yResolution;		// +0x34
	unsigned char m_pad38[0x62 - 0x38];
	Bool m_streaks;				// +0x62
	unsigned char m_pad63[0x134 - 0x63];
	Int m_timeOfDay;			// +0x134
	unsigned char m_pad138[0x988 - 0x138];
	Int m_numGlobalLights;			// +0x988
	unsigned char m_pad98c[0x9C3 - 0x98C];
	Bool m_debugStats;			// +0x9C3
	Bool m_debug9C4;			// +0x9C4
	unsigned char m_pad9c5[3];
	Bool m_debugAnim;			// +0x9C8
	unsigned char m_pad9c9[0xB01 - 0x9C9];
	Bool m_minVertexBuffer;			// +0xB01
	unsigned char m_padb02[0xBCC - 0xB02];
	Real m_gamma;				// +0xBCC
	unsigned char m_padbd0[0xD38 - 0xBD0];
	AsciiString m_assetRoot;		// +0xD38
	AsciiString m_assetArchive;		// +0xD3C
	unsigned char m_padd40[0xD48 - 0xD40];
	Int m_assetFlag;			// +0xD48
	unsigned char m_padd4c[0x11C8 - 0xD4C];
	Bool m_11C8;				// +0x11C8
};
extern GlobalData *TheGlobalData;

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
	for (i = 0; i < TheGlobalData->m_numGlobalLights; i++)
	{
		m_myLight[i] = new LightClass(LightClass::DIRECTIONAL);
		m_myLight2[i] = new LightClass(LightClass::DIRECTIONAL);
	}
	setTimeOfDay(TheGlobalData->m_timeOfDay);
	for (i = 0; i < TheGlobalData->m_numGlobalLights; i++)
	{
		m_3DScene->rva0006E52A(m_myLight[i], i);
		m_3DScene->rva0006E567(m_myLight2[i], i);
	}

	if (TheGlobalData->m_minVertexBuffer)
		SortingRendererClass::SetMinVertexBufferSize(1);

	if (WW3D::Init(ApplicationHWnd, 0, false) != true)
		throw ERROR_INVALID_D3D;

	WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS);
	WW3D::rva001174D0(0);
	WW3D::Enable_Static_Sort_Lists(true);
	WW3D::Set_Thumbnail_Enabled(false);
	WW3D::Set_Screen_UV_Bias(true);
	Rva00116E40Set(32);

	setWindowed(TheGlobalData->m_windowed);
	m_2DRender = new Render2DClass;

	if (TheGameLODManager && TheGameLODManager->m_staticLODLevel == STATIC_GAME_LOD_UNKNOWN)
		TheGameLODManager->rva00202739(TheGameLODManager->findStaticLODLevel());

	setWidth(TheGlobalData->m_xResolution);
	setHeight(TheGlobalData->m_yResolution);
	setBitDepth(32);

	{
		DX8ThreadLock lock;
		if (!WW3D::Set_Render_Device(0, getWidth(), getHeight(), getBitDepth(), getWindowed(), true, false, true))
		{
			TheGlobalData->m_xResolution = 800;
			TheGlobalData->m_yResolution = 600;
			setWidth(TheGlobalData->m_xResolution);
			setHeight(TheGlobalData->m_yResolution);
			if (WW3D::Set_Render_Device(0, getWidth(), getHeight(), getBitDepth(), getWindowed(), true, false, true) != true)
			{
				shutdownRenderDevice();
				WWMath::rva0069E440();
				throw ERROR_INVALID_D3D;
			}
		}
		if (getWindowed())
			WW3D::Set_Ext_Swap_Interval(0);
		else
			clipCursorToClient();
	}

	m_2DRender->Set_Coordinate_Range(RectClass(0.0f, 0.0f, (Real)getWidth(), (Real)getHeight()));

	TheRva0061EEE0 = new Rva0061EEE0;
	InitializeAssetManager(TheGlobalData->m_assetRoot, TheGlobalData->m_assetArchive, TheGlobalData->m_assetFlag > 0);
	if (TheGlobalData->m_11C8)
		bfmeClearReceiverFlag(0);

	if (TheGlobalData->m_gamma != 1.0f)
		setGamma(TheGlobalData->m_gamma, 0.0f, 1.0f, false);

	{
		DX8ThreadLock lock;
		W3DShaderManager::init();
	}

	SimpleStreakRendererClass::Init(TheGlobalData->m_streaks);

	m_nativeDebugDisplay = new Rva0007517F;
	m_debugDisplay = m_nativeDebugDisplay;
	if (m_nativeDebugDisplay)
	{
		m_nativeDebugDisplay->rva000747E5();
		GameFont *font;
		if (TheGlobalLanguageData && !TheGlobalLanguageData->m_defaultDisplayFont.isEmpty())
			font = TheFontLibrary->getFont(&TheGlobalLanguageData->m_defaultDisplayFont,
				(Real)TheGlobalLanguageData->m_defaultDisplayFontSize, TheGlobalLanguageData->m_defaultDisplayFontBold);
		else
			font = TheFontLibrary->getFont(&AsciiString("FixedSys"), 8.0f, false);
		m_nativeDebugDisplay->rva000748DF((Int)font);
		m_nativeDebugDisplay->m_24 = 13;
		m_nativeDebugDisplay->m_20 = 9;
	}

	m_initialized = true;

	if (TheGlobalData->m_debugStats)
		m_debugDisplayCallback = StatDebugDisplay;
	else if (TheGlobalData->m_debug9C4)
		m_debugDisplayCallback = rva000B3FD0DebugDisplay;
	else
		m_debugDisplayCallback = TheGlobalData->m_debugAnim ? AnimDebugDisplay : 0;
}
