// ?rva0054034A@Rva0054034A@@QAE_NH@Z
// partial score=0.55 date=2026-10-06
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7
//
// ?rva00540301@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @ 0x00540301 35B
// ?rva0054034A@Rva0054034A@@QAE_NH@Z @ 0x0054034A 200B
// Evidence: lower_bound wrapper mirror of the verified 0x005414C2 wrap
// (less temp plus null distance tag around the rowed Pod40
// __lower_bound at 0x00540253), plus the sorted-key locator over
// 0x28-stride BfmePod40 keys: hint validation with unsigned count
// compares, lower_bound fallback through the wrapper, found on key
// equality. Sibling of the banked 0x00541579 Pod28 locator shape.
// Names are generated.
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
	};
	template <class _Fwd, class _T, class _C, class _D>
	_Fwd __lower_bound(_Fwd, _Fwd, const _T &, _C, _D *);
}

BfmePod40 *rva00540301(BfmePod40 *first, BfmePod40 *last, const BfmePod40 &value)
{
	return _STL::__lower_bound(first, last, value, _STL::less<BfmePod40>(), (int *)0);
}

class Rva0054034A
{
public:
	bool rva0054034A(int key);
private:
	char m_pad00[0x10];
	BfmePod40 *m_begin10;
	BfmePod40 *m_end14;
	int m_pad18;
	int m_hint1C;
};

bool Rva0054034A::rva0054034A(int key)
{
	volatile int prev;
	int hint = m_hint1C;
	if (hint < 0)
		goto slow;
	int count = (int)((char *)m_end14 - (char *)m_begin10) / 0x28;
	if ((unsigned int)hint >= (unsigned int)count)
		goto slow;
	{
		BfmePod40 *e = &m_begin10[hint];
		if (key < (prev = e->m_00))
			goto slow;
		int count2 = (int)((char *)m_end14 - (char *)m_begin10) / 0x28;
		++hint;
		if ((unsigned int)hint >= (unsigned int)count2)
			goto found;
		if (key >= e[1].m_00)
			goto slow;
found:
		return prev == key;
	}
slow:
	{
		BfmePod40 *begin = m_begin10;
		if (begin == m_end14) {
			m_hint1C = -1;
			return false;
		}
		BfmePod40 *e2 = m_begin10;
		int idx = (int)((char *)rva00540301(e2, m_end14, (const BfmePod40 &)key) - (char *)e2) / 0x28;
		m_hint1C = idx;
		int count3 = (int)((char *)m_end14 - (char *)e2) / 0x28;
		if ((unsigned int)idx >= (unsigned int)count3)
			goto dec;
		if (idx <= 0)
			goto check;
		{
			int off = idx * 0x28;
			if (((BfmePod40 *)((char *)e2 + off))->m_00 == key)
				goto check;
		}
dec:
		idx--;
		m_hint1C = idx;
check:
		{
			int off = m_hint1C * 0x28;
			return ((BfmePod40 *)((char *)e2 + off))->m_00 == key;
		}
	}
}
