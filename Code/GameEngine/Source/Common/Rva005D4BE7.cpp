// cl: /O1 /MD
// ?rva005D4BE7@Rva005D4BE7@@QAEXXZ @0x005D4BE7 26B: holder clear deleting Rva005D4913 pointee at +0. Evidence: retail mov esi [ecx] and [ecx] 0 test je call rowed ??1Rva005D4913@@QAE@XZ @0x005D4913 then rowed ??3@YAXPAX@Z @0x0002FD60 caller 0x005D4C97.
class Rva005D4913
{
public:
	~Rva005D4913();
};

class Rva005D4BE7
{
	Rva005D4913 *m_ptr;
public:
	void rva005D4BE7();
};
void Rva005D4BE7::rva005D4BE7()
{
	Rva005D4913 *p = m_ptr;
	m_ptr = 0;
	delete p;
}
