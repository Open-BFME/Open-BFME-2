// ?rva00271EAD@@YAXPBUIRegion2D@@PBUICoord2D@@M@Z
// partial score=0.9972586356858847 date=2026-10-10
// ?rva002720A4@@YAXPBUIRegion2D@@PBUICoord2D@@M@Z
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Drawable region bars, retail 0x00271EAD (four bands) and 0x002720A4 (three
// bands), 503B each, cdecl. BFME 1's DrawableRegionRenderA.cpp
// (bfmeRegionRenderA/B, retail 0x00412750 / 0x004129B0) is the donor: fetch
// the band colours for the fill value (unrowed native lookups 0x00270CE4 / 0x00270E48,
// the BFME 2 counterparts of BFME 1's bfmeColorLookup00411270 / 00411400),
// draw the shadow and border frames and the back fill through TheDisplay slots
// 56/57, then one one-pixel row per band scaled by the value.
// Target evidence: both bodies test and set one flag word (0x009FEBD0)
// before storing three colours, so the flags and colours are file statics
// shared by both painters; donor carried: the frame/row geometry.
typedef int Int;
typedef float Real;
typedef int Color;
typedef unsigned char UnsignedByte;

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
};

#define BFME_REGION_DISPLAY_SLOT(n) virtual void slot##n();
class Display
{
public:
	BFME_REGION_DISPLAY_SLOT(00) BFME_REGION_DISPLAY_SLOT(01) BFME_REGION_DISPLAY_SLOT(02) BFME_REGION_DISPLAY_SLOT(03)
	BFME_REGION_DISPLAY_SLOT(04) BFME_REGION_DISPLAY_SLOT(05) BFME_REGION_DISPLAY_SLOT(06) BFME_REGION_DISPLAY_SLOT(07)
	BFME_REGION_DISPLAY_SLOT(08) BFME_REGION_DISPLAY_SLOT(09) BFME_REGION_DISPLAY_SLOT(10) BFME_REGION_DISPLAY_SLOT(11)
	BFME_REGION_DISPLAY_SLOT(12) BFME_REGION_DISPLAY_SLOT(13) BFME_REGION_DISPLAY_SLOT(14) BFME_REGION_DISPLAY_SLOT(15)
	BFME_REGION_DISPLAY_SLOT(16) BFME_REGION_DISPLAY_SLOT(17) BFME_REGION_DISPLAY_SLOT(18) BFME_REGION_DISPLAY_SLOT(19)
	BFME_REGION_DISPLAY_SLOT(20) BFME_REGION_DISPLAY_SLOT(21) BFME_REGION_DISPLAY_SLOT(22) BFME_REGION_DISPLAY_SLOT(23)
	BFME_REGION_DISPLAY_SLOT(24) BFME_REGION_DISPLAY_SLOT(25) BFME_REGION_DISPLAY_SLOT(26) BFME_REGION_DISPLAY_SLOT(27)
	BFME_REGION_DISPLAY_SLOT(28) BFME_REGION_DISPLAY_SLOT(29) BFME_REGION_DISPLAY_SLOT(30) BFME_REGION_DISPLAY_SLOT(31)
	BFME_REGION_DISPLAY_SLOT(32) BFME_REGION_DISPLAY_SLOT(33) BFME_REGION_DISPLAY_SLOT(34) BFME_REGION_DISPLAY_SLOT(35)
	BFME_REGION_DISPLAY_SLOT(36) BFME_REGION_DISPLAY_SLOT(37) BFME_REGION_DISPLAY_SLOT(38) BFME_REGION_DISPLAY_SLOT(39)
	BFME_REGION_DISPLAY_SLOT(40) BFME_REGION_DISPLAY_SLOT(41) BFME_REGION_DISPLAY_SLOT(42) BFME_REGION_DISPLAY_SLOT(43)
	BFME_REGION_DISPLAY_SLOT(44) BFME_REGION_DISPLAY_SLOT(45) BFME_REGION_DISPLAY_SLOT(46) BFME_REGION_DISPLAY_SLOT(47)
	BFME_REGION_DISPLAY_SLOT(48) BFME_REGION_DISPLAY_SLOT(49) BFME_REGION_DISPLAY_SLOT(50) BFME_REGION_DISPLAY_SLOT(51)
	BFME_REGION_DISPLAY_SLOT(52) BFME_REGION_DISPLAY_SLOT(53) BFME_REGION_DISPLAY_SLOT(54) BFME_REGION_DISPLAY_SLOT(55)
	virtual void drawOpenRect(Real x, Real y, Real width, Real height, Real lineWidth, Color color);	// slot 56
	virtual void drawFillRect(Real x, Real y, Real width, Real height, Color color);		// slot 57
};
#undef BFME_REGION_DISPLAY_SLOT
extern Display *TheDisplay;

void rva00270CE4ColorBands(Real value, Color *colors);
void rva00270E48ColorBands(Real value, Color *colors);

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// The three frame colours are initialised on first use behind one flag word
// shared by both bar painters.
static unsigned int s_barColorsReady;
static Color s_barShadowColor;
static Color s_barBorderColor;
static Color s_barBackColor;

static __forceinline void drawBarFrame(const IRegion2D *region, const ICoord2D *offset, Int left, Real width)
{
	if (!(s_barColorsReady & 1))
	{
		s_barColorsReady |= 1;
		s_barShadowColor = GameMakeColor(0x00, 0x00, 0x00, 0x7f);
	}
	if (!(s_barColorsReady & 2))
	{
		s_barColorsReady |= 2;
		s_barBorderColor = GameMakeColor(0xba, 0x92, 0x52, 0xff);
	}
	if (!(s_barColorsReady & 4))
	{
		s_barColorsReady |= 4;
		s_barBackColor = GameMakeColor(0x00, 0x00, 0x00, 0xff);
	}
	TheDisplay->drawOpenRect((Real)(left + offset->x - 3), (Real)(offset->y + region->lo.y - 3), width + 6.0f, 10.0f, 1.0f, s_barShadowColor);
	TheDisplay->drawOpenRect((Real)(region->lo.x + offset->x - 2), (Real)(region->lo.y + offset->y - 2), width + 4.0f, 8.0f, 1.0f, s_barBorderColor);
	TheDisplay->drawFillRect((Real)(region->lo.x + offset->x - 1), (Real)(region->lo.y + offset->y - 1), width + 2.0f, 6.0f, s_barBackColor);
}

void rva00271EAD(const IRegion2D *region, const ICoord2D *offset, Real value)
{
	Int i;
	Int left = (region?region:region)->lo.x;
	Color colors[4];
	Real width = (Real)((region?region:region)->hi.x - left);
	rva00270CE4ColorBands(value, colors);
	drawBarFrame(region, offset, left, width);
	for (i = 0, width *= value; i < 4; ++i)
	{
		TheDisplay->drawFillRect((Real)((region?region:region)->lo.x + offset->x), (Real)((region?region:region)->lo.y + offset->y + i), width, 1.0f, colors[i]);
	}
}

void rva002720A4(const IRegion2D *region, const ICoord2D *offset, Real value)
{
	Int i;
	Int left = (region?region:region)->lo.x;
	Color colors[3];
	Real width = (Real)((region?region:region)->hi.x - left);
	rva00270E48ColorBands(value, colors);
	drawBarFrame(region, offset, left, width);
	for (i = 0, width *= value; i < 3; ++i)
	{
		TheDisplay->drawFillRect((Real)((region?region:region)->lo.x + offset->x), (Real)((region?region:region)->lo.y + offset->y + i), width, 1.0f, colors[i]);
	}
}
