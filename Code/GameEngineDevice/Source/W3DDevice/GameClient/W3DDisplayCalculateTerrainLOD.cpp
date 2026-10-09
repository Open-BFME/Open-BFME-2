// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?calculateTerrainLOD@W3DDisplay@@IAEXXZ, retail 0x00043DC3..0x00043F94
// (465B), thiscall.
//
// Donor: Zero Hour W3DDisplay.cpp W3DDisplay::calculateTerrainLOD (protected
// in W3DDisplay.h). BFME 2 differences read from retail only:
//   * no sprintf/OutputDebugString frame log (and no buffer);
//   * each sample frame runs under the DX8 device lock (rowed
//     BFME_DX8_Thread_Lock 0x0011F520 after updateViews and the rowed
//     BFME_DX8_Thread_Assert 0x00120F50 at the end of the sample, EH state 0);
//   * Begin_Render is the rowed WW3D::rva00118170 0x00118170 returning bool,
//     compared with true; End_Render(true) 0x00117410;
//   * the LOD walk is AUTOMATIC 8 -> MAX 7 -> NO_WATER 6 -> HALF_CLOUDS 3 ->
//     disable, the target time is the int at TheGlobalData +0x58 and the LOD
//     the int at +0x50; drawTerrainOnly is the inline byte store at
//     W3DDisplay::m_3DScene +0x12C; adjustTerrainLOD is terrain vtable slot
//     135 (+0x21C); updateViews / drawViews are this's slots 40 / 38.
// Performance counter helpers: rowed Rva00043024Get (frequency) and
// Rva0004300DGet (counter). Sole caller 0x00044011.
//
// Callee note: all six retail callers of 0x00118170 push four arguments (add
// esp,0x10); the row spells a fifth (unused) function-pointer parameter, so
// the call here uses the four-argument spelling.

typedef int Int;
typedef __int64 Int64;
typedef float Real;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

Int64 Rva00043024Get();
Int64 Rva0004300DGet();

class Vector3
{
public:
	__declspec(dllimport) __forceinline Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

class WW3D
{
public:
	static bool rva00118170(bool clear, bool clearz, const Vector3 &color, float destAlpha);
	static bool End_Render(bool flipFrame);
};

enum TerrainLOD
{
	TERRAIN_LOD_MIN = 1,
	TERRAIN_LOD_HALF_CLOUDS = 3,
	TERRAIN_LOD_NO_WATER = 6,
	TERRAIN_LOD_MAX = 7,
	TERRAIN_LOD_AUTOMATIC = 8,
	TERRAIN_LOD_DISABLE = 9
};

class GlobalData
{
public:
	unsigned char m_pad00[0x50];
	Int m_terrainLOD;			// +0x50
	unsigned char m_pad54[0x58 - 0x54];
	Int m_terrainLODTargetTimeMS;		// +0x58
};

extern GlobalData *TheWritableGlobalData;

class RTS3DScene
{
public:
	void drawTerrainOnly(bool draw) { m_drawTerrainOnly = draw; }
private:
	unsigned char m_pad000[0x12C];
	bool m_drawTerrainOnly;			// +0x12C
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class BaseHeightMapRenderObjClass
{
public:
	PAD_VIRTUALS10(a0) PAD_VIRTUALS10(a1) PAD_VIRTUALS10(a2) PAD_VIRTUALS10(a3)
	PAD_VIRTUALS10(a4) PAD_VIRTUALS10(a5) PAD_VIRTUALS10(a6) PAD_VIRTUALS10(a7)
	PAD_VIRTUALS10(a8) PAD_VIRTUALS10(a9) PAD_VIRTUALS10(b0) PAD_VIRTUALS10(b1)
	PAD_VIRTUALS10(b2)
	virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34();
	virtual void adjustTerrainLOD(Int adj);	// slot 135
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DDisplay
{
public:
	PAD_VIRTUALS10(s0) PAD_VIRTUALS10(s1) PAD_VIRTUALS10(s2)
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37();
	virtual void drawViews();		// slot 38
	virtual void s39();
	virtual void updateViews();		// slot 40

	static RTS3DScene *m_3DScene;

protected:
	void calculateTerrainLOD(void);
};

void W3DDisplay::calculateTerrainLOD(void)
{
	const Int NUM_SAMPLES = 20;
	const Int NUM_TO_DISCARD = 5;

	Int64 freq64 = Rva00043024Get();

	float frameTime = 0;
	float maxTimeLimit = TheWritableGlobalData->m_terrainLODTargetTimeMS / 1000.0f;
	TerrainLOD goodLOD = TERRAIN_LOD_MIN;
	TerrainLOD curLOD = TERRAIN_LOD_AUTOMATIC;
	Int count = 0;
	do {
		Int i;
		float timeForFrame = 0;
		frameTime = 0;
		switch (curLOD) {
			default: curLOD = TERRAIN_LOD_DISABLE; break;
			case TERRAIN_LOD_AUTOMATIC: curLOD = TERRAIN_LOD_MAX; break;
			case TERRAIN_LOD_MAX: curLOD = TERRAIN_LOD_NO_WATER; break;
			case TERRAIN_LOD_HALF_CLOUDS: curLOD = TERRAIN_LOD_DISABLE; break;
			case TERRAIN_LOD_NO_WATER: curLOD = TERRAIN_LOD_HALF_CLOUDS; break;
		}
		if (curLOD == TERRAIN_LOD_DISABLE) {
			break;
		}
		TheWritableGlobalData->m_terrainLOD = curLOD;
		m_3DScene->drawTerrainOnly(true);
		TheTerrainRenderObject->adjustTerrainLOD(0);
		for (i = 0; i < NUM_SAMPLES; i++) {
			Int64 startTime64 = Rva0004300DGet();
			updateViews();
			BFMEDX8DeviceLock lock;
			if (WW3D::rva00118170(true, true, Vector3(0.0f, 0.0f, 0.0f), 0.0f) == true)
			{
				drawViews();
				WW3D::End_Render(true);
			}
			Int64 time64 = Rva0004300DGet();
			timeForFrame = (float)((double)(time64 - startTime64) / (double)(freq64));
			if (i >= NUM_TO_DISCARD) {
				frameTime += timeForFrame;
				if (i > NUM_TO_DISCARD + 1 &&
					(timeForFrame / ((i + 1) - NUM_TO_DISCARD)) > 2 * maxTimeLimit) {
					i++;
					break;
				}
			}
		}
		frameTime /= ((i) - NUM_TO_DISCARD);
		count++;
		if (frameTime < maxTimeLimit && goodLOD < curLOD) {
			goodLOD = curLOD;
		}
		if (frameTime < maxTimeLimit) break;
	} while (count < 10);

	TheWritableGlobalData->m_terrainLOD = goodLOD;
	m_3DScene->drawTerrainOnly(false);
	TheTerrainRenderObject->adjustTerrainLOD(0);
}
