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
class FreelistPool { public: void *pop(); };
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

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82();
	virtual void disregardDrawable(Drawable *draw); // slot 0x14C
};

extern InGameUI *TheInGameUI;

class Object
{
public:
	void friend_bindToDrawable(Drawable *draw);
};

#include "../../Include/GameClient/Drawable.h"

// The lookup-table removal 0x00239C38 is rowed as Rva00239C38::rva00239C38
// (Rva00239C38Erase.cpp): call it by that name, not by GameClient.cpp's
// Zero Hour removeDrawableFromLookupTable body, which is not retail's.
class Rva0055A88BDwordField;
class Rva00239C38
{
public:
	void rva00239C38(const Rva0055A88BDwordField *arg);
};

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
