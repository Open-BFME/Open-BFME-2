// cl: /O1 /MD
// ?rva005E88DD@Rva005E88DDNullTarget@@QAEXXZ @0x005E88DD 7B
// Chain from 0x005E8892: null-target forwarder mov ecx,[ecx]; jmp rowed body.
// Evidence: pin name; callers 0x005CE215 and rowed 0x005CE9F7 forwarder.
class Rva005E888A
{
public:
	void rva005E8892();
};

class Rva005E88DDNullTarget
{
public:
	void rva005E88DD();

private:
	Rva005E888A *m_ptr;
};

void Rva005E88DDNullTarget::rva005E88DD()
{
	m_ptr->rva005E8892();
}
