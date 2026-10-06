// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00240000@@QAE@XZ, retail 0x00240000, 46 bytes.
// Ctor with vtable 0xBEDCB4 vector BfmeE12 at +4 second ptr 0xBEDAA8 at +0x10 zeros at +0x14..0x1C.
// Evidence: unlock lane, vtable store at +0, Vector_base ctor 0x7FAEA, caller fanout 7, prev/next neighbours.
extern const void *const g_00BEDCB4[];
extern const void *const g_00BEDAA8[];
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
		_Vector_base(const A &);
		void *_M_start;
		void *_M_finish;
		void *_M_end;
	};
}
struct BfmeE12
{
	float x;
	float y;
	float z;
};
class Rva00240000
{
public:
	Rva00240000();
private:
	const void *m_00;
	_STL::_Vector_base<BfmeE12, _STL::allocator<BfmeE12> > m_04;
	const void *m_10;
	int m_14;
	int m_18;
	int m_1C;
};
Rva00240000::Rva00240000()
	: m_00((const void *)g_00BEDCB4)
	, m_04(_STL::allocator<BfmeE12>())
{
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_10 = (const void *)g_00BEDAA8;
}
