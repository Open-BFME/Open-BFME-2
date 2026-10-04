// cl: -DNDEBUG -MD -EHs-c- -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// BFME1 donor: game/GameEngine/Source/GameClient/DrawableRegionBandColors.cpp
// at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, compiled with the flags above.
// Original owner and source-level function/type names are not established.
// bfmeColorLookup00411220 and table address tokens below are donor labels.
//
// BFME2 evidence: Ghidra starts 0x00270BD9/205 and 0x00270CA6/62. Five direct
// calls from 0x00270CC8, 0x00270D67, 0x00270DFA, 0x00270ECB, 0x00270F5E reach
// the helper; callers provide from in EDI, to in ESI and a stack float, then
// clean the stack. The native helper has no absolute entry references.
// The TU-local donor function lets MSVC naturally emit that private ABI.
// Target data access observes four unsigned 32-bit channels at +0/+4/+8/+12,
// then narrows each interpolated channel to a byte and packs A8R8G8B8.
// RGBAColorInt and channel-role names come from the verified donor header;
// this layout/packing and the related caller family have independent target
// evidence. __ftol2 reaches the existing native CRT body 0x00629228/117.
// The whole four-function donor was mined. The two additional 356-byte
// band lookups are banked with their SSE2/runtime-palette-loop adaptations.

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
