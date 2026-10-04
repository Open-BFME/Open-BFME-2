// cl: /O1 /MD
// ?rva0042D7A3@Rva0042D7A3@@QAEXPAVRva005794ED@@@Z @0x0042D7A3 35B: set holder at +0 clearing old via dtor plus delete.
// Evidence: calls rowed dtor 0x005794ED plus rowed delete 0x0002FD60; caller 0x0042DAF0; prev Rva0042D71ACond.
class Rva005794ED
{
public:
	virtual ~Rva005794ED();
};

class Rva0042D7A3
{
public:
	void rva0042D7A3(Rva005794ED *newPtr);
private:
	Rva005794ED *m_00;
};

void operator delete(void *p);

void Rva0042D7A3::rva0042D7A3(Rva005794ED *newPtr)
{
	Rva005794ED *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->Rva005794ED::~Rva005794ED();
	operator delete(old);
}
