// cl: /MD
// ?rva00431955@Rva00431955@@QAE_NXZ @0x00431955 35B: thiscall bool check of +8 against 4 selecting Mouse +0x4F24 or +0x4F30 null test. Evidence: unlock lane; global TheMouse; caller 0x00431B79.
class Mouse
{
public:
	char m_pad[0x4f24];
	void *m_4f24;
	char m_pad2[8];
	void *m_4f30;
};

extern Mouse *TheMouse;

class Rva00431955
{
	int m_00;
	int m_04;
	int m_08;
public:
	bool rva00431955();
};

bool Rva00431955::rva00431955()
{
	void *p;
	if (m_08 == 4)
		p = TheMouse->m_4f24;
	else
		p = TheMouse->m_4f30;
	return p != 0;
}
