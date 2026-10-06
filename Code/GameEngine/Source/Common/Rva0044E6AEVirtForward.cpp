// cl: /DNDEBUG /MD
// ?rva0044E6AE@Rva0044E6AE@@QAEXXZ @0x0044E6AE 10B
// Virtual forward with (0 1) through slot 0x34. Retail is mov eax [ecx]
// push 1 push 0 call [eax+0x34] ret. Evidence: unlock lane; callers at
// 0x0029314E 0x0049C96F 0x0049C9BD plus jmp at 0x0049C937; unblocks 0x0049C8FC
// 0x00293105 0x0049C93F; abuts prev row 0x0044E6A7 which ends at this start;
// flags copied from next TU ModuleDataBuildFieldParseChained.cpp. Owner
// unproven so the name stays address-derived. Class extended with +0x08
// Object plus +0x40 ID plus +0x89 flag for chain caller 0x0049C8FC below
// which tail-jmps here with the same this; noinline keeps that tail as a
// jmp instead of inlining this 10B body.
enum ObjectID
{
	INVALID_ID = 0
};

class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmd);
};

struct AIUpdateInterface
{
	char m_pad[0x20];
	AICommandInterface m_cmd20;
};

class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai258;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva0044E6AE
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual void virt34(int a, int b);
	__declspec(noinline) void rva0044E6AE();
	void rva0049C8FC();
	char m_pad04[4];
	Object *m_obj08;
	char m_pad0C[0x40 - 0x0C];
	ObjectID m_id40;
	char m_pad44[0x89 - 0x44];
	unsigned char m_flag89;
};

void Rva0044E6AE::rva0044E6AE()
{
	virt34(0, 1);
}

// ?rva0049C8FC@Rva0044E6AE@@QAEXXZ @0x0049C8FC 67B
// Chain caller of the 10B forward above with the same this (tail jmp).
// Retail finds Object via TheGameLogic at 0x00DFE78C with +0x40 ID; returns
// when null or when +0x89 flag is clear; else idles AI via +0x08 Object
// through +0x258 plus 0x20 with CMD_FROM_AI (2); clears the flag; tail-jmps
// here. Evidence: chain lane calls rowed 0x0044E6AE; caller at 0x0049478C;
// prev GiveUpgradeUpdateModuleDataDtor; flags /O1 /DNDEBUG /MD already fit.
void Rva0044E6AE::rva0049C8FC()
{
	Object *found = TheGameLogic->findObjectByID(m_id40);
	if (found == 0)
		return;
	if (m_flag89 == 0)
		return;
	m_obj08->m_ai258->m_cmd20.aiIdle(CMD_FROM_AI);
	m_flag89 = 0;
	return rva0044E6AE();
}
