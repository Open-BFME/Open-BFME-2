// cl: /MD
//
// ?rva00444362@Rva00444362@@QAEXPAX@Z, retail 0x00444362, 20 bytes.
// Conditionally sets dword at +0x6A4 from 1 to 7; ignores void* arg.
// Evidence: lea ecx+0x6A4 plus cmp 1 plus mov 7 plus ret 4,
// caller 0x004448AF pushes 0x007BAC1C.

class Rva00444362
{
public:
	void rva00444362(void *unused);

private:
	unsigned char m_pad00[0x6A4];
	int m_field;
};

void Rva00444362::rva00444362(void *unused)
{
	(void)unused;
	int *p = &m_field;
	if (*p == 1)
		*p = 7;
}
