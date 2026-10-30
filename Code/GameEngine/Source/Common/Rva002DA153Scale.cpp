// Native singleton VA 0x00DFE77C is GameClient.cpp's class GameClient pointer.
// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/bfmealloc
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

#include "GameLogicObjectLookupView.h"
#include "Common/BfmeAudioEventPrefix136.h"

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad00[0x38];
	BfmeEventPositionView position; // +0x38
	char m_pad44[0x54];
	int m_98; // +0x98
};

extern GameLogic *TheGameLogic;

class ClientHolder
{
public:
	char m_padFC[0xFC];
	Object *m_objFC;
	char m_pad100[0x34A];
	unsigned char m_44A; // +0x44A
};

class ClientFrameSubsystem
{
public:
	virtual void _u000();
	virtual void _u001();
	virtual void _u002();
	virtual void _u003();
	virtual void _u004();
	virtual void _u005();
	virtual void _u006();
	virtual void _u007();
	virtual void _u008();
	virtual void _u009();
	virtual void _u010();
	virtual void _u011();
	virtual void _u012();
	virtual void _u013();
	virtual void _u014();
	virtual void _u015();
	virtual ClientHolder *rva040(ObjectID id); // +0x40
};

extern class GameClient *TheGameClient;

struct Sub08
{
public:
	char m_pad00[0x10];
	float m_10; // +0x10
	char m_pad14[0x8];
	float m_1C; // +0x1C
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
				unsigned int objectFlags = (unsigned int)obj->m_98;
				objectFlags >>= 0x14;
				unsigned char invertedFlags = (unsigned char)objectFlags;
				invertedFlags = (unsigned char)~invertedFlags;
				if ((invertedFlags & 1) == 0)
					return 0.0f;
			}
		}
	}
	else
	{
		ClientHolder *drawable = reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->rva040(m_34);
		if (drawable != 0)
		{
			if (drawable->m_44A == 0)
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
