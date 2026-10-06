// cl: /MD
// ??1Rva004FF2F4@@QAE@XZ at 0x004FF2F4 (8B).
// Tail-jmp dtor to rowed base 0x4E3184 at +4. Evidence: 5 callers incl
// unwind funclets, unblocks 2.

class Rva004E3184
{
public:
	virtual ~Rva004E3184();
};

class Rva004FF2F4
{
public:
	~Rva004FF2F4();
private:
	int m_00;
	Rva004E3184 m_04;
};

Rva004FF2F4::~Rva004FF2F4() {}
