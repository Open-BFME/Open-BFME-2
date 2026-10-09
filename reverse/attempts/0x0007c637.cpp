// ?Rva0007C637ConvexHull@@YA_NABV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@AAV12@M@Z
// partial score=0.6 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// NEAR (about 0.6; 667 vs 631 bytes): the control flow, the call sequence
// and the SSE/x87 distance math (WWMath::Sqrt's fsqrt block) all match, but
// register allocation differs throughout: retail keeps the kept-points base
// in esi across the whole body (reloaded only after push_back), the point
// list in edi and the output list in a scratch register (so its callee-saved
// pushes follow the first loads), and its inner loop counter lives in the
// [ebp+8] slot; this source's __asm Sqrt makes cl reload the vector fields
// every iteration and push ebx/esi/edi first. The intrinsic sqrt (/Oi or
// #pragma intrinsic) instead computes the distance in x87. The allocator
// temporary also lands in a new slot instead of retail's [ebp+0xF].
//
// ?Rva0007C637ConvexHull@@YA_NABV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@AAV12@M@Z,
// retail 0x0007C637 (631 bytes). Cdecl; one caller 0x0007CEAA. Builds the
// convex hull of a list of 2D points (8-byte records; WorldBuilder twin
// 0x007EF110 inlines WWMath's Vector2::Distance and Perp_Dot_Product, the
// math below) by gift wrapping, with a tolerance:
//  - the output list is cleared (rowed 8-byte vector erase 0x003FA4DB);
//  - points closer than the tolerance to an already kept point are dropped
//    (kept points through the rowed vector push_back 0x00539A2E);
//  - fewer than three kept points fail;
//  - the hull starts at the rowed min-element 0x0007B734 under the rowed
//    comparator 0x0007B701 and repeatedly adds the first candidate with every
//    other point on one side (perp-dot test against the tolerance, sign by
//    the parity of sorting the three indices) until it returns to a hull
//    point (pinned int find 0x0020E873; int index list push_back 0x004DFCB0);
//  - the output then receives the hull points in order.
// The element and allocator type names are the ones the folded template
// bodies are rowed/pinned under; only their 8-byte and 4-byte layouts matter.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;


extern "C" void __cdecl free(void *p);

struct BfmeE8
{
	Real x;
	Real y;
};

struct BfmePod8
{
	Real x;
	Real y;
};

template <class T> class Rva002444BEAllocator
{
public:
	Rva002444BEAllocator() {}
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	~_Vector_base()
	{
		if (_M_start)
			free(_M_start);
	}
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};

template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	explicit vector(const A &a = A()) : _Vector_base<T, A>(a) {}
	T *begin() const { return this->_M_start; }
	T *end() const { return this->_M_finish; }
	UnsignedInt size() const { return this->_M_finish - this->_M_start; }
	T &operator[](UnsignedInt n) const { return this->_M_start[n]; }
	T &back() const { return this->_M_finish[-1]; }
	T *erase(T *first, T *last);
	void push_back(const T &value);
	void clear() { erase(begin(), end()); }
};

template <class I, class T> I find(I first, I last, const T &value);
}

typedef _STL::vector<BfmeE8> Rva0007C637PointList;
typedef _STL::vector<BfmePod8> Rva0007C637EraseView;
typedef _STL::vector<Int, Rva002444BEAllocator<Int> > Rva0007C637IndexList;

struct Rva0007B734Item
{
	char m_pad[8];
};
typedef bool (__cdecl *Rva0007B734Pred)(const Rva0007B734Item *, const Rva0007B734Item *);
Rva0007B734Item *__cdecl Rva0007B734Find(Rva0007B734Item *first, Rva0007B734Item *last, Rva0007B734Pred pred);
bool __cdecl Rva0007B701Cmp(const BfmeE8 &a, const BfmeE8 &b);

// WWMath's Sqrt (its own x87 fsqrt block in wwmath.h), Vector2::Distance and
// Perp_Dot_Product on the 8-byte records.
struct Rva0007C637Math
{
	static __forceinline Real sqrt(Real val)
	{
		Real retval;
		__asm
		{
			fld val
			fsqrt
			fstp retval
		}
		return retval;
	}
	static __forceinline Real distance(const BfmeE8 &a, const BfmeE8 &b)
	{
		BfmeE8 d;
		d.x = a.x - b.x;
		d.y = a.y - b.y;
		return sqrt(d.x * d.x + d.y * d.y);
	}
	static __forceinline Real perpDot(const BfmeE8 &a, const BfmeE8 &b)
	{
		return a.x * b.y - a.y * b.x;
	}
};

bool __cdecl Rva0007C637ConvexHull(const Rva0007C637PointList &points, Rva0007C637PointList &hull, Real tolerance)
{
	((Rva0007C637EraseView &)hull).clear();

	Rva0007C637PointList kept;
	for (UnsignedInt i = 0; i < points.size(); ++i)
	{
		UnsignedInt j;
		for (j = 0; j < kept.size(); ++j)
		{
			if (Rva0007C637Math::distance(kept[j], points[i]) < tolerance)
				break;
		}
		if (j == kept.size())
			kept.push_back(points[i]);
	}

	UnsignedInt count = kept.size();
	if (count < 3)
		return false;

	Rva0007C637IndexList indices;
	Int next = (BfmeE8 *)Rva0007B734Find((Rva0007B734Item *)kept.begin(), (Rva0007B734Item *)kept.end(),
		(Rva0007B734Pred)Rva0007B701Cmp) - kept.begin();
	indices.push_back(next);
	for (;;)
	{
		Int current = indices.back();
		UnsignedInt candidate;
		for (candidate = 0; candidate < count; ++candidate)
		{
			if (candidate == (UnsignedInt)current)
				continue;
			UnsignedInt other;
			for (other = 0; other < count; ++other)
			{
				if (other == candidate || other == (UnsignedInt)current)
					continue;
				Int a = current;
				Int b = candidate;
				Int c = other;
				Bool flip = false;
				if (a > b)
				{
					a = candidate;
					b = current;
					flip = true;
				}
				if (b > c)
				{
					c = b;
					b = other;
					flip = !flip;
				}
				if (a > b)
				{
					Int t = a;
					a = b;
					b = t;
					flip = !flip;
				}
				BfmeE8 ab;
				ab.x = kept[b].x - kept[a].x;
				ab.y = kept[b].y - kept[a].y;
				BfmeE8 ac;
				ac.x = kept[c].x - kept[a].x;
				ac.y = kept[c].y - kept[a].y;
				Real cross = Rva0007C637Math::perpDot(ac, ab);
				if (flip ? cross > tolerance : cross < -tolerance)
					break;
			}
			if (other == count)
				break;
		}
		if (_STL::find(indices.begin(), indices.end(), (Int)candidate) != indices.end())
			break;
		indices.push_back(candidate);
	}

	((Rva0007C637EraseView &)hull).clear();
	for (Int *it = indices.begin(); it != indices.end(); ++it)
		hull.push_back(kept[*it]);
	return true;
}
