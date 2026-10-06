// cl: /DNDEBUG /MD
// ?rva0052518E@Rva0052518E@@QAEXPAX@Z, retail 0x0052518E 15B unlock via two-level store.
// Setter: m_ptr->+0x10->+0x18 = arg; unblocks 0x002D36C3.
// Evidence: no callees; caller jmp 0x002D36D0; prev 0x00525162 same flags.
class Rva0052518EInner
{
public:
	unsigned char m_pad[0x18];
	void *m_18;
};

class Rva0052518EMid
{
public:
	unsigned char m_pad[0x10];
	Rva0052518EInner *m_10;
};

class Rva0052518E
{
public:
	Rva0052518EMid *m_ptr;
	void rva0052518E(void *p);
};

void Rva0052518E::rva0052518E(void *p)
{
	m_ptr->m_10->m_18 = p;
}
