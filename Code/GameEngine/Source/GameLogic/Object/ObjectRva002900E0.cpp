// cl: /DNDEBUG /MD
// ?rva002900E0@Object@@QAEXH@Z retail 0x002900E0 26B.
// Object status-plus-frame setter: setStatus(0x4A true) then store frame at +0x42C.
// Evidence: same-this call to rowed ?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z at 0x002900E7;
// neighbours ?healCompletely@Object (0x0028FF9E) and ?isAbleToAttack@Object (0x00290B73);
// callers pass Object* in ecx plus GameLogic frame in stack e.g. 0x00492BC0 mov ecx edi,
// 0x00379228 mov ecx esi push frame, 0x00492E04 mov ecx ebx; status 0x4A per Rva004AD9B0 TU.
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


class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
	void rva002900E0(int frame);
	void rva002900FA(int frame);
	void rva002903C3();
	void rva002903EF();

private:
	char m_pad[0x42C];
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
