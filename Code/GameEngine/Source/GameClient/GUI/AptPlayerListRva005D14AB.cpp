// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ?rva005D14AB@Rva005D14AB@@QAEXXZ, retail 0x005D14AB 8B.
// Unconditional ptr-chase tail forwarder to rowed 0x005D13D5.
// Evidence: mov ecx [ecx+4] then jmp rowed ?rva005D13D5@Rva005D13D5@@QAEXXZ; caller at 0x00576D65; neighbours AptPlayerList share /O1.
class Rva005D13D5
{
public:
	void rva005D13D5();
};

class Rva005D14AB
{
public:
	void rva005D14AB();

private:
	char m_pad00[4];
	Rva005D13D5 *m_04;
};

void Rva005D14AB::rva005D14AB()
{
	m_04->rva005D13D5();
}
