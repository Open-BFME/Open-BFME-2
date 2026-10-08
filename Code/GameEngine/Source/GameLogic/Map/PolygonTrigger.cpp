// cl: /O1 /EHsc /MD /arch:SSE
// PolygonTrigger.cpp -- PolygonTrigger members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Zero Hour's addPolygonTrigger
// (GameLogic/Map/PolygonTrigger.cpp): BFME2 keeps the list head behind the
// holder pointer at 0x00DBD0F4 (see Common/Rva002E36D5Find.cpp) and the next
// link at +0x3C. The region/bounds members came from the former split unit
// Common/PolygonTriggerRegionRva0007E03A.cpp (rehomed per tu_map).

#include <math.h>

class PolygonTrigger;

struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

struct FloatRect0073CE30
{
	float x1;
	float y1;
	float x2;
	float y2;
};

// PolygonTrigger's shape member at +0x08; its region getter is the rowed
// Rva0030B719Shape::rva0030B6E3 0x0030B6E3.
class Rva0030B719Shape
{
public:
	Region2D rva0030B6E3();
};

class Rva002E373CHolder
{
public:
	PolygonTrigger *m_head;
};

extern Rva002E373CHolder *g_Va00DBD0F4;	// ThePolygonTriggerListPtr holder

class PolygonTrigger
{
public:
	static void addPolygonTrigger(PolygonTrigger *pTrigger);
	PolygonTrigger *getNext() { return m_nextPolygonTrigger; }
	Region2D rva0007E03A();
	void getBounds(FloatRect0073CE30 *rect);
	void getBounds(int *out);

private:
	unsigned char m_pad00[0x08];
	Rva0030B719Shape m_shape;	// +0x08
	unsigned char m_pad09[0x3c - 0x09];
	PolygonTrigger *m_nextPolygonTrigger;	// +0x3C
};

// PolygonTrigger::addPolygonTrigger, retail 0x002E36EF.
void PolygonTrigger::addPolygonTrigger(PolygonTrigger *pTrigger)
{
	PolygonTrigger *pTrig;
	for (pTrig = g_Va00DBD0F4->m_head; pTrig; pTrig = pTrig->getNext())
	{
		if (pTrig == pTrigger)
			return;
	}
	pTrigger->m_nextPolygonTrigger = g_Va00DBD0F4->m_head;
	g_Va00DBD0F4->m_head = pTrigger;
}

// ?rva0007E03A@PolygonTrigger@@QAE?AURegion2D@@XZ retail 0x0007E03A 19B: region of
// m_shape (add ecx,8) via the rowed 0x0030B6E3.
Region2D PolygonTrigger::rva0007E03A()
{
	return m_shape.rva0030B6E3();
}

// ?getBounds@PolygonTrigger@@QAEXPAUFloatRect0073CE30@@@Z @ 0x002E3954 (36B). PolygonTrigger rect copy: if out is null return; else take region via rowed rva0007E03A 0x0007E03A and copy 16B to out. Callers 0x0035784F 0x00357912 0x003C0169 name it; LINK 2 files 306B. Honest pin name.
void PolygonTrigger::getBounds(FloatRect0073CE30 *rect)
{
	if (!rect)
		return;
	*(Region2D *)rect = rva0007E03A();
}

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// ?getBounds@PolygonTrigger@@QAEXPAH@Z retail 0x002E3978 155B
// PolygonTrigger int-bounds: null-checked; region via rowed rva0007E03A then
// floor x_min/y_min and ceil x_max/y_max into 4 ints. Callers 0x003665E3
// 0x0027F196 name PolygonTrigger this. floor/ceil come from <math.h> (the
// CRT import declarations); a hand prototype missed retail's codegen.
void PolygonTrigger::getBounds(int *out)
{
	if (!out)
		return;
	Region2D r = rva0007E03A();
	out[0] = fast_float2long_round(floor(r.x_min));
	out[1] = fast_float2long_round(floor(r.y_min));
	out[2] = fast_float2long_round(ceil(r.x_max));
	out[3] = fast_float2long_round(ceil(r.y_max));
}
