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
	~Rva0029FB3BMember() throw();
};

class Rva00331EAD
{
public:
	int m_00;
	int m_04;
	Rva0029FB3BMember m_08;

	Rva00331EAD(int a, int b);
	~Rva00331EAD() {}
};

class Rva003328ED
{
public:
	void rva003328ED(void *listItem, int nameKey1, int nameKey2);

private:
	void *m_unk0;
	_STL::vector<Rva003328B6Element> m_vec;
};

// bfme link decl-only begin
namespace _STL { template <> void _Construct<Rva003328B6Element,Rva003328B6Element>(Rva003328B6Element *,Rva003328B6Element const &); }
namespace _STL { template <> void _Destroy<Rva003328B6Element *>(Rva003328B6Element *,Rva003328B6Element *); }
namespace _STL { template <> void _Destroy<Rva003328B6Element>(Rva003328B6Element *); }
namespace _STL { template <> void __destroy<Rva003328B6Element *,Rva003328B6Element>(Rva003328B6Element *,Rva003328B6Element *,Rva003328B6Element *); }
namespace _STL { template <> void __destroy_aux<Rva003328B6Element *>(Rva003328B6Element *,Rva003328B6Element *,_STL::__false_type const &); }
namespace _STL { template <> Rva003328B6Element * __uninitialized_copy<Rva003328B6Element *,Rva003328B6Element *>(Rva003328B6Element *,Rva003328B6Element *,Rva003328B6Element *,_STL::__false_type const &); }
namespace _STL { template <> Rva003328B6Element * __uninitialized_fill_n<Rva003328B6Element *,unsigned int,Rva003328B6Element>(Rva003328B6Element *,unsigned int,Rva003328B6Element const &,_STL::__false_type const &); }
namespace _STL { template <> void vector<Rva003328B6Element,_STL::allocator<Rva003328B6Element> >::_M_clear(); }
namespace _STL { template <> void vector<Rva003328B6Element,_STL::allocator<Rva003328B6Element> >::_M_insert_overflow(Rva003328B6Element *,Rva003328B6Element const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> void vector<Rva003328B6Element,_STL::allocator<Rva003328B6Element> >::push_back(Rva003328B6Element const &); }
// bfme link decl-only end
void Rva003328ED::rva003328ED(void *listItem, int nameKey1, int nameKey2)
{
	Rva003328B6Element *element = m_vec.begin();
	bool found = false;
	do
	{
		if (element == m_vec.end())
			break;
		if (element->m_key1 == nameKey1 && element->m_key2 == nameKey2)
		{
			((Rva003320C7ListOwner *)element)->appendIfAbsent(listItem);
			found = true;
		}
		++element;
	} while (!found);
	// Codegen: this barrier fixes the native statement/schedule order (found by a per-statement barrier sweep).
	_ReadWriteBarrier();
	if (found != false)
		return;
	Rva00331EAD tmp(nameKey1, nameKey2);
	m_vec.push_back(*(Rva003328B6Element *)&tmp);
	Rva003328B6Element *plast = m_vec.end();
	--plast;
	((Rva003320C7ListOwner *)plast)->appendIfAbsent(listItem);
}
