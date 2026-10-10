// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?updateLocalPhantomStructureDisplay@InGameUI@@QAEXXZ, retail 0x002A1158
// (231 bytes, EH frame for one list<int> temporary).
// Name and owner from the WorldBuilder twin 0x00DC4050
// (InGameUI::updateLocalPhantomStructureDisplay, InGameUI.cpp assert 8780
// "InGameUI phantom structure ID missing object!"); retail matches its
// shape. Called directly (not through the vtable) from 0x002A1A67 in the
// 1413-byte InGameUI update body 0x002A1582.
// Body: the phantoms are hidden unless exactly one drawable is selected
// (getSelectCount +0x118 == 1) whose object (Drawable +0xFC) has KindOf bit
// 14 (ThingTemplate byte +0x109 bit 0x40; WB tests KindOf 0xE). For every
// object ID in the list<int> at +0x9C4 (the InGameUICtor/InGameUIDtor
// member) the live object's drawable (rowed Thing::getDrawable 0x005508E2)
// gets setDrawableHidden (0x00271601 pinned name); IDs whose object is gone
// are collected (inlined push_back = rowed list<int>::insert 0x005925E2)
// and removed afterwards (list<int>::remove 0x0047BAF7 pinned name).
// Retail evidence: both loops cache the end node in edi (a local end
// iterator); /EHs keeps the state reset before the rowed _List_base dtor
// 0x004EC395 (ctor 0x004EC36C).
// Facts from retail: slots offsets and callees; names from the WB twin.
#include <list>
#include "../Common/GameLogicObjectLookupView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;

class Drawable;

class ThingTemplate
{
public:
	// KindOf bit 14 (the flag word starts at +0x108).
	bool isKindOf14() const { return (m_kindOf[1] & 0x40) != 0; }

private:
	char m_pad000[0x108];
	unsigned char m_kindOf[4]; // +0x108
};

class Thing
{
public:
	Drawable *getDrawable() const;
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
};

class Object : public Thing
{
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
	Object *getObject() const { return m_object; }

private:
	char m_pad000[0xFC];
	Object *m_object; // +0xFC
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
#define V(n) virtual void r##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	virtual int getSelectCount(); // +0x118
	V(71) V(72) V(73) V(74)
	virtual Drawable *getFirstSelectedDrawable(); // +0x12C
#undef V
	void updateLocalPhantomStructureDisplay();

private:
	char m_pad004[0x9C4 - 4];
	_STL::list<int> m_phantomStructures; // +0x9C4
};

void InGameUI::updateLocalPhantomStructureDisplay()
{
	Bool hide = true;
	if (getSelectCount() == 1)
	{
		Object *obj = getFirstSelectedDrawable()->getObject();
		if (obj && obj->getTemplate()->isKindOf14())
			hide = false;
	}
	_STL::list<int> dead;
	_STL::list<int>::iterator it;
	_STL::list<int>::iterator end = m_phantomStructures.end();
	for (it = m_phantomStructures.begin(); it != end; ++it)
	{
		int id = *it;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
		if (obj)
		{
			Drawable *draw = obj->getDrawable();
			if (draw)
				draw->setDrawableHidden(hide);
		}
		else
			dead.push_back(id);
	}
	end = dead.end();
	for (it = dead.begin(); it != end; ++it)
	{
		int id = *it;
		m_phantomStructures.remove(id);
	}
}
