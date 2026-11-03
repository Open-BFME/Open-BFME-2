// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva0027F1DD@BfmeThingCME@@QAEXPAUCoord3D@@M@Z, retail 0x0027F1DD, 177 bytes, ret 8.
// Walks the pointer vector at +0x578..+0x57C; every entry with a nonzero id at +0x0C whose
// position lies within the given 2D radius of the argument position is retired: its id is
// removed from the fire grid (rowed 0x0028641F, when TheTriggerManager exists), the entry
// is reset through rowed 0x0027D098, the id is passed to slot 22 (+0x58) of the object at
// VA 0x00DFF080 and the game-logic frame (+0x40) is stored at +0x1910. Evidence: target
// bytes and the rowed callees (GetLength2D 0x0040599F included); names are neutral views.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
class G00DFF080Obj;
extern G00DFF080Obj *TheTerrainVisual;
class GameLogic;
extern GameLogic *TheGameLogic;

#include "../../Include/GameLogic/FireLogicSystem.h"

class G00DFF080Obj
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void slot22(int id);
};

struct Rva0027F1DDFrames
{
	char m_pad[0x40];
	int m_frame40;
};

class Rva0027D098
{
public:
	void rva0027D098();
	Coord3D m_position;
	int m_id;
};

class BfmeThingCME
{
public:
	void rva0027F1DD(Coord3D *position, float radius);
private:
	char m_pad[0x578];
	Rva0027D098 **m_begin;
	Rva0027D098 **m_end;
	char m_pad580[0x1910 - 0x580];
	int m_frame1910;
};

void BfmeThingCME::rva0027F1DD(Coord3D *position, float radius)
{
	for (Rva0027D098 **it = m_begin; it != m_end; ++it)
	{
		if ((*it)->m_id == 0)
			continue;
		volatile Coord3D *source = position;
		float px = source->x;
		float py = source->y;
		float pz = source->z;
		float dx = px - (*it)->m_position.x;
		float dy = py - (*it)->m_position.y;
		float dz = pz - (*it)->m_position.z;
		_ReadWriteBarrier();
		Coord3D delta;
		delta.x = dx;
		delta.y = dy;
		delta.z = dz;
		if (!(delta.GetLength2D() <= radius))
			continue;
		int id = (*it)->m_id;
		if (TheTriggerManager)
			((FireLogicSystem *)TheTriggerManager)->rva0028641F(id, &(*it)->m_position);
		(*it)->rva0027D098();
		TheTerrainVisual->slot22(id);
		m_frame1910 = ((Rva0027F1DDFrames *)TheGameLogic)->m_frame40;
	}
}
