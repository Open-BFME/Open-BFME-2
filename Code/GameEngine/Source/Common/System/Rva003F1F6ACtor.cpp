// cl: /DNDEBUG /MD /GX-
// ??0Rva003F1F6A@@QAE@PAX@Z, retail 0x003F1F6A, 76 bytes.
// Ctor storing void* at +0 then default vector<BfmeE16> at +4 via rowed
// Vector_base 0x00211E58 with one-byte stack allocator temp at [ebp+0xb]
// (Rva002AC3BE precedent), then -1 at +0x18, 0.0f at +0x1c/+0x20/+0x24,
// 0 at +0x28, 0 byte at +0x2c, then clear of the +4 vector via rowed
// voidptr erase 0x0031BD55. Gap +0x10..+0x17 left uninit. Prev/next share
// /O1 /DNDEBUG /MD /GX-; /arch:SSE for xorps/movss float zeroing.
// Declared-only _Vector_base/erase force CALLs (LivingWorldRegionConnection
// precedent); reinterpret shares the 12B layout for the voidptr erase.
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

template <class T, class A = allocator<T> > class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *erase(T *first, T *last);
};
}

class Rva003F1F6A
{
public:
	Rva003F1F6A(void *a);
private:
	void *m_00;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_04;
	int m_10;
	int m_14;
	int m_18;
	float m_1C;
	float m_20;
	float m_24;
	int m_28;
	bool m_2C;
};

Rva003F1F6A::Rva003F1F6A(void *a)
	: m_00(a), m_04(_STL::allocator<BfmeE16>())
{
	m_18 = -1;
	m_28 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_2C = false;
	_STL::vector<void *, _STL::allocator<void *> > *vp
		= reinterpret_cast<_STL::vector<void *, _STL::allocator<void *> > *>(&m_04);
	vp->erase(vp->begin(), vp->end());
}
