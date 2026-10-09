// cl: /O1 /DNDEBUG /MD /EHsc
// BF1 f98983a7d Rva006C13E0ColorBlend semantic donor.
// Native 0x4DE72..0x4DF6F is a 253-byte CDECL body used by the radar blip
// helpers. Packed ARGB extraction and weighted alpha agree with the donor;
// the original target name is unknown. Preserve one final destination store
// for both branches, as witnessed by the native shared epilog. Color remains
// in EAX at RET; no extra caller cleanup or callee pins are introduced.
typedef int Color;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
void GameGetColorComponents(Color,UnsignedByte *,UnsignedByte *,UnsignedByte *,UnsignedByte *);
inline Color GameMakeColor(UnsignedByte r,UnsignedByte g,UnsignedByte b,UnsignedByte a) {
 Color c=(a<<8)|r; c<<=8; c|=g; c<<=8; c|=b; return c;
}
Color Rva0004DE72Blend(Color *color, Color source, UnsignedByte alpha)
{
	Color *out = color;
	UnsignedByte oldAlpha, blue, green, red;
	UnsignedByte sourceAlpha, sourceBlue, sourceGreen, sourceRed;

	GameGetColorComponents(*out, &red, &green, &blue, &oldAlpha);
	GameGetColorComponents(source, &sourceRed, &sourceGreen, &sourceBlue, &sourceAlpha);

	UnsignedByte effectiveAlpha = (UnsignedInt)(sourceAlpha * alpha) / 255;
	Color result;
	if (oldAlpha == 0 || effectiveAlpha == 255)
		result = GameMakeColor(sourceRed, sourceGreen, sourceBlue, effectiveAlpha);
	else {

	red = (UnsignedInt)(red * oldAlpha + sourceRed * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	green = (UnsignedInt)(green * oldAlpha + sourceGreen * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	blue = (UnsignedInt)(blue * oldAlpha + sourceBlue * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	oldAlpha = 255 - (UnsignedInt)((255 - oldAlpha) * (255 - effectiveAlpha)) / 255;
	result = (Color)(UnsignedInt)blue;
	result |= (oldAlpha << 24) | (red << 16) | (green << 8);
	}
	return *out = result;
}
