// cl: /O1 /DNDEBUG /MD
//
// ?Rva0048F6EEHelper@AssaultTransportAIUpdate@@QAEXXZ, retail 0x0048F6EE
// (185 bytes). Dual-command passenger sweep over the +0x3E8 ObjectID array
// for the +0x43C count: each live passenger exposes its AIUpdateInterface at
// +0x258, a second lookup resolves the +0x430 member ID, and then either the
// target command (pinned 0x26C2D9) issues when the +0x441 flag is set with a
// live target, or the position command (pinned 0x295A0F) issues from the
// +0x424 triple when the +0x440 flag is set; either way the interface's
// +0x3C1 byte clears. The two commands are if/else chained (the target path
// jumps over the position check). Counter and cursor stay homed in stack
// slots while constants live in registers, matching the retail prologue.

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0026C2D9Commands
{
public:
	void Rva0026C2D9Command(void *target, int range, int source);
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *target, int range, int source);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	Rva0026C2D9Commands m_commands;
	unsigned char m_pad21[0x3C1 - 0x21];
	unsigned char m_byte3C1;
};

class Object
{
public:
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_aiDirect;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AssaultTransportAIUpdate
{
public:
	void Rva0048F6EEHelper();

private:
	unsigned char m_pad00[0x3E8];
	ObjectID m_passengerIDs[10];
	unsigned char m_pad410[0x424 - 0x410];
	float m_float424;
	float m_float428;
	float m_float42C;
	ObjectID m_member430;
	unsigned char m_pad434[0x43C - 0x434];
	int m_count43C;
	unsigned char m_byte440;
	unsigned char m_byte441;
};

void AssaultTransportAIUpdate::Rva0048F6EEHelper()
{
	int index = 0;
	if (index >= m_count43C)
		return;
	ObjectID *idCursor = m_passengerIDs;
	while (index < m_count43C)
	{
		Object *passenger = TheGameLogic->findObjectByID(*idCursor);
		AIUpdateInterface *commandInterface = passenger != 0 ? passenger->m_aiDirect : 0;
		if (passenger != 0 && commandInterface != 0)
		{
			Object *other = TheGameLogic->findObjectByID(m_member430);
			if (m_byte441 != 0 && other != 0)
				commandInterface->m_commands.Rva0026C2D9Command(other, 0x7FFFFFFF, 0);
			else if (m_byte440 != 0)
				((Rva00295A0FCommands *)&commandInterface->m_commands)->Rva00295A0FCommand(&m_float424, 0x7FFFFFFF, 0);
			commandInterface->m_byte3C1 = 0;
		}
		++index;
		++idCursor;
	}
}
