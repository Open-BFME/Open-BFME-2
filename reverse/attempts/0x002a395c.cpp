// ?canSelectedObjectsDoSpecialPower@InGameUI@@QBE_NPBVCommandButton@@PBVObject@@PBUCoord3D@@W4SelectionRules@1@IPAV3@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ob2
//
// ?canSelectedObjectsDoSpecialPower@InGameUI@@QBE_NPBVCommandButton@@PBVObject@@PBUCoord3D@@W4SelectionRules@1@IPAV3@@Z,
// retail 0x002A395C..0x002A3AFA (414B), thiscall ret 0x18.
//
// Donor: Zero Hour InGameUI.cpp InGameUI::canSelectedObjectsDoSpecialPower
// (special power template +0x44 and options +0x1C of the command button;
// object-target bits 0x7 and NEED_TARGET_POS 0x20; the ignored selection
// object's drawable in a temporary DrawableList, else the selected
// drawables from TheInGameUI slot 73; per drawable the ActionManager
// special power checks with CMD_FROM_PLAYER; SELECTION_ANY / SELECTION_ALL).
// BFME 2 differences read from retail:
//   * the sanity checks fail only when the other target kind is not also
//     accepted (a command taking an object or a position passes with either);
//   * a command needing a target tries the object check (when an object is
//     given) and then the position check (when a position is given), each
//     counted separately;
//   * the three ActionManager checks take a trailing bool (true).
// Callees at the retail REL32s: pinned Object::getDrawable 0x005508E2,
// DrawableList construction through _List_base 0x00239BB0, pinned
// list::insert 0x00239D02 (push_back), pinned ~DrawableList 0x00239AF4,
// ActionManager::canDoSpecialPower 0x0041CCD5 / canDoSpecialPowerAtObject
// 0x0041CFCC / pinned canDoSpecialPowerAtLocation 0x0041D60B. Callers
// 0x0042A1DE and 0x0042A2A8. WorldBuilder twin 0xDBAA80 (callgraph lead).

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Drawable;
class Object;
class SpecialPowerTemplate;
struct Coord3D;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Object
{
public:
	Drawable *getDrawable() const;
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad000[0xFC];
	Object *m_object;			// +0xFC
};

class CommandButton
{
public:
	UnsignedInt getOptions() const { return m_options; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
private:
	unsigned char m_pad00[0x1C];
	UnsignedInt m_options;			// +0x1C
	unsigned char m_pad20[0x44 - 0x20];
	const SpecialPowerTemplate *m_specialPower;	// +0x44
};

class ActionManager
{
public:
	Bool canDoSpecialPower(const Object *obj, const SpecialPowerTemplate *spTemplate, CommandSourceType commandSource, UnsignedInt commandOptions, Bool checkSourceRequirements);
	Bool canDoSpecialPowerAtObject(const Object *obj, const Object *target, CommandSourceType commandSource, const SpecialPowerTemplate *spTemplate, UnsignedInt commandOptions, Bool checkSourceRequirements);
	Bool canDoSpecialPowerAtLocation(const Object *obj, const Coord3D *loc, CommandSourceType commandSource, const SpecialPowerTemplate *spTemplate, const Object *objectInWay, UnsignedInt commandOptions, Bool checkSourceRequirements);
};
extern ActionManager *TheActionManager;

struct DrawableListNode
{
	DrawableListNode *next;
	DrawableListNode *prev;
	Drawable *value;
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T> struct _Nonconst_traits
{
};
template <class T, class Traits> struct _List_iterator
{
	_List_iterator(DrawableListNode *n) : _M_node(n) {}
	_List_iterator(const _List_iterator &x) : _M_node(x._M_node) {}
	DrawableListNode *_M_node;
};
template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
	DrawableListNode *_M_node;
};
template <class T, class A> class list : public _List_base<T, A>
{
public:
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;
	list(const A &a = A()) : _List_base<T, A>(a) {}
	iterator insert(iterator pos, const T &x);
	void push_back(const T &x) { insert(iterator(this->_M_node), x); }
};
}

class DrawableList : public _STL::list<Drawable *, _STL::allocator<Drawable *> >
{
public:
	__declspec(nothrow) ~DrawableList();

	class const_iterator
	{
	public:
		const_iterator(DrawableListNode *n) : node(n) {}
		bool operator!=(const const_iterator &b) const { return node != b.node; }
		Drawable *operator*() const { return node->value; }
		const_iterator &operator++() { node = node->next; return *this; }
	private:
		DrawableListNode *node;
	};
	const_iterator begin() const { return const_iterator(_M_node->next); }
	const_iterator end() const { return const_iterator(_M_node); }
	UnsignedInt size() const
	{
		UnsignedInt n = 0;
		for (DrawableListNode *p = _M_node->next; p != _M_node; p = p->next)
			++n;
		return n;
	}
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class InGameUI
{
public:
	enum SelectionRules
	{
		SELECTION_ANY = 0,
		SELECTION_ALL = 1
	};

	PAD_VIRTUALS10(s0) PAD_VIRTUALS10(s1) PAD_VIRTUALS10(s2) PAD_VIRTUALS10(s3)
	PAD_VIRTUALS10(s4) PAD_VIRTUALS10(s5) PAD_VIRTUALS10(s6)
	virtual void s70(); virtual void s71(); virtual void s72();
	virtual const DrawableList *getAllSelectedDrawables() const;	// slot 73

	Bool canSelectedObjectsDoSpecialPower(const CommandButton *command, const Object *objectToInteractWith, const Coord3D *position, SelectionRules rule, UnsignedInt commandOptions, Object *ignoreSelObj) const;
};
extern InGameUI *TheInGameUI;

Bool InGameUI::canSelectedObjectsDoSpecialPower(const CommandButton *command, const Object *objectToInteractWith, const Coord3D *position, SelectionRules rule, UnsignedInt commandOptions, Object *ignoreSelObj) const
{
	const SpecialPowerTemplate *spTemplate = command->getSpecialPowerTemplate();

	Bool doAtPosition = (command->getOptions() & 0x20) != 0;
	Bool doAtObject = (command->getOptions() & 0x7) != 0;

	if (doAtObject && !objectToInteractWith && !doAtPosition)
		return false;
	if (doAtPosition && !position && !doAtObject)
		return false;

	Bool result = false;
	Drawable *ignoreSelDraw = ignoreSelObj ? ignoreSelObj->getDrawable() : 0;

	DrawableList tmpList;
	if (ignoreSelDraw)
		tmpList.push_back(ignoreSelDraw);

	const DrawableList *selected = (tmpList.size() > 0) ? &tmpList : TheInGameUI->getAllSelectedDrawables();

	Int count = 0;
	Int qualify = 0;

	for (DrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it)
	{
		Drawable *other = *it;
		count++;

		if (!doAtObject && !doAtPosition)
		{
			if (TheActionManager->canDoSpecialPower(other->getObject(), spTemplate, CMD_FROM_PLAYER, commandOptions, true))
			{
				if (rule == SELECTION_ANY)
					{ result = true; goto done; }
				qualify++;
			}
		}
		else
		{
			if (doAtObject && objectToInteractWith)
			{
				if (TheActionManager->canDoSpecialPowerAtObject(other->getObject(), objectToInteractWith, CMD_FROM_PLAYER, spTemplate, commandOptions, true))
				{
					if (rule == SELECTION_ANY)
						{ result = true; goto done; }
					qualify++;
				}
			}
			if (doAtPosition && position)
			{
				if (TheActionManager->canDoSpecialPowerAtLocation(other->getObject(), position, CMD_FROM_PLAYER, spTemplate, objectToInteractWith, commandOptions, true))
				{
					if (rule == SELECTION_ANY)
						{ result = true; goto done; }
					qualify++;
				}
			}
		}
	}
	if (rule == SELECTION_ALL && count > 0 && qualify == count)
		result = true;
done:
	return result;
}
