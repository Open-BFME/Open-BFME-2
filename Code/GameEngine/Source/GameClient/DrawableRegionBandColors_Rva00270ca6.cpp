// cl: -DNDEBUG -MD -EHs-c- -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// Band colour tables for the drawable region bars at retail 0x00411110 and
// 0x00411270.
//
// bfmeRegionRenderB (DrawableRegionRenderA.cpp, retail 0x004129B0) calls
// bfmeColorLookup00411270 through ILT 0x00017256 with its raw fill ratio and a
// four-entry Color array, then paints one bar row per entry. The lookup is a
// five-band threshold table (0.8 / 0.6 / 0.4 / 0.2): the three solid bands
// store the packed colours of the three RGBAColorInt tables below, and the two
// transition bands lerp between neighbouring tables with t = (value - low) * 5.
//
// lerpColor00411110 is the retail body at 0x00411110. It is a TU-local static
// helper: MSVC gives it a custom register convention (from in EDI, to in ESI,
// t on the stack, caller-cleaned), which is why retail's call sites preload
// ESI/EDI with the two table entries. A scan of retail .text finds exactly
// five direct calls to it (0x00411220 x1, 0x00411270 x2, 0x00411400 x2) and no
// ILT thunk, as expected of a static function; 0x00411220 and 0x00411400 are
// sibling band lookups over further tables and belong in this TU.
//
// No owning class or source-level names are proven: the function names keep
// their retail address tokens, and the tables are named by the colour they
// hold and their retail .rdata address (VA 0x010F1270 / 0x010F12C0 /
// 0x010F1310; initialisers read from the image).

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
static Color lerpColor00411110( const RGBAColorInt &from, const RGBAColorInt &to, Real t )
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
		colors[i] = lerpColor00411110( s_colors00CF11D0[i], s_colors00CF1220[i], value );
}
