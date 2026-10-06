// cl: /MD
// ?rva00532330@Rva00532330@@QAE_NPAG0@Z @ 0x00532330 (49B): __thiscall pop two WORDs from top, empty when +0x38==+0x3c.
// Evidence: offsets +0x38/+0x3c compare then WORD loads at top-4/top-2 into out params, add [ecx+0x3c],-4, al 0/1, ret 8; callers at 0x00533000 0x00533049.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva00532330
{
public:
	bool rva00532330(unsigned short *a, unsigned short *b);
	char m_pad[0x38];
	unsigned short *m_begin;
	unsigned short *m_cur;
};
bool Rva00532330::rva00532330(unsigned short *a, unsigned short *b)
{
	if (m_begin == m_cur)
		return false;
	_ReadWriteBarrier();
	*a = *(m_cur - 2);
	*b = *(m_cur - 1);
	m_cur -= 2;
	return true;
}
