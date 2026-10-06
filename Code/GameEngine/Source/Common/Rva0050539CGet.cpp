// cl: /MD
// ?rva0050539C@Rva0050539C@@QAEPAVPlayer@@XZ, retail 0x0050539C, 8 bytes.
// Evidence: tail-jmp to rowed ?rva005A910E@Rva005A910E@@QAEPAVPlayer@@XZ 0x005A910E; caller 0x002C5FD9 null-checks +0xc then jmps here.
class Player;
class Rva005A910E
{
public:
	Player *rva005A910E();
};
class Rva0050539C
{
	char m_pad[4];
	Rva005A910E *m_04;
public:
	Player *rva0050539C();
};
Player *Rva0050539C::rva0050539C()
{
	return m_04->rva005A910E();
}
