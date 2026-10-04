// cl: /O1 /MD
// ?rva0042D897@Rva0042D897@@QAEXPAVRva0057C04F@@@Z @0x0042D897 35B: set holder at +0 clearing old via dtor plus delete.
// Evidence: calls rowed dtor 0x0057C04F plus rowed delete 0x0002FD60; caller 0x0042DD06; sibling Rva0042D7E0Set.
class Rva0057C04F
{
public:
	~Rva0057C04F();
};

void operator delete(void *p);

class Rva0042D897
{
public:
	void rva0042D897(Rva0057C04F *newPtr);
private:
	Rva0057C04F *m_00;
};

void Rva0042D897::rva0042D897(Rva0057C04F *newPtr)
{
	Rva0057C04F *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->Rva0057C04F::~Rva0057C04F();
	operator delete(old);
}
