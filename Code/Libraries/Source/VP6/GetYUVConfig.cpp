// cl: /O2 /G6 /MD
//
// _VP6_GetYUVConfig, retail 0x001B5C60..0x001B60DB (1147 bytes), cdecl.
// Clean room: reverse/vp6_cleanroom/specs/001b5c60.md plus retail only.
// Field names below are descriptive labels from the spec text.

struct Rva009A6130Context;
struct Rva009A5C40Context;
struct Rva009AAC80Context;
struct Rva009AABB0Context;
struct Rva009AA8F0Context;
struct Rva009AA8F0Block;
struct BfmeVp6Context;

void __cdecl Rva001B8E70(unsigned int *result);
extern "C" int __cdecl bfmeVp6ThresholdSelect(BfmeVp6Context *ctx);
int Rva009A5C40Initialize(Rva009A5C40Context *post);
void Rva009A6130PostFilterDispatch(Rva009A6130Context *post, int version, int frameType, int level,
	int frameQ, unsigned char *source, unsigned char *dest, unsigned char *fragInfo, int elementSize, int codedMask);
void Rva009AAC80CodecGrid(Rva009AAC80Context *instance);
void Rva009AABB0CodecDispatch(Rva009AABB0Context *instance);
void Rva009AA8F0Dispatch(Rva009AA8F0Context *post, int source, Rva009AA8F0Block *config);

class Rva001B6400Allocation
{
public:
	enum AllocationTag
	{
		TAG_NONE = 0
	};
	static void *operator new(unsigned int size, AllocationTag tag);
};

// The clamp routine is slot 19 of the codec dispatch table at VA 0x00E22F7C
// (0x00E22FC8), installed by bfmeInstallCpuDispatchTable.
typedef void (__cdecl *BfmeDispatchFn)();
struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};
extern BfmeCodecDispatchTable g_bfmeCodecDispatch;
typedef void (__cdecl *VP6ClampLevelsFn)(void *post, int black, int white, unsigned char *source, unsigned char *dest);
#define CLAMP_LEVELS ((VP6ClampLevelsFn)g_bfmeCodecDispatch.slot[19])

// The system-state clear routine pointer at VA 0x00E22D10.
extern void (__cdecl *g_bfmeToneReady)();

struct VP6YUVConfig
{
	int yWidth;
	int yHeight;
	int yStride;
	int uvWidth;
	int uvHeight;
	int uvStride;
	unsigned char *y;
	unsigned char *u;
	unsigned char *v;
	unsigned char *yOrigin;
};

struct VP6Instance
{
	unsigned char pad000[0x148];
	unsigned char *fragInfo;			// +0x148
	unsigned char pad14C[0x19C - 0x14C];
	unsigned char version;				// +0x19C
	unsigned char pad19D[0x1A0 - 0x19D];
	unsigned int level;					// +0x1A0
	unsigned int processorFrequency;	// +0x1A4
	unsigned char pad1A8[0x1AC - 0x1A8];
	unsigned char frameType;			// +0x1AC
	unsigned char pad1AD[0x1B0 - 0x1AD];
	unsigned int width;					// +0x1B0
	unsigned int height;				// +0x1B4
	int yStride;						// +0x1B8
	int uvStride;						// +0x1BC
	unsigned char pad1C0[0x1DC - 0x1C0];
	int interlaced;						// +0x1DC
	unsigned char pad1E0[0x208 - 0x1E0];
	int reconYPlaneSize;				// +0x208
	int reconUVPlaneSize;				// +0x20C
	unsigned char pad210[0x21C - 0x210];
	int reconYOffset;					// +0x21C
	int reconUOffset;					// +0x220
	int reconVOffset;					// +0x224
	unsigned char pad228[0x23C - 0x228];
	unsigned int outputWidth;			// +0x23C
	unsigned int outputHeight;			// +0x240
	unsigned char pad244[0x254 - 0x244];
	unsigned char *lastRecon;			// +0x254
	unsigned char pad258[0x25C - 0x258];
	unsigned char *postBuffer;			// +0x25C
	unsigned char *postBufferRaw;		// +0x260
	unsigned char *scaleBuffer;			// +0x264
	unsigned char pad268[0x298 - 0x268];
	void *postProcessor;				// +0x298
	unsigned char pad29C[0x6A0 - 0x29C];
	int averageFrameQ;					// +0x6A0
	unsigned char pad6A4[0x918 - 0x6A4];
	unsigned int averagePostTime[10];	// +0x918
	unsigned char pad940[0x493C - 0x940];
	int blackClamp;						// +0x493C
	int whiteClamp;						// +0x4940
	int deinterlaceMode;				// +0x4944
};

extern "C" void __cdecl VP6_GetYUVConfig(VP6Instance *instance, VP6YUVConfig *config)
{
	unsigned int end;
	unsigned int start;

	Rva001B8E70(&start);
	instance->level = bfmeVp6ThresholdSelect((BfmeVp6Context *)instance);

	if (instance->level || (instance->interlaced && instance->deinterlaceMode))
	{
		if (!instance->postBuffer)
		{
			instance->postBufferRaw = (unsigned char *)Rva001B6400Allocation::operator new(
				instance->reconYPlaneSize + 2 * instance->reconUVPlaneSize + 32 + instance->yStride,
				Rva001B6400Allocation::TAG_NONE);
			instance->postBuffer = (unsigned char *)(((unsigned int)instance->postBufferRaw + 31) & ~31);
			Rva009A5C40Initialize((Rva009A5C40Context *)instance->postProcessor);
		}

		if (instance->level > 200)
		{
			Rva009A6130PostFilterDispatch((Rva009A6130Context *)instance->postProcessor, instance->version, instance->frameType,
				instance->level - 200, instance->averageFrameQ, instance->lastRecon, instance->postBuffer,
				instance->fragInfo, 4, 1);
			Rva001B8E70(&end);
			Rva009AAC80CodecGrid((Rva009AAC80Context *)instance);
		}
		else if (instance->level > 100)
		{
			Rva009A6130PostFilterDispatch((Rva009A6130Context *)instance->postProcessor, instance->version, instance->frameType,
				instance->level - 100, instance->averageFrameQ, instance->lastRecon, instance->postBuffer,
				instance->fragInfo, 4, 1);
			Rva001B8E70(&end);
			Rva009AABB0CodecDispatch((Rva009AABB0Context *)instance);
		}
		else
		{
			Rva009A6130PostFilterDispatch((Rva009A6130Context *)instance->postProcessor, instance->version, instance->frameType,
				instance->level, instance->averageFrameQ, instance->lastRecon, instance->postBuffer,
				instance->fragInfo, 4, 1);
			Rva001B8E70(&end);
		}

		if (instance->blackClamp)
			CLAMP_LEVELS(instance->postProcessor, instance->blackClamp, instance->whiteClamp, instance->postBuffer, instance->postBuffer);
	}

	if (instance->width >= instance->outputWidth && instance->height >= instance->outputHeight)
	{
		config->yWidth = instance->width;
		config->yHeight = instance->height;
		config->yStride = instance->yStride;
		config->uvWidth = instance->width >> 1;
		config->uvHeight = instance->height >> 1;
		config->uvStride = instance->uvStride;

		if (instance->level || (instance->interlaced && instance->deinterlaceMode))
		{
			config->y = instance->postBuffer + instance->reconYOffset + 48 * (instance->yStride + 1);
			config->u = instance->postBuffer + instance->reconUOffset + 24 * (instance->uvStride + 1);
			config->v = instance->postBuffer + instance->reconVOffset + 24 * (instance->uvStride + 1);
			config->yOrigin = instance->postBuffer + instance->reconYOffset;
		}
		else
		{
			config->y = instance->lastRecon + instance->reconYOffset + 48 * (instance->yStride + 1);
			config->u = instance->lastRecon + instance->reconUOffset + 24 * (instance->uvStride + 1);
			config->v = instance->lastRecon + instance->reconVOffset + 24 * (instance->uvStride + 1);
			config->yOrigin = instance->lastRecon + instance->reconYOffset;
		}
	}
	else
	{
		config->yWidth = instance->outputWidth + 32;
		config->yHeight = instance->outputHeight + 32;
		config->yStride = config->yWidth;
		config->uvWidth = config->yWidth / 2;
		config->uvHeight = config->yHeight / 2;
		config->uvStride = config->uvWidth;
		config->y = instance->scaleBuffer;
		config->u = instance->scaleBuffer + config->yWidth * config->yHeight;
		config->v = instance->scaleBuffer + config->yWidth * config->yHeight + config->uvWidth * config->uvHeight;
		config->yOrigin = instance->scaleBuffer;

		if (instance->level)
			Rva009AA8F0Dispatch((Rva009AA8F0Context *)instance->postProcessor, (int)instance->postBuffer, (Rva009AA8F0Block *)config);
		else
			Rva009AA8F0Dispatch((Rva009AA8F0Context *)instance->postProcessor, (int)instance->lastRecon, (Rva009AA8F0Block *)config);

		config->y += ((config->yHeight - instance->outputHeight) >> 1) * config->yStride
			+ ((config->yWidth - instance->outputWidth) >> 1);
		config->yWidth = instance->outputWidth;
		config->yHeight = instance->outputHeight;
		config->u += ((config->uvHeight - (instance->outputHeight >> 1)) >> 1) * config->uvStride
			+ ((config->uvWidth - (instance->outputWidth >> 1)) >> 1);
		config->v += ((config->uvHeight - (instance->outputHeight >> 1)) >> 1) * config->uvStride
			+ ((config->uvWidth - (instance->outputWidth >> 1)) >> 1);
		config->uvWidth = instance->outputWidth >> 1;
		config->uvHeight = instance->outputHeight >> 1;
	}

	g_bfmeToneReady();

	unsigned int duration = (end - start) / instance->processorFrequency;
	if (instance->averagePostTime[instance->level % 10] == 0)
		instance->averagePostTime[instance->level % 10] = duration;
	else
		instance->averagePostTime[instance->level % 10] = (7 * instance->averagePostTime[instance->level % 10] + duration) >> 3;
}
