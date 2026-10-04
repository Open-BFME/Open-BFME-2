// ?rva002EAC14@Rva002EAC14@@QAEXPBI@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
// ?rva002EAC14@Rva002EAC14@@QAEXPBI@Z @0x002EAC14 45B
// Ring-buffer push: slots[0x200] at +0, count at +0x804 with wrap at 0x1FF.
// Evidence: [ecx+eax*4] store then sub/neg/sbb/and wrap and ret 4; callers at 0x002EBD58/0x002EBD8E pass &stack-local.
class Rva002EAC14
{
public:
	void rva002EAC14(const unsigned int *p);
private:
	unsigned int m_slots[0x200];
	int m_read;
	int m_write;
};

// ?rva002EAC14@Rva002EAC14@@QAEXPBI@Z present-unmatched
void Rva002EAC14::rva002EAC14(const unsigned int *p)
{
	int idx = m_write;
	m_slots[idx] = *p;
	m_write = (m_write + 1) & ((m_write - 0x1FF) ? -1 : 0);
}
