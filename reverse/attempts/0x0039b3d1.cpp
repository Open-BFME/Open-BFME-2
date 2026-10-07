// ?rva0039B3D1@Rva003BD306Target@@QAEXM_N@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0039B548@Rva003BD306Target@@QAEXXZ @0x0039B548 55B
// Clear method: zero m_38/m_0C, 0.0f to m_10, global float to m_1C,
// empty AsciiString at +8 via rowed releaseBuffer, zero m_20, then rowed
// Rva003BD306Target::rva0039B28F(1) on same this. Evidence: pin-only callee
// ?rva0039B28F@Rva003BD306Target@@QAEXH@Z proves owner Rva003BD306Target;
// callers 0x0029405F 0x004BDA78; float global g_Va00BBB8D8 (?g_Va00BBB8D8@@3MA);
// neighbours Rva0039B2E6 Rva0039B632 share flags.
#include "ascii_string.h"

extern float g_Va00BBB8D8;

class ExperienceTracker
{
public:
	int rva0039AC23(bool update);
};

class Rva003BD306Target;

class ObjectState
{
public:
	char m_pad00[0x5E7];
	unsigned char m_canUpdate;
};

class BfmeThingEFC
{
public:
	char m_pad00[0x0C];
	int m_lastExperience;
	void bfmeUpdate(int experience);
};

class Object
{
public:
	char m_pad00[0x264];
	Rva003BD306Target *m_target264;
};

enum ObjectID
{
	INVALID_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva003BD306Target : public ExperienceTracker
{
public:
	void rva0039B28F(int v);
	void rva0039B548();
	void rva0039B2C7(int count, int value);
	void rva0039B3D1(float value, bool update);
private:
	char m_pad00[4];
	ObjectState *m_state04;
	AsciiString m_str08;
	int m_0C;
	float m_10;
	char m_pad14[0x1C - 0x14];
	float m_1C;
	unsigned char m_20;
	char m_pad21[0x2C - 0x21];
	BfmeThingEFC *m_updateState2C;
	char m_pad30[0x38 - 0x30];
	int m_38;
	bool m_3C;
	char m_pad3D[3];
};

void Rva003BD306Target::rva0039B548()
{
	m_38 = 0;
	m_10 = 0.0f;
	m_1C = g_Va00BBB8D8;
	m_str08.clear();
	m_0C = 0;
	m_20 = 0;
	rva0039B28F(1);
}

void Rva003BD306Target::rva0039B2C7(int count, int value)
{
	for (; count > 0; --count)
		rva0039B28F(value);
}

void Rva003BD306Target::rva0039B3D1(float value, bool update)
{
	Rva003BD306Target *target = this;
	if (target->m_38 != INVALID_ID)
	{
		do
		{
			Object *object = TheGameLogic->findObjectByID((ObjectID)target->m_38);
			if (!object)
				break;
			target = object->m_target264;
		} while (target->m_38 != INVALID_ID);
	}

	if (target->m_state04->m_canUpdate)
	{
		target->m_10 = value;
		int experience = target->rva0039AC23(target->m_3C);
		if (update && experience != 0 && experience != target->m_updateState2C->m_lastExperience)
			target->m_updateState2C->bfmeUpdate(experience);
	}
}
