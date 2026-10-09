// _DiagonalBlur
// partial score=0.97 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c2b80.md plus retail only.
// No decoder source was consulted.
extern "C" void DiagonalBlur(void *instance, unsigned char *source, unsigned char *dest, int pitch)
{
	unsigned char *src = source;
	unsigned char *dst = dest;
	int row, col;
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {
			dst[col] = (unsigned char)((16 + 8 * src[col]
				+ 4 * (src[col - pitch - 1] + src[col + pitch - 1] + src[col - pitch + 1] + src[col + pitch + 1])
				+ 2 * (src[col - 2 * pitch - 2] + src[col + 2 * pitch + 2] + src[col + 2 * pitch - 2] + src[col - 2 * pitch + 2])) >> 5);
		}
		dst += pitch;
		src += pitch;
	}
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {
			int value = (1 + 6 * src[col] - src[col - 1] - src[col - pitch] - src[col + pitch] - src[col + 1]) >> 1;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			dst[col] = (unsigned char)value;
		}
		dst += pitch;
		src += pitch;
	}
}
