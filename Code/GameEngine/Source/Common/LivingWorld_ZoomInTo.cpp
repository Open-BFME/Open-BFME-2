// cl: /O1 /arch:SSE /G7 /MD
//
// ?ZoomInTo@LivingWorld@@QAEXPAX@Z @0x002BE8F9 279B.
// Branch on +0x18/+0x14: +0x18==0 returns; +0x14==1 runs the living-world
// item gate plus mouse/manager notifies; +0x14==0 runs the v38 fill plus the
// 8-key lookup and v58/v4c tails with a float pair to the manager.
// Evidence: caller at 0x002B8A92 passes +0x8c pointer; callees rowed
// 0x002B2B2D 0x0020F27E 0x00211075 0x002B38A3 0x00504138 0x002BE7DB 0x00213AFC;
// globals TheLivingWorldLogic TheMouse TheLivingWorldManager; prev 0x002BE8D4
// next 0x002BECCD share /MD in the same dir.

struct Rva002B3740Item;

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "RegionCenterPointDispatchView.h"

class Rva00211075
{
public:
	void rva00211075();
};

class Rva002B38A3
{
public:
	void *rva002B38A3(int key);
};

class Rva00504138
{
public:
	void *rva00504138(int n);
};

struct Rva002BE7DBValue
{
	float x;
	float y;
	float z;
};

class Rva002BE7DB
{
public:
	float m_x;
	float m_y;
	float m_z;
	Rva002BE7DBValue &rva002BE7DB(Rva002BE7DBValue &out) const;
};

class Rva00213A85
{
public:
	void rva00213AFC(void *value);
};

#include "../../Include/GameLogic/LivingWorldLogic.h"

class Mouse
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual void m18();
	virtual void m19(int flag);
};
extern Mouse *TheMouse;

#include "../../Include/GameLogic/LivingWorldManager.h"
extern LivingWorldManager *TheLivingWorldManager;

struct Rva002BE8F9Pair
{
	float a;
	float b;
};

#include "../../Include/GameLogic/LivingWorldClass.h"

// ?ZoomInTo@LivingWorld@@QAEXPAX@Z
void LivingWorld::ZoomInTo(void *arg)
{
	if (m_18 == 0)
		return;
	switch (field14)
	{
	case 1:
		{
			Rva002B3740Item *item = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B2B2D();
			if (item == 0)
				return;
			int itemValue = *(int *)((char *)item + 0x12C);
			Rva0020F27EHost *host = (Rva0020F27EHost *)TheLivingWorldLogic->fieldB0;
			if (!host->rva0020F27E(itemValue, (int)&field1C))
				return;
			v40(1);
			TheMouse->m19(0);
			v19(2, 0);
			if (TheLivingWorldManager == 0)
				return;
			((Rva00211075 *)TheLivingWorldManager)->rva00211075();
			return;
		}
	case 0:
		{
			Rva002BE7DBValue position;
			Rva002BE7DBValue nodePosition;
			v14(arg, &position);
			void *found = ((Rva002B38A3 *)TheLivingWorldLogic)->rva002B38A3(8);
			if (found != 0)
			{
				void *node = ((Rva00504138 *)((char *)found + 0x0C))->rva00504138(0);
				if (node != 0)
					position = ((Rva002BE7DB *)node)->rva002BE7DB(nodePosition);
			}
			v22(&position);
			v19(1, 0);
			if (TheLivingWorldManager == 0)
				return;
			Rva002BE8F9Pair pair;
			pair.a = position.x;
			pair.b = position.y;
			((Rva00213A85 *)TheLivingWorldManager)->rva00213AFC(&pair);
			return;
		}
	default:
		return;
	}
}
