// ?update@ScreenGridRva000F83FA@@QAEXPAVDynamicIBAccessClass@@HPAVDynamicVBAccessClass@@HHHMMMMPAVCoord2D@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c- /ICode/Libraries/Include
//
// ?update@ScreenGridRva000F83FA@@QAEXPAVDynamicIBAccessClass@@HPAVDynamicVBAccessClass@@HHHMMMMPAVCoord2D@@@Z
// retail 0x000F83FA..0x000F8735 (827 bytes) thiscall ret 0x2C, no EH frame.
// Dynamic index/vertex grid update of a screen filter: the unrowed
// 0x000F88E8 (slot 7 of the filter vftable at 0x007CF260) calls it with the
// filter's index and vertex buffer accessors and their counts (unused) a
// 10x10 grid the tactical view rectangle and the viewport size.
// Reference transfer from BFME 1's W3DScreenFireFilter.cpp /
// W3DScreenOneRingFilter.cpp update (BFME 1 retail 0x007D4AF0 / 0x007D95B0):
// same control flow constants and 52-byte vertex. Target evidence: the
// frame scale is the float g_Va00DB457C times 0.0125 clamped to [0.6 6]
// (two separate tests in BFME 2) times +0x54 of the rowed 0x00309E65
// record; the rowed DynamicIBAccessClass::WriteLockClass 0x00138CA0 /
// 0x00138D80 and DynamicVBAccessClass::WriteLock 0x0013AA00 / 0x0013AB00
// bracket the index and vertex loops; the two phases at 0x00DEC078 /
// 0x00DEC07C advance by 0.05 and the six wave statics at 0x00DB5AC8..
// 0x00DB5ADC hold 0.2 4PI 2 0.5 4PI 2 as in the donor; sin is the CRT
// thunk 0x00629216. BFME 2 writes u1 once (no reload) before the waves.
// The twin 0x000F6DB0 differs in its scale getter (0x00309E7F) and statics.
#include <math.h>
#include "Lib/Coord2D.h"

class DynamicIBAccessClass
{
public:
	class WriteLockClass
	{
		DynamicIBAccessClass *access;

	public:
		unsigned short *indices;
		WriteLockClass(DynamicIBAccessClass *ib);
		~WriteLockClass();
	};
};

struct Vertex
{
	float x, y, z, rhw;
	unsigned color;
	float u0, v0, u1, v1, u2, v2, u3, v3;
};

class DynamicVBAccessClass
{
public:
	class WriteLock
	{
		DynamicVBAccessClass *access;

	public:
		Vertex *vertices;
		WriteLock(DynamicVBAccessClass *vb);
		~WriteLock();
	};
};

struct GridGlobals
{
	char pad[0x54];
	float scale;
};

int Rva00309E65Get(void);
extern float g_Va00DB457C;

static float GridPhase0, GridPhase1;
static float GridWave0Amplitude = 0.2f, GridWave0Frequency = 12.566370964f, GridWave0Phase = 2.0f;
static float GridWave1Amplitude = 0.5f, GridWave1Frequency = 12.566370964f, GridWave1Phase = 2.0f;

class ScreenGridRva000F83FA
{
	char pad[0x20];
	float scrollX, scrollY, spread;

public:
	void update(DynamicIBAccessClass *ib, int ibCount, DynamicVBAccessClass *vb, int vbCount,
		int columns, int rows, float left, float top, float width, float height, Coord2D *dims);
};

void ScreenGridRva000F83FA::update(DynamicIBAccessClass *ib, int ibCount, DynamicVBAccessClass *vb, int vbCount,
	int columns, int rows, float left, float top, float width, float height, Coord2D *dims)
{
	++columns;
	++rows;
	float scale = g_Va00DB457C * 0.0125f;
	if (scale > 6.0f)
		scale = 6.0f;
	if (scale < 0.6f)
		scale = 0.6f;
	float amplitude = scale * ((GridGlobals *)Rva00309E65Get())->scale;
	{
		DynamicIBAccessClass::WriteLockClass lock(ib);
		unsigned short *p = lock.indices;
		for (int y = 0; y < rows - 1; ++y) {
			for (int x = 0; x < columns - 1; ++x) {
				p[0] = y * columns + x;
				p[1] = (y + 1) * columns + x + 1;
				p[2] = (y + 1) * columns + x;
				p[3] = y * columns + x;
				p[4] = y * columns + x + 1;
				p[5] = (y + 1) * columns + x + 1;
				p += 6;
			}
		}
	}
	GridPhase0 += 0.05f;
	GridPhase1 += 0.05f;
	{
		DynamicVBAccessClass::WriteLock lock(vb);
		Vertex *p = lock.vertices;
		float invRows = 1.0f / (rows - 1);
		float invColumns = 1.0f / (columns - 1);
		for (int y = 0; y < rows; ++y) {
			float fy = y * invRows;
			float py = fy * height + top;
			float screenY = py - 0.5f;
			for (int x = 0; x < columns; ++x) {
				float fx = x * invColumns;
				float px = fx * width + left;
				p->x = px - 0.5f;
				p->y = screenY;
				p->z = 0;
				p->rhw = 1;
				p->color = 0x64ffffff;
				p->u0 = px / dims->x;
				p->v0 = py / dims->y;
				float u = fx * amplitude * 2 + scrollX;
				float v = fy * amplitude + scrollY;
				p->u1 = u;
				p->v1 = v;
				p->v2 = v + spread;
				p->u2 = u - spread;
				p->u1 = u + spread;
				p->u3 = (0.5f - 0.5f * (float)sin((fx + fy) * GridWave0Frequency + GridWave0Phase * GridPhase0)) * GridWave0Amplitude;
				float wave = (0.5f - 0.5f * (float)sin((fx + fy) * GridWave1Frequency + GridWave1Phase * GridPhase1)) * GridWave1Amplitude;
				p->v3 = 0;
				p->u1 += wave;
				p->u2 += wave;
				++p;
			}
		}
	}
}
