// cl: /MD
// ??0Rva003818F4@@QAE@XZ, retail 0x003818F4, 12 bytes.
// Default ctor forwarding to member Rva00330757Member at +0. Evidence: leaf
// lane; callee ??0Rva00330757Member@@QAE@XZ rowed at 0x00330757; callers
// Unwind@00bab7d2 FUN_00bafc6b; prev/next stlport_vector_stringrecord.
class Rva00330757Member
{
public:
	Rva00330757Member();
};

class Rva003818F4
{
public:
	Rva003818F4();
private:
	Rva00330757Member m_member;
};

Rva003818F4::Rva003818F4()
{
}
