// ?rva00270E48ColorBands@@YAXMPAH@Z
// partial score=0.898876404494382 date=2026-10-04
// cl: /O1 /arch:SSE2 /DNDEBUG /MD /EHs-c- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Near-match BFME2 reconstruction of the whole clean BFME1 donor
// game/GameEngine/Source/GameClient/DrawableRegionBandColors.cpp at
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24. Original owner/method names remain
// unknown; address labels identify native bodies rather than donor identities.
// Boundaries: native helper 0x00270BD9/205 (exact) and caller0 0x00270CA6/62
// (exact); caller4 0x00270CE4/356 and caller3 0x00270E48/356 are near matches.
// Native caller4/caller3 directly call helper twice each with EDI/ESI inputs;
// the TU-local function naturally emits this ABI. Existing __ftol2/117 is the
// only external helper, native RVA 0x00629228. No new pin or address literal.
// Target palettes match the donor initializers: caller4 red/amber/green are
// RVAs 0x007FAE18/0x007FAE58/0x007FAE98 (4 entries each); caller3 palettes are
// 0x007FAED8/0x007FAF08/0x007FAF38 (3 entries). Four uint32 fields at +0/+4/
// +8/+12 and byte packing are native observations; RGBAColorInt names and
// declared roles are donor facts. Native five-band thresholds and transition
// interpolation support the same semantics. /arch:SSE2 and runtime packing
// loops replace donor literal stores based on native COMISS and array loops.
// Both near bodies emit 356 bytes; remaining pointer induction is based at
// green+4 instead of the native struct base, with differing float-temp/output
// pointer spills. These are banked source candidates, not matched claims.

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

static inline Color packPaletteColor(const RGBAColorInt &color) {
 UnsignedByte alpha=color.alpha,red=color.red,green=color.green,blue=color.blue;
 return (alpha<<24)|(red<<16)|(green<<8)|blue;
}

// ?rva00270CE4ColorBands@@YAXMPAH@Z
void rva00270CE4ColorBands( Real value, Color *colors )
{
	if( value >= 0.8f )
	{
		for (Int i=0;i<4;++i) {
			const RGBAColorInt &color=s_greenColors00CF1310[i];
			colors[i]=packPaletteColor(color);
		}
	}
	else if( value >= 0.6f )
	{
		Real transition = ( value - 0.6f ) * 5.0f;
		for( Int i = 0; i < 4; ++i )
			colors[i] = rva00270BD9Blend( s_amberColors00CF12C0[i], s_greenColors00CF1310[i], transition );
	}
	else if( value >= 0.4f )
	{
		for (Int i=0;i<4;++i) {
			const RGBAColorInt &color=s_amberColors00CF12C0[i];
			colors[i]=packPaletteColor(color);
		}
	}
	else if( value >= 0.2f )
	{
		Real transition = ( value - 0.2f ) * 5.0f;
		for( Int i = 0; i < 4; ++i )
			colors[i] = rva00270BD9Blend( s_redColors00CF1270[i], s_amberColors00CF12C0[i], transition );
	}
	else
	{
		for (Int i=0;i<4;++i) {
			const RGBAColorInt &color=s_redColors00CF1270[i];
			colors[i]=packPaletteColor(color);
		}
	}
}

// ?rva00270E48ColorBands@@YAXMPAH@Z
void rva00270E48ColorBands( Real value, Color *colors )
{
	if( value >= 0.8f )
	{
		for (Int i=0;i<3;++i) {
			const RGBAColorInt &color=s_greenColors00CF13D4[i];
			colors[i]=packPaletteColor(color);
		}
	}
	else if( value >= 0.6f )
	{
		Real transition = ( value - 0.6f ) * 5.0f;
		for( Int i = 0; i < 3; ++i )
			colors[i] = rva00270BD9Blend( s_amberColors00CF1398[i], s_greenColors00CF13D4[i], transition );
	}
	else if( value >= 0.4f )
	{
		for (Int i=0;i<3;++i) {
			const RGBAColorInt &color=s_amberColors00CF1398[i];
			colors[i]=packPaletteColor(color);
		}
	}
	else if( value >= 0.2f )
	{
		Real transition = ( value - 0.2f ) * 5.0f;
		for( Int i = 0; i < 3; ++i )
			colors[i] = rva00270BD9Blend( s_redColors00CF135C[i], s_amberColors00CF1398[i], transition );
	}
	else
	{
		for (Int i=0;i<3;++i) {
			const RGBAColorInt &color=s_redColors00CF135C[i];
			colors[i]=packPaletteColor(color);
		}
	}
}

// ?bfmeColorLookup00411220@@YAXMPAH@Z
void bfmeColorLookup00411220( Real value, Color *colors )
{
	for( Int i = 0; i < 4; ++i )
		colors[i] = rva00270BD9Blend( s_colors00CF11D0[i], s_colors00CF1220[i], value );
}


