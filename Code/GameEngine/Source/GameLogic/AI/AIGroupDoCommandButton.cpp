// cl: /O1 /DNDEBUG /MD
//
// AIGroup::groupDoCommandButtonAtPosition, retail 0x0036DCB8 (47 bytes), and
// AIGroup::groupDoCommandButtonAtObject, retail 0x0036DCE7 (47 bytes), ported
// from Zero Hour's GameEngine/Source/GameLogic/AI/AIGroup.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): every member does
// the command button. BFME 2's Object::doCommandButtonAtPosition (0x00297149)
// and doCommandButtonAtObject (0x00297000) take a fourth argument, passed 0
// here. The member list follows AIGroupIsIdle.cpp's view (list head at +4).
#include <list>

class CommandButton;
struct Coord3D;
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Object
{
public:
	void rva00297149(const CommandButton *commandButton, const Coord3D *pos, int cmdSource, int bfmeArg);
	void rva00297000(const CommandButton *commandButton, Object *obj, int cmdSource, int bfmeArg);
	void doCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource)
	{
		rva00297149(commandButton, pos, cmdSource, 0);
	}
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource)
	{
		rva00297000(commandButton, obj, cmdSource, 0);
	}
};

class AIGroup
{
public:
	void groupDoCommandButtonAtPosition( const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource );
	void groupDoCommandButtonAtObject( const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource );

private:
	std::list<Object *> m_memberList;
};

//-------------------------------------------------------------------------------------------------
void AIGroup::groupDoCommandButtonAtPosition( const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource )
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		(*i)->doCommandButtonAtPosition( commandButton, pos, cmdSource );
	}
}

//-------------------------------------------------------------------------------------------------
void AIGroup::groupDoCommandButtonAtObject( const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource )
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		(*i)->doCommandButtonAtObject( commandButton, obj, cmdSource );
	}
}
