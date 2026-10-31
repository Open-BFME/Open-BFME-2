// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??4?$vector@URva005F8F96@@V?$allocator@URva005F8F96@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z, retail 0x001537d8, 180 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Vector assign 3-path sar 3 stride 8 via allocate_and_copy 0x153489 plus clear 0x15373C plus copy 0x1534B6 plus Destroy 0x153470 plus uninit_copy 0x153425.
// Evidence: cmp ebx esi je then sar 3 capacity check jbe then allocate_and_copy plus clear plus copy plus Destroy plus copy plus uninit_copy then finish update; caller 0x1539D8 loops 6 vectors; callees rowed.
#include <vector>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
struct Rva00153252
{
public:
	Rva00153252 &operator=(const Rva00153252 &other);
	TreeHintRef00217D4C m_00; // +0x00
	int m_04; // +0x04
};
class Rva00468520;
struct Tag
{
public:
	Tag() {}
	char x; // +0x00
};
struct BfmeE8
{
	int a;
	int b;
};
Rva00153252 *Rva001534B6Copy(Rva00153252 *first, Rva00153252 *last, Rva00153252 *result, const Tag &tag);
void _DestroyRva005F8F96(Rva005F8F96 *first, Rva005F8F96 *last);
Rva00468520 *Rva00153425Copy(Rva00468520 *first, Rva00468520 *last, Rva00468520 *result, const Tag &tag);
// The row 0x00153489 names retail's folded allocate-and-copy under vector<BfmeE8>, which
// nothing here otherwise uses: only that member and the three words it needs are declared.
namespace _STL
{
template <> class vector<BfmeE8, allocator<BfmeE8> >
{
	friend class vector<Rva005F8F96, allocator<Rva005F8F96> >;
protected:
	template <class ForwardIter>
	BfmeE8 *_M_allocate_and_copy(unsigned int n, ForwardIter first, ForwardIter last);
private:
	BfmeE8 *_M_start;
	BfmeE8 *_M_finish;
	_STLP_alloc_proxy<BfmeE8 *, BfmeE8, allocator<BfmeE8> > _M_end_of_storage;
};
}
template <> _STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > &_STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> >::operator=(const _STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			BfmeE8 *tmpB = reinterpret_cast<_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > *>(this)->_M_allocate_and_copy<Rva00468520 *>(xsize, (Rva00468520 *)x.begin(), (Rva00468520 *)x.end());
			pointer tmp = (pointer)tmpB;
			_M_clear();
			_M_start = tmp;
			_M_end_of_storage._M_data = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			Rva00153252 *new_finish = Rva001534B6Copy((Rva00153252 *)x.begin(), (Rva00153252 *)x.end(), (Rva00153252 *)_M_start, Tag());
			_STL::_Destroy((Rva005F8F96 *)new_finish, (Rva005F8F96 *)_M_finish);
		}
		else
		{
			Rva001534B6Copy((Rva00153252 *)x.begin(), (Rva00153252 *)(x.begin() + size()), (Rva00153252 *)_M_start, Tag());
			Rva00153425Copy((Rva00468520 *)(x.begin() + size()), (Rva00468520 *)x.end(), (Rva00468520 *)_M_finish, Tag());
		}
		_M_finish = _M_start + xsize;
	}
	return *this;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x001534B6 -> ?Rva001534B6Copy@@YAPAURva00153252@@PAU1@00@Z
#pragma comment(linker, "/alternatename:?Rva001534B6Copy@@YAPAURva00153252@@PAU1@00ABUTag@@@Z=?Rva001534B6Copy@@YAPAURva00153252@@PAU1@00@Z")
