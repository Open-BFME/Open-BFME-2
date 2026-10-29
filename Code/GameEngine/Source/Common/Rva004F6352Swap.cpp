// cl: /O1 /EHsc /MD
// stlport46
//
// _STL::swap<Rva004F6352>, retail 0x004F6E62, 79 bytes. Dedicated TU so the
// temp copy/assign/destroy stays out-of-line through the rowed copy ctor
// 0x004F62DE assign 0x004F6352 and release 0x0007DEEF. Temp at ebp-0x18 with
// EH state 0 then -1. Caller at 0x004F7840 in FUN_008f7801 stride 0xC.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
};

struct Rva004F6352
{
	int m_00;
	int m_04;
	TreeHintRef00217D4C m_08;
	Rva004F6352(const Rva004F6352 &other);
	Rva004F6352 &operator=(const Rva004F6352 &other);
	~Rva004F6352();
};

// ??1TreeHintRef00217D4C@@QAE@XZ present-unmatched
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

// ??1Rva004F6352@@QAE@XZ present-unmatched
inline Rva004F6352::~Rva004F6352()
{
}

namespace _STL
{

template <class T>
void swap(T &lhs, T &rhs)
{
	T tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

}

template void _STL::swap<Rva004F6352>(Rva004F6352 &, Rva004F6352 &);
