// cl: /MD
//
// ?rva004B8B0F@Rva004B8B0F@@QAEXXZ, retail 0x004B8B0F, 50 bytes.
// Update-module helper: if the Object at +8 is FAERIE_FIRE (0x26) return;
// else if its AI at +0x258 is null return; else issue AI command 0x31 with
// value 0 source 2 via the +0x20 subobject then setSelectable(false).
// Evidence: testStatus 0x0004E536 plus rowed rva0045003E 0x0045003E plus
// pinned setSelectable 0x0028B76D; caller at 0x004B8B6A via lea ecx,[esi-0x10];
// Object+0x258 AI plus +0x20 command subobject per ScriptActions_doNamedExitAll.

typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_FAERIE_FIRE = 0x26
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;

class AICommandInterface
{
public:
	void rva0045003E(int value, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void setSelectable(Bool selectable);
	AIUpdateInterface *getAIUpdateInterface();
};

class Rva004B8B0F
{
public:
	void rva004B8B0F();

private:
	char m_pad[8];
	Object *m_object; // +8
};

void Rva004B8B0F::rva004B8B0F()
{
	Object *obj = m_object;
	if (obj->testStatus(OBJECT_STATUS_FAERIE_FIRE))
		return;
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)obj + 0x258);
	if (!ai)
		return;
	ai->m_command.rva0045003E(0, CMD_FROM_AI);
	obj->setSelectable(false);
}
