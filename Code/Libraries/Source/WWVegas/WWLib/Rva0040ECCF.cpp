// cl: /O1 /DNDEBUG /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /G7 /EHsc
// stlport
// ?rva0040ECCF@Rva0040ECCF@@QAEHABVRva004F6093Holder@@@Z @0x0040ECCF 128B
// Adds holder to sorted entry vector and broadcasts to listener list.
// Evidence: callees rowed (forEach 0x0040D8D6, Entry ctor 0x0040CB11,
// push_back 0x0040E8D1, Release 0x0007DEEF, forwarders 0x001FF3A9 slot0 and
// 0x005CC208 slot2); callers at 0x0040EE4E 0x0040F0CB 0x0040F178 0x0040F291
// 0x0040F428 0x004F7D07; vector at +0x40 and index at +0x3c shared with
// 0x0040ED4F; Entry (int plus Holder) and Holder layouts from
// stlport_sort_rva0040cb11entry.cpp.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/arch:SSE /G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0040F454Target
{
	char m_pad00[8];
	float m_value;
	char m_pad0C[0xAC - 0xC];
	TargetRef00217D4C m_ac;
};

class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->m_ac.references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
			m_ptr = other.m_ptr;
		}
		return *this;
	}

public:
	Rva0040F454Target *m_ptr;
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(int key, const Rva004F6093Holder &val);

private:
	int m_first;
	Rva004F6093Holder m_second;
};

class Rva0040D8D6Listener
{
public:
	virtual void notify0(void *arg, int value);
	virtual void dummy();
	virtual void notify2(void *arg, int value);
};

class Rva0040D8D6List
{
public:
	void forEach(void (Rva0040D8D6Listener::*notify)(void *, int), void *arg, int value);

private:
	Rva0040D8D6Listener **m_begin;
	Rva0040D8D6Listener **m_end;
	Rva0040D8D6Listener **m_capacity;
	unsigned int m_index;
};

class Rva0040ECCF
{
public:
	int rva0040ECCF(const Rva004F6093Holder &holder);

private:
	char m_pad00[4];
	Rva0040D8D6List m_list;
	char m_pad14[0x3C - 0x14];
	int m_next;
	_STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> > m_vec;
};

int Rva0040ECCF::rva0040ECCF(const Rva004F6093Holder &holder)
{
	int argVal = (int)holder.m_ptr;
	m_list.forEach(&Rva0040D8D6Listener::notify0, this, argVal);
	int old = m_next;
	m_next = old + 1;
	{
		m_vec.push_back(Rva0040CB11Entry(old, holder));
	}
	m_list.forEach(&Rva0040D8D6Listener::notify2, this, old);
	return old;
}
