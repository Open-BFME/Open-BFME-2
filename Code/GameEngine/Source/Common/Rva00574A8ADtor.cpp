// cl: /DNDEBUG /MD
// ??1Rva00574A8A@@UAE@XZ @0x00574A8A 14B evidence: vtable 0x0083C6D0 store at [this] plus add ecx 4 plus tail-jmp to rowed base dtor ??1Rva00577010@@QAE@XZ @0x00577010; callers unclaimed FUN_0082c5c3 plus funclets; ghidra 14B vs 27B trust ret plus int3 gate
class Rva00574A8A;

class Rva0057525FCall
{
public:
	Rva0057525FCall(Rva00574A8A *owner, unsigned int first, unsigned int second);

private:
	unsigned char m_layout[0x80];
};

class Rva00577010
{
public:
	~Rva00577010();
};

class Rva00574A8A
{
public:
	Rva00574A8A(unsigned int first, unsigned int second);
	virtual ~Rva00574A8A();

private:
	void *m_value;
};

Rva00574A8A::~Rva00574A8A()
{
	((Rva00577010 *)((char *)this + 4))->~Rva00577010();
}

// Target vtable xrefs identify this class; its dtor calls the 0x00577010
// holder cleanup at +4. Retail allocates a 0x80-byte object and calls
// 0x0057525F with this and two raw 32-bit arguments. The inner object's
// identity and argument meanings remain unresolved.
Rva00574A8A::Rva00574A8A(unsigned int first, unsigned int second)
{
	m_value = new Rva0057525FCall(this, first, second);
}
