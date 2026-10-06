// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// AIUpdateInterface voice responses, retail 0x0026B25A..0x0026B486:
//   0x0026B25A 161B playAttackVoiceResponse(Object *)        message 0x7E6
//   0x0026B2FB 132B playAttackVoiceResponse(const Coord3D *) message 0x7E6
//   0x0026B37F 132B rva0026B37F(const Coord3D *)              message 0x7E8
//   0x0026B403 132B playMoveVoiceResponse(const Coord3D *)    message 0x7E7
// Each address is pinned from its AI command handlers. Donor: Open-BFME-1
// AIUpdateInterface_playMoveVoiceResponse.cpp (Zero Hour AIUpdate.cpp):
// put the owner's drawable in a one-element list and hand it with a
// PickAndPlayInfo to pickAndPlayUnitVoiceResponse. BFME 2 renumbers the
// messages (attack 0x7E6, move 0x7E7) and adds a third position variant
// (0x7E8, posted from the attack-follow-waypoint and command 0x49 paths;
// its name is unknown). getDrawable is the out-of-line Object getter.

#include <list>

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Drawable;

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

// Retail calls the list destructor out of line (the shared pointer-list
// destructor 0x00239AF4); declaring it here keeps /O1 from expanding it.
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
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

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class AIUpdateInterface
{
protected:
	virtual void slot00();
	void playAttackVoiceResponse(Object *victim);
	void playAttackVoiceResponse(const Coord3D *position);
	void rva0026B37F(const Coord3D *position);
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
		DrawableList list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		if (victim)
		{
			info.m_drawTarget = victim->getDrawable();
			info.m_position = *victim->getPosition();
			info.m_air = victim->isUsingAirborneLocomotor();
		}
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_DO_ATTACK_OBJECT, &info);
	}
}

void AIUpdateInterface::playAttackVoiceResponse(const Coord3D *position)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		DrawableList list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_DO_ATTACK_OBJECT, &info);
	}
}

void AIUpdateInterface::rva0026B37F(const Coord3D *position)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		DrawableList list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7E8, &info);
	}
}

void AIUpdateInterface::playMoveVoiceResponse(const Coord3D *position)
{
	Drawable *drawable = m_object->getDrawable();
	if (drawable)
	{
		DrawableList list;
		list.push_back(drawable);
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_DO_MOVETO, &info);
	}
}
