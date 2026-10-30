// cl: /O1 /DNDEBUG /MD /EHsc /G7
//
// ?rva00540301@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @ 0x00540301 35B
// Evidence: lower_bound wrapper mirror of the verified 0x005414C2 wrap
// (less temp plus null distance tag around the rowed Pod40
// __lower_bound at 0x00540253).
//
// ?rva0054034A@Rva0054034A@@QAE_NH@Z @ 0x0054034A 200B: the hinted search
// of the sorted key vector (WB 0x00455B00 shape; same template as the
// matched 0x00541641). The cached index answers directly when the key falls
// in its slot; otherwise it is re-found with the wrapper above and stepped
// back past the end or between keys.
//
// __lower_bound is defined here as STLport's halving loop: with its body
// visible the locator's tail reloads the key at both compares as retail
// does. Without /Oy- this unit's copy of it is retail's 0x00540253 and all
// four bodies still match. Names are generated.
struct BfmePod40
{
	int m_00;
	char m_pad04[0x24];
};

namespace _STL
{
	template <class _Tp>
	struct less
	{
		bool operator()(const _Tp &a, const _Tp &b) const { return a.m_00 < b.m_00; }
	};
	template <class _Fwd, class _T, class _C, class _D>
	_Fwd __lower_bound(_Fwd __first, _Fwd __last, const _T &__val, _C __comp, _D *)
	{
		_D __len = __last - __first;
		_D __half;
		_Fwd __middle;
		while (__len > 0) {
			__half = __len >> 1;
			__middle = __first;
			__middle += __half;
			if (__comp(*__middle, __val)) {
				__first = __middle;
				++__first;
				__len = __len - __half - 1;
			}
			else
				__len = __half;
		}
		return __first;
	}
	template <class T>
	class allocator
	{
	};
	template <class T, class A>
	class vector
	{
	public:
		void push_back(const T &x);
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

BfmePod40 *rva00540301(BfmePod40 *first, BfmePod40 *last, const BfmePod40 &value)
{
	return _STL::__lower_bound(first, last, value, _STL::less<BfmePod40>(), (int *)0);
}

class Rva0054000B
{
public:
	Rva0054000B();
	int m_00;
private:
	char m_pad04[0x24];
};

// The retail class this view spells Rva0054034A: the rowed ctor at 0x00540B03
// (Rva00540B03Ctors.cpp) ends with a call to rva00540A26 below on a
// reinterpret_cast<Rva0054034A *> view, and Rva00540888CameraTransform.cpp
// holds one at +0x24. Layout: a 40-byte sorted key vector (begin +0x10, end
// +0x14) plus an int hint at +0x1C. The vector is a member with inline
// size()/empty(), which keeps retail's per-use begin loads on the fast path.
struct KeyVector40
{
	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
	BfmePod40 *m_begin, *m_end, *m_capacity;
};
class Rva0054034A
{
public:
	void rva005404CF(int value);
	void rva00540A26();
	bool rva0054034A(int key);
private:
	char m_pad00[0x10];
	KeyVector40 m_keys;
	int m_hint1C;
};

void Rva0054034A::rva00540A26()
{
	typedef _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > Vec4000B;
	BfmePod40 **vec = &m_keys.m_begin;
	while ((unsigned int)(((char *)vec[1] - (char *)vec[0]) / 40) > 1)
		rva005404CF(m_keys.m_begin[1].m_00);
	Rva0054000B sentinel;
	sentinel.m_00 = 0;
	((Vec4000B *)vec)->push_back(sentinel);
}

bool Rva0054034A::rva0054034A(int key)
{
	int cachedIndex = m_hint1C;
	if (cachedIndex >= 0 && (unsigned)cachedIndex < m_keys.size()) {
		BfmePod40 *keyBegin = m_keys.m_begin;
		int cur = keyBegin[cachedIndex].m_00;
		if (key >= cur && ((unsigned)(cachedIndex + 1) >= (unsigned)(m_keys.m_end - keyBegin) || key < keyBegin[cachedIndex + 1].m_00))
			return cur == key;
	}
	if (m_keys.empty())
	{
		m_hint1C = -1;
		return false;
	}
	int &hint = m_hint1C;
	BfmePod40 *keyBegin = m_keys.m_begin;
	hint = rva00540301(keyBegin, m_keys.m_end, *reinterpret_cast<const BfmePod40 *>(&key)) - keyBegin;
	if ((unsigned)hint >= (unsigned)(m_keys.m_end - keyBegin) || (hint > 0 && keyBegin[hint].m_00 != key))
		--hint;
	return keyBegin[hint].m_00 == key;
}
