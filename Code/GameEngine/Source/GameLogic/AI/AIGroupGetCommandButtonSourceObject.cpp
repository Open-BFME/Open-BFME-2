// cl: /O1 /DNDEBUG /MD
//
// AIGroup::getCommandButtonSourceObject(GUICommandType), retail 0x0036E158
// (107 bytes), pinned. Zero Hour's body (GameLogic/AI/AIGroup.cpp): the
// first member (list at +0x04) whose command set (looked up on
// TheControlBar 0x00E01CFC through the rowed 0x0031D5F8, by the member's
// command-set name from the rowed Object accessor 0x00290E67) holds a button
// of the given type (+0x14) among its 32 slots (rowed
// CommandSet::getCommandButton 0x00409EE8).
typedef int Int;

class AsciiString;

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
private:
	char m_pad[0x14];
	GUICommandType m_command; // +0x14
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name); // ControlBar::findCommandSet
};
class ControlBar;
extern ControlBar *TheControlBar;

class Object
{
public:
	const AsciiString *rva00290E67() const; // Object::getCommandSetString
};

struct ObjectListNode
{
	ObjectListNode *m_next;
	ObjectListNode *m_prev;
	Object *m_data;
};

enum
{
	MAX_COMMANDS_PER_SET = 32
};

class AIGroup
{
public:
	Object *getCommandButtonSourceObject( GUICommandType type );
private:
	int m_00;
	ObjectListNode *m_memberList; // +0x04 (STLport list sentinel)
};

Object *AIGroup::getCommandButtonSourceObject( GUICommandType type )
{
	for( ObjectListNode *it = m_memberList->m_next; it != m_memberList; it = it->m_next )
	{
		Object *obj = it->m_data;
		if( !obj )
			continue;

		const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8( obj->rva00290E67() );
		if( commandSet )
		{
			for( Int j = 0; j < MAX_COMMANDS_PER_SET; j++ )
			{
				const CommandButton *commandButton = commandSet->getCommandButton( j );
				if( commandButton && commandButton->getCommandType() == type )
					return obj;
			}
		}
	}
	return 0;
}
