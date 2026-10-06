// cl: /DNDEBUG /MD
//
// ?rva002632C7@AIUpdateInterface@@QBEHXZ, retail 0x002632C7, 23 bytes.
// Leaf int beside AIUpdateInterface tail: machine at +0x30 null-safe
// then field50 non-zero and field54 == -1 means 1 else 0 shares
// zero getter at 0x002632DE. Callers at 295F69 337193 352C56 4C05EB.
// No direct callees.

class MiniMachine
{
public:
	char m_pad00[0x50];
	int m_field50;
	int m_field54;
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	MiniMachine *m_machine;
public:
	int rva002632C7() const;
};

int AIUpdateInterface::rva002632C7() const
{
	MiniMachine *m = m_machine;
	if (m && m->m_field50 && m->m_field54 == -1)
		return 1;
	return 0;
}
