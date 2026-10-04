// cl: /O1 /MD /arch:SSE /G7
//
// ?Rva0027D815@Rva0062AF7@@UAEMMM@Z retail 0x0027D815 70 bytes.
// Vslot 25 (offset 0x64) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ
// whose slot 2 returns W3DTerrainLogic and slot 15 is isClearLineOfSight.
// Shared with base TerrainLogic vtable 0x007FB2C8 at same address. Calls slot
// 19 (offset 0x4C unclaimed 0x0027D77D 5-arg bool) with x y and two float outs
// plus 0 and returns a minus b on true else pooled 0.0f at retail 0x007BAEAC.
// Identity is class plus slot and method name is honest address name.
// Secondary MI vptrs plus 0x04 plus 0x10 plus 0x14 omitted as body touches
// primary only. Flags per section 4.1: /O1 for EBP frame plus /arch:SSE for
// xorps and movss float zeroing.
extern int g_Va00DBA4E4;

#include <math.h>
struct Rva0027D5E0Box
{
	float loX;
	float loY;
	float loZ;
	float hiX;
	float hiY;
	float hiZ;
};

// Result pair of Rva0027D6DF (+0/+4 used, +8 spare keeps retail's frame).
struct Rva0027D6DFRes
{
	float out1;
	float out2;
	float m_spare;
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Matrix3D
{
public:
	float m[16];
};
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
class Object;
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
void alignToTerrain(float angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);
class Rva0062AF7
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float slot06(float x, float y, int z);
	virtual float slot07(float x, float y, int layer, Coord3D *out, int flag);
	virtual void slot08(Rva0027D5E0Box *box);
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void Rva0027D5E0(float *out, const float *in);
	virtual void Rva0027D6DF(float *out, const float *in);
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual PathfindLayerEnum Rva002811DD(float angle, const Coord3D &pos, bool stickToGround, Matrix3D &mtx);
	virtual bool Rva0027D77D(float x, float y, float *a, float *b, bool *c);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual float Rva0027D815(float x, float y);
	virtual void *slot26(float x, float y, float z);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual float Rva0027D85B(void *water);
	virtual void slot31();
	virtual void Rva0027D88E(void *water, float finalHeight, float transitionTime, float damageAmount);
	void Rva0027D960(void *water, float *out);
	void Rva0027DA58();

private:
	char m_pad04[0x20];
	char *m_arr24;
	char m_pad28[0x40];
	struct WaterEntry
	{
		void *waterTable;
		float changePerFrame;
		float targetHeight;
		float damageAmount;
		float currentHeight;
	};
	WaterEntry m_entries[64];
	int m_count;
};
float Rva0062AF7::Rva0027D815(float x, float y)
{
	float a = 0.0f;
	float b = 0.0f;
	if (!Rva0027D77D(x, y, &a, &b, 0))
		return 0.0f;
	return a - b;
}

//
// ?Rva0027D85B@Rva0062AF7@@UAEMPAX@Z retail 0x0027D85B 51 bytes.
// Vslot 30 (offset 0x78) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ.
// Null or grid-handle (global 0x00DBB710) returns pooled 0.0f at 0x007BAEAC.
// Else water+0x18 holds inner, inner+0x04 holds byte offset, real object at
// water+0x18+offset exposes int at slot 2 (offset 8) converted via fild.
// Layout witnessed from retail bytes only; helper view names are honest
// address-derived, not donor claims. Identity class plus slot, honest name.
// Flags: /O1 plus /arch:SSE plus /G7 (section 4.1, same TU as neighbours).
extern void *g_Va00DBB710;
struct Rva0027D85BPolyView
{
	virtual void slot00();
	virtual void slot01();
	virtual int slot08();
};
struct Rva0027D85BInnerView
{
	char m_pad00[4];
	int m_off04;
};
struct Rva0027D85BWaterView
{
	char m_pad00[0x18];
	Rva0027D85BInnerView *m_inner18;
};
float Rva0062AF7::Rva0027D85B(void *water)
{
	Rva0027D85BWaterView *view = (Rva0027D85BWaterView *)water;
	if (water == 0)
		return 0.0f;
	if (water == g_Va00DBB710)
		return 0.0f;
	int off = view->m_inner18->m_off04;
	Rva0027D85BPolyView *real = (Rva0027D85BPolyView *)((char *)water + 0x18 + off);
	return (float)real->slot08();
}

//
// ?Rva0027D88E@Rva0062AF7@@UAEXPAXMMM@Z retail 0x0027D88E 210 bytes.
// Vslot 32 (offset 0x80) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ.
// Donor: BFME1 TerrainLogic::changeWaterHeightOverTime in
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// (dedup swap-with-last via rep movsd, getWaterHeight via slot 0x78, then
// (final-current)/(LogicFrames*transition) with LogicFrames global 0x00DBA4E4).
// Array at +0x68 stride 0x14 count at +0x568 max 64. Identity class plus slot,
// honest address name. Flags: /O1 for EBP frame plus /arch:SSE for movss
// float moves plus /G7 for imul 0x14 and edx loop index (section 4.1).
void Rva0062AF7::Rva0027D88E(void *water, float finalHeight, float transitionTime, float damageAmount)
{
#define LogicFramesPerSecond g_Va00DBA4E4
	enum { MAX_DYNAMIC_WATER = 64 };
	if (m_count >= MAX_DYNAMIC_WATER)
		return;
	if (water == 0)
		return;
	for (int i = 0; i < m_count; ++i)
	{
		if (m_entries[i].waterTable == water)
		{
			m_entries[i] = m_entries[m_count - 1];
			--m_count;
			--i;
		}
	}
	float currentHeight = Rva0027D85B(water);
	m_entries[m_count].waterTable = water;
	m_entries[m_count].changePerFrame = (finalHeight - currentHeight) / (LogicFramesPerSecond * transitionTime);
	m_entries[m_count].targetHeight = finalHeight;
	m_entries[m_count].damageAmount = damageAmount;
	m_entries[m_count].currentHeight = currentHeight;
	++m_count;
}

//
// ?Rva0027D77D@Rva0062AF7@@UAE_NMMPAM0PA_N@Z retail 0x0027D77D 152 bytes.
// Vslot 19 (offset 0x4C) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ.
// Ground height via slot 6 (offset 0x18) with x y and 0, water via slot 26
// (offset 0x68) with x y and ground, null water returns false, else height
// via slot 30 Rva0027D85B into *a, ground into *b, water slot 1 into *c,
// returns height above ground. Identity class plus slot, honest address name.
// Flags: /O1 plus /arch:SSE plus /G7 (same TU as neighbours).
struct Rva0027D77DWaterView
{
	virtual void slot00();
	virtual bool slot01();
};
bool Rva0062AF7::Rva0027D77D(float x, float y, float *a, float *b, bool *c)
{
	float ground = slot06(x, y, 0);
	void *water = slot26(x, y, ground);
	if (water == 0)
		return false;
	float h = Rva0027D85B(water);
	if (a != 0)
		*a = h;
	if (b != 0)
		*b = ground;
	if (c != 0)
		*c = ((Rva0027D77DWaterView *)water)->slot01();
	return h > ground;
}

//
// ?Rva0027D5E0@Rva0062AF7@@UAEXPAMPBM@Z retail 0x0027D5E0 255 bytes.
// Vslot 13 (offset 0x34) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ.
// Donor: BFME1 TerrainLogic::findClosestEdgePoint in
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// (fabs of y-loY x-hiX y-hiY x-loX then min-index picks loY hiX hiY loX then
// slot06 grounds the pair plus out triple). Box at ebp-0x28 is Region3D loHi
// six floats; distances at ebp-0x10..-0x4 give 0x28 frame. Identity class plus
// slot honest address name. Flags /O1 /arch:SSE /G7 same TU as neighbours.
void Rva0062AF7::Rva0027D5E0(float *out, const float *in)
{
	Rva0027D5E0Box box;
	slot08(&box);
	float distances[4];
	distances[0] = (float)fabs(in[1] - box.loY);
	distances[1] = (float)fabs(in[0] - box.hiX);
	distances[2] = (float)fabs(in[1] - box.hiY);
	distances[3] = (float)fabs(in[0] - box.loX);
	float best = distances[0];
	int bestIndex = 0;
	for (int i = 1; i < 4; ++i)
	{
		if (distances[i] < best)
		{
			best = distances[i];
			bestIndex = i;
		}
	}
	distances[1] = in[0];
	distances[2] = in[1];
	if (bestIndex == 0)
		distances[2] = box.loY;
	else if (bestIndex == 1)
		distances[1] = box.hiX;
	else if (bestIndex == 2)
		distances[2] = box.hiY;
	else
		distances[1] = box.loX;
	out[2] = slot06(distances[1], distances[2], 0);
	out[0] = distances[1];
	out[1] = distances[2];
}

//
// ?Rva0027D960@Rva0062AF7@@QAEXPAXPAM@Z retail 0x0027D960 248 bytes.
// Follows 0x0027D88E in retail (0x27D88E+210=0x27D960), same TU flags.
// slot08 box expanded by *(float*)0x7FB1C8, out lo/hi init to empty
// (lo=hi+c hi=lo-c), water+0x18+off real gives count via slot0,
// points via rowed 0x7E016 forwarder to slot1, Z via slot2 int to float.
// Callers: 0x282E8B. Identity class plus honest address name.
class Rva0007E016
{
	virtual void f0();
	virtual void vfunc(int a0, int a1);
public:
	int rva0007E016(int a0, int a1);
};

struct Rva0027D960Real
{
	virtual int getCount();
	virtual void getPoint(int a0, int a1);
	virtual int getFinal();
};

struct Rva0027D960Inner
{
	char m_pad00[4];
	int m_off04;
};

struct Rva0027D960Water
{
	char m_pad00[0x18];
	Rva0027D960Inner *m_inner18;
};

void Rva0062AF7::Rva0027D960(void *water, float *out)
{
	if (water == 0)
		return;
	if (out == 0)
		return;
	Rva0027D5E0Box tmp;
	slot08(&tmp);
	const float c = 99999.9f;
	out[0] = tmp.hiX + c;
	out[1] = tmp.hiY + c;
	out[3] = tmp.loX - c;
	out[4] = tmp.loY - c;
	Rva0027D960Water *w = (Rva0027D960Water *)water;
	Rva0027D960Real *real0 = (Rva0027D960Real *)((char *)water + 0x18 + w->m_inner18->m_off04);
	int n = real0->getCount();
	int i = 0;
	if (n <= 0)
		return;
	for (; i < n; ++i)
	{
		float xy[2];
		Rva0027D960Water *w2 = (Rva0027D960Water *)water;
		Rva0027D960Real *real1 = (Rva0027D960Real *)((char *)water + 0x18 + w2->m_inner18->m_off04);
		((Rva0007E016 *)real1)->rva0007E016((int)xy, i);
		if (out[0] > xy[0])
			out[0] = xy[0];
		if (xy[0] > out[3])
			out[3] = xy[0];
		if (out[1] > xy[1])
			out[1] = xy[1];
		if (xy[1] > out[4])
			out[4] = xy[1];
		Rva0027D960Water *w3 = (Rva0027D960Water *)water;
		Rva0027D960Real *real2 = (Rva0027D960Real *)((char *)water + 0x18 + w3->m_inner18->m_off04);
		float f = (float)real2->getFinal();
		out[5] = f;
		out[2] = f;
	}
}

//
// ?Rva0027DA58@Rva0062AF7@@QAEXXZ retail 0x0027DA58 18 bytes.
// Follows 0x0027D960 in retail (0x27D960+248=0x27DA58), same TU flags.
// delete[] at +0x24 then null. Pad split preserves +0x68 entries.
// Callers 0x23E795 0x2817FD 0x2835F7.
void __cdecl operator delete[](void *p);
void Rva0062AF7::Rva0027DA58()
{
	operator delete[](m_arr24);
	m_arr24 = 0;
}

// ?Rva0027D6DF@Rva0062AF7@@UAEXPAMPBM@Z @0x0027D6DF 158B, vslot 14 (offset
// 0x38) next to Rva0027D5E0 at slot 13 with the same signature. Snaps the
// point to the far or near box edge per axis (half the box extent against
// the input coordinate), then fills z from the slot-6 height query.
// Structural inference: the half factor is the 0.5f literal (pooled at
// 0x00BC26F0); the banked attempt read it through a pointer cast, which
// hoisted the factor load.
void Rva0062AF7::Rva0027D6DF(float *out, const float *in)
{
	Rva0027D5E0Box box;
	Rva0027D6DFRes res;
	slot08(&box);
	res.out1 = (0.5f * (box.hiX - box.loX) > in[0]) ? box.hiX : box.loX;
	res.out2 = (0.5f * (box.hiY - box.loY) > in[1]) ? box.hiY : box.loY;
	out[2] = slot06(res.out1, res.out2, 0);
	out[0] = res.out1;
	out[1] = res.out2;
}

//
// ?Rva002811DD@Rva0062AF7@@UAE?AW4PathfindLayerEnum@@MABUCoord3D@@_NAAVMatrix3D@@@Z retail 0x002811DD 127 bytes.
// Vslot 18 (offset 0x48) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ.
// Donor: BFME1 TerrainLogic::alignOnTerrain in
// reference/open-bfme-1/game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// (getLayerForDestination NULL pos, getLayerHeight x y layer normal, +2.5f
// above ground, alignToTerrain angle pos normal mtx, Set_Z_Translation).
// Slot07 is getLayerHeight (float x y int layer Coord3D out int 1) via 0x1c.
// LAYER_GROUND is 1 (cmp ebx 1 jle). 2.5f pooled at 0x00BCFB10 via /arch:SSE.
// Identity class plus slot honest address name. Flags /O1 /arch:SSE /G7 same TU.
PathfindLayerEnum Rva0062AF7::Rva002811DD(float angle, const Coord3D &pos, bool stickToGround, Matrix3D &mtx)
{
	Coord3D terrainNormal;
	PathfindLayerEnum layer = ((TerrainLogic *)this)->getLayerForDestination(0, &pos);
	float terrainAtPos = slot07(pos.x, pos.y, layer, &terrainNormal, 1);
	if (layer > LAYER_GROUND)
		terrainAtPos += 2.5f;
	alignToTerrain(angle, pos, terrainNormal, mtx);
	if (stickToGround)
		mtx.m[11] = terrainAtPos;
	return layer;
}
