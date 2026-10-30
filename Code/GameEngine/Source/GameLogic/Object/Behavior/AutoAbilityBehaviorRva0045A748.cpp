// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0045A748@AutoAbilityBehavior@@QAEXPAX_N@Z, retail 0x0045A748, 71 bytes.
// If src is null or its string at +0x10 differs from the member at +0x20,
// or the flag differs from zero, copies via the rowed 0x0045A421; otherwise
// clears via the rowed 0x0045A413 plus rowed setWakeFrame FOREVER. Compare
// rides the rowed StringBase::compare at 0x000069D6. Layout follows the rowed
// dtor ??1AutoAbilityBehavior at 0x0045A37F (AsciiString at +0x20, Object at
// +8) and the sibling 0x0045A6FE. Callers at 0x003C32B0 plus 0x003C339E.

class Object;

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"


enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModule
{
	friend class AutoAbilityBehavior;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime delay);
};

struct Rva0045A748Arg
{
	unsigned char m_pad[0x10];
	AsciiString m_str10;
};

class AutoAbilityBehavior
{
public:
	void rva0045A748(void *src, bool flag);
	void rva0045A8C2(Object *source, Object *target, const struct Rva0045A8C2Options *options);
	void rva0045A413();
	void rva0045A421(void *src);

private:
	unsigned char m_pad[8];
	Object *m_obj8;
	unsigned char m_mid[0x20 - 0xC];
	AsciiString m_str20;
};

void AutoAbilityBehavior::rva0045A748(void *src, bool flag)
{
	Rva0045A748Arg *source = (Rva0045A748Arg *)src;
	if (!source || source->m_str10.compare(m_str20) != 0 || flag != false) {
		rva0045A421(source);
		return;
	}
	rva0045A413();
	((UpdateModule *)this)->setWakeFrame(m_obj8, UPDATE_SLEEP_FOREVER);
}

// Target caller45AD11 supplies primary module receiver plus source-target-options.
// Voice-response semantics follow matched AIUpdateInterface siblings; bit3 name unknown.
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
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Drawable;
class Object {
public:
    Drawable *getDrawable() const;
    const Coord3D *getPosition() const { return &position; }
private:
    char pad[0x38]; Coord3D position;
};
class DrawableList : public _STL::list<Drawable *> {
public: ~DrawableList() throw();
};
class PickAndPlayInfo {
public:
    PickAndPlayInfo();
    bool air; Drawable *drawTarget; void *weaponSlot; int specialPowerType;
    unsigned int unknown10; Coord3D position; const Rva0045A8C2Options *commandOptions;
};
class GameMessage { public: enum Type { Rva7E3 = 0x7E3 }; };
bool pickAndPlayUnitVoiceResponse(const DrawableList *, GameMessage::Type, PickAndPlayInfo *);
struct Rva0045A8C2Options { char pad[0x1c]; unsigned int options; };
void AutoAbilityBehavior::rva0045A8C2(Object *source, Object *target, const Rva0045A8C2Options *options)
{
    if ((unsigned char)~(options->options >> 3) & 1) {
        PickAndPlayInfo info;
        info.commandOptions = options;
        if (target) {
            info.position = *target->getPosition();
            info.drawTarget = target->getDrawable();
        }
        DrawableList list;
        Drawable *drawable = source->getDrawable();
        list.push_back(drawable);
        pickAndPlayUnitVoiceResponse(&list, GameMessage::Rva7E3, &info);
    }
}
