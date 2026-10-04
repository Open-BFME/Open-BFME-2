// cl: /O1 /Ob0
// ??0Rva0044BDD8@@QAE@PBURva004C5DD0Pair@@@Z @0x0044BDD8 31B
// Ctor twin of rowed Rva0044BD34 (0x0044BD34 31B): forward its Pair arg to the
// rowed Rva004C5DD0::set at +8 after storing vtable VA 0x00C3EDFC (data RVA
// 0x0083EDFC) and zeroing +4. Same /O1 /Ob0 recipe and holder layout.
// Evidence: rowed callee set 0x0044BD00; vtable g_00C3EDFC; caller 0x0044BF28;
// landing unblocks 0x0044BF13.
extern const void *const g_00C3EDFC[];

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

class __declspec(novtable) Rva0044BDD8
{
public:
	explicit Rva0044BDD8(const Rva004C5DD0Pair *p);

private:
	const void *m_vptr;
	int m_04;
	Rva004C5DD0 m_08;
};

Rva0044BDD8::Rva0044BDD8(const Rva004C5DD0Pair *p)
{
	*(const void **)this = g_00C3EDFC;
	m_04 = 0;
	m_08.set(p);
}
