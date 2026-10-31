// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272835@Drawable@@QAE_NHH@Z retail 0x00272835 59B
// Evidence: unlock lane; member +0x14C array of ptrs; virtual slot 0xA4 returns ptr plus slot 0x14 takes 2 ints returns bool; callees all rowed-pinned; callers 9 incl 0x000B710D 0x000B75FF 0x000CFDFB; prev-next Drawable same flags.


#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
bool Drawable::rva00272835(int a, int b)
{
	DrawModule **cur = ((DrawModule **)m_modules[0]);
	while (*cur != 0) {
		DrawModule *e = *cur;
		void *p = e->slotA4();
		if (p != 0) {
			DrawModule *q = (DrawModule *)p;
			if (q->slot14(a, b))
				return true;
		}
		++cur;
	}
	return false;
}
