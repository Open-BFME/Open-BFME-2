// cl: /O1 /DNDEBUG /MD
//
// ?Rva0048F690Helper@AssaultTransportAIUpdate@@QAEXXZ, retail 0x0048F690
// (94 bytes). Passenger-AI sweep over the +0x3E8 ObjectID array for the
// +0x43C count: each ID resolves through TheGameLogic->findObjectByID, the
// live ones expose their AIUpdateInterface at +0x258, and interfaces whose
// +0x274 word is clear get the 2-param AI command (0x26C347, pinned
// Rva-addressed) with the +0x08 member and constant 2. Layout matches the
// rowed Rva0048F365Helper TU (IDs at +0x3E8, count at +0x43C). The bound is
// checked against the zeroed index up front so the cursor setup stays below
// the branch, reproducing the retail split prologue.

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0026C347Commands
{
public:
	void Rva0026C347Command(void *target, int source);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	Rva0026C347Commands m_commands;
};

class Object
{
public:
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_aiDirect;
	unsigned char m_pad25C[0x274 - 0x25C];
	int m_bfme274;
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
	void Rva0048F690Helper();

private:
	unsigned char m_pad00[8];
	void *m_bfme08;
	unsigned char m_pad0C[0x3E8 - 0x0C];
	ObjectID m_passengerIDs[10];
	unsigned char m_pad410[0x43C - 0x410];
	int m_count43C;
};

void AssaultTransportAIUpdate::Rva0048F690Helper()
{
	int index = 0;
	if (index >= m_count43C)
		return;
	ObjectID *idCursor = m_passengerIDs;
	while (index < m_count43C)
	{
		Object *passenger = TheGameLogic->findObjectByID(*idCursor);
		AIUpdateInterface *commandInterface = passenger != 0 ? passenger->m_aiDirect : 0;
		if (passenger != 0 && commandInterface != 0 && passenger->m_bfme274 == 0)
			commandInterface->m_commands.Rva0026C347Command(m_bfme08, 2);
		++index;
		++idCursor;
	}
}
