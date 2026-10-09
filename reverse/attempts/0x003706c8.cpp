// ?groupRotateFiringarc@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.9254123112659699 date=2026-10-10
// ?groupRotateFiringarc@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /ICode/Libraries/Include/Lib
// AIGroup::groupRotateFiringarc, retail 0x003706C8 (205 bytes):
// ?groupRotateFiringarc@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z
// Identity (target): WorldBuilder's debug AIGroup.cpp
// AIGroup::groupRotateFiringarc calls Coord3D::Normalize2D, ACos and the
// AICommandInterface float command 0x0036F6A7 in retail's order (its
// planar length test is inlined in retail).
// Body (target): for each member with an AI, the planar direction from the
// member (Object +0x38) to the position; members within one unit are
// skipped; otherwise the normalized direction's angle (ACos of x, negated
// for negative y) goes to the member's command interface (AI +0x20) with
// the command source.
#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
	float Normalize2D();
	float lengthSqr2D() const { return x * x + y * y; }
};

struct RotateCoord:Coord3D{__forceinline RotateCoord(float X,float Y,float Z){y=Y;x=X;z=Z;}__forceinline RotateCoord(const Coord3D&p){x=p.x;y=p.y;z=p.z;}__forceinline void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}};
float ACos(float x);

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void rva0036F6A7(float angle, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	AICommandInterface *getCommands() { return &m_commands; }

private:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands; // +0x20
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getObservedAI() const { return m_ai; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};

class AIGroup
{
public:
	void groupRotateFiringarc(const Coord3D *pos, CommandSourceType cmdSource);

private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupRotateFiringarc(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (!obj)
			continue;
		AIUpdateInterface *ai = obj->getObservedAI();
		if (!ai)
			continue;
RotateCoord dir(pos->x-obj->getPosition()->x,pos->y-obj->getPosition()->y,pos->z-obj->getPosition()->z);		if (dir.lengthSqr2D() < 1.0f)
			continue;
		dir.Normalize2D();
		float angle;
		if (dir.y < 0.0f)
			angle = -ACos(dir.x);
		else
			angle = ACos(dir.x);
		ai->getCommands()->rva0036F6A7(angle, cmdSource);
	}
}
