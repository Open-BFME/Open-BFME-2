// ?rva0052E6E6@Rva0052E6E6@@QAE_NHHPAURva0052E6E6Obj@@PAVPolygonTrigger@@H_N@Z
// partial score=0.970943245403677 date=2026-10-09
// ?rva0052E6E6@Rva0052E6E6@@QAE_NHHPAURva0052E6E6Obj@@PAVPolygonTrigger@@H_N@Z
// partial score=0.964 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE /ICode/GameEngine/Source/Common
// ?rva0052E6E6@Rva0052E6E6@@QAE_NHHPAURva0052E6E6Obj@@PAVPolygonTrigger@@H_N@Z retail 0x0052E6E6 558B: cell-corner trigger test then flag/grid update. Evidence: 4x pointInTrigger corners counting in [ebp-4], float compare at this+0x1BE78 via Rva002E6E8AGet range, grid at this+0x460 via PathfindZoneManager::MarkDirty, TheGameLogic findObjectByID + PathfindCell::rva0052DFB1, Rva00366500/Rva0052DA1C/Rva0052E001 setters. Caller at 0x0052FCF4.

class ICoord3D
{
public:
	int x;
	int y;
	int z;
};

class PolygonTrigger
{
public:
	bool pointInTrigger(const ICoord3D &pt);
};

int __cdecl Rva002E6E8AGet(int v);

class Rva00366500
{
public:
	bool rva00366500(int v);
	bool rva0036652D(int v);
};

class PathfindZoneManager
{
public:
	void MarkDirty(int a, int b);
};

class Object;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct Rva0052DFB1Arg
{
	char _00[0x74];
	int m_value;
};

class PathfindCell
{
public:
	bool rva0052DFB1(const Rva0052DFB1Arg *arg);
 bool SetType_Dirty(int);
};

class Rva0052E001
{
public:
	bool rva0052E001(bool v);
};



struct Rva0052E6E6Aux
{
	char _00[0x28];
	int m_28;
};

struct Rva0052E6E6Obj
{
	Rva0052E6E6Aux *m_0;
	int m_4;
	unsigned short m_8;
	unsigned short m_A;
	unsigned m_C;
};

class Rva0052E6E6
{
	char _00[0x460];
public:
	bool rva0052E6E6(int x, int y, Rva0052E6E6Obj *obj, PolygonTrigger *trigger, int idx, bool flag);
};

// ?rva0052E6E6@Rva0052E6E6@@QAE_NHHPAURva0052E6E6Obj@@PAVPolygonTrigger@@H_N@Z present-unmatched
bool Rva0052E6E6::rva0052E6E6(int x, int y, Rva0052E6E6Obj *obj, PolygonTrigger *trigger, int idx, bool flag)
{
	ICoord3D p2;
	ICoord3D p0;
	ICoord3D p1;
	int count = 0;
	p0.y = y * 10;
	p2.y = y * 10 + 10;
	p0.x = x * 10;
	p2.x = x * 10 + 10;
	if (trigger->pointInTrigger(p0))
		count = 1;
	p1 = p0;
	p1.y = p2.y;
	if (trigger->pointInTrigger(p1))
		++count;
	if (trigger->pointInTrigger(p2))
		++count;
	p1 = p0;
	p1.x = p2.x;
	if (trigger->pointInTrigger(p1))
		++count;
	if (count == 0)
		return false;
	if (flag) {
		unsigned field = obj->m_C;
		unsigned v = (field >> 4) & 0x3f;
		if ((unsigned char)Rva002E6E8AGet((int)v) == 0 || *(float *)((char *)this + 0x1BE78 + idx * 4) > *(float *)((char *)this + 0x1BE78 + (int)v * 4))
		{
			if (((Rva00366500 *)obj)->rva00366500(idx))
				((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
		}
		if ((obj->m_C & 0xf) == 4) {
			int id = obj->m_0 ? obj->m_0->m_28 : 0;
			Object *o = TheGameLogic->findObjectByID((ObjectID)id);
			if (o && ((PathfindCell *)obj)->rva0052DFB1((Rva0052DFB1Arg *)o))
				((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
		}
		bool t=((Rva0052E001 *)obj)->rva0052E001(true);
bool b=((Rva00366500 *)obj)->rva0036652D(0); *(unsigned char *)&t=*(volatile unsigned char *)&t|b;
if(*(volatile unsigned char *)&t|((PathfindCell *)obj)->SetType_Dirty(0))
			((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
		obj->m_C &= ~0x10000u;
		return true;
	} else {
		if (count == 4) {
			bool a = ((Rva00366500 *)obj)->rva00366500(1);
			if (a | ((Rva00366500 *)obj)->rva0036652D(0))
				((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
			if ((obj->m_C & 0xf) != 4) {
				if (((PathfindCell *)obj)->SetType_Dirty(0))
					((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
			}
		} else {
			if ((obj->m_C & 0xf) == 8) {
				((Rva00366500 *)obj)->rva00366500(1);
				((PathfindCell *)obj)->SetType_Dirty(0);
				((Rva00366500 *)obj)->rva0036652D(0);
				((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
			}
		}
		if (((Rva0052E001 *)obj)->rva0052E001(false))
			((PathfindZoneManager *)((char *)this + 0x460))->MarkDirty(x, y);
		return true;
	}
}
