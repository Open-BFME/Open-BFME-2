// cl: /DNDEBUG /MD
//
// ?rva002632B3@AIUpdateInterface@@QBEHXZ, retail 0x002632B3, 20 bytes.
// Leaf int beside AIUpdateInterface tail: machine at +0x30 null-safe
// then non-zero dword at machine+0x50 means 1 else 0. Caller at 0x45AA48.
// No direct callees.

class MiniMachine
{
public:
	char m_pad00[0x50];
	int m_field50;
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	MiniMachine *m_machine;
public:
	int rva002632B3() const;
};

int AIUpdateInterface::rva002632B3() const
{
	MiniMachine *m = m_machine;
	if (m && m->m_field50)
		return 1;
	return 0;
}
