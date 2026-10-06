// cl: /DNDEBUG /MD /GX-
//
// ??0Rva003F1FB6@@QAE@XZ, retail 0x003F1FB6 26B
// Default ctor: vector<BfmeE16> base at +0 via rowed _Vector_base
// 0x00211E58 with one-byte stack allocator temp, then int 1 at +0xC.
// Evidence: unlock lane; frameless push ecx/push esi + lea [esp+7] shape
// matches Rva003F1F6A ctor precedent (vector at +4 there, here at +0);
// callee row stlport_vector_e16_o1.cpp; caller 0x003F259C unclaimed.
// Honest address class.
struct BfmeE16 { float x; float y; float z; float w; };

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A = allocator<T> > struct _Vector_base
{
	_Vector_base(const A &alloc);
	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
};
}

class Rva003F1FB6
{
public:
	Rva003F1FB6();
private:
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_00;
	int m_0C;
};

Rva003F1FB6::Rva003F1FB6()
	: m_00(_STL::allocator<BfmeE16>())
{
	m_0C = 1;
}
