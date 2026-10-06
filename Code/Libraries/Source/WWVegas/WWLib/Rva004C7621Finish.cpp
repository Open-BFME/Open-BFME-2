// ?Rva004C7621Collect@@YGXPAURva004C7621Range@@PBURva004C7621Pos@@PAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@@Z
// partial score=0.96 date=2026-10-02
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?Rva004C7621Collect@@YGXPAURva004C7621Range@@PBURva004C7621Pos@@PAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@@Z @0x004C7621 (139B):
// gather {dist-squared, item} pairs for records near ref into a BfmeE8 vector
// then sort it. Evidence: rowed vector<BfmeE8>::push_back 0x00539A2E and rowed
// 3-arg sort 0x004C75DE; comparator pushed at +0x72 is unclaimed 0x0007B701;
// landing this unblocks 0x004C76AC; neighbours share these flags.

struct BfmeE8
{
	float m_distSq;
	void *m_item;
};

struct Rva004C7621Pos
{
	char m_pad[0x38];
	float m_x;
	float m_y;
};

struct Rva004C7621Rec
{
	float *m_vals;
	void *m_item;
	int m_f8;
	int m_fC;
};

struct Rva004C7621Range
{
	Rva004C7621Rec *m_first;
	Rva004C7621Rec *m_last;
};

namespace _STL {

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &v);
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end;
};

template <class _Tp, class _Pred> void sort(_Tp, _Tp, _Pred);

}

typedef bool (*BfmeE8Less)(const BfmeE8 &, const BfmeE8 &);

namespace _STL {
template <> void sort<BfmeE8 *, BfmeE8Less>(BfmeE8 *, BfmeE8 *, BfmeE8Less);
}

bool Rva0007B701Cmp(const BfmeE8 &, const BfmeE8 &);

bool Rva0007B701Cmp(const BfmeE8 &a, const BfmeE8 &b)
{
	return a.m_distSq < b.m_distSq;
}

void __stdcall Rva004C7621Collect(Rva004C7621Range *range, const Rva004C7621Pos *ref, _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > *out)
{
	float refs[3];
	refs[0] = ref->m_x;
	refs[1] = ref->m_y;
	Rva004C7621Rec *rec = range->m_first;
	for (; rec != range->m_last; ++rec) {
		float *p = (float *)((char *)rec->m_vals + 0x38);
		float dx = p[0];
		float dy = p[1];
		dx -= refs[0];
		dy -= refs[1];
		BfmeE8 e;
		e.m_item = &rec->m_item;
		e.m_distSq = dy * dy + dx * dx;
		out->push_back(e);
	}
	_STL::sort(out->_M_start, out->_M_finish, &Rva0007B701Cmp);
}
