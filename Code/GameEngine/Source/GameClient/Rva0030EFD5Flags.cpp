// cl: /EHs-
// stlport
// ?Rva0030EFD5@@YAI_N@Z, retail 0x0030EFD5, 117 bytes.
// Selection capability mask for caller 0x0030F099 (which forwards an
// argument this body never reads). Returns 0 unless
// InGameUI::areSelectedObjectsControllable; otherwise walks TheInGameUI's
// slot 0x124 selection list (STL node data at +8, object at +0xFC) and ORs
// 0x8 for Object 0x002917E8 and 0x200 for Object 0x00291837, stopping at the
// first selected object that contributes either bit.

#include <list>

// Compare list nodes with a local overload so this TU emits no iterator-base operator!= copy.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a,
                              const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class Rva002917E8
{
public:
	bool rva002917E8();	// 0x002917E8
};

#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/Drawable.h"

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

unsigned int Rva0030EFD5(bool alternate)
{
	unsigned int flags = 0;
	if (!TheInGameUI->areSelectedObjectsControllable())
		return 0;
	const _STL::list<Drawable *> *selected = TheInGameUI->getAllSelectedDrawables();
	for (_STL::list<Drawable *>::const_iterator it = selected->begin(); it != selected->end(); ++it)
	{
		Drawable *draw = *it;
		if (draw == 0)
			continue;
		Object *obj = draw->getObject();
		if (obj == 0)
			continue;
		if (reinterpret_cast<Rva002917E8 *>(obj)->rva002917E8())
			flags |= 0x8;
		if (obj->rva00291837())
			flags |= 0x200;
		if (flags & 0x208)
			break;
	}
	return flags;
}