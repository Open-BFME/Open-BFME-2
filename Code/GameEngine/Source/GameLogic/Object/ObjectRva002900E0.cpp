// cl: /O1 /DNDEBUG /MD
// ?rva002900E0@Object@@QAEXH@Z retail 0x002900E0 26B.
// Object status-plus-frame setter: setStatus(0x4A true) then store frame at +0x42C.
// Evidence: same-this call to rowed ?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z at 0x002900E7;
// neighbours ?healCompletely@Object (0x0028FF9E) and ?isAbleToAttack@Object (0x00290B73);
// callers pass Object* in ecx plus GameLogic frame in stack e.g. 0x00492BC0 mov ecx edi,
// 0x00379228 mov ecx esi push frame, 0x00492E04 mov ecx ebx; status 0x4A per Rva004AD9B0 TU.
//
// ?rva00290357@Object@@QAEXXZ @0x00290357 108B chain via rowed rva001E4A4E.
// Thiscall void, 11-iteration disabled clear: if rva001E4A4E(i) and frame >=
// m_1cc[i] then clearDisabled(i) plus bit clear in m_1c8 plus for i==1 the
// 0x14e bit2 clear with rva0028AE6D. Evidence: TheGameLogic+0x40 frame,
// rowed 0x001E4A4E plus pin clearDisabled 0x00291CAC plus pin rva0028AE6D,
// callers 0x00245CE0 0x00291E81, neighbours 0x002900FA 0x002903C3.
enum ObjectStatusTypes
{
	STATUS_04 = 4,
	STATUS_4A = 0x4A
};

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;


enum DisabledType
{
	DISABLED_DEFAULT,
	DISABLED_HACKED,
	DISABLED_EMP,
	DISABLED_HELD,
	DISABLED_PARALYZED,
	DISABLED_UNMANNED,
	DISABLED_UNDERPOWERED,
	DISABLED_FREEFALL,
	DISABLED_AWESTRUCK,
	DISABLED_BRAINWASHED,
	DISABLED_SUBDUED,
	DISABLED_SCRIPT_DISABLED,
	DISABLED_SCRIPT_UNDERPOWERED,
	DISABLED_COUNT
};

class Rva001E4A4E
{
public:
	int rva001E4A4E(int bit);
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
	void rva002900E0(int frame);
	void rva002900FA(int frame);
	void rva002903C3();
	void rva002903EF();
	bool clearDisabled(DisabledType type);
	void rva0028AE6D();
	void rva00290357();

private:
	char m_pad00[0x14C];
	unsigned int m_condition14C;
	char m_pad150[0x1C8 - 0x150];
	unsigned int m_1c8[1];
	unsigned int m_1cc[11];
	char m_pad1F8[0x42C - 0x1F8];
	unsigned int m_frame42C;
	unsigned int m_frame430;
};

void Object::rva002900E0(int frame)
{
	setStatus(STATUS_4A, true);
	m_frame42C = frame;
}

void Object::rva002900FA(int frame)
{
	setStatus(STATUS_04, true);
	m_frame430 = frame;
}

void Object::rva002903C3()
{
	unsigned int f = m_frame42C;
	if (f <= 0)
		return;
	if (TheGameLogic->m_frame <= f)
		return;
	setStatus(STATUS_4A, false);
	m_frame42C = 0;
}

void Object::rva002903EF()
{
	unsigned int f = m_frame430;
	if (f <= 0)
		return;
	if (TheGameLogic->m_frame <= f)
		return;
	setStatus(STATUS_04, false);
	m_frame430 = 0;
}

void Object::rva00290357()
{
	unsigned int frame = TheGameLogic->m_frame;
	for (int i = 0; i < 11; ++i)
	{
		if ((unsigned char)((Rva001E4A4E *)this)->rva001E4A4E(i) == 0)
			continue;
		if (frame < m_1cc[i])
			continue;
		clearDisabled((DisabledType)i);
		m_1c8[(unsigned int)i >> 5] &= ~(1U << (i & 31));
		if (i != 1)
			continue;
		if ((((const unsigned char*)&m_condition14C)[2] & 2) == 0)
			continue;
		m_condition14C &= ~0x20000U;
		rva0028AE6D();
	}
}

// Native 290357..2903C3; disabled-mask/timer offsets measured independently.
// Mixed byte test and dword clear preserve the native model-condition access.
