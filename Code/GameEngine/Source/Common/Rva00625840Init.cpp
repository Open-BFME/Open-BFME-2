// cl: /O2 /Ob0
// ?rva00625840@Rva00625840@@QAEXXZ @0x00625840 40B. Intrusive-list hook twin of
// ?init@Rva009A2350@@QAEXXZ (Code/GameEngine/Source/Common/Rva009A2350Init.cpp):
// same shape with head at owner+0x120 and links at +0x18/+0x1c. Callers pass
// Object+0x4c8 (0x0028ABA0 0x0028B1BE 0x00296713 0x00298B92).

class Rva00625840;

struct Rva00625840Owner
{
	char pad[0x120];
	Rva00625840 *m_120;
};

class Rva00625840
{
	Rva00625840Owner *m_00;
	char pad[0x14];
	void *m_18;
	void *m_1c;

public:
	void rva00625840();
};

void Rva00625840::rva00625840()
{
	if (m_18)
		return;
	char *head = (char *)m_00 + 0x120;
	m_18 = head;
	void *next = *(void **)head;
	m_1c = next;
	if (next)
		((void **)next)[6] = &m_1c;
	m_00->m_120 = this;
}
