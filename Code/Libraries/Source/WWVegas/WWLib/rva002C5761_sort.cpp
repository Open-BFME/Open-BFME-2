// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002C5761@GameWindowManager@@QAEXPAVGameWindow@@@Z @0x002C5761 162B: collect a window's
// doubly-linked child nodes via vector then sort and relink. Both callers (0x005A1F47,
// 0x005BAA20) load TheWindowManager into ECX and push one window; the body ignores ECX (ret 4).
// Evidence: calls rowed push_back ModuleData 0x004DFCB0, sort int 0x002C571E, base BfmeE16 0x00211E58, free 0x00030830;
// list offsets +0x204 head, +0x1f8 next, +0x1fc prev; comparator push 0x006C0C45; callers 0x005A1F47 and 0x005BAA20.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <algorithm>

#include "../../../Include/Lib/BfmeE16.h"
class ModuleData;

struct RvaNode
{
	char m_pad[0x1f8];
	RvaNode *m_next;
	RvaNode *m_prev;
};

struct RvaHead
{
	char m_pad[0x204];
	RvaNode *m_head;
};

// ??$sort@PAHP6A_NHH@Z@_STL@@YAXPAH0P6A_NHH@Z@Z present-unmatched
class BfmeItemEG;
bool bfmeLess(const BfmeItemEG *, const BfmeItemEG *); // rowed 0x002C0C45, the sort comparator
class GameWindow;
#include "../../../../GameEngine/Include/GameClient/GameWindowManager.h"

void GameWindowManager::rva002C5761(GameWindow *window)
{
	RvaHead *obj = (RvaHead *)window;
	_STL::vector<BfmeE16> tmp;
	RvaNode **headLoc = &obj->m_head;
	const ModuleData *cur = (const ModuleData *)*headLoc;
	while (cur) {
		(( _STL::vector<const ModuleData *> *)&tmp)->push_back(cur);
		cur = (const ModuleData *)((RvaNode *)cur)->m_next;
	}
	typedef bool (__cdecl *CmpFn)(int, int);
	CmpFn cmp = (CmpFn)&bfmeLess;
	_STL::sort((int *)(( _STL::vector<const ModuleData *> *)&tmp)->begin(),
		(int *)(( _STL::vector<const ModuleData *> *)&tmp)->end(), cmp);
	RvaNode *prev = 0;
	RvaNode **dst = headLoc;
	int *src = (int *)(( _STL::vector<const ModuleData *> *)&tmp)->begin();
	int *fin = (int *)(( _STL::vector<const ModuleData *> *)&tmp)->end();
	if (src != fin) {
		do {
			RvaNode *rvaNode = (RvaNode *)*src;
			*dst = rvaNode;
			rvaNode->m_prev = prev;
			prev = *dst;
			++src;
			dst = &prev->m_next;
		} while (src != fin);
	}
	*dst = 0;
}
