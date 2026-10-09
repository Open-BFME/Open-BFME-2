// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b9140.md plus retail only.
// No decoder source was consulted.
// _VP6_AllocateFragmentInfo retail 0x001B9140..0x001B92CC (396 bytes) cdecl
// (instance) returning 1 on success and 0 on failure. Frees the previous
// buffers through 0x001B9040 then allocates through the duck-memory shim
// 0x001B6400 (tag 0) the coefficient buffer / the above Y U V contexts / the
// interlaced flags / prediction modes / motion vectors and the fragment
// info. Each buffer is kept raw and rounded up to 32 bytes. Any null result
// frees everything again through 0x001B9040 and returns 0.
class Rva001B6400Allocation
{
public:
	enum AllocationTag
	{
		TAG_NONE = 0
	};
	static void *operator new(unsigned int size, AllocationTag tag);
};
void bfmeStepJW(void *instance);
struct Vp6FragmentInstance {
	unsigned char *coeffRaw;
	unsigned char *coeff;
	unsigned char unknown8[0x10c - 0x8];
	unsigned char *aboveY, *aboveU, *aboveV;
	unsigned char *aboveYRaw, *aboveURaw, *aboveVRaw;
	unsigned char unknown124[0x148 - 0x124];
	unsigned char *fragInfo;
	unsigned char *fragInfoRaw;
	unsigned char unknown150[0x1f8 - 0x150];
	unsigned hFragments;
	unsigned unitFragments;
	unsigned char unknown200[0x228 - 0x200];
	unsigned macroBlocks;
	unsigned char unknown22c[0x6ec - 0x22c];
	unsigned char *interlaced, *predictionMode, *motionVector;
	unsigned char *interlacedRaw, *predictionModeRaw, *motionVectorRaw;
};
#define VP6_ALIGN32(p) ((unsigned char *)(((unsigned)(p) + 31) & ~31))
extern "C" int VP6_AllocateFragmentInfo(Vp6FragmentInstance *pbi)
{
	bfmeStepJW(pbi);
	pbi->coeffRaw = (unsigned char *)Rva001B6400Allocation::operator new(0x320, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->coeffRaw)
		goto fail;
	pbi->coeff = VP6_ALIGN32(pbi->coeffRaw);
	pbi->aboveYRaw = (unsigned char *)Rva001B6400Allocation::operator new((pbi->hFragments + 10) * 16, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->aboveYRaw)
		goto fail;
	pbi->aboveY = VP6_ALIGN32(pbi->aboveYRaw);
	pbi->aboveURaw = (unsigned char *)Rva001B6400Allocation::operator new(((pbi->hFragments >> 1) + 10) * 16, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->aboveURaw)
		goto fail;
	pbi->aboveU = VP6_ALIGN32(pbi->aboveURaw);
	pbi->aboveVRaw = (unsigned char *)Rva001B6400Allocation::operator new(((pbi->hFragments >> 1) + 10) * 16, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->aboveVRaw)
		goto fail;
	pbi->aboveV = VP6_ALIGN32(pbi->aboveVRaw);
	pbi->interlacedRaw = (unsigned char *)Rva001B6400Allocation::operator new(pbi->macroBlocks + 32, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->interlacedRaw)
		goto fail;
	pbi->interlaced = VP6_ALIGN32(pbi->interlacedRaw);
	pbi->predictionModeRaw = (unsigned char *)Rva001B6400Allocation::operator new(pbi->macroBlocks + 32, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->predictionModeRaw)
		goto fail;
	pbi->predictionMode = VP6_ALIGN32(pbi->predictionModeRaw);
	pbi->motionVectorRaw = (unsigned char *)Rva001B6400Allocation::operator new(pbi->macroBlocks * 4 + 32, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->motionVectorRaw)
		goto fail;
	pbi->motionVector = VP6_ALIGN32(pbi->motionVectorRaw);
	pbi->fragInfoRaw = (unsigned char *)Rva001B6400Allocation::operator new(pbi->unitFragments * 4 + 32, Rva001B6400Allocation::TAG_NONE);
	if (!pbi->fragInfoRaw)
		goto fail;
	pbi->fragInfo = VP6_ALIGN32(pbi->fragInfoRaw);
	return 1;
fail:
	bfmeStepJW(pbi);
	return 0;
}
