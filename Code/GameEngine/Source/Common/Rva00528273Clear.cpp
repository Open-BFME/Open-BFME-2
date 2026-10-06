// cl: /MD
// ?rva00528273@Rva00528273@@QAEXXZ retail 0x00528273 7B
// Evidence: mov eax [ecx]; and [eax+0x1C] 0; ret; caller jmp at 0x002D36A9
class Rva00528273Inner
{
public:
	char m_pad1C[0x1C];
	unsigned int m_flags;
};

class Rva00528273
{
public:
	void rva00528273();
private:
	Rva00528273Inner *m_ptr;
};

void Rva00528273::rva00528273()
{
	m_ptr->m_flags &= 0;
}
