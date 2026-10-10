// DOTManager::update, retail 0x0043B73D (WorldBuilder name; WB's body in
// GameLogic/System/DOTManager.cpp carries the __FUNCTION__ string
// "DOTManager::update" and calls findObjectByID, 0x0043B2A4 and 0x0043B72D
// as retail does)
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Evidence: this+4 Rva0043B2E2 tree via rva0043B72D erase; TheGameLogic+0x40
// frame; rowed findObjectByID 0x49DC5, push_back ScienceType 0x2E01C6, Clear
// 0x43B2A4, _M_increment 0x24250, free 0x30830, plus pin attemptDamage
// 0x29848E; caller 0x245941.
//
// Rva0043B2A4Clear (0x0043B2A4) is reached through `this`: retail loads `this`
// into ecx immediately before each call, so it is a thiscall member of this class
// rather than the free stdcall that name also carries. `di` is bound inside the
// obj!=0 arm, which is what defers `lea esi,[ebx+0x14]` past the early exit.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <map>
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum ScienceType
{
	SCIENCE_FIRST = 0
};

class DamageInfo;
class Object;
class Drawable;

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class DamageInfo
{
public:
	char m_pad00[0x10];
	int m_10;
	char m_pad14[0x7c - 0x14];
	unsigned int m_7c;
	unsigned int m_80;
	unsigned int m_84;
};

class Object
{
public:
	void attemptDamage(DamageInfo *damageInfo);
	char m_pad438[0x438];
	unsigned char m_flag438;
};



struct MapNode
{
	int m_color;
	MapNode *m_parent;
	MapNode *m_left;
	MapNode *m_right;
	ScienceType m_key;
	DamageInfo m_data;
};

class Rva0043B2E2
{
public:
	unsigned int rva0043B4EC(const int &x);
	MapNode *m_head;
	int m_count;
};

class DOTManager
{
public:
	void rva0043B725();
	unsigned int rva0043B72D(int x);
	void update();
	void rva0043B2A4Clear(ObjectID id, int value);
private:
	char m_pad[4];
	Rva0043B2E2 m_tree;
};

void DOTManager::update()
{
	unsigned int curFrame = TheGameLogic->m_frame;
	_STL::vector<BfmeE16> vecRaw;
	MapNode *node = m_tree.m_head->m_left;
	while (node != m_tree.m_head)
	{
		ScienceType *keyPtr = &node->m_key;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*keyPtr);
		if (obj == 0)
		{
			((_STL::vector<ScienceType> &)vecRaw).push_back(*keyPtr);
		}
		else
		{
			DamageInfo *di = &node->m_data;
			if (di->m_80 == 0)
			{
				((_STL::vector<ScienceType> &)vecRaw).push_back(*keyPtr);
				this->rva0043B2A4Clear((ObjectID)*keyPtr, di->m_10);
			}
			else if (di->m_84 != 0 && curFrame >= di->m_84)
			{
				obj->attemptDamage(di);
				di->m_84 = di->m_7c + curFrame;
			}
			if ((obj->m_flag438 & 1) != 0)
			{
				((_STL::vector<ScienceType> &)vecRaw).push_back(*keyPtr);
			}
			else if (di->m_80 != 0 && curFrame >= di->m_80)
			{
				((_STL::vector<ScienceType> &)vecRaw).push_back(*keyPtr);
				this->rva0043B2A4Clear((ObjectID)*keyPtr, di->m_10);
			}
		}
		node = (MapNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)node);
	}
	for (ScienceType *p = ((_STL::vector<ScienceType> &)vecRaw).begin(); p != ((_STL::vector<ScienceType> &)vecRaw).end(); ++p)
		rva0043B72D(*p);
//</REGION>
}
