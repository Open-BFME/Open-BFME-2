// ?rva0052E6E6@Rva0052E6E6@@QAE_NHHPAURva0052E6E6Obj@@PAVPolygonTrigger@@H_N@Z
// partial score=0.964 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
// ?rva0052E6E6@Rva0052E6E6@@QAE_NHHPAURva0052E6E6Obj@@PAVPolygonTrigger@@H_N@Z retail 0x0052E6E6 558B: cell-corner trigger test then flag/grid update. Evidence: 4x pointInTrigger corners counting in [ebp-4], float compare at this+0x1BE78 via Rva002E6E8AGet range, grid at this+0x460 via Rva005312BE::rva00531431, TheGameLogic findObjectByID + Rva0052DE5B::rva0052DFB1, Rva00366500/Rva0052DA1C/Rva0052E001 setters. Caller at 0x0052FCF4.

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

class Rva005312BE
{
public:
	void rva00531431(int a, int b);
};

class Object;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct Rva0052DFB1Arg
{
	char _00[0x74];
	int m_value;
};

class Rva0052DE5B
{
public:
	bool rva0052DFB1(const Rva0052DFB1Arg *arg);
};

class Rva0052E001
{
public:
	bool rva0052E001(bool v);
};

class Rva0052DA1C
{
public:
	bool rva0052DA1C(int v);
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
				((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
		}
		if ((obj->m_C & 0xf) == 4) {
			int id = obj->m_0 ? obj->m_0->m_28 : 0;
			Object *o = TheGameLogic->findObjectByID((ObjectID)id);
			if (o && ((Rva0052DE5B *)obj)->rva0052DFB1((Rva0052DFB1Arg *)o))
				((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
		}
		volatile bool t = ((Rva0052E001 *)obj)->rva0052E001(true);
		t = (bool)((unsigned char)t | (unsigned char)((Rva00366500 *)obj)->rva0036652D(0));
		if (t | ((Rva0052DA1C *)obj)->rva0052DA1C(0))
			((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
		obj->m_C &= ~0x10000u;
		return true;
	} else {
		if (count == 4) {
			bool a = ((Rva00366500 *)obj)->rva00366500(1);
			if (a | ((Rva00366500 *)obj)->rva0036652D(0))
				((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
			if ((obj->m_C & 0xf) != 4) {
				if (((Rva0052DA1C *)obj)->rva0052DA1C(0))
					((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
			}
		} else {
			if ((obj->m_C & 0xf) == 8) {
				((Rva00366500 *)obj)->rva00366500(1);
				((Rva0052DA1C *)obj)->rva0052DA1C(0);
				((Rva00366500 *)obj)->rva0036652D(0);
				((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
			}
		}
		if (((Rva0052E001 *)obj)->rva0052E001(false))
			((Rva005312BE *)((char *)this + 0x460))->rva00531431(x, y);
		return true;
	}
}
