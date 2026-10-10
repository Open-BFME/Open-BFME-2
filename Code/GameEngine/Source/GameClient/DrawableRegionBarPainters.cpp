// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?Rva00271EAD@@YAXPAX0M@Z  retail 0x00271EAD..0x002720A4  503 bytes  cdecl
// ?Rva002720A4@@YAXPAX0M@Z  retail 0x002720A4..0x0027229B  503 bytes  cdecl
//
// Two of the three drawable region bar painters that the matched
// Drawable::rva0027411F (0x0027411F) chooses between: it passes the region
// held at Drawable+0x460 / the screen offset / the fill ratio. Both bodies
// fetch the band colours for the ratio (four bands through 0x00270CE4 and
// three through 0x00270E48: the 356-byte lookups banked beside the matched
// band-colour unit DrawableRegionBandColors_Rva00270ca6.cpp) then draw a
// shadow frame / a border frame / the back fill through TheDisplay slots
// 56 (drawOpenRect) and 57 (drawFillRect) and finally one one-pixel row per
// band scaled by the ratio. The three-band bar is one pixel shorter: frame
// heights 9 / 7 / 5 against 10 / 8 / 6 (retail float pool).
//
// Target evidence: each body owns a guard word and three colour words
// (0x009FEBD0 with 0x009FEBCC/C8/C4 and 0x009FEBE0 with 0x009FEBDC/D8/D4)
// initialised on first use behind guard bits 1/2/4: function-local statics
// with dynamic initialisers. The names come from the matched caller's pins.
// Donor carried: the frame / row geometry of BFME 1's DrawableRegionRenderA.cpp
// (bfmeRegionRenderA/B/C) including its volatile read of the offset in the
// first frame. WorldBuilder twin 0x00CB99E0 (debug) shows the same layout.
//
// Codegen note: the volatile offset read in the first frame (as in the BFME 1
// donor) reproduces retail's lea operand order there. A probe with a lookup
// defined earlier in the same unit shows cl then keeps the region's left edge
// in a frame slot across the call by itself (as the debug twin's lack of a
// left local suggests) so the original may have been one unit with the
// lookups.
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

void Rva00271EAD(void *state, void *out, float time)
{
	const IRegion2D *region = (const IRegion2D *)state;
	const ICoord2D *offset = (const ICoord2D *)out;
	Int left = region->lo.x;
	Color colors[4];
	Real width = (Real)(region->hi.x - left);
	rva00270CE4ColorBands(time, colors);
	static const Color shadowColor = GameMakeColor(0x00, 0x00, 0x00, 0x7f);
	static const Color borderColor = GameMakeColor(0xba, 0x92, 0x52, 0xff);
	static const Color backColor = GameMakeColor(0x00, 0x00, 0x00, 0xff);
	TheDisplay->drawOpenRect((Real)(left + *(const volatile Int *)&offset->x - 3), (Real)(region->lo.y + offset->y - 3), width + 6.0f, 10.0f, 1.0f, shadowColor);
	TheDisplay->drawOpenRect((Real)(region->lo.x + offset->x - 2), (Real)(region->lo.y + offset->y - 2), width + 4.0f, 8.0f, 1.0f, borderColor);
	TheDisplay->drawFillRect((Real)(region->lo.x + offset->x - 1), (Real)(region->lo.y + offset->y - 1), width + 2.0f, 6.0f, backColor);
	Int i;
	for (i = 0, width *= time; i < 4; ++i)
	{
		TheDisplay->drawFillRect((Real)(region->lo.x + offset->x), (Real)(region->lo.y + offset->y + i), width, 1.0f, colors[i]);
	}
}

void Rva002720A4(void *state, void *out, float time)
{
	const IRegion2D *region = (const IRegion2D *)state;
	const ICoord2D *offset = (const ICoord2D *)out;
	Int left = region->lo.x;
	Color colors[3];
	Real width = (Real)(region->hi.x - left);
	rva00270E48ColorBands(time, colors);
	static const Color shadowColor = GameMakeColor(0x00, 0x00, 0x00, 0x7f);
	static const Color borderColor = GameMakeColor(0xba, 0x92, 0x52, 0xff);
	static const Color backColor = GameMakeColor(0x00, 0x00, 0x00, 0xff);
	TheDisplay->drawOpenRect((Real)(left + *(const volatile Int *)&offset->x - 3), (Real)(region->lo.y + offset->y - 3), width + 6.0f, 9.0f, 1.0f, shadowColor);
	TheDisplay->drawOpenRect((Real)(region->lo.x + offset->x - 2), (Real)(region->lo.y + offset->y - 2), width + 4.0f, 7.0f, 1.0f, borderColor);
	TheDisplay->drawFillRect((Real)(region->lo.x + offset->x - 1), (Real)(region->lo.y + offset->y - 1), width + 2.0f, 5.0f, backColor);
	Int i;
	for (i = 0, width *= time; i < 3; ++i)
	{
		TheDisplay->drawFillRect((Real)(region->lo.x + offset->x), (Real)(region->lo.y + offset->y + i), width, 1.0f, colors[i]);
	}
}
