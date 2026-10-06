// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7
//
// ?rva00540301@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @ 0x00540301 35B
// Evidence: lower_bound wrapper mirror of the verified 0x005414C2 wrap
// (less temp plus null distance tag around the rowed Pod40
// __lower_bound at 0x00540253). The 200B sorted-key locator caller at
// 0x0054034A is banked as a partial (same TU shape stashed) pending
// fast-path regalloc work: hint must stay in ECX with late push-edi,
// EDI divisor and real imul-40 (this TU's /G7 emits the imul).
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

class Rva0054034A
{
public:
	void rva005404CF(int value);
	void rva00540A26();
private:
	char m_pad00[0x10];
	BfmePod40 *m_begin10;
	BfmePod40 *m_end14;
	int m_pad18;
	int m_hint1C;
};

void Rva0054034A::rva00540A26()
{
	typedef _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > Vec4000B;
	BfmePod40 **vec = &m_begin10;
	while ((unsigned int)(((char *)vec[1] - (char *)vec[0]) / 40) > 1)
		rva005404CF(m_begin10[1].m_00);
	Rva0054000B tmp;
	tmp.m_00 = 0;
	((Vec4000B *)vec)->push_back(tmp);
}
