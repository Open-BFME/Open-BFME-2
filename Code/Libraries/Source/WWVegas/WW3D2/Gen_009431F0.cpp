// cl: /DNDEBUG /MD /EHs-c-
#include <math.h>

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long bfme_fistp(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);

private:
	float origin_x;
	float origin_y;
	unsigned char pad[0x18];
	float scale;
	int count;
};

int Gen_009431F0::map_x(float x)
{
	float t = (x - origin_x) * scale * (float)(unsigned)count;
	int i = (int)bfme_fistp((float)floor((double)t));
	if (i < 0)
		return 0;
	int c = count;
	if ((unsigned)i >= (unsigned)c)
		return c - 1;
	return i;
}

int Gen_009431F0::map_y(float y)
{
	float t = (y - origin_y) * scale * (float)(unsigned)count;
	int i = (int)bfme_fistp((float)floor((double)t));
	if (i < 0)
		return 0;
	int c = count;
	if ((unsigned)i >= (unsigned)c)
		return c - 1;
	return i;
}

// BFME1 donor: game/GameEngine/Source/Common/SmallGaps/log2Word.cpp
// at 40e7f2f21f0011b42a5654697cdedbc2658b6d9b (unchanged from 34f59164).
// Retail 0x00140F70 is a complete cdecl bit-index helper; its original name
// is unknown. The neighboring spatial-cell routine at 0x00140FA0 repeats
// these masks and calls map_x/map_y, supporting this existing family home.
int Rva00140F70BitIndex(unsigned int value)
{
    int result = 0;
    if (value & 0xff00) { value >>= 8; result = 8; }
    if (value & 0xf0) { value >>= 4; result |= 4; }
    if (value & 0xc) { value >>= 2; result |= 2; }
    if (value & 2) result |= 1;
    return result;
}
