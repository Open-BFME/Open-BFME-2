// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// The 139-byte collect body belongs to ManTheWallsSpecialPower: native
// 4C76AC and WB 1268940 pass its receiver, which WB 1268800 saves as this.
// Its former free __stdcall declaration had exact bytes but the wrong ABI.
// Retain the independently matched comparator here.

struct BfmeE8
{
	float m_distSq;
	void *m_item;
};

struct Rva004C7621Rec
{
	float *m_vals;
	void *m_item;
	int m_f8;
	int m_fC;
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

bool Rva0007B701Cmp(const BfmeE8 &lhs, const BfmeE8 &rhs)
{
	return lhs.m_distSq < rhs.m_distSq;
}
