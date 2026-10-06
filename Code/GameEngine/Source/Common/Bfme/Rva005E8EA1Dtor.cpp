// cl: /MD
// ??1Rva005E8EA1@@QAE@XZ @0x005E8EA1 8B
// Non-virtual dtor holding rowed member Rva005F83DF at +8 via tail-jmp.
// Same recipe as 0x005E888A with wider pad. No vptr and no EH frame.
class Rva005F83DF
{
public:
	virtual ~Rva005F83DF();

private:
	char m_pad04[8];
};

class Rva005E8EA1
{
public:
	~Rva005E8EA1();

private:
	char m_pad00[8];
	Rva005F83DF m_08; // +8
};

Rva005E8EA1::~Rva005E8EA1()
{
}
