// ?drawImage@W3DDisplay@@UAEXPAVImage@@MMMMH@Z
// partial score=0.99 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// ?drawImage@W3DDisplay@@UAEXPAVImage@@MMMMH@Z @ 0x00044E77 (322B)
// W3DDisplay::drawImage ported from the BFME1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawImage.cpp
// (same shape as the present-unmatched copy in W3DDisplayDrawImage.cpp,
// which still uses donor slots and donor callee spellings): fast
// surface-copy path when the rowed Rva00042FE4::test passes on the image
// (surfaceState at +0x40 with flag 4, same offsets the rowed test reads),
// else beginImageDraw/drawImageCore/endImageDraw at retail slots 53/63/64.
// Evidence: VTABLE slot 65 of 0x007C3C80; rowed 006e helpers 0x0011E050 and
// 0x0011DCA0; IsRectEmpty import; donor body.
typedef int Int;
typedef float Real;

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};

extern "C" __declspec(dllimport) Int __stdcall IsRectEmpty(const BfmeRect *rect);

class SurfaceResource;

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(const W3DRadarResetSurface &other);
	~W3DRadarResetSurface();
private:
	SurfaceResource *m_surface;
};

struct ImageSurfaceState
{
	char unused00[0x10];
	unsigned long status;
};

class Image
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual const W3DRadarResetSurface &getSurface() const;

	char padding04[0x08];
	Int width;
	Int height;
	char padding14[0x14];
	unsigned char ready;
	char padding29[0x17];
	ImageSurfaceState *surfaceState;
};

class Rva00042FE4
{
public:
	int test() const;
};

W3DRadarResetSurface getBackBufferSurface006e(Int index);
void copySurfaceRects006e(W3DRadarResetSurface source, const BfmeRect *sourceRect,
	W3DRadarResetSurface destination, const BfmeRect *destinationRect, Int mode);

class W3DDisplay
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52();
	virtual void beginImageDraw();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62();
	virtual void drawImageCore(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);
	virtual void endImageDraw();
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);
};

// ?drawImage@W3DDisplay@@UAEXPAVImage@@MMMMH@Z @0x00044E77
void W3DDisplay::drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color)
{
	unsigned char ready = image->ready;
	if (!ready)
		return;

	unsigned char useSurface = ((const Rva00042FE4 *)image)->test();
	if (useSurface != 0)
	{
		W3DRadarResetSurface source = image->getSurface();
		W3DRadarResetSurface destination = getBackBufferSurface006e(0);
		BfmeRect sourceRect = { 0, 0, image->width, image->height };
		BfmeRect destinationRect = { (long)x0, (long)y0, (long)x1, (long)y1 };

		if (!IsRectEmpty(&sourceRect) && !IsRectEmpty(&destinationRect))
			copySurfaceRects006e(source, &sourceRect, destination, &destinationRect, 2);
	}
	else
	{
		beginImageDraw();
		drawImageCore(image, x0, y0, x1, y1, color);
		endImageDraw();
	}
}
