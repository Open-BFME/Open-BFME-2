// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ?rva00498DF3@Rva00498DF3@@QAEXPAURva00498DF3Arg@@M@Z, retail 0x00498DF3, 59 bytes.
// Evidence: calls rowed 0x00262DD3 AIUpdateInterface::rva00262DD3 and rowed 0x0026C411 AICommandInterface::rva0026C411; Object+0x38 Coord3D and CMD_FROM_AI=2 match donors; caller at 0x00498F9E pushes ebp plus float and tests nothing; this+0xC Object pattern matches caller 0x00498F46.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos38;
};

class AIUpdateInterface
{
public:
	bool rva00262DD3(const Object *obj) const;
	Object *getCurrentVictim() const;
};

class AICommandInterface
{
public:
	void rva0026C411(Object *victim, const Coord3D *pos, CommandSourceType cmdSource);
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

unsigned char __cdecl Rva00498B8BGet(Object *p);

extern float g_00C50244;
// g_00C50244: matched references place it at VA 0xc50244 (retail .rdata value 16.67f).
float g_00C50244 = 16.67f;

struct Rva00498F46Sub08
{
	char m_pad[0x18];
	unsigned char m_flag18;
};

struct Rva00498DF3Mid
{
	char m_pad[0x20];
	char m_cmd20[0x10];
	TurretStateMachine *m_turret30;
};

struct Rva00498DF3Arg
{
	char m_pad[0x258];
	Rva00498DF3Mid *m_mid258;
};

class Rva00498DF3
{
public:
	char m_pad0[0x8];
	Rva00498F46Sub08 *m_ptr08;
	Object *m_objC;
	char m_pad10[0x2C - 0x10];
	int m_field2C;
public:
	void rva00498DF3(Rva00498DF3Arg *arg, float flt);
	void rva00498F46(Rva00498DF3Arg *arg, int u1, int u2);
};

void Rva00498DF3::rva00498DF3(Rva00498DF3Arg *arg, float flt)
{
	Object *obj = m_objC;
	if (!obj)
		return;
	if (!arg)
		return;
	Rva00498DF3Mid *mid = arg->m_mid258;
	if (!mid)
		return;
	if (((AIUpdateInterface *)mid)->rva00262DD3(obj))
		return;
	((AICommandInterface *)((char *)mid + 0x20))->rva0026C411(obj, &obj->m_pos38, CMD_FROM_AI);
}

void Rva00498DF3::rva00498F46(Rva00498DF3Arg *arg, int u1, int u2)
{
	if (m_ptr08->m_flag18 == 0)
		return;
	if (m_field2C != 1)
		return;
	if (!Rva00498B8BGet((Object *)arg))
		return;
	Rva00498DF3Mid *mid = arg->m_mid258;
	if (mid != 0)
	{
		Object *o1 = m_objC;
		if (mid->m_turret30->getGoalObject() == o1)
			return;
		Object *o2 = m_objC;
		if (((AIUpdateInterface *)mid)->getCurrentVictim() == o2)
			return;
	}
	rva00498DF3(arg, g_00C50244);
}
