// cl: /O1 /MD /G7
// ?rva005328E2@PathfindZoneManager@@QAEXPAURva005312BERect@@@Z @ 0x005328E2 (230B): __thiscall grid alloc outer/inner from rect, new Item[outer*inner] + new Item*[outer], fill row pointers, set flag at +0x1BA31.
// Evidence: offsets 0x1BA34/0x1BA38/0x1BA3C/0x1BA40 shared with Rva005312BEClear.cpp siblings; rect 16B copy to +0x1BA44 matches Rva005312BERect x0/y0/x1/y1; (x1-x0+16)/16 + (y1-y0+16)/16 via idiv 16; 0x44 elt with eh-vector ctor; caller at 0x002E8E8E.
class GameWindow;
namespace _STL
{
template <class T>
class allocator
{
public:
	allocator() {}
};
template <class T, class Alloc>
class _Vector_base
{
public:
	_Vector_base(const Alloc &a);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}
struct Rva005328B2Vec : _STL::_Vector_base<GameWindow *, _STL::allocator<GameWindow *> >
{
	Rva005328B2Vec(const _STL::allocator<GameWindow *> &alloc = _STL::allocator<GameWindow *>())
		: _STL::_Vector_base<GameWindow *, _STL::allocator<GameWindow *> >(alloc) {}
};
class Rva00531132
{
public:
	Rva00531132() : m_count(0) {}
	void rva00531132(bool add, int value);
	int rva0053117F(int index);
	int m_count;
	int m_items[12];
};
#include <new>

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

class Rva005312BEItem
{
public:
	Rva005312BEItem();
	~Rva005312BEItem();
	Rva00531132 m_set;
	unsigned char m_cleared;
	unsigned char m_35;
	char m_pad36[2];
	Rva005328B2Vec m_p38;
};
Rva005312BEItem::Rva005312BEItem()
	: m_cleared(1), m_35(1)
{
}
Rva005312BEItem::~Rva005312BEItem()
{
	if (m_p38._M_start != 0)
		free(m_p38._M_start);
}
struct Rva005312BERect
{
	int x0;
	int y0;
	int x1;
	int y1;
};
#include "../../Include/GameLogic/PathfindZoneManager.h"
void PathfindZoneManager::rva005328E2(Rva005312BERect *rect)
{
	field1BA44 = *(const IRegion2D *)rect;
	field1BA3C = (rect->x1 - rect->x0 + 16) / 16;
	field1BA40 = (rect->y1 - rect->y0 + 16) / 16;
	int total = field1BA3C * field1BA40;
	field1BA34 = new Rva005312BEItem[total];
	field1BA38 = (Rva005312BEItem **)new unsigned char[field1BA3C * 4];
	for (int i = 0; i < field1BA3C; ++i)
		field1BA38[i] = field1BA34 + i * field1BA40;
	field1BA31 = 1;
}
