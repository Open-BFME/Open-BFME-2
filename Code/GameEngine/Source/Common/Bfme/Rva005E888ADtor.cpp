// cl: /MD
// ??1Rva005E888A@@QAE@XZ @0x005E888A 8B
// Non-virtual dtor holding rowed member Rva005F83DF at +4 via tail-jmp.
// No vptr and no EH frame. Unlocks 0x005E88C1.
class Rva005F83DF
{
public:
	virtual ~Rva005F83DF();

private:
	char m_pad04[8];
};

class Rva005E888A
{
public:
	~Rva005E888A();

private:
	int m_pad00;
	Rva005F83DF m_04; // +4
};

Rva005E888A::~Rva005E888A()
{
}
