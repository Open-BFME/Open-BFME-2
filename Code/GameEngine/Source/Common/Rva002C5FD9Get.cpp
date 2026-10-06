// cl: /MD
// ?rva002C5FD9@Rva002C5FD9@@QAEPAVPlayer@@XZ, retail 0x002C5FD9, 15 bytes.
// Evidence: null-checks +0xc then tail-jmps to rowed ?rva0050539C@Rva0050539C@@QAEPAVPlayer@@XZ 0x0050539C; caller 0x002C6AF5 jmp.
class Player;
class Rva0050539C
{
public:
	Player *rva0050539C();
};
class Rva002C5FD9
{
	char m_00[0xc];
	Rva0050539C *m_0C;
public:
	Player *rva002C5FD9();
};

Player *Rva002C5FD9::rva002C5FD9()
{
	if (m_0C != 0)
		return m_0C->rva0050539C();
	return 0;
}
