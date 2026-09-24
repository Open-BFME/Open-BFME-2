// cl: /O1 /DNDEBUG /MD
//
// ??0ViewShakeFXNugget@@QAE@XZ 35B @0x1E07DF: no-arg ctor called by
// ViewShakeFXNugget::parse (0x001E1611) for the ViewShake FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDD7F4 (Type@0x148) and the BFME1 donor (m_shake plus
// FXNugget::m_field04 type id 6).
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_field04; // +4, nugget type id (BFME1 FXNugget::m_field04)
	unsigned char m_pad[0x148 - 8];
};

class ViewShakeFXNugget : public Rva001DFEAABase
{
public:
	ViewShakeFXNugget();
private:
	int m_shake; // +0x148
};

// ??0ViewShakeFXNugget@@QAE@XZ
ViewShakeFXNugget::ViewShakeFXNugget()
{
	*(unsigned int *)this = 0x00BDD7E0;
	m_shake = 1;
	m_field04 = 6;
}
