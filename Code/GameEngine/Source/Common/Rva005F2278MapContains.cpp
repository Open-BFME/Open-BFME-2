// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva005F2278@Rva005F2278@@QBE_NH@Z, retail 0x005F2278, 29 bytes.
// Map<int int> contains-check at this+0x10 via rowed _M_find 0x00388F63.
// Callees all rowed. Callers 7 unclaimed (0x005E4D60 0x005E4E32 0x005E50FD 0x005E5119 0x005E5146 jmp 0x005E39A9 jmp 0x005E3B20).
// Prev Disp8PtrChase getter / next OpaqueScalarDeletingDtor. Honest address name; class and method identity unproven.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva005F2278
{
public:
	bool rva005F2278(int key) const;
private:
	char m_pad[0x10];
	_STL::map<int, int> m_map;
};

bool Rva005F2278::rva005F2278(int key) const
{
	return m_map.find(key) != m_map.end();
}

// ?rva005E3B1A@Rva005E3B1A@@QBE_NH@Z, retail 0x005E3B1A, 11 bytes.
// Ptr-chase tail-jmp into rowed ?rva005F2278@Rva005F2278@@QBE_NH@Z at 0x005F2278.
// this+0x10 holds Mid*, Mid+0x14 holds Rva005F2278*. Callees all
// rowed after 0x005F2278 landed. Callers 0x005E690A 0x005E6987. Honest name.
struct Rva005E3B1AMid
{
	char m_pad[0x14];
	Rva005F2278 *m_inner;
};

class Rva005E3B1A
{
public:
	bool rva005E3B1A(int key) const;
private:
	char m_pad[0x10];
	Rva005E3B1AMid *m_ptr;
};

bool Rva005E3B1A::rva005E3B1A(int key) const
{
	return m_ptr->m_inner->rva005F2278(key);
}

// ?rva005F2767@Rva005F2767@@QBE_NXZ, retail 0x005F2767, 12 bytes.
// Bit-4 getter: m_ptr at this+4, flag bit at ptr+0x58 bit 4 (0x10).
// Retail mov eax,[ecx+4] / mov al,[eax+0x58] / shr al,4 / and al,1 / ret.
// Bitfield spelling reproduces the byte shr+and shape. Callees none.
// Caller 0x005E5469. Honest address name.
struct Rva005F2767Inner
{
	char m_pad[0x58];
	unsigned char _lo:4;
	unsigned char m_flag:1;
	unsigned char _hi:3;
};

class Rva005F2767
{
public:
	bool rva005F2767() const;
private:
	char m_pad2[0x4];
	Rva005F2767Inner *m_ptr;
};

bool Rva005F2767::rva005F2767() const
{
	return m_ptr->m_flag;
}

// ?rva005F2577@Rva005F2577Holder@@QAEXXZ, retail 0x005F2577, 23 bytes.
// Ref-release: if m_ptr non-null, dec ref at +4, virt slot0 on zero, null m_ptr.
// Retail push esi / mov esi,ecx / mov ecx,[esi] / test / dec [ecx+4] / jne /
// mov eax,[ecx] / call [eax] / and [esi],0 / pop / ret. Callees none
// (indirect call). Callers 7 unclaimed. Honest address name.
struct Rva005F2577Inner
{
	virtual void virt0();
	int m_ref;
};

class Rva005F2577Holder
{
public:
	void rva005F2577();
	void rva005F2773(Rva005F2577Inner *p);
private:
	Rva005F2577Inner *m_ptr;
};

void Rva005F2577Holder::rva005F2577()
{
	Rva005F2577Inner *p = m_ptr;
	if (!p)
		return;
	if (--p->m_ref == 0)
		p->virt0();
	m_ptr = 0;
}

// ?rva005F2773@Rva005F2577Holder@@QAEXPAURva005F2577Inner@@@Z, retail 0x005F2773, 31 bytes.
// Smart-ptr assign via rowed release 0x005F2577. If new != m_ptr, release old,
// store new, inc ref on non-null. Callees all rowed. Caller 0x005F37DC.
// Honest address name.

void Rva005F2577Holder::rva005F2773(Rva005F2577Inner *p)
{
	if (p != m_ptr) {
		rva005F2577();
		m_ptr = p;
		if (p)
			++p->m_ref;
	}
}
