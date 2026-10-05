// cl: /O1 /MD
// ?rva00492089@Rva00492089@@QAEXPAX@Z @0x00492089 44B
// Evidence: callees rowed rva002632EE 0x002632EE and rva00352ECA 0x00352ECA; caller 0x00492114 passes factory pointer; [esi+8]+0x258 AI pointer with +0x20 command iface.
// Links: no literals, callees by row names.
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_FROM_PLAYER2 = 2
};

class Rva00352ECA
{
public:
	void rva00352ECA(void *obj, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	void rva002632EE();
private:
	char m_pad[0x20];
public:
	Rva00352ECA m_cmd;
};

class Thing
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class Rva00492089
{
public:
	char m_pad[8];
	Thing *m_thing;
	void rva00492089(void *arg);
};

void Rva00492089::rva00492089(void *arg)
{
	m_thing->m_ai->rva002632EE();
	m_thing->m_ai->m_cmd.rva00352ECA(arg, CMD_FROM_PLAYER2);
}
