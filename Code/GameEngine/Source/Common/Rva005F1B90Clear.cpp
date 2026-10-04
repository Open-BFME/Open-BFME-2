// cl: /O1 /MD
// ?rva005F1B90@Rva005F1B90@@QAEXXZ @0x005F1B90 26B: clear holder at +0 deleting via rowed dtor 0x005F18C1 plus rowed delete 0x0002FD60.
// Evidence: calls rowed dtor 0x005F18C1 plus rowed delete; caller jmp at 0x005F1CF1; sibling Rva0042D897Assign.
class Rva005F18C1
{
public:
	~Rva005F18C1();
};

void operator delete(void *p);

class Rva005F1B90
{
public:
	void rva005F1B90();
private:
	Rva005F18C1 *m_00;
};

void Rva005F1B90::rva005F1B90()
{
	Rva005F18C1 *old = m_00;
	m_00 = 0;
	if (old == 0)
		return;
	old->Rva005F18C1::~Rva005F18C1();
	operator delete(old);
}
