// cl: /MD
// ?rva003B8B2A@Rva003B8B2A@@QAEHXZ @0x003B8B2A 19B.
// Triple-and predicate: byte +0x4C==0 and dword +0x20==0 and dword +0x1C!=0.
// Evidence: retail xor eax,eax; cmp [ecx+0x4C],al; jne ret; cmp [ecx+0x20],eax; jne ret;
// cmp [ecx+0x1C],eax; je ret; inc eax; ret. Callers at 0x003B92E6 0x003B933E 0x0052243D
// test al,al for the bool.
class Rva003B8B2A
{
	char m_pad00[0x1C];
	int m_field1C;
	int m_field20;
	char m_pad24[0x4C - 0x24];
	unsigned char m_flag4C;
public:
	int rva003B8B2A();
};

int Rva003B8B2A::rva003B8B2A()
{
	int result = 0;
	if (m_flag4C == 0 && m_field20 == 0 && m_field1C != 0)
		result = 1;
	return result;
}
