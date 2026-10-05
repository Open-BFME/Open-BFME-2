// cl: /O1 /DNDEBUG /MD
// ??1Rva00574A8A@@UAE@XZ @0x00574A8A 14B evidence: vtable 0x0083C6D0 store at [this] plus add ecx 4 plus tail-jmp to rowed base dtor ??1Rva00577010@@QAE@XZ @0x00577010; callers unclaimed FUN_0082c5c3 plus funclets; ghidra 14B vs 27B trust ret plus int3 gate
class Rva00577010
{
public:
	~Rva00577010();
};

class Rva00574A8A : public Rva00577010
{
public:
	virtual ~Rva00574A8A();
};

Rva00574A8A::~Rva00574A8A()
{
}
