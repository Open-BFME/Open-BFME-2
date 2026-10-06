// cl: /MD
// ??1Rva005F1749@@UAE@XZ @ 0x005F1749 14B
// Evidence: vtable 0x00C78EFC slot0; tail-jmp to rowed ?clear@Rva005F13CC@@QAEXXZ at +4; deleting dtor 0x005F1757 calls it; chain from 0x005F13CC which this session landed.
class Rva005F13CC
{
public:
	void clear();
};

class Rva005F1749
{
public:
	virtual ~Rva005F1749();
private:
	Rva005F13CC m_04;
};

Rva005F1749::~Rva005F1749()
{
	m_04.clear();
}
