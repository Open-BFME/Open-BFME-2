// cl: /O1 /MD
// ??1Rva005FF95C@@UAE@XZ @0x005FF95C 14B
// Opaque dtor: stores vtable 0x0087A530 then tail-calls clear on member at +4.
// Evidence: deleting dtor 0x005FF9A9 calls it; vtable 0x00C7A530 slot0; helper row ?clear@Rva005FF8F8@@QAEXXZ at 0x005FF8F8; caller Rva005FEF65 holds it at +8.
class Rva005FF8F8
{
public:
	void clear();

private:
	void *m_ptr;
};

class Rva005FF95C
{
public:
	virtual ~Rva005FF95C();

private:
	Rva005FF8F8 m_04;
};

Rva005FF95C::~Rva005FF95C()
{
	m_04.clear();
}
