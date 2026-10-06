// cl: /O1 /MD
// ?rva003FDD29@Rva003FDD29@@QAEEXZ @0x003FDD29 15B: null-checked tail-jump to rowed int callee, truncation to byte. Evidence: retail mov ecx [ecx+0x38] test je xor al ret jmp 0x0031912E pin QAEHXZ; callers at 0x003FDE1A push eax to virtual and 0x003FE412.
class Rva0031912E
{
public:
	int rva0031912E();
};

class Rva003FDD29
{
	char m_pad[0x38];
	Rva0031912E *m_ptr; // +0x38
public:
	unsigned char rva003FDD29();
};

unsigned char Rva003FDD29::rva003FDD29()
{
	if (m_ptr)
		return (unsigned char)m_ptr->rva0031912E();
	return 0;
}
