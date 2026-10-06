// cl: /O1 /DNDEBUG /MD
//
// ?rva004B15E6@Rva004B15E6@@QAEXXZ @0x004B15E6 77B.
// When the pointer at +0x7C is live, call 0x004DD2C0 on it and clear the
// slot. Then destroy each non-null element of the vector at +0x70 through
// the rowed destructor 0x004DCE8E and operator delete 0x0002FD60, and erase
// the whole range through the rowed vector erase 0x0031BD55.

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
	T *erase(T *first, T *last);
};
}

class Rva004DD2C0
{
public:
	void rva004DD2C0();
};

class Rva004DCE8E
{
public:
	~Rva004DCE8E();
};

class Rva004B15E6
{
public:
	void rva004B15E6();

private:
	char m_pad[0x70];
	_STL::vector<void *, _STL::allocator<void *> > m_vec;
	Rva004DD2C0 *m_slot;
};

void Rva004B15E6::rva004B15E6()
{
	Rva004DD2C0 *slot = m_slot;
	if (slot != 0)
	{
		slot->rva004DD2C0();
		m_slot = 0;
	}
	_STL::vector<void *, _STL::allocator<void *> > *vec = &m_vec;
	for (void **it = vec->m_start; it != m_vec.m_finish; ++it)
	{
		Rva004DCE8E *elem = (Rva004DCE8E *)*it;
		if (elem != 0)
		{
			elem->~Rva004DCE8E();
			::operator delete(elem);
		}
	}
	vec->erase(vec->m_start, vec->m_finish);
}
