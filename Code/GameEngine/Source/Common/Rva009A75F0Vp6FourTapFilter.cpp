// cl: /DNDEBUG /MD
// VP6 four-tap fractional-pixel filter, 8-bit source to 16-bit destination,
// retail 0x001B8050 (174 bytes; BFME 1 0x009A75F0, a dump there). The scalar
// predictor Rva009A7B00Vp6Filter calls it for the bicubic one-dimensional
// cases with the weight row for the fractional position; the two-tap sibling
// is inlined there. Each output is the weighted sum of the pixels one step
// before, at, one and two steps after, rounded, shifted by 7 and clamped to
// 0..255. The sum is written in retail's evaluation order.

void __cdecl Rva009A75F0Vp6FourTapFilter(
	const unsigned char *source,
	unsigned short *destination,
	unsigned int sourcePitch,
	unsigned int pixelStep,
	unsigned int rows,
	unsigned int columns,
	const int *weights)
{
	unsigned int row;
	unsigned int column;
	int value;
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
			value = (source[2 * pixelStep] * weights[3] + source[0] * weights[1] +
				source[pixelStep] * weights[2] + source[-(int)pixelStep] * weights[0] + 0x40) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			destination[column] = (unsigned short)value;
			source++;
		}
		source += sourcePitch - columns;
		destination += columns;
	}
}
