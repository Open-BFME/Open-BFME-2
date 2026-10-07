// ?Rva001BA460@@YAXPAEHHH0HHH@Z
// partial score=0.9 date=2026-10-07
// Open-BFME5 conversion of the retail strided byte copy.

void __cdecl bfmeCopyColAA90(
	unsigned char *pSrc,
	int pSrcPitch,
	int pUnused2,
	int pUnused3,
	unsigned char *pDst,
	int pDstPitch,
	int pUnused6,
	int pCount)
{
	int step = pSrcPitch;
	int srcDelta = step + step;
	int pitch = pDstPitch;
	unsigned int limit = (unsigned int)pitch * (unsigned int)pCount;
	unsigned int off = 0;

	if (limit > 0) {
		unsigned char *d = pDst;
		unsigned char *s = pSrc;
		do {
			*(unsigned char *)(off + (unsigned int)d) = *s;
			off += (unsigned int)pitch;
			s += srcDelta;
		} while (off < limit);
	}
}

// Native 0x001BA460..0x001BA4C2, cdecl, eight stack arguments.
// Strided codec sibling: retain the first sample, then filter three rows
// at twice the source pitch with weights 3/10/3 and rounding before >>4.
// Layout, signed pitches and the unsigned loop bound follow native accesses
// and the verified BFME1 copy sibling above; the filter's name is unknown.
void __cdecl Rva001BA460(unsigned char *src, int srcPitch, int, int,
    unsigned char *dst, int dstPitch, int, int count)
{
    int step = srcPitch + srcPitch;
    unsigned char first = src[0];
    unsigned offset = (unsigned)dstPitch;
    unsigned limit = offset * (unsigned)count;
    dst[0] = first;
    if (offset < limit)
    {
        unsigned char *middle = src + step;
        do
        {
            unsigned sum = (middle[step] + src[0]) * 3;
            sum += middle[0] * 10;
            dst[offset] = (unsigned char)((sum + 8) >> 4);
            offset += (unsigned)dstPitch;
            src += step;
            middle += step;
        } while (offset < limit);
    }
}
