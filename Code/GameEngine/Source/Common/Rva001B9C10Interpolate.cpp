// cl: /O2 /DNDEBUG /MD /EHs-c-
// Source lead: Open-BFME-1 at 7c4d488c5bc928bb8eaf37171ae5700b4e33937f,
// game/GameEngine/Source/Common/Rva009A91D0.cpp. This self-contained snapshot
// preserves the verified 6583b3c1 header and compiler inputs.
// Native RVA 0x001B9C10 is a complete 247-byte scalar interpolation operation:
// advance source by 4 and output by 5; round weighted unsigned-byte samples;
// leave the final fourth sample unchanged. The native dispatch installer at
// RVA 0x001C1750 independently installs this entry at VA 0x00E22F78
// (MOV at RVA 0x001C1A59). Original function/API name and exact formal types,
// count and codec role remain unknown; this signature models three observed
// stack words. Unsigned count arithmetic preserves the native 32-bit
// subtraction and shift without claiming original signedness or valid inputs.

void __cdecl rva001B9C10Interpolate4To5(const void *source, unsigned int countWord, void *destination)
{
	unsigned char *dst = (unsigned char *)destination;
	const unsigned char *src = (const unsigned char *)source;
	unsigned int remaining = countWord - 4;

	if (remaining != 0)
	{
		unsigned int groups = (remaining - 1) / 4 + 1;
		do
		{
			unsigned int first = src[0];
			unsigned int second = src[1];
			dst[0] = (unsigned char)first;
			dst[1] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

			unsigned int third = src[2] * 154;
			unsigned int fourth = src[3];
			dst[2] = (unsigned char)((second * 102 + third + 128) >> 8);
			dst[3] = (unsigned char)((third + fourth * 102 + 128) >> 8);

			unsigned int fifth = src[4];
			dst[4] = (unsigned char)((fourth * 205 + fifth * 51 + 128) >> 8);
			src += 4;
			dst += 5;
			--groups;
		}
		while (groups != 0);
	}

	unsigned int first = src[0];
	unsigned int second = src[1];
	dst[0] = (unsigned char)first;
	dst[1] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

	unsigned int third = src[2] * 154;
	unsigned int fourth = src[3];
	dst[2] = (unsigned char)((second * 102 + third + 128) >> 8);
	dst[3] = (unsigned char)((third + fourth * 102 + 128) >> 8);
	dst[4] = (unsigned char)fourth;
}
