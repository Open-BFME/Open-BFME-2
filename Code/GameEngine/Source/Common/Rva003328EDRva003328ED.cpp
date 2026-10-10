// cl: /O1 /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?rva003328ED@Rva003328ED@@QAEXPAXHH@Z, retail 0x003328ed, 136 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
//
//
// Leaf search-insert on vector<Rva003328B6Element> at +4 (same 12-byte
// two-NameKey plus list record as Rva00331EAD / Rva003320C7ListOwner).
// Donor: Rva003328EDChain caller plus Gen_guarded_list_push_back owner.
// Evidence: push_back row 0x3328B6, Rva00331EAD row 0x331EAD,
// appendIfAbsent row 0x3320C7, PoolMember release row 0x268902,
// caller 0x2628D8 in Rva003328EDChain.cpp, ret 0xC three-arg shape.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva003328B6Element
{
	int m_key1;
	int m_key2;
	void *m_ptr;
};

class Rva003320C7ListOwner
{
public:
	void appendIfAbsent(void *value) throw();
};

class PoolMember
{
public:
	void Rva00268902() throw();
};

class Rva0029FB3BMember : public PoolMember
{
public:
	void *init(void *context);
};

class Rva00331EAD
{
public:
	int m_00;
	int m_04;
	Rva0029FB3BMember m_08;

	Rva00331EAD(int a, int b);
	~Rva00331EAD() { m_08.Rva00268902(); }
};

class Rva003328ED
{
public:
	void rva003328ED(void *x, int k1, int k2);

private:
	void *m_unk0;
	_STL::vector<Rva003328B6Element> m_vec;
};

void Rva003328ED::rva003328ED(void *x, int k1, int k2)
{
	Rva003328B6Element *p = m_vec.begin();
	bool found = false;
	do
	{
		if (p == m_vec.end())
			break;
		if (p->m_key1 == k1 && p->m_key2 == k2)
		{
			((Rva003320C7ListOwner *)p)->appendIfAbsent(x);
			found = true;
		}
		++p;
	} while (!found);
	// Codegen: this barrier fixes the native statement/schedule order (found by a per-statement barrier sweep).
	_ReadWriteBarrier();
	if (found != false)
		return;
	Rva00331EAD tmp(k1, k2);
	m_vec.push_back(*(Rva003328B6Element *)&tmp);
	Rva003328B6Element *plast = m_vec.end();
	--plast;
	((Rva003320C7ListOwner *)plast)->appendIfAbsent(x);
}
