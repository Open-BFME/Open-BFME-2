// _LoopDeringBlock
// partial score=0.4 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8b40.md plus retail only.
// No decoder source was consulted.
#include <stdlib.h>
#include <string.h>
struct Vp6LoopDeringInstance
{
	unsigned char pad0000[0x453C];
	unsigned int deringThreshold[256];
};

extern "C" void LoopDeringBlock(Vp6LoopDeringInstance *pbi, unsigned char *block, unsigned int stride, unsigned int width, unsigned int height)
{
	unsigned char buffer[16];
	unsigned char minValue = 255;
	unsigned char maxValue = 0;
	unsigned int i, j;
	unsigned char *p = block;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			if (p[0] < minValue)
				minValue = p[0];
			if (p[0] > maxValue)
				maxValue = p[0];
			p++;
		}
		p += stride - width;
	}
	unsigned int high = pbi->deringThreshold[maxValue];
	unsigned int low = pbi->deringThreshold[255 - minValue];
	int threshold = low > high ? low : high;
	threshold += (maxValue - minValue) >> 5;

	unsigned char *row = block;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			int diffRight = abs(row[i] - row[i + 1]);
			int diffLeft = abs(row[i] - row[i - 1]);
			int sum = row[i] + row[i];
			if (diffLeft <= threshold)
				sum += row[i - 1];
			else
				sum += row[i];
			if (diffRight <= threshold)
				sum += row[i + 1];
			else
				sum += row[i];
			buffer[i] = (unsigned char)((sum + 2) >> 2);
		}
		memcpy(row, buffer, width);
		row += stride;
	}

	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			int diffDown = abs(block[j * stride + i] - block[(j + 1) * stride + i]);
			int diffUp = abs(block[j * stride + i] - block[(j - 1) * stride + i]);
			int sum = block[j * stride + i] + block[j * stride + i];
			if (diffUp <= threshold)
				sum += block[(j - 1) * stride + i];
			else
				sum += block[j * stride + i];
			if (diffDown <= threshold)
				sum += block[(j + 1) * stride + i];
			else
				sum += block[j * stride + i];
			buffer[j] = (unsigned char)((sum + 2) >> 2);
		}
		for (j = 0; j < height; j++)
			block[j * stride + i] = buffer[j];
	}
}
