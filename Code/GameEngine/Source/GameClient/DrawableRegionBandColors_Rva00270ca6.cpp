// cl: -DNDEBUG -MD -EHs-c- -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// BFME1 donor: game/GameEngine/Source/GameClient/DrawableRegionBandColors.cpp
// at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 (band tables / blend / lookups)
// and DrawableRegionRenderA.cpp (bar geometry). Original owner and
// source-level function/type names are not established; the address-named
// functions keep the names of their caller pins.
//
// ?rva00270BD9Blend@@YAHABURGBAColorInt@@0M@Z  0x00270BD9  205
// ?bfmeColorLookup00411220@@YAXMPAH@Z          0x00270CA6   62
// ?rva00270CE4ColorBands@@YAXMPAH@Z            0x00270CE4  356
// ?rva00270E48ColorBands@@YAXMPAH@Z            0x00270E48  356
// ?Rva00271CB6@@YAXPAX0M@Z                     0x00271CB6  503
// ?Rva00271EAD@@YAXPAX0M@Z                     0x00271EAD  503
// ?Rva002720A4@@YAXPAX0M@Z                     0x002720A4  503
//
// BFME2 evidence: Ghidra starts 0x00270BD9/205 and 0x00270CA6/62. Five direct
// calls from 0x00270CC8 / 0x00270D67 / 0x00270DFA / 0x00270ECB / 0x00270F5E
// reach the blend; callers provide from in EDI / to in ESI and a stack float
// then clean the stack. The native helper has no absolute entry references.
// The TU-local static lets MSVC naturally emit that private ABI.
// Target data access observes four unsigned 32-bit channels at +0/+4/+8/+12
// then narrows each interpolated channel to a byte and packs A8R8G8B8.
// RGBAColorInt and channel-role names come from the verified donor header;
// this layout/packing and the related caller family have independent target
// evidence. __ftol2 reaches the existing native CRT body 0x00629228/117.
//
// The two 356-byte band lookups 0x00270CE4 (four bands: red / amber / green
// tables at RVA 0x007FAE18 / 0x007FAE58 / 0x007FAE98) and 0x00270E48 (three
// bands: 0x007FAED8 / 0x007FAF08 / 0x007FAF38) follow the donor's five-band
// thresholds (0.8 / 0.6 / 0.4 / 0.2) and t = (value - low) * 5 transitions,
// but BFME 2 packs the solid bands from the tables at run time: retail's
// byte loads (green first then alpha / red into dh / dl) with the struct base
// as the induction pointer are GameMakeColor( t[i].red / t[i].green /
// t[i].blue / t[i].alpha ) with ZH's Color.h packing.
//
// The bar painters 0x00271CB6 (four bands over 0x00270CA6) 0x00271EAD (four
// bands) and 0x002720A4 (three bands) are the drawable region bars the
// matched Drawable::rva0027411F (0x0027411F) chooses between; it passes the region held at Drawable+0x460 / the screen
// offset / the fill ratio. Each body owns a guard word and three colour words
// (0x009FEBC0 / 0x009FEBD0 / 0x009FEBE0 each with the three words below it)
// initialised behind guard bits 1/2/4: function-local statics. Frames go
// through TheDisplay slots 56 (drawOpenRect) and 57 (drawFillRect).
// The WorldBuilder debug twin 0x00CB99E0 (callsite-matched to 0x00271EAD)
// gives the source shape: a band-count local and a Real height copied from
// it (frame heights height + 6 / + 4 / + 2: 10 / 8 / 6 against 9 / 7 / 5 for
// the three-band bar) and no saved left edge. Retail nonetheless keeps the
// region's left edge in a frame slot across the lookup call and reuses it
// for the first frame only: cl does that only when the lookup is defined
// earlier in the same unit, which places the painters in this unit (as the
// retail layout 0x00270BD9..0x00270FAC / 0x00271CB6..0x0027229B allows).
// The offset is cast before the region (register and operand order) and the
// fill width is scaled in the loop initializer (store before xor ebx).

#include "basetype.h"

typedef Int Color;

static const RGBAColorInt s_colors00CF11D0[4] =
{
	{ 0x15, 0x56, 0xad, 0xff }, { 0x6b, 0xe0, 0xf5, 0xff },
	{ 0x12, 0x9a, 0xdc, 0xff }, { 0x08, 0x27, 0x75, 0xff },
};

static const RGBAColorInt s_colors00CF1220[4] =
{
	{ 0x1c, 0xcf, 0xfb, 0xff }, { 0xac, 0xff, 0xfe, 0xff },
	{ 0x10, 0xdf, 0xe5, 0xff }, { 0x03, 0xa5, 0xba, 0xff },
};

static const RGBAColorInt s_redColors00CF1270[4] =
{
	{ 0xdf, 0x03, 0x20, 0xff }, { 0xff, 0xb7, 0x6c, 0xff },
	{ 0xff, 0x2a, 0x19, 0xff }, { 0xd1, 0x01, 0x0d, 0xff },
};

static const RGBAColorInt s_amberColors00CF12C0[4] =
{
	{ 0xd0, 0x90, 0x00, 0xff }, { 0xff, 0xff, 0xc5, 0xff },
	{ 0xff, 0xb2, 0x00, 0xff }, { 0xbd, 0x6f, 0x00, 0xff },
};

static const RGBAColorInt s_greenColors00CF1310[4] =
{
	{ 0x0b, 0x80, 0x08, 0xff }, { 0xff, 0xff, 0x80, 0xff },
	{ 0x4d, 0xb4, 0x03, 0xff }, { 0x04, 0x5d, 0x03, 0xff },
};

static const RGBAColorInt s_redColors00CF135C[3] =
{
	{ 0xff, 0x13, 0x4e, 0xff }, { 0xff, 0x83, 0x6c, 0xff }, { 0xcc, 0x00, 0x01, 0xff },
};

static const RGBAColorInt s_amberColors00CF1398[3] =
{
	{ 0xe6, 0xa2, 0x00, 0xff }, { 0xff, 0xff, 0xb0, 0xff }, { 0xb0, 0x61, 0x00, 0xff },
};

static const RGBAColorInt s_greenColors00CF13D4[3] =
{
	{ 0x0c, 0x9c, 0x24, 0xff }, { 0xdd, 0xf5, 0x8e, 0xff }, { 0x05, 0x71, 0x16, 0xff },
};

// from * (1 - t) + to * t per channel, packed as A8R8G8B8.  Each channel is
// widened to Real before the blend; retail schedules the second channel's
// sign test ahead of the first product only in that form.
static Color rva00270BD9Blend( const RGBAColorInt &from, const RGBAColorInt &to, Real t )
{
	Real inv = 1.0f - t;

	Real fromAlpha = from.alpha;
	Real toAlpha = to.alpha;
	UnsignedByte alpha = (UnsignedByte)(Int)( fromAlpha * inv + toAlpha * t );

	Real fromRed = from.red;
	Real toRed = to.red;
	UnsignedByte red = (UnsignedByte)(Int)( fromRed * inv + toRed * t );

	Real fromGreen = from.green;
	Real toGreen = to.green;
	UnsignedByte green = (UnsignedByte)(Int)( fromGreen * inv + toGreen * t );

	Real fromBlue = from.blue;
	Real toBlue = to.blue;
	UnsignedByte blue = (UnsignedByte)(Int)( fromBlue * inv + toBlue * t );

	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// ?bfmeColorLookup00411220@@YAXMPAH@Z
void bfmeColorLookup00411220( Real value, Color *colors )
{
	for( Int i = 0; i < 4; ++i )
		colors[i] = rva00270BD9Blend( s_colors00CF11D0[i], s_colors00CF1220[i], value );
}

inline Color GameMakeColor( UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha )
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// ?rva00270CE4ColorBands@@YAXMPAH@Z
void rva00270CE4ColorBands( Real value, Color *colors )
{
	if( value >= 0.8f )
	{
		for( Int i = 0; i < 4; ++i )
			colors[i] = GameMakeColor( s_greenColors00CF1310[i].red, s_greenColors00CF1310[i].green, s_greenColors00CF1310[i].blue, s_greenColors00CF1310[i].alpha );
	}
	else if( value >= 0.6f )
	{
		Real transition = ( value - 0.6f ) * 5.0f;
		for( Int i = 0; i < 4; ++i )
			colors[i] = rva00270BD9Blend( s_amberColors00CF12C0[i], s_greenColors00CF1310[i], transition );
	}
	else if( value >= 0.4f )
	{
		for( Int i = 0; i < 4; ++i )
			colors[i] = GameMakeColor( s_amberColors00CF12C0[i].red, s_amberColors00CF12C0[i].green, s_amberColors00CF12C0[i].blue, s_amberColors00CF12C0[i].alpha );
	}
	else if( value >= 0.2f )
	{
		Real transition = ( value - 0.2f ) * 5.0f;
		for( Int i = 0; i < 4; ++i )
			colors[i] = rva00270BD9Blend( s_redColors00CF1270[i], s_amberColors00CF12C0[i], transition );
	}
	else
	{
		for( Int i = 0; i < 4; ++i )
			colors[i] = GameMakeColor( s_redColors00CF1270[i].red, s_redColors00CF1270[i].green, s_redColors00CF1270[i].blue, s_redColors00CF1270[i].alpha );
	}
}

// ?rva00270E48ColorBands@@YAXMPAH@Z
void rva00270E48ColorBands( Real value, Color *colors )
{
	if( value >= 0.8f )
	{
		for( Int i = 0; i < 3; ++i )
			colors[i] = GameMakeColor( s_greenColors00CF13D4[i].red, s_greenColors00CF13D4[i].green, s_greenColors00CF13D4[i].blue, s_greenColors00CF13D4[i].alpha );
	}
	else if( value >= 0.6f )
	{
		Real transition = ( value - 0.6f ) * 5.0f;
		for( Int i = 0; i < 3; ++i )
			colors[i] = rva00270BD9Blend( s_amberColors00CF1398[i], s_greenColors00CF13D4[i], transition );
	}
	else if( value >= 0.4f )
	{
		for( Int i = 0; i < 3; ++i )
			colors[i] = GameMakeColor( s_amberColors00CF1398[i].red, s_amberColors00CF1398[i].green, s_amberColors00CF1398[i].blue, s_amberColors00CF1398[i].alpha );
	}
	else if( value >= 0.2f )
	{
		Real transition = ( value - 0.2f ) * 5.0f;
		for( Int i = 0; i < 3; ++i )
			colors[i] = rva00270BD9Blend( s_redColors00CF135C[i], s_amberColors00CF1398[i], transition );
	}
	else
	{
		for( Int i = 0; i < 3; ++i )
			colors[i] = GameMakeColor( s_redColors00CF135C[i].red, s_redColors00CF135C[i].green, s_redColors00CF135C[i].blue, s_redColors00CF135C[i].alpha );
	}
}


// Display view: only the two slots the bar painters call are spelled.
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

// ?Rva00271CB6@@YAXPAX0M@Z
// four-band bar over the 0x00270CA6 blend lookup: retail 0x00271CB6..0x00271EAD (503 bytes) cdecl; guard 0x009FEBC0 with colour words 0x009FEBBC/B8/B4
void Rva00271CB6(void *state, void *out, float time)
{
	const ICoord2D *offset = (const ICoord2D *)out;
	const IRegion2D *region = (const IRegion2D *)state;
	Real width = (Real)(region->hi.x - region->lo.x);
	Int numBands = 4;
	Real height = (Real)numBands;
	Color colors[4];
	bfmeColorLookup00411220(time, colors);
	static const Color shadowColor = GameMakeColor(0x00, 0x00, 0x00, 0x7f);
	static const Color borderColor = GameMakeColor(0xba, 0x92, 0x52, 0xff);
	static const Color backColor = GameMakeColor(0x00, 0x00, 0x00, 0xff);
	TheDisplay->drawOpenRect(region->lo.x + offset->x - 3, region->lo.y + offset->y - 3, width + 6.0f, height + 6.0f, 1.0f, shadowColor);
	TheDisplay->drawOpenRect(region->lo.x + offset->x - 2, region->lo.y + offset->y - 2, width + 4.0f, height + 4.0f, 1.0f, borderColor);
	TheDisplay->drawFillRect(region->lo.x + offset->x - 1, region->lo.y + offset->y - 1, width + 2.0f, height + 2.0f, backColor);
	Int i;
	for (i = 0, width *= time; i < numBands; ++i)
		TheDisplay->drawFillRect(region->lo.x + offset->x, region->lo.y + offset->y + i, width, 1.0f, colors[i]);
}

// ?Rva00271EAD@@YAXPAX0M@Z
// four-band bar: retail 0x00271EAD..0x002720A4 (503 bytes) cdecl
void Rva00271EAD(void *state, void *out, float time)
{
	const ICoord2D *offset = (const ICoord2D *)out;
	const IRegion2D *region = (const IRegion2D *)state;
	Real width = (Real)(region->hi.x - region->lo.x);
	Int numBands = 4;
	Real height = (Real)numBands;
	Color colors[4];
	rva00270CE4ColorBands(time, colors);
	static const Color shadowColor = GameMakeColor(0x00, 0x00, 0x00, 0x7f);
	static const Color borderColor = GameMakeColor(0xba, 0x92, 0x52, 0xff);
	static const Color backColor = GameMakeColor(0x00, 0x00, 0x00, 0xff);
	TheDisplay->drawOpenRect(region->lo.x + offset->x - 3, region->lo.y + offset->y - 3, width + 6.0f, height + 6.0f, 1.0f, shadowColor);
	TheDisplay->drawOpenRect(region->lo.x + offset->x - 2, region->lo.y + offset->y - 2, width + 4.0f, height + 4.0f, 1.0f, borderColor);
	TheDisplay->drawFillRect(region->lo.x + offset->x - 1, region->lo.y + offset->y - 1, width + 2.0f, height + 2.0f, backColor);
	Int i;
	for (i = 0, width *= time; i < numBands; ++i)
		TheDisplay->drawFillRect(region->lo.x + offset->x, region->lo.y + offset->y + i, width, 1.0f, colors[i]);
}

// ?Rva002720A4@@YAXPAX0M@Z
// three-band bar: retail 0x002720A4..0x0027229B (503 bytes) cdecl
void Rva002720A4(void *state, void *out, float time)
{
	const ICoord2D *offset = (const ICoord2D *)out;
	const IRegion2D *region = (const IRegion2D *)state;
	Real width = (Real)(region->hi.x - region->lo.x);
	Int numBands = 3;
	Real height = (Real)numBands;
	Color colors[3];
	rva00270E48ColorBands(time, colors);
	static const Color shadowColor = GameMakeColor(0x00, 0x00, 0x00, 0x7f);
	static const Color borderColor = GameMakeColor(0xba, 0x92, 0x52, 0xff);
	static const Color backColor = GameMakeColor(0x00, 0x00, 0x00, 0xff);
	TheDisplay->drawOpenRect(region->lo.x + offset->x - 3, region->lo.y + offset->y - 3, width + 6.0f, height + 6.0f, 1.0f, shadowColor);
	TheDisplay->drawOpenRect(region->lo.x + offset->x - 2, region->lo.y + offset->y - 2, width + 4.0f, height + 4.0f, 1.0f, borderColor);
	TheDisplay->drawFillRect(region->lo.x + offset->x - 1, region->lo.y + offset->y - 1, width + 2.0f, height + 2.0f, backColor);
	Int i;
	for (i = 0, width *= time; i < numBands; ++i)
		TheDisplay->drawFillRect(region->lo.x + offset->x, region->lo.y + offset->y + i, width, 1.0f, colors[i]);
}
