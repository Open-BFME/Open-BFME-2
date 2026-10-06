// cl: /DNDEBUG /MD
//
// ?GameGetColorComponents@@YAXHPAE000@Z, retail 0x002D2A9F, 43 bytes.
//
// Direct port of the Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/color_ops.cpp,
// matched 44 bytes there): unpack an int color into its alpha/red/green/blue
// bytes. BFME2 retail is one byte shorter; the channel-unpack head
// (shr 0x18, sar 0x10) matches the reference shape.

typedef int Color;
typedef unsigned char UnsignedByte;

// ?GameGetColorComponents@@YAXHPAE000@Z
void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha)
{
	*alpha = (color & 0xFF000000) >> 24;
	*red = (color & 0x00FF0000) >> 16;
	*green = (color & 0x0000FF00) >> 8;
	*blue = (color & 0x000000FF);
}

int __cdecl Rva002D2B9ADarken(int color, int amount)
{
	if (amount < 90 && amount > 0)
	{
		UnsignedByte red, green, blue, alpha;
		GameGetColorComponents(color, &red, &green, &blue, &alpha);
		red += (red * amount) / -100;
		green += (green * amount) / -100;
		blue += (blue * amount) / -100;
		return (alpha << 24) | (red << 16) | (green << 8) | blue;
	}
	return color;
}

//-------------------------------------------------------------------------------------------------
// ?Rva0004D76EBlend@@YAHHH@Z, retail 0x0004D76E, 149 bytes.
// Channel-wise multiply of two packed ARGB colors via GameGetColorComponents;
// callers 0x00050125 0x0005053E. TU owns GameGetColorComponents and Darken.
int __cdecl Rva0004D76EBlend(int color1, int color2)
{
	UnsignedByte red1, green1, blue1, alpha1;
	UnsignedByte red2, green2, blue2, alpha2;
	GameGetColorComponents(color1, &red1, &green1, &blue1, &alpha1);
	GameGetColorComponents(color2, &red2, &green2, &blue2, &alpha2);
	UnsignedByte alpha = (UnsignedByte)((alpha1 * alpha2) / 255);
	UnsignedByte red = (UnsignedByte)((red1 * red2) / 255);
	UnsignedByte green = (UnsignedByte)((green1 * green2) / 255);
	UnsignedByte blue = (UnsignedByte)((blue1 * blue2) / 255);
	int result = (alpha << 8) | red;
	result <<= 8;
	result |= green;
	result <<= 8;
	result |= blue;
	return result;
}

// ?Rva0009FE01Get@@YAHH@Z @ 0x0009FE01 (72B): invert RGB keep alpha.
// Calls rowed ?GameGetColorComponents@@YAXHPAE000@Z; caller 0x0009FE49.
// Opaque address-derived name.
int __cdecl Rva0009FE01Get(int color)
{
	UnsignedByte red, green, blue, alpha;
	GameGetColorComponents(color, &red, &green, &blue, &alpha);
	int result = (alpha << 8) | (UnsignedByte)(255 - red);
	result <<= 8;
	result |= (UnsignedByte)(255 - green);
	result <<= 8;
	result |= (UnsignedByte)(255 - blue);
	return result;
}
