// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// AIUpdateInterface voice responses, retail 0x0026B25A..0x0026B486:
//   0x0026B25A 161B playAttackVoiceResponse(Object *)        message 0x7E6
//   0x0026B2FB 132B playAttackVoiceResponse(const Coord3D *) message 0x7E6
//   0x0026B37F 132B playVoiceEnterStateAttackMove(const Coord3D *)              message 0x7E8
//   0x0026B403 132B playMoveVoiceResponse(const Coord3D *)    message 0x7E7
// Each address is pinned from its AI command handlers. Donor: Open-BFME-1
// AIUpdateInterface_playMoveVoiceResponse.cpp (Zero Hour AIUpdate.cpp):
// put the owner's drawable in a one-element list and hand it with a
// PickAndPlayInfo to pickAndPlayUnitVoiceResponse. BFME 2 renumbers the
// messages (attack 0x7E6, move 0x7E7) and adds a third position variant
// (0x7E8, posted from the attack-follow-waypoint and command 0x49 paths;
// its name is unknown). getDrawable is the out-of-line Object getter.

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
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base() throw(); // no EH state store before retail's calls
}

typedef bool Bool;
typedef float Real;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Drawable;
namespace _STL {
template<> __declspec(noinline) _List_node<Drawable*>* list<Drawable*>::_M_create_node(Drawable*const &value) {
 _List_node<Drawable*>* node=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
 if(&node->_M_data!=0) node->_M_data=value;
 return node;
}
}


class Object
{
public:
	Drawable *getDrawable() const;
	const Coord3D *getPosition() const { return &m_position; }
	Bool isUsingAirborneLocomotor() const;

private:
	unsigned char m_unmodelled_00[0x38];
	Coord3D m_position;
};

// pickAndPlayUnitVoiceResponse's parameter type. The list a caller hands it
// is a plain list<Drawable *>: retail destroys it with the base destructor
// 0x00239AF4 on the normal path and with the list<Drawable *> destructor
// thunk 0x00239BAB in the unwind funclet.
class DrawableList : public _STL::list<Drawable *>
{
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	int m_specialPowerType;
	unsigned int m_unmodelled_10;
	Coord3D m_position;
	unsigned int m_unmodelled_20;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_DO_ATTACK_OBJECT = 0x7E6,
		MSG_DO_MOVETO = 0x7E7,
		MSG_BFME2_0x7E8 = 0x7E8
	};
};

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class AIUpdateInterface
{
protected:
	virtual void slot00();
	void playAttackVoiceResponse(Object *victim);
	void playAttackVoiceResponse(const Coord3D *position);
	void playVoiceEnterStateAttackMove(const Coord3D *position);
	void playMoveVoiceResponse(const Coord3D *position);

private:
	unsigned char m_unmodelled_04[4];
	Object *m_object;
};

void AIUpdateInterface::playAttackVoiceResponse(Object *victim)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		_STL::list<Drawable *> list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		if (victim)
		{
			info.m_drawTarget = victim->getDrawable();
			info.m_position = *victim->getPosition();
			info.m_air = victim->isUsingAirborneLocomotor();
		}
		pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_DO_ATTACK_OBJECT, &info);
	}
}

void AIUpdateInterface::playAttackVoiceResponse(const Coord3D *position)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		_STL::list<Drawable *> list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_DO_ATTACK_OBJECT, &info);
	}
}

void AIUpdateInterface::playVoiceEnterStateAttackMove(const Coord3D *position)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		_STL::list<Drawable *> list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_BFME2_0x7E8, &info);
	}
}

void AIUpdateInterface::playMoveVoiceResponse(const Coord3D *position)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		_STL::list<Drawable *> list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_DO_MOVETO, &info);
	}
}
