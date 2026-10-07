// ?rva00283505@Rva002834E6Owner@@QAEXXZ
// partial score=0.92 date=2026-10-07
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

private:
	char m_unmodelled00[4];
};

class Rva002834E6Owner : public Rva00283114
{
public:
	void rva002834E6(void *key);
	void rva00283505();

private:
	_STL::vector<Rva004DFCB0Element> m_values;
	_STL::vector<void *> m_ownedObjects;
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

class Rva00281A06
{
public:
	~Rva00281A06();
};
void __cdecl operator delete(void *block);

void Rva002834E6Owner::rva002834E6(void *key)
{
	Rva004DFCB0Element const &element = *(Rva004DFCB0Element const *)&key;
	m_values.push_back(element);
	rva00283114(key);
}

void Rva002834E6Owner::rva00283505()
{
	void **end = m_ownedObjects.end();
	for (void **it = m_ownedObjects.begin(); it != end; ++it)
		delete static_cast<Rva00281A06 *>(*it);
	m_ownedObjects.erase(m_ownedObjects.begin(), m_ownedObjects.end());

	if (m_values.begin() == m_values.end())
		return;
	Rva004DFCB0Element *valuesEnd = m_values.end();
	for (Rva004DFCB0Element *it = m_values.begin(); it != valuesEnd; ++it)
		rva00283114((void *)it->word0);
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
