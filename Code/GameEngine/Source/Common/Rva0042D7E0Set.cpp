// cl: /O1 /MD
// ?rva0042D7E0@Rva0042D7E0@@QAEXPAVRva00579AB7@@@Z @0x0042D7E0 35B: set holder at +0 clearing old via dtor plus delete.
// Evidence: calls rowed dtor 0x00579AB7 plus rowed delete 0x0002FD60; caller 0x0042DF98; sibling Rva0042D7A3Set.
class Rva00579AB7
{
public:
	virtual ~Rva00579AB7();
};

void operator delete(void *p);

class Rva0042D7E0
{
public:
	void rva0042D7E0(Rva00579AB7 *newPtr);
private:
	Rva00579AB7 *m_00;
};

void Rva0042D7E0::rva0042D7E0(Rva00579AB7 *newPtr)
{
	Rva00579AB7 *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->Rva00579AB7::~Rva00579AB7();
	operator delete(old);
}
