// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva000481AA@W3DDisplay@@UAE?AV?$StringBase@D@@ABV2@@Z, retail 0x000481AA (194 bytes, EH,
// RET 8), W3DDisplay vtable 0x007C3C80 slot 34. Returns the given name with a variant suffix
// ("L" for mode 0, "M" for mode 1, none for 2/3; the mode is +0x1774 of
// TheGameLODManager) when the rowed 0x0021F3E0 accepts that variant, else the name unchanged. The
// two return statements give the construct-on-return flag retail keeps in its frame.
#include <new>

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

struct BfmeR1025
{
	char *m_bfmeName;
};
char bfmeGo1025F(BfmeR1025 *p);

StringBase<char> W3DDisplay::rva000481AA(const StringBase<char> &name)
{
	StringBase<char> suffix;
	StringBase<char> full;
	switch (TheGameLODManager->m_detailVariant)
	{
	case 0:
		suffix.set("L");
		break;
	case 1:
		suffix.set("M");
		break;
	case 2:
	case 3:
		suffix.clear();
		break;
	default:
		break;
	}
	full.set(name);
	full.concat(suffix);
	if (bfmeGo1025F((BfmeR1025 *)&full))
		return full;
	return name;
}
