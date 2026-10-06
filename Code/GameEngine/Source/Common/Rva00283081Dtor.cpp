// cl: /DNDEBUG /MD /EHs
// ??1Rva00283081@@UAE@XZ, RVA 0x00283081, 84 bytes.
// Dtor twin of 0x004DFED8: vstore 0x008615D4, calls rowed clear 0x002827F3, frees vec buffers
// at +0x10 and +0x4 via rowed free 0x00030830.
// Evidence: same vtable and clear as Rva004DFED8Dtor; caller 0x00283246 deleting dtor; callees all rowed.
extern "C" void __cdecl free(void *block);

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	~vector() { if (m_start) free(m_start); }
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *erase(T *first, T *last);
};
}

class Rva002827F3
{
public:
	void rva002827F3();
};

class Rva00283081
{
public:
	virtual ~Rva00283081();
private:
	_STL::vector<void *, _STL::allocator<void *> > m_vec4;
	_STL::vector<void *, _STL::allocator<void *> > m_vec10;
};

Rva00283081::~Rva00283081()
{
	((Rva002827F3 *)this)->rva002827F3();
}
