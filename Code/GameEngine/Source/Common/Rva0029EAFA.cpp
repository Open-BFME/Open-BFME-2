// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?rva0029EAFA@Rva0029EAFA@@QAEXPBVGameMessage@@@Z @0x0029EAFA 232B
// evidence: chain from 0x0029DE76; rowed GameMessage::getArgument plus Object::rva002907A1 plus Rva0029ACA0::rva0029ACC7
struct Coord3D
{
	float x;
	float y;
	float z;
};

union GameMessageArgumentType
{
	int integer;
	float real;
	int boolean;
	int objectID;
	int drawableID;
	unsigned int teamID;
	struct Loc { float x; float y; float z; } location;
	struct Pix { int x; int y; } pixel;
	struct PixReg { int loX; int loY; int hiX; int hiY; } pixelRegion;
	unsigned int timestamp;
	unsigned short wChar;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;
};

class Rva0029DE76
{
public:
	bool rva0029DE76(const Coord3D *pos);
};

class Rva0029ACA0
{
public:
	void rva0029ACC7(int guard);
};

class Template108
{
public:
	char m_pad[0x108];
	unsigned char m_108;
};

class Object
{
public:
	bool rva002907A1();
	void *m_vtable;
	Template108 *m_template;
	char m_pad08[0xfc - 8];
	Object *m_fc;
};

class ClientFrameSubsystem
{
public:
	virtual void c00();
	virtual void c01();
	virtual void c02();
	virtual void c03();
	virtual void c04();
	virtual void c05();
	virtual void c06();
	virtual void c07();
	virtual void c08();
	virtual void c09();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual int getValue();
};
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

struct Elem0029
{
	Coord3D pos;
	int unk;
	unsigned char flag;
	char pad[3];
};

class Rva0029EAFA
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void d55();
	virtual void d56();
	virtual void d57();
	virtual void d58();
	virtual void d59();
	virtual void d60();
	virtual void d61();
	virtual void d62();
	virtual void d63();
	virtual void d64();
	virtual void d65();
	virtual void d66();
	virtual void d67();
	virtual void d68();
	virtual void d69();
	virtual int v118();
	virtual void e11c();
	virtual void e120();
	virtual void e124();
	virtual void e128();
	virtual Object *v12c();
	void rva0029EAFA(const GameMessage *msg);
private:
	char m_pad04[0x40 - 4];
	Elem0029 m_elems[25];
	int m_count;
};

void Rva0029EAFA::rva0029EAFA(const GameMessage *msg)
{
	if (v118() == 1)
	{
		Object *ret = v12c();
		Object *inner = ret ? ret->m_fc : (Object *)0;
		if (inner)
		{
			if ((inner->m_template->m_108 & 4) != 0)
				return;
			if (!inner->rva002907A1())
				return;
		}
	}
	const GameMessageArgumentType *arg = msg->getArgument(0);
	Coord3D pos;
	pos.x = arg->location.x;
	pos.y = arg->location.y;
	pos.z = arg->location.z;
	if (!((Rva0029DE76 *)this)->rva0029DE76(&pos))
		return;
	((Rva0029ACA0 *)this)->rva0029ACC7(0);
	int v = ((ClientFrameSubsystem *)TheGameClient)->getValue();
	m_elems[m_count].unk = v;
	m_elems[m_count].pos = pos;
	m_elems[m_count].flag = 0;
	m_count++;
	if (m_count != 0x19)
		return;
	m_count = 0;
}
