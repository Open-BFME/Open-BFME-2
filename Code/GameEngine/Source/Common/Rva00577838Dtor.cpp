// cl: /DNDEBUG /MD
// ??1Rva00577838@@UAE@XZ @0x00577838 14B: vtable 0x0086E978 plus member at plus4 via tail-jmp to pinned base 0x00577010. Evidence: pin ??1 plus caller deleting dtor 0x00577891 plus vtable store plus add ecx 4 plus jmp.
class Rva00577010
{
public:
	~Rva00577010();
private:
	void *m_value;
};

class Rva00577838
{
public:
	virtual ~Rva00577838();
private:
	Rva00577010 m_04;
};

Rva00577838::~Rva00577838()
{
}
