// cl: /MD /GX- /Oi-
// ?Rva00590D19Add@@YAXHPAVNetGameCommandMsg@@PBXPAHH@Z @0x00590D19 506B leaf: if-chain on type 0-10 memcpy from base+*off then addArgument
// evidence: calls rowed memcpy thunk @0x006291A8 with sizes 4 4 1 4 4 4 12 8 16 4 2 plus rowed addArgument @0x004D5A7A; caller 0x00591FF5; prev/next /O1 flags
// The caller (NetPacket.cpp) pushes a fifth argument, the message type, which the
// body never reads ([ebp+0x18] is untouched); declaring it keeps both sides on one
// name, so the link resolves the call.
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);

enum GameMessageArgumentDataType
{
	ARG_INT = 0,
	ARG_REAL = 1,
	ARG_BOOL = 2,
	ARG_INT2 = 3,
	ARG_INT3 = 4,
	ARG_INT4 = 5,
	ARG_VEC3 = 6,
	ARG_INT64 = 7,
	ARG_PIXEL = 8,
	ARG_INT5 = 9,
	ARG_SHORT = 10
};

union GameMessageArgumentType
{
	int integer;
	float real;
	unsigned char b;
	unsigned short w;
	int ints[4];
	char bytes[16];
};

struct TriInt
{
	int a, b, c;
};

class NetGameCommandMsg
{
public:
	void addArgument(GameMessageArgumentDataType type, GameMessageArgumentType arg);
};

void __cdecl Rva00590D19Add(int type, NetGameCommandMsg *msg, const void *base, int *off, int /*msgType*/)
{
	GameMessageArgumentType arg;
	if (type == 0)
	{
		int v;
		memcpy(&v, (const char *)base + *off, 4);
		*off += 4;
		arg.integer = v;
		msg->addArgument((GameMessageArgumentDataType)0, arg);
	}
	else if (type == 1)
	{
		float f;
		memcpy(&f, (const char *)base + *off, 4);
		*off += 4;
		arg.real = f;
		msg->addArgument((GameMessageArgumentDataType)1, arg);
	}
	else if (type == 2)
	{
		unsigned char c;
		memcpy(&c, (const char *)base + *off, 1);
		*off += 1;
		arg.b = c;
		msg->addArgument((GameMessageArgumentDataType)2, arg);
	}
	else if (type == 3)
	{
		int v;
		memcpy(&v, (const char *)base + *off, 4);
		*off += 4;
		arg.integer = v;
		msg->addArgument((GameMessageArgumentDataType)3, arg);
	}
	else if (type == 4)
	{
		int v;
		memcpy(&v, (const char *)base + *off, 4);
		*off += 4;
		arg.integer = v;
		msg->addArgument((GameMessageArgumentDataType)4, arg);
	}
	else if (type == 5)
	{
		int v;
		memcpy(&v, (const char *)base + *off, 4);
		*off += 4;
		arg.integer = v;
		msg->addArgument((GameMessageArgumentDataType)5, arg);
	}
	else if (type == 6)
	{
		TriInt tmp;
		memcpy(&tmp, (const char *)base + *off, 12);
		*off += 12;
		*(TriInt *)arg.bytes = tmp;
		msg->addArgument((GameMessageArgumentDataType)6, arg);
	}
	else if (type == 7)
	{
		int tmp[2];
		memcpy(tmp, (const char *)base + *off, 8);
		*off += 8;
		arg.ints[0] = tmp[0];
		arg.ints[1] = tmp[1];
		msg->addArgument((GameMessageArgumentDataType)7, arg);
	}
	else if (type == 8)
	{
		memcpy(arg.bytes, (const char *)base + *off, 16);
		*off += 16;
		msg->addArgument((GameMessageArgumentDataType)8, arg);
	}
	else if (type == 9)
	{
		int v;
		memcpy(&v, (const char *)base + *off, 4);
		*off += 4;
		arg.integer = v;
		msg->addArgument((GameMessageArgumentDataType)9, arg);
	}
	else if (type == 10)
	{
		unsigned short s;
		memcpy(&s, (const char *)base + *off, 2);
		*off += 2;
		arg.w = s;
		msg->addArgument((GameMessageArgumentDataType)10, arg);
	}
}
