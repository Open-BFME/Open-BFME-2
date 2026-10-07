// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The 4-byte vector element is an ABI view needed to reuse the rowed STLport
// push_back body. Its semantic identity is unresolved.
// Ghidra FUN_006834e6 is a 31-byte thiscall body. It appends the pointer value
// from its stack argument to the vector at this+4, then forwards that value
// through the same-this helper at 0x00283114. Ghidra FUN_0068360c is a 54-byte
// wrapper that clears the +0x584 worker, then forwards the +0x578 vector's
// entries to 0x002834e6. The class names are address-based.
#include <vector>

struct Rva004DFCB0Element
{
	unsigned word0;
	Rva004DFCB0Element &operator=(const Rva004DFCB0Element &other)
	{
		if (this != &other)
			word0 = other.word0;
		return *this;
	}
	bool operator<(const Rva004DFCB0Element &) const;
	bool operator==(const Rva004DFCB0Element &) const;
};

class Rva00283114
{
public:
	void rva00283114(void *value);
};

class Rva002834E6Owner
{
public:
	void rva002834E6(void *key);

private:
	char m_pad00[4];
	_STL::vector<Rva004DFCB0Element> m_values;
};

class Rva002827F3
{
public:
	void rva002827F3() throw();
};

class Rva0028360CHost
{
public:
	void rva0028360C();

private:
	char m_pad00[0x578];
	void **m_begin;
	void **m_end;
	void **m_capacity;
	Rva002827F3 *m_worker;
};

void Rva002834E6Owner::rva002834E6(void *key)
{
	Rva004DFCB0Element const &element = *(Rva004DFCB0Element const *)&key;
	m_values.push_back(element);
	((Rva00283114 *)this)->rva00283114(key);
}

void Rva0028360CHost::rva0028360C()
{
	m_worker->rva002827F3();
	void **end = m_end;
	void **it = m_begin;
	for (;;)
	{
		if (it == end)
			break;
		((Rva002834E6Owner *)m_worker)->rva002834E6(*it);
		++it;
	}
}
