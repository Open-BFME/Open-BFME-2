// cl: /O1 /MD /GX-
//
// ?rva003B44AB@Rva003B44AB@@QAEPAV1@PBV1@@Z retail 0x003B44AB 28B.
// Clear +0x00 then copy Rva003529B0 member at +0x04 from other+0x04.
// Return this. Evidence: callee ??0Rva003529B0@@QAE@PBV0@@Z rowed;
// LINK body unblocking 0x003B7FE0; prev ScriptListNode dtor TU flags.
class Rva003529B0
{
public:
	Rva003529B0(const Rva003529B0 *other);
};

class Rva003B44AB
{
public:
	Rva003B44AB *rva003B44AB(const Rva003B44AB *other);
private:
	int m_00;			// +0x00
	Rva003529B0 m_04;		// +0x04
};

Rva003B44AB *Rva003B44AB::rva003B44AB(const Rva003B44AB *other)
{
	m_00 = 0;
	m_04.Rva003529B0::Rva003529B0(&other->m_04);
	return this;
}
