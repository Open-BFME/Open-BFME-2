// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva0050F6AD@Rva0050F6AD@@QAEXXZ 26B @0x0050F6AD: holder clear that nulls m_ptr then deletes old Rva0050ED58 via rowed dtor plus operator delete. Evidence: rowed callees 0x0050ED58 0x0002FD60 plus callers at 0x00510CDE (outer dtor +0x24) 0x00510236 (add ecx 0x24 thunk) 0x00510225 tail to 0x0050FFC0; neighbours /O1 /EHsc.
class Rva0050ED58
{
public:
	~Rva0050ED58();
};

class Rva0050F6AD
{
public:
	void rva0050F6AD();
private:
	Rva0050ED58 *m_ptr;
};

void Rva0050F6AD::rva0050F6AD()
{
	Rva0050ED58 *tmp = m_ptr;
	m_ptr = 0;
	delete tmp;
}
