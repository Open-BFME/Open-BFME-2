// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva0004A462@W3DDisplay@@QAE_NI@Z @0x0004A462 1425B: one W3DDisplay frame render pass,
// called by the unrowed 0x0004BEF2. Returns false while the script engine or game logic
// freezes time.
// Target evidence (retail bytes): the DX8 thread lock/assert pair brackets the whole body
// with EH state 0; Prepare_Render_New_Frame gates the pre-render (particle, terrain shroud
// and taint, shadow-map and water-reflection updates); Begin_Render receives the clear
// colour at +0x20 and the terrain's float at +0x37E8; the loading-screen branch (global
// byte +0xAF5) draws only the UI windows. The function-local couldRender byte and the
// 0x140-byte BFME2ScopedRenderEvent labels "UpdateShadowMap", "UpdateWaterReflection",
// "RenderViews", "RenderUI" are retail's. Every callee except InGameUI 0x002A4A68 is rowed.
// Donor: Zero Hour W3DDisplay::draw (static couldRender, Begin_Render, loadScreenRender,
// the freezeTime test of isTimeFrozenScript/isTimeFrozenDebug/isGamePaused) supplies the
// structure; BFME 2's split into this helper, its slot numbers and the field offsets are
// read from retail only. Slot and field names are opaque where neither source names them.
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

// Shared W3DDisplay unit view: one declaration of each class for every body
// retail built into this unit. Display slots follow the retail W3DDisplay
// vtable 0x007C3C80 (101 slots); unnamed slots are ABI padding.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef __int64 Int64;
struct Coord3D;
struct RGBColor;
class Image;
class VideoBuffer;
class Render2DClass;
class Rva006E8800DisplayString;
class W3DDisplaySubView;
// Retail's lock calls are the BFME_DX8_Thread_Lock / BFME_DX8_Thread_Assert
// providers at 0x0011F520 / 0x00120F50.
void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);
class BFMEDX8DeviceLock
{
public:
	// Keep the inline lock without emitting a competing constructor copy.
	__declspec(dllimport) __forceinline BFMEDX8DeviceLock(void)
	{
		BFME_DX8_Thread_Lock();
	}

	~BFMEDX8DeviceLock(void)
	{
		BFME_DX8_Thread_Assert();
	}
};
class Vector3
{
public:
	__declspec(dllimport) __forceinline Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};
class WW3D
{
public:
	static bool Prepare_Render_New_Frame();
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
	static bool Begin_Render(bool clear, bool clearz, const Vector3 &color, float destAlpha);
	static bool End_Render(bool flipFrame);
};
class IDirect3DSurface9;
class DX8Caps;
class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();
	static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }

protected:
	// The caps at 0x00DEDA7C (defined in dx8wrapper.cpp).
	static DX8Caps *CurrentCaps;
};
class GlobalData
{
public:
	unsigned char m_pad00[0x50];
	Int m_terrainLOD;			// +0x50
	bool m_54;				// +0x54
	unsigned char m_pad55[0x58 - 0x55];
	Int m_terrainLODTargetTimeMS;		// +0x58
	unsigned char m_pad5C[0xEA5 - 0x5C];
	bool m_delayBeforeCapture;		// +0xEA5
};
extern GlobalData *TheWritableGlobalData;
class RTS3DScene
{
public:
	void drawTerrainOnly(bool draw) { m_drawTerrainOnly = draw; }
private:
	unsigned char m_pad000[0x12C];
	bool m_drawTerrainOnly;			// +0x12C
};
class GameLODManager
{
public:
	char m_pad[0x1774];
	int m_detailVariant;		// +0x1774
};
extern GameLODManager *TheGameLODManager;
template <typename T> class StringBase
{
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &src);
	void set(const T *str);
	void clear()
	{
		releaseBuffer();
	}
	void concat(const StringBase<T> &str);
private:
	friend class W3DDisplay;
	~StringBase() { releaseBuffer(); }
};
// Retail ordinary teardown calls releaseBuffer36410; return-value
// cleanup75D142 calls the five-byte private StringBase destructor48BA39.
// Keeping that destructor inline permits the worker call at ordinary
// exits while giving the EH return-value callback its actual wrapper.
// The friend grants access only for this address-named by-value ABI
// view; the original method return type remains unproven.

class Display
{
public:
	Display();
	virtual ~Display();	// slot 0
	virtual void init();	// slot 1
	virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void reset();	// slot 9
	virtual void slot10(); virtual void slot11();
	virtual void draw();	// slot 12
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual UnsignedInt getWidth();	// slot 16
	virtual UnsignedInt getHeight();	// slot 17
	virtual void setBitDepth(UnsignedInt bitDepth);	// slot 18
	virtual UnsignedInt getBitDepth();	// slot 19
	virtual void setWindowed(Bool windowed);	// slot 20
	virtual Bool getWindowed();	// slot 21
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);	// slot 22
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual StringBase<char> rva000481AA(const StringBase<char> &name);	// slot 34
	virtual void slot35();
	virtual unsigned char *getView();	// slot 36
	virtual void slot37();
	virtual void drawViews();	// slot 38
	virtual void slot39();
	virtual void updateViews();	// slot 40
	virtual VideoBuffer *createVideoBuffer(Bool allowAlpha);	// slot 41
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46();
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color, Real innerRadius, Real attenuationWidth, UnsignedInt increaseTime, UnsignedInt decayTime);	// slot 47
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52();
	virtual void beginImageDraw();	// slot 53
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62();
	virtual void drawImageCore(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);	// slot 63
	virtual void endImageDraw();	// slot 64
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);	// slot 65
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73();
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81();
	virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
	virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93();
	virtual void slot94(); virtual void slot95(); virtual void slot96(); virtual void slot97();
	virtual void slot98(); virtual void slot99(); virtual void slot100();

	void DrawStaticImage(int, int);

protected:
	unsigned char m_pad004[0x20 - 0x04];
	Vector3 m_20;				// +0x20, Begin_Render clear colour
	unsigned char m_pad2c[0x30 - 0x2c];
	void *m_30;				// +0x30, debug display
	unsigned char m_pad34[0x38 - 0x34];
	W3DDisplaySubView *m_38;		// +0x38
	unsigned char m_pad3c[0xd4 - 0x3c];
	float m_d4;				// +0xd4
	unsigned char m_padD8[0xfc - 0xd8];
	float m_fc, m_100, m_104, m_108;	// +0xfc
	unsigned char m_pad10c[0x140 - 0x10c];
	unsigned char m_140;			// +0x140
	unsigned char m_141;			// +0x141
	unsigned char m_pad142[0x144 - 0x142];
};
class W3DDisplay : public Display
{
public:
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);
	virtual StringBase<char> rva000481AA(const StringBase<char> &name);
	virtual VideoBuffer *createVideoBuffer(Bool allowAlpha);
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color, Real innerRadius, Real attenuationWidth, UnsignedInt increaseTime, UnsignedInt decayTime);
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);

	void rva000438CB();
	void rva00043FB9();
	bool rva0004A462(unsigned int now);
	void rva0025D205();

	static RTS3DScene *m_3DScene;

protected:
	void calculateTerrainLOD(void);
	void drawCurrentDebugDisplay();

private:
	void rva00045213(char *image, unsigned int rowBytes);

	unsigned char m_pad144[0x168 - 0x144];
	Render2DClass *m_render2D;		// +0x168
	unsigned char m_pad16C[0x180 - 0x16C];
	Real m_180;				// +0x180
	unsigned char m_pad184[0x234 - 0x184];
	Rva006E8800DisplayString *m_displayStrings[17];	// +0x234
};

class Rva0004263F
{
	virtual void slot00();
public:
	void rva0004263F(float x0, float y0, float x1, float y1, int color);	// 0x0004263F
};

class Rva00044018 : public Rva0004263F
{
	char m_pad04[8];
	unsigned int m_width;		// +0x0C
	unsigned int m_height;		// +0x10
	char m_pad14[0xD4 - 0x14];
	float m_progress;			// +0xD4
	unsigned char m_fadingIn;	// +0xD8
	char m_padD9[3];
	unsigned int m_startTime;	// +0xDC
public:
	void rva00044018(unsigned int now);
};

class CameraClass;
class ScriptEngine;
class ParticleSystemManager;
class BaseHeightMapRenderObjClass;
class InGameUI;
class LivingWorld;
class LivingWorldLogic;
class GameWindowManager;
class BfmeAptWindowManager;
class Mouse;
class GameWindowTransitionsHandler;

class BFME2ScopedRenderEvent
{
	char Label[256];
	char Group[64];
public:
	BFME2ScopedRenderEvent(const char *, const char *, unsigned int);
	~BFME2ScopedRenderEvent();
};

void Rva00755C80();
class Rva00068D43 { public: void rva00068D43(); };
class W3DShroud { public: void rva00073628(void *); };
class W3DTaint { public: void render(CameraClass *); };
class W3DShadowMapManager { public: void UpdateShadowMap(RTS3DScene *); };
class WaterRenderObjClass { public: bool IsReflectionVisible(void *); };
class Rva0007F92AHost { public: void rva0007F92A(int, int); };
class Rva0007DA23ResourceManager { public: void rva0007C18E(); void rva0007B6F3(); };
class Rva000B3FD0 { public: void rva000B3FD0(); };
class Rva0081D520Owner { public: void broadcast(int, float, float, float, float); };
class BfmeSelectionState { public: bool isSelectionLocked() const; };
void bfmeGoKA();
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00203ACEByteField { public: unsigned char get() const; };
class InGameUI { public: void rva002A4A68(); };

extern GameLogic *TheGameLogic;
extern ScriptEngine *TheScriptEngine;
extern ParticleSystemManager *TheParticleSystemManager;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
extern void *W3DGCData00DE2000;
extern LivingWorld *TheLivingWorld;
extern GameWindowManager *TheWindowManager;
extern InGameUI *TheInGameUI;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern Mouse *TheMouse;
extern LivingWorldLogic *TheLivingWorldLogic;
extern GameWindowTransitionsHandler *TheTransitionHandler;

// The sub-view at W3DDisplay +0x38.
class W3DDisplaySubView
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual int s20();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual Image *s3c();
};

// The common slots the manager globals are called through.
class Rva0004A462SystemView
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void s20();
	virtual void v024();
	virtual void s28();
	virtual void v02c();
	virtual void s30();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14c();
	virtual void v150();
	virtual void v154();
	virtual void s158();
	virtual void v15c();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16c();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual bool s17c();
};

#define SYS(p) ((Rva0004A462SystemView *)(p))
#define TWGD ((unsigned char *)TheWritableGlobalData)
#define TERRAIN ((unsigned char *)TheTerrainRenderObject)
#define LIVINGWORLD ((unsigned char *)TheLivingWorld)
#define WINDOWMODE (*(int *)((char *)TheWindowManager + 0x3c))

bool W3DDisplay::rva0004A462(unsigned int now)
{
    BFMEDX8DeviceLock lock;
    static bool couldRender = true;
    if (WW3D::Prepare_Render_New_Frame())
    {
        if (!TheGameLogic->getFlag125())
        {
            updateViews();
            Rva00755C80();
        }
        SYS(TheParticleSystemManager)->s28();
        if (TheTerrainRenderObject != 0)
        {
            ((Rva00068D43 *)TheTerrainRenderObject)->rva00068D43();
            if (TheTerrainRenderObject != 0 && *(void **)(TERRAIN + 0x37c0) != 0)
            {
                unsigned char *view = getView();
                if (*(void **)(TERRAIN + 0x3878) != 0)
                    ((W3DShroud *)*(void **)(TERRAIN + 0x3878))->rva00073628(*(void **)(view + 0x104));
                if (*(void **)(TERRAIN + 0x387c) != 0)
                    ((W3DTaint *)*(void **)(TERRAIN + 0x387c))->render((CameraClass *)*(void **)(view + 0x104));
            }
        }
        if (TheGameLogic == 0 || !TheGameLogic->m_6d)
        {
            if (Rva00DE1FF8Manager != 0 && TWGD[0x62] != 0)
            {
                BFME2ScopedRenderEvent event("UpdateShadowMap", "Frame", 0);
                ((W3DShadowMapManager *)Rva00DE1FF8Manager)->UpdateShadowMap(m_3DScene);
            }
            unsigned char *view = getView();
            if (W3DGCData00DE2000 != 0 && view != 0 &&
                ((WaterRenderObjClass *)W3DGCData00DE2000)->IsReflectionVisible(*(void **)(view + 0x104)))
            {
                BFME2ScopedRenderEvent event("UpdateWaterReflection", "Frame", 0);
                ((Rva0007F92AHost *)W3DGCData00DE2000)->rva0007F92A((int)m_3DScene, (int)*(void **)(view + 0x104));
            }
        }
        if (TWGD[0xd36] == 0 && TWGD[0xb6f] == 0 &&
            WW3D::Begin_Render(true, true, m_20, *(float *)(TERRAIN + 0x37e8)))
        {
            if (TWGD[0xaf5] == 1)
            {
                WINDOWMODE = 1;
                SYS(TheInGameUI)->s30();
                SYS(g_bfmeAptWindowManager)->s30();
                WINDOWMODE = -1;
                if (TheMouse != 0)
                    SYS(TheMouse)->s30();
                WW3D::End_Render(true);
                return true;
            }
            *(int *)((char *)m_3DScene + 0x7ec) = 0;
            couldRender = 1;
            bool cameraValid = m_d4 > 0.0f;
            if (TheLivingWorld != 0 && LIVINGWORLD[0x18] != 0 && LIVINGWORLD[0x19] == 0)
            {
                SYS(TheLivingWorld)->s20();
                if (*(int *)(LIVINGWORLD + 0x14) != 2)
                {
                    WINDOWMODE = 1;
                    SYS(TheInGameUI)->s30();
                    if (!cameraValid)
                        SYS(TheInGameUI)->s158();
                    SYS(g_bfmeAptWindowManager)->s30();
                    WINDOWMODE = 0;
                    SYS(TheInGameUI)->s30();
                    WINDOWMODE = -1;
                }
            }
            else
            {
                {
                    BFME2ScopedRenderEvent event("RenderViews", "Frame", 0);
                    if (Rva00DE1FF8Manager != 0 && TWGD[0x62] != 0)
                        Rva00DE1FF8Manager->rva0007C18E();
                    drawViews();
                    if (Rva00DE1FF8Manager != 0 && TWGD[0x62] != 0)
                        Rva00DE1FF8Manager->rva0007B6F3();
                }
                DrawStaticImage(0, 2);
                DrawStaticImage(1, 2);
                DrawStaticImage(2, 2);
                if (m_38 == 0)
                    rva0025D205();
                {
                    BFME2ScopedRenderEvent event("RenderUI", "Frame", 0);
                    WINDOWMODE = 1;
                    SYS(TheInGameUI)->s30();
                    if (!cameraValid)
                        SYS(TheInGameUI)->s158();
                    SYS(g_bfmeAptWindowManager)->s30();
                    WINDOWMODE = 0;
                    SYS(TheInGameUI)->s30();
                    WINDOWMODE = -1;
                }
            }
            TheInGameUI->rva002A4A68();
            if (TheMouse != 0)
                SYS(TheMouse)->s30();
            if (m_38 != 0)
            {
                DrawStaticImage(0, 1);
                DrawStaticImage(1, 1);
                drawImage(m_38->s3c(), m_fc, m_100, m_104, m_108, -1);
                DrawStaticImage(2, 1);
                rva0025D205();
                ((Rva000B3FD0 *)this)->rva000B3FD0();
                Rva0081D520Owner *node = *(Rva0081D520Owner **)(*(unsigned char **)((unsigned char *)m_38 + 8) + 0x18);
                if (node != 0)
                {
                    node->broadcast(m_38->s20(), 0.0f, 0.0f, (float)getWidth(), (float)getHeight());
                }
            }
            ((Rva00044018 *)this)->rva00044018(now);
            if (cameraValid)
                SYS(TheInGameUI)->s158();
            if (!SYS(TheInGameUI)->s17c() &&
                (((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked() || TheGameLogic->rva0042219()) &&
                m_140 != 0)
            {
                slot100();
                bfmeGoKA();
            }
            if (m_141 == 0)
                SYS(TheTransitionHandler)->s30();
            if (m_30 != 0)
                drawCurrentDebugDisplay();
            WW3D::End_Render(true);
        }
        else
        {
            if (couldRender != 0)
                couldRender = 0;
        }
    }
    if (((Rva00203B08 *)TheScriptEngine)->rva0020424FF() || ((Rva00203ACEByteField *)TheScriptEngine)->get() ||
        TheGameLogic->isGamePaused())
        return false;
    return true;
}
