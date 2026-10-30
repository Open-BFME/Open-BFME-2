// ?canSelectedObjectsDoSpecialPower@InGameUI@@QBE_NPBVCommandButton@@PBVObject@@PBUCoord3D@@W4SelectionRules@1@IPAV3@@Z
// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?canSelectedObjectsDoSpecialPower@InGameUI@@QBE_NPBVCommandButton@@PBVObject@@PBUCoord3D@@W4SelectionRules@1@IPAV3@@Z,
// retail 0x002A395C..0x002A3AFA (414B), thiscall ret 0x18.
//
// Donor checkout: BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
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
// Callees at the retail REL32s: Object::getDrawable 0x005508E2,
// DrawableList construction through _List_base 0x00239BB0,
// list::insert 0x00239D02 (push_back), ~_List_base 0x00239AF4,
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

#include <list>
// list<Drawable *> nodes come from the freelist pool at VA 0x00DBA5E0 (pop
// 0x002393E2), as in the rowed _List_base ctor 0x00239BB0.
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
// bfme link decl-only begin
namespace _STL
{
template <> inline
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base() throw(); // no EH state store before retail's calls
template <> inline __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
// bfme link decl-only end
// Keep the typed comparison local; the incidental base COMDAT differs from
// the selected provider under this unit's compiler settings.
namespace _STL {
template <class _ListVal, class _ListLeft, class _ListRight>
static inline bool operator!=(const _List_iterator<_ListVal, _ListLeft> &a,
                              const _List_iterator<_ListVal, _ListRight> &b)
{ return a._M_node != b._M_node; }
}
// The selected-drawables list type. The temporary list here is a plain
// list<Drawable *>: retail destroys it with the base destructor 0x00239AF4 on
// the normal path and with the list<Drawable *> destructor thunk 0x00239BAB
// in the unwind funclet.
class DrawableList : public _STL::list<Drawable *> { };

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

	// Each exit below assigns the result; no live false value spans list setup.
	Bool result;
	Drawable *ignoreSelDraw = ignoreSelObj ? ignoreSelObj->getDrawable() : 0;

	_STL::list<Drawable *> tmpList;
	// Insertion keeps the sentinel stable; retain it for the size walk.
	DrawableList::iterator tmpEnd = tmpList.end();
	if (ignoreSelDraw)
		tmpList.push_back(ignoreSelDraw);

	const DrawableList *selected = ((UnsignedInt)_STL::distance(DrawableList::iterator((_STL::_List_node<Drawable *> *)tmpEnd._M_node->_M_next), tmpEnd) > 0) ? static_cast<const DrawableList *>(&tmpList) : TheInGameUI->getAllSelectedDrawables();

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
	result = false;
	if (rule == SELECTION_ALL && count > 0 && qualify == count)
		result = true;
done:
	return result;
}
