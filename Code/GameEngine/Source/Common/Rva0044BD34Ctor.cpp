// cl: /O1 /Ob0
// ??0Rva0044BD34@@QAE@PBURva004C5DD0Pair@@@Z @0x0044BD34 31B
// Ctor forwarding its Pair arg to the rowed Rva004C5DD0::set at +8,
// after storing vtable VA 0x00C3EDEC (data RVA 0x0083EDEC) and zeroing +4.
// Evidence: rowed callee set 0x0044BD00; vtable g_00C3EDEC; caller 0x0044BECE;
// landing unblocks 0x0044BEB9; neighbours Rva004C5DD0Set.cpp / Rva004C5EF0Handle.cpp.
extern const void *const g_00C3EDEC[];

struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

struct Rva004C5DD0Pair
{
	Rva004C5DD0Ref *a;
	Rva004C5DD0Ref *b;
};

class Rva004C5DD0
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;

public:
	Rva004C5DD0 &set(const Rva004C5DD0Pair *p);
};

class __declspec(novtable) Rva0044BD34
{
public:
	explicit Rva0044BD34(const Rva004C5DD0Pair *p);

private:
	const void *m_vptr;
	int m_04;
	Rva004C5DD0 m_08;
};

Rva0044BD34::Rva0044BD34(const Rva004C5DD0Pair *p)
{
	*(const void **)this = g_00C3EDEC;
	m_04 = 0;
	m_08.set(p);
}
