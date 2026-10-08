// Native singleton VA 0x00DFE77C is GameClient.cpp's class GameClient pointer.
// cl: /MD
// ?rva002DA153@Rva002DA153@@QAEMXZ @0x002DA153 121B: float getter with mode branches.
// Evidence: TheGameLogic findObjectByID row 0x49DC5, TheGameClient virtual 0x40,
// BfmeZeroRange, native -1.0f literal at VA 0x00BBB9AC, call sites 0x00059B4C and 0x0005C974,
// neighbour stlport_stringtailrecord144 /O1.
// Mode 1 asks the client slot 0x40 for the id at +0x34 and yields 0 when its
// byte +0x44A is clear; mode 2 yields 0 when the logic object's bit 20 at
// +0x98 is set. Otherwise a -1 scale at +0x28 inherits the +0x08 owner's
// +0x1C value times +0x2C, else +0x2C times +0x28.
// Target evidence: ucomiss/lahf/test ah,44h/jp sends the not-equal case to
// the +0x2C * +0x28 tail, so the -1 test is written as equality.

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	unsigned char m_pad[0x98];
	int m_98;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class ClientFrameSubsystem
{
public:
	virtual void *slot00();
	virtual void *slot04();
	virtual void *slot08();
	virtual void *slot0C();
	virtual void *slot10();
	virtual void *slot14();
	virtual void *slot18();
	virtual void *slot1C();
	virtual void *slot20();
	virtual void *slot24();
	virtual void *slot28();
	virtual void *slot2C();
	virtual void *slot30();
	virtual void *slot34();
	virtual void *slot38();
	virtual void *slot3C();
	virtual void *slot40(void *a);
};

extern class GameClient *TheGameClient;

struct Sub08
{
	char m_pad[0x1C];
	float m_1C;
};

class Rva002DA153
{
public:
	float rva002DA153();
private:
	char m_pad00[8];
	Sub08 *m_08;
	char m_pad0C[0x1C];
	float m_28;
	float m_2C;
	int m_pad30;
	ObjectID m_34;
	int m_38;
};

float Rva002DA153::rva002DA153()
{
	int t = m_38 - 1;
	if (t != 0)
	{
		t = t - 1;
		if (t == 0)
		{
			Object *obj = TheGameLogic->findObjectByID(m_34);
			if (obj != 0)
			{
				unsigned int v = (unsigned int)obj->m_98;
				v >>= 0x14;
				unsigned char c = (unsigned char)v;
				c = (unsigned char)~c;
				if ((c & 1) == 0)
					return 0.0f;
			}
		}
	}
	else
	{
		void *p = reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->slot40((void *)m_34);
		if (p != 0)
		{
			if (*(unsigned char *)((char *)p + 0x44A) == 0)
				return 0.0f;
		}
	}
	if (m_28 == -1.0f)
	{
		if (m_08 != 0)
			return m_08->m_1C * m_2C;
		return 0.0f;
	}
	return m_2C * m_28;
}
