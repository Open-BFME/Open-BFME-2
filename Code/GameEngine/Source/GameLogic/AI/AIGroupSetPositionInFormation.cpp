// cl: /O1 /DNDEBUG /MD /arch:SSE
// AIGroup::groupSetPositionInFormation, retail 0x0036D6F4 (178 bytes):
// ?groupSetPositionInFormation@AIGroup@@QAEXPBUCoord3D@@0H@Z
// Identity (target): WorldBuilder's debug AIGroup.cpp:1846..1847 body
// AIGroup::groupSetPositionInFormation asserts the position and the goal
// position, and calls, in retail's order, 0x0036D6B4,
// AIGroup::createFormation (0x005494A0), then per member
// AIGroup::rotateOffset (0x0036CBF9), Object::teleportTo (0x0029660C),
// Object::GetRelativeAngle (0x000B4542) and Thing::setOrientation.
// Body (target): each member is placed at the position plus its formation
// offset (Object +0x414/+0x418) rotated toward the goal, keeping the
// position's height, and turned to face the goal; a null member ends the
// walk. The third argument is passed to createFormation with 0; its meaning
// is not recovered.
#include <list>

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Thing
{
public:
	void setOrientation(float angle);
};

class Object : public Thing
{
public:
	// WB names this Object::teleportTo; held here under its existing pin.
	void rva0029660C(const Coord3D *pos, int flags);
	float GetRelativeAngle(const Coord3D *target) const;
	const Coord2D *getFormationOffset() const { return &m_formationOffset; }

private:
	unsigned char m_pad000[0x414];
	Coord2D m_formationOffset; // +0x414
};

class AIGroup
{
public:
	void groupSetPositionInFormation(const Coord3D *position, const Coord3D *goalPosition, int formation);
	void rva0036D6B4();
	void createFormation(int formation, int flags);
	static void rotateOffset(const Coord3D *position, const Coord3D *goalPosition, Coord2D *offset);

private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupSetPositionInFormation(const Coord3D *position, const Coord3D *goalPosition, int formation)
{
	rva0036D6B4();
	createFormation(formation, 0);

	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (obj == 0)
			return;
		Coord2D offset = *obj->getFormationOffset();
		rotateOffset(position, goalPosition, &offset);
		Coord3D dest;
		dest.x = position->x + offset.x;
		dest.y = position->y + offset.y;
		dest.z = position->z;
		obj->rva0029660C(&dest, 0);
		obj->setOrientation(obj->GetRelativeAngle(goalPosition));
	}
}
