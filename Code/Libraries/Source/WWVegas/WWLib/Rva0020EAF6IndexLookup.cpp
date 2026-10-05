// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EAF6@Rva0020EAF6View@@QAEPAVRva0020E89C@@H@Z @0x0020EAF6 17B.
// Target evidence: Ghidra bounds FUN_0060eaf6 at 17 bytes. It loads this+8,
// returns null when that pointer is null, and otherwise tail-jumps to the
// 146-byte FUN_0060e90f with the original one-dword argument. The two views
// are address-derived; the underlying collection and entry identities remain
// unproven.

class Rva0020E89C;

class Rva0020E90FView
{
public:
	Rva0020E89C *rva0020E90F(int index);
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);

private:
	char m_pad00[8];
	Rva0020E90FView *m_holder;
};

Rva0020E89C *Rva0020EAF6View::rva0020EAF6(int index)
{
	if (m_holder == 0)
		return 0;
	return m_holder->rva0020E90F(index);
}
