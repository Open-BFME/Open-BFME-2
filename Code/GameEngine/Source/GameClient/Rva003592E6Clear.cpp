// cl: /GX-
// ?rva003592E6@Rva003592E6@@QAEXXZ @0x003592E6 (20B):
// Clear two embedded rb-tree maps at +0xc and +0x18 via rowed 0x00358F7C; second is tail jmp.
// Evidence: calls 0x00358F7C twice (call plus jmp); same /O1 /GX- /arch:SSE2 as neighbours.
struct Header00358E6A;

class Rva00358E6A
{
	Header00358E6A *m_00;
	int m_04;
public:
	void rva00358F7C();
};

class Rva003592E6
{
	char m_00[12];
	Rva00358E6A m_0c;
	char m_14[4];
	Rva00358E6A m_18;
public:
	void rva003592E6();
};

void Rva003592E6::rva003592E6()
{
	m_0c.rva00358F7C();
	m_18.rva00358F7C();
}
