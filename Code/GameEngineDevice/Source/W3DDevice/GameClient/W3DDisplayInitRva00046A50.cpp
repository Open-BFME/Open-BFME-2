// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva00046A50@W3DDisplay@@QAEXXZ, retail 0x00046A50, 1594 bytes.
// W3DDisplay::init (identity: WB 0x965B70 W3DDisplay::init, callgraph match;
// ZH GeneralsMD W3DDisplay.cpp init is the structural donor).
// Retail-measured BFME2 deltas against ZH: scenes/file system are globals, two
// 4-entry light arrays (+0x148/+0x158) are filled per global light, the
// Set_Render_Device retry runs under the DX8 guard, and the debug display is a
// pair of members (+0x2c view, +0x27c owner).
#include "ascii_string.h"

class DebugDisplayInterface;
struct _iobuf;
typedef void(__cdecl *DebugDisplayCallback)(DebugDisplayInterface *, void *, _iobuf *);
void __cdecl StatDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
void __cdecl AnimDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
void __cdecl BfmeNoopDebugDisplay(DebugDisplayInterface *, void *, _iobuf *);

class W3DFileSystem { public: W3DFileSystem(); virtual void s00(); };
class WWMath { public: static void Init(void); };
class Vec3 { public: Vec3(float a, float b, float c) : X(a), Y(b), Z(c) {} float X, Y, Z; };
class Rva0006EE6F { public: Rva0006EE6F(); virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C(); virtual void s10(); virtual void s14(); virtual void setAmbient(const Vec3 &v); char pad[0x108 - 4]; };
class Rva0006F9D6 { public: Rva0006F9D6(); virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C(); virtual void s10(); virtual void s14(); virtual void setAmbient(const Vec3 &v); char pad[0x11c - 4]; };
class RTS3DScene { public: RTS3DScene(); char pad[0x818]; };
class LightClass { public: enum LightType { POINT, DIRECTIONAL, SPOT }; LightClass(LightType t); char pad[0x120]; };
class Rva0006E52AObj;
class Rva0006E567Obj;
class Rva0006E52A { public: void rva0006E52A(Rva0006E52AObj *o, int i); };
class Rva0006E567 { public: void rva0006E567(Rva0006E567Obj *o, int i); };
class SortingRendererClass { public: static void SetMinVertexBufferSize(unsigned n); };
class WW3D { public: static bool Init(void *hwnd, char *def, bool vis); static bool Set_Render_Device(int dev, int w, int h, int bits, int windowed, bool resize, bool reset, bool restore); static void Set_Ext_Swap_Interval(long n); };
void __cdecl Rva001174D0(int);
void __cdecl Rva00116E40Set(int);
bool __cdecl shutdownRenderDevice(void);
void __cdecl DX8_Assert(void);
void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);
void __cdecl clipCursorToClient(void);
void __cdecl bfmeClearReceiverFlag(int);
bool InitializeAssetManager(AsciiString a, AsciiString b, bool skip);

class RectClass
{
public:
	RectClass(float x, float y, float w, float h) : X(x), Y(y), Width(w), Height(h) {}
	float X, Y, Width, Height;
};
class Render2DClass { public: Render2DClass(); void Set_Coordinate_Range(const RectClass &range); char pad[0x4c]; };
class Rva0061EEE0 { public: Rva0061EEE0(); char pad[0x10]; };
class Rva00066A9AHost { public: void headA(void); };
union HeadAView { void (Rva00066A9AHost::*method)(void); void(__cdecl *plain)(void); };
class SimpleStreakRendererClass { public: static void Init(bool b); };
class Rva0007517F { public: Rva0007517F(); char pad[0x130]; };
class Rva000747E5 { public: void rva000747E5(void); void rva000748DF(int font); };
class GameFont;
class FontLibrary { public: GameFont *getFont(const AsciiString *name, float size, bool bold); };

class Rva00202739 { public: bool rva00202739(int level); };
enum StaticGameLODLevel { STATIC_GAME_LOD_UNKNOWN = -1 };
class GameLODManager { public: StaticGameLODLevel findStaticLODLevel(void); };
struct GameLODView { char pad[0x1768]; int staticLevel; };

struct GlobalDataView
{
	char pad00[0x2c];
	bool windowed2c;
	char pad2d[3];
	int xRes;
	int yRes;
	char pad38[0x62 - 0x38];
	bool streak62;
	char pad63[0x134 - 0x63];
	int timeOfDay;
	char pad138[0x988 - 0x138];
	int numLights;
	char pad98c[0x9c3 - 0x98c];
	bool dbg9c3;
	bool dbg9c4;
	char pad9c5[3];
	bool dbg9c8;
	char pad9c9[0xb01 - 0x9c9];
	bool incAGP;
	char padb02[0xbcc - 0xb02];
	float gamma;
	char padbd0[0xd38 - 0xbd0];
	AsciiString strD38;
	AsciiString strD3C;
	char padd40[0xd48 - 0xd40];
	int intD48;
	char padd4c[0x11c8 - 0xd4c];
	bool recv11c8;
};
struct LanguageDataView
{
	char pad00[0xc8];
	AsciiString fontName;
	int fontSize;
	bool fontBold;
};

class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setWidth(unsigned int w);
	virtual void setHeight(unsigned int h);
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual void setBitDepth(unsigned int d);
	virtual unsigned int getBitDepth();
	virtual void setWindowed(bool w);
	virtual bool getWindowed();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void setGamma(float g, float b, float c, bool r);
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void setTimeOfDay(int t);
	char pad04[0x28];
	Rva000747E5 *m_debugDisplay;
	DebugDisplayCallback m_debugDisplayCallback;
	char pad34[0x144 - 0x34];
	bool m_initialized;
};

class W3DDisplay : public Display
{
public:
	void rva00046A50(void);
private:
	LightClass *m_myLight[4];
	LightClass *m_myLightB[4];
	Render2DClass *m_2DRender;
	char pad16c[0x27c - 0x16c];
	Rva000747E5 *m_nativeDebugDisplay;
};

extern W3DFileSystem *TheW3DFileSystem;
extern Rva0006EE6F *TheScene2D;
extern Rva0006F9D6 *TheScene3DInterface;
extern RTS3DScene *TheScene3D;
extern GlobalDataView *TheWritableGlobalData;
extern GameLODManager *TheGameLODManager;
extern LanguageDataView *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;
extern void *ApplicationHWnd;
extern int WW3DField0DB5F88;
extern bool WW3DFlag0DEC3D9;
extern bool WW3DFlag0DB5F8C;
extern bool WW3DFlag0DEC3D7;
extern Rva0061EEE0 *TheRva0061EEE0;

class DX8DeviceGuard
{
public:
	DX8DeviceGuard(void) { BFME_DX8_Thread_Lock(); }
	~DX8DeviceGuard(void) { BFME_DX8_Thread_Assert(); }
};

void W3DDisplay::rva00046A50(void)
{
	if (m_initialized)
		return;

	TheW3DFileSystem = new W3DFileSystem;
	WWMath::Init();

	TheScene2D = new Rva0006EE6F;
	TheScene2D->setAmbient(Vec3(1.0f, 1.0f, 1.0f));
	TheScene3DInterface = new Rva0006F9D6;
	TheScene3DInterface->setAmbient(Vec3(1.0f, 1.0f, 1.0f));
	TheScene3D = new RTS3DScene;

	int i;
	for (i = 0; i < TheWritableGlobalData->numLights; i++)
	{
		m_myLight[i] = new LightClass(LightClass::DIRECTIONAL);
		m_myLightB[i] = new LightClass(LightClass::DIRECTIONAL);
	}
	setTimeOfDay(TheWritableGlobalData->timeOfDay);
	for (i = 0; i < TheWritableGlobalData->numLights; i++)
	{
		((Rva0006E52A *)TheScene3D)->rva0006E52A((Rva0006E52AObj *)m_myLight[i], i);
		((Rva0006E567 *)TheScene3D)->rva0006E567((Rva0006E567Obj *)m_myLightB[i], i);
	}

	if (TheWritableGlobalData->incAGP)
		SortingRendererClass::SetMinVertexBufferSize(1);

	if (WW3D::Init(ApplicationHWnd, 0, false) != true)
		throw 0xdead0007;

	WW3DField0DB5F88 = 1;
	Rva001174D0(0);
	WW3DFlag0DEC3D9 = true;
	WW3DFlag0DB5F8C = false;
	WW3DFlag0DEC3D7 = true;
	Rva00116E40Set(32);
	setWindowed(TheWritableGlobalData->windowed2c);
	m_2DRender = new Render2DClass;

	if (TheGameLODManager && ((GameLODView *)TheGameLODManager)->staticLevel == -1)
		((Rva00202739 *)TheGameLODManager)->rva00202739(TheGameLODManager->findStaticLODLevel());

	setWidth(TheWritableGlobalData->xRes);
	setHeight(TheWritableGlobalData->yRes);
	setBitDepth(32);
	{
		DX8DeviceGuard lock;
		if (!WW3D::Set_Render_Device(0, getWidth(), getHeight(), getBitDepth(), getWindowed(), true, false, true))
		{
			TheWritableGlobalData->xRes = 800;
			TheWritableGlobalData->yRes = 600;
			setWidth(TheWritableGlobalData->xRes);
			setHeight(TheWritableGlobalData->yRes);
			if (WW3D::Set_Render_Device(0, getWidth(), getHeight(), getBitDepth(), getWindowed(), true, false, true) != 1)
			{
				shutdownRenderDevice();
				DX8_Assert();
				throw 0xdead0007;
			}
		}
		if (getWindowed())
			WW3D::Set_Ext_Swap_Interval(0);
		else
			clipCursorToClient();
	}

	float h = (float)getHeight();
	float w = (float)getWidth();
	m_2DRender->Set_Coordinate_Range(RectClass(0.0f, 0.0f, w, h));

	TheRva0061EEE0 = new Rva0061EEE0;

	InitializeAssetManager(TheWritableGlobalData->strD38, TheWritableGlobalData->strD3C, TheWritableGlobalData->intD48 > 0);
	if (TheWritableGlobalData->recv11c8)
		bfmeClearReceiverFlag(0);
	if (TheWritableGlobalData->gamma != 1.0f)
		setGamma(TheWritableGlobalData->gamma, 0.0f, 1.0f, false);

	{
		DX8DeviceGuard lock;
		HeadAView head;
		head.method = &Rva00066A9AHost::headA;
		head.plain();
	}
	SimpleStreakRendererClass::Init(TheWritableGlobalData->streak62);

	Rva0007517F *dbg = new Rva0007517F;
	m_nativeDebugDisplay = (Rva000747E5 *)dbg;
	m_debugDisplay = (Rva000747E5 *)dbg;
	if (dbg)
	{
		m_nativeDebugDisplay->rva000747E5();
		GameFont *font;
		if (TheGlobalLanguageData && !TheGlobalLanguageData->fontName.isEmpty())
			font = TheFontLibrary->getFont(&TheGlobalLanguageData->fontName, (float)TheGlobalLanguageData->fontSize, TheGlobalLanguageData->fontBold);
		else
		{
			AsciiString fixed("FixedSys");
			font = TheFontLibrary->getFont(&fixed, 8.0f, false);
		}
		m_nativeDebugDisplay->rva000748DF((int)font);
		((int *)m_nativeDebugDisplay)[9] = 13;
		((int *)m_nativeDebugDisplay)[8] = 9;
	}

	m_initialized = true;
	if (TheWritableGlobalData->dbg9c3)
		m_debugDisplayCallback = StatDebugDisplay;
	else if (TheWritableGlobalData->dbg9c4)
		m_debugDisplayCallback = BfmeNoopDebugDisplay;
	else
		m_debugDisplayCallback = TheWritableGlobalData->dbg9c8 ? AnimDebugDisplay : 0;
}
