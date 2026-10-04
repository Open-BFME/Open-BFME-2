// cl: /O1 /MD
// ?rva0057866D@Rva0057866D@@QAEXPAVRva005D25F2@@@Z @0x0057866D 35B: setter with same-pointer early-out then explicit virtual dtor plus global operator delete on old.
// Evidence: callees rowed 0x005D25F2 ??1Rva005D25F2@@UAE@XZ and rowed 0x0002FD60 ??3@YAXPAX@Z; caller 0x00578761 passes esi=ecx+0x44; same 35B shape as Rva00053D66Assign precedent.
class Rva005D25F2
{
public:
	virtual ~Rva005D25F2();
};

class Rva0057866D
{
public:
	void rva0057866D(Rva005D25F2 *p);
private:
	void *m_ptr;
};

void __cdecl operator delete(void *p);

void Rva0057866D::rva0057866D(Rva005D25F2 *p)
{
	void *old = m_ptr;
	if (p == old)
		return;
	m_ptr = p;
	if (old == 0)
		return;
	((Rva005D25F2 *)old)->Rva005D25F2::~Rva005D25F2();
	operator delete(old);
}
