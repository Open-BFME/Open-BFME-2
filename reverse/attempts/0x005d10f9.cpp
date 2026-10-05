// ??1Rva005D10F9@@UAE@XZ
// partial score=0.5 date=2026-10-05
class Rva005D10F9OwnedPointer
{
public:
	void clear();
private:
	void *m_pointer;
};

class __declspec(novtable) Rva005D10F9
{
public:
	Rva005D10F9(EmitVtableTag *);
	virtual ~Rva005D10F9();
private:
	unsigned int m_opaque04;
	Rva005D10F9OwnedPointer m_member08;
};

// The target body at 0x005D10F9 calls the 0x005EC4AA cleanup thunk with ECX=this+8;
// the thunk tail-jumps to Rva005EC422::clear. Offset +4 and the final vptr's
// class identity remain unresolved.
// ?<Rva005D10F9::Rva005D10F9> absent-from-retail
Rva005D10F9::Rva005D10F9(EmitVtableTag *)
{
}

Rva005D10F9::~Rva005D10F9()
{
	m_member08.clear();
	*reinterpret_cast<volatile unsigned int *>(this) = 0x00C7559C;
}
