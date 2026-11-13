// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// GameClient::destroyDrawable, retail 0x00239F40 (96 bytes):
// ?destroyDrawable@GameClient@@UAEXPAVDrawable@@@Z
// Identity (target): WorldBuilder's debug GameClient.cpp
// GameClient::destroyDrawable calls, in retail's order, the drawable's
// 0x00270234, TheInGameUI's slot 0x14C, Drawable::removeFromList,
// Object::friend_bindToDrawable / Drawable::friend_bindToObject with null,
// the lookup-table removal 0x00239C38 and the pending-delete list's
// push_back.
// Donor (Zero Hour GameClient::destroyDrawable): disregard the drawable in
// the UI, unlink it from the master list (+0x14) and the id lookup table,
// sever its object link (Drawable +0xFC). BFME 2 deltas (target): the
// drawable's own 0x00270234 step comes first, and instead of deleting it
// the drawable is queued on the +0xE4 list.
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
#include "../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
}

class Drawable;
namespace _STL {
template<> __declspec(noinline) _List_node<Drawable*>* list<Drawable*>::_M_create_node(Drawable*const &value) {
 _List_node<Drawable*>* node=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
 if(&node->_M_data!=0) node->_M_data=value;
 return node;
}
}

class Object;

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/Drawable.h"

// The lookup-table removal 0x00239C38 is rowed as Rva00239C38::rva00239C38
// (Rva00239C38Erase.cpp): call it by that name, not by GameClient.cpp's
// Zero Hour removeDrawableFromLookupTable body, which is not retail's.
class Rva0055A88BDwordField;
#include "../../Include/GameClient/Rva00239C38.h"

class GameClient
{
public:
	virtual void destroyDrawable(Drawable *draw);

private:
	unsigned char m_pad004[0x14 - 0x04];
	Drawable *m_drawableList; // +0x14
	unsigned char m_pad018[0xE4 - 0x18];
	_STL::list<Drawable *> m_drawablesToDelete; // +0xE4
};

void GameClient::destroyDrawable(Drawable *draw)
{
	draw->rva00270234();
	// remove any notion of the Drawable in the in game user interface
	TheInGameUI->disregardDrawable(draw);
	// remove from the master list
	draw->removeFromList(&m_drawableList);
	// if the drawable has an object, sever the link
	Object *obj = draw->getObject();
	if (obj)
	{
		obj->friend_bindToDrawable(0);
		draw->friend_bindToObject(0);
	}
	// remove from the drawable lookup table
	reinterpret_cast<Rva00239C38 *>(this)->rva00239C38(reinterpret_cast<const Rva0055A88BDwordField *>(draw));
	m_drawablesToDelete.push_back(draw);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x00270234 -> ?rva00270234@Rva00270234@@QAEXXZ
#pragma comment(linker, "/alternatename:?rva00270234@Drawable@@QAEXXZ=?rva00270234@Rva00270234@@QAEXXZ")
