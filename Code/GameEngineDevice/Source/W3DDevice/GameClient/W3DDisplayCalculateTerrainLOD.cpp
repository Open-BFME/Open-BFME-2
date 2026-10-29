// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?calculateTerrainLOD@W3DDisplay@@IAEXXZ, retail 0x00043DC3..0x00043F94
// (465B), thiscall.
//
// Donor: Zero Hour W3DDisplay.cpp W3DDisplay::calculateTerrainLOD (protected
// in W3DDisplay.h). BFME 2 differences read from retail only:
//   * no sprintf/OutputDebugString frame log (and no buffer);
//   * each sample frame runs under the DX8 device lock (rowed
//     BFME_DX8_Thread_Lock 0x0011F520 after updateViews and the rowed
//     BFME_DX8_Thread_Assert 0x00120F50 at the end of the sample, EH state 0);
//   * Begin_Render is the rowed WW3D::Begin_Render 0x00118170 returning bool,
//     compared with true; End_Render(true) 0x00117410;
//   * the LOD walk is AUTOMATIC 8 -> MAX 7 -> NO_WATER 6 -> HALF_CLOUDS 3 ->
//     disable, the target time is the int at TheGlobalData +0x58 and the LOD
//     the int at +0x50; drawTerrainOnly is the inline byte store at
//     W3DDisplay::m_3DScene +0x12C; adjustTerrainLOD is terrain vtable slot
//     135 (+0x21C); updateViews / drawViews are this's slots 40 / 38.
// Performance counter helpers: rowed Rva00043024Get (frequency) and
// Rva0004300DGet (counter). Sole caller 0x00044011.
//
// Callee note: all six retail callers of 0x00118170 push four arguments (add
// esp,0x10); the row spells a fifth (unused) function-pointer parameter, so
// the call here uses the four-argument spelling.
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
	virtual void slot35(); virtual void slot36(); virtual void slot37();
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

protected:
	unsigned char m_pad004[0x144 - 0x04];
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

	static RTS3DScene *m_3DScene;

protected:
	void calculateTerrainLOD(void);

private:
	void rva00045213(char *image, unsigned int rowBytes);

	unsigned char m_pad144[0x168 - 0x144];
	Render2DClass *m_render2D;		// +0x168
	unsigned char m_pad16C[0x180 - 0x16C];
	Real m_180;				// +0x180
	unsigned char m_pad184[0x234 - 0x184];
	Rva006E8800DisplayString *m_displayStrings[17];	// +0x234
};

Int64 Rva00043024Get();
Int64 Rva0004300DGet();

enum TerrainLOD
{
	TERRAIN_LOD_MIN = 1,
	TERRAIN_LOD_HALF_CLOUDS = 3,
	TERRAIN_LOD_NO_WATER = 6,
	TERRAIN_LOD_MAX = 7,
	TERRAIN_LOD_AUTOMATIC = 8,
	TERRAIN_LOD_DISABLE = 9
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class BaseHeightMapRenderObjClass
{
public:
	PAD_VIRTUALS10(a0) PAD_VIRTUALS10(a1) PAD_VIRTUALS10(a2) PAD_VIRTUALS10(a3)
	PAD_VIRTUALS10(a4) PAD_VIRTUALS10(a5) PAD_VIRTUALS10(a6) PAD_VIRTUALS10(a7)
	PAD_VIRTUALS10(a8) PAD_VIRTUALS10(a9) PAD_VIRTUALS10(b0) PAD_VIRTUALS10(b1)
	PAD_VIRTUALS10(b2)
	virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34();
	virtual void adjustTerrainLOD(Int adj);	// slot 135
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

void W3DDisplay::calculateTerrainLOD(void)
{
	const Int NUM_SAMPLES = 20;
	const Int NUM_TO_DISCARD = 5;

	Int64 freq64 = Rva00043024Get();

	float frameTime = 0;
	float maxTimeLimit = TheWritableGlobalData->m_terrainLODTargetTimeMS / 1000.0f;
	TerrainLOD goodLOD = TERRAIN_LOD_MIN;
	TerrainLOD curLOD = TERRAIN_LOD_AUTOMATIC;
	Int count = 0;
	do {
		Int i;
		float timeForFrame = 0;
		frameTime = 0;
		switch (curLOD) {
			default: curLOD = TERRAIN_LOD_DISABLE; break;
			case TERRAIN_LOD_AUTOMATIC: curLOD = TERRAIN_LOD_MAX; break;
			case TERRAIN_LOD_MAX: curLOD = TERRAIN_LOD_NO_WATER; break;
			case TERRAIN_LOD_HALF_CLOUDS: curLOD = TERRAIN_LOD_DISABLE; break;
			case TERRAIN_LOD_NO_WATER: curLOD = TERRAIN_LOD_HALF_CLOUDS; break;
		}
		if (curLOD == TERRAIN_LOD_DISABLE) {
			break;
		}
		TheWritableGlobalData->m_terrainLOD = curLOD;
		m_3DScene->drawTerrainOnly(true);
		TheTerrainRenderObject->adjustTerrainLOD(0);
		for (i = 0; i < NUM_SAMPLES; i++) {
			Int64 startTime64 = Rva0004300DGet();
			updateViews();
			BFMEDX8DeviceLock lock;
			if (WW3D::Begin_Render(true, true, Vector3(0.0f, 0.0f, 0.0f), 0.0f) == true)
			{
				drawViews();
				WW3D::End_Render(true);
			}
			Int64 time64 = Rva0004300DGet();
			timeForFrame = (float)((double)(time64 - startTime64) / (double)(freq64));
			if (i >= NUM_TO_DISCARD) {
				frameTime += timeForFrame;
				if (i > NUM_TO_DISCARD + 1 &&
					(timeForFrame / ((i + 1) - NUM_TO_DISCARD)) > 2 * maxTimeLimit) {
					i++;
					break;
				}
			}
		}
		frameTime /= ((i) - NUM_TO_DISCARD);
		count++;
		if (frameTime < maxTimeLimit && goodLOD < curLOD) {
			goodLOD = curLOD;
		}
		if (frameTime < maxTimeLimit) break;
	} while (count < 10);

	TheWritableGlobalData->m_terrainLOD = goodLOD;
	m_3DScene->drawTerrainOnly(false);
	TheTerrainRenderObject->adjustTerrainLOD(0);
}

// ?rva00043FB9@W3DDisplay@@QAEXXZ, retail 0x00043FB9 (95 bytes): the only
// caller of calculateTerrainLOD. It sets the game LOD manager's static level
// (rowed 0x0020276C) to the level the manager picks for the +0x180 value
// (rowed 0x00202613) when TheGlobalData's +0x54 flag and TheGameLogic's +0x9B
// byte are both set, else to level 4; an automatic terrain LOD with a terrain
// render object present is then measured.
class Rva00202613 { public: Int rva00202613(Real value); };
class Rva0020276C { public: bool rva0020276C(Int level); };

class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva00043FB9GameLogicView
{
	unsigned char m_pad00[0x9B];
	bool m_9B;				// +0x9B
};

void W3DDisplay::rva00043FB9()
{
	if (TheWritableGlobalData->m_54 && ((Rva00043FB9GameLogicView *)TheGameLogic)->m_9B)
		((Rva0020276C *)TheGameLODManager)->rva0020276C(((Rva00202613 *)TheGameLODManager)->rva00202613(m_180));
	else
		((Rva0020276C *)TheGameLODManager)->rva0020276C(4);
	if (TheWritableGlobalData->m_terrainLOD == TERRAIN_LOD_AUTOMATIC && TheTerrainRenderObject)
		calculateTerrainLOD();
}
