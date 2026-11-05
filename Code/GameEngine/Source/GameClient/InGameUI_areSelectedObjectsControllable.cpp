// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?areSelectedObjectsControllable@InGameUI@@QBE_NXZ @0x0029C752 39B.
// ZH InGameUI::areSelectedObjectsControllable; receiver is unused.
// Member ABI independently proven by native evaluator42A032 and WB E79EC0.
// Helper over TheInGameUI slot 0x124 selection list: empty list returns
// false, else tail-jmps to rowed Object::isLocallyControlled on [nodeData+0xfc].
// Evidence: TheInGameUI global plus virtual 0x124 same as caller 0x0030EFD5;
// list nodes with data at +8 (STL list layout); +0xfc plus rowed 0x0028B07A;
/// caller 0x0030EFDE tests al al for bool.
#include <list>

// Compare list nodes with a local overload so this TU emits no iterator-base operator!= copy.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a,
                              const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/Drawable.h"

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

bool InGameUI::areSelectedObjectsControllable() const
{
	const _STL::list<Drawable *> *selected = TheInGameUI->getAllSelectedDrawables();
	if (!selected->empty())
		return selected->front()->getObject()->isLocallyControlled();
	return false;
}
