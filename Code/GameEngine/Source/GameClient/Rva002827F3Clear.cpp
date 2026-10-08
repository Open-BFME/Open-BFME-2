// cl: /DNDEBUG /MD
// ?rva002827F3@Rva002827F3@@QAEXXZ, RVA 0x002827F3, 80 bytes.
// Clears two voidptr vectors at +0x4 and +0x10; deletes each non-null
// Rva00281A06 element of the second via rowed dtor 0x00281A06 and rowed delete 0x0002FD60
// then empties both via rowed voidptr erase 0x0031BD55.
// Evidence: callers at 0x0028309F 0x002835CA 0x00283617 0x004DFEF6; callees all rowed.
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
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *erase(T *first, T *last);
};
}

struct Rva00281A06
{
	~Rva00281A06();
};

class Rva002827F3
{
public:
	void rva002827F3() throw();
private:
	unsigned char m_pad[4];
	_STL::vector<void *, _STL::allocator<void *> > m_vec4;
	_STL::vector<void *, _STL::allocator<void *> > m_vec10;
};

void Rva002827F3::rva002827F3() throw()
{
	void **last = m_vec10.m_finish;
	_STL::vector<void *, _STL::allocator<void *> > *vec2 = &m_vec10;
	void **first = vec2->m_start;
	for (void **it = first; it != last; ++it)
	{
		Rva00281A06 *p = (Rva00281A06 *)*it;
		if (p)
		{
			p->~Rva00281A06();
			::operator delete(p);
		}
	}
	vec2->erase(vec2->m_start, vec2->m_finish);
	_STL::vector<void *, _STL::allocator<void *> > *vec1 = &m_vec4;
	vec1->erase(vec1->m_start, vec1->m_finish);
}

// The lifetime call below targets 0x0028279F, whose listener header and
// record vector differ from the two pointer vectors of Rva002827F3 above.
class Rva0028279F
{
public:
	~Rva0028279F();
};

class Rva002833E7Holder
{
public:
	~Rva002833E7Holder();

private:
	Rva0028279F *m_ptr;
};

Rva002833E7Holder::~Rva002833E7Holder()
{
	Rva0028279F *ptr = m_ptr;
	m_ptr = 0;
	if (ptr)
	{
		ptr->~Rva0028279F();
		::operator delete(ptr);
	}
}
