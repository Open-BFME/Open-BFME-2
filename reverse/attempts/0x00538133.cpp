// ??1Rva00538133@@UAE@XZ
// partial score=0.8478 date=2026-10-06
// ??1Rva00538133@@UAE@XZ
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
// ??1Rva00538133@@UAE@XZ @ 0x00538133 134B
// Dtor with virtual base: derived vtable 0x00C691EC, virtual base vtable 0x00C6EE28,
// base vtable 0x00BC6F20. List at +8 (forEach 0x00537F56 rowed, free 0x00030830
// inlined), _List_base<int> at +0x1C (0x004EC395 rowed), AsciiStrings at
// +0x20/+0x24 (releaseBuffer 0x00036410 rowed). Two non-virtual bases push the
// vbptr to +0x18: empty vptr base for the final store, holder (int + list) for
// the list at +8. /EHs keeps the state around the extern C free.
#include <stdlib.h>
#include "ascii_string.h"

class Rva0053805DBase;

class Rva0053805DListener
{
public:
	virtual void notify00(Rva0053805DBase *owner);
	virtual void notify04(Rva0053805DBase *owner);
	virtual void notify08(Rva0053805DBase *owner);
	virtual void notify0C(Rva0053805DBase *owner);
	virtual void notify10(Rva0053805DBase *owner);
	virtual void notify14(Rva0053805DBase *owner);
};

class Rva00537F56List
{
public:
	void forEach(void (Rva0053805DListener::*notify)(Rva0053805DBase *), Rva0053805DBase *owner);
	Rva0053805DListener **m_begin;
	Rva0053805DListener **m_end;
	Rva0053805DListener **m_capacity;
	unsigned int m_index;
	~Rva00537F56List();
};

// (CRT prototype from the standard header)

namespace _STL
{
template <typename T>
class allocator
{
};

template <typename T, typename A>
class _List_base
{
public:
	~_List_base();
};
}

class Rva00538133Base
{
public:
	virtual ~Rva00538133Base();
};

class Rva00538133Holder
{
public:
	~Rva00538133Holder();
	int m_00;
	Rva00537F56List m_list;
};

class Rva00538133VBase
{
public:
	virtual ~Rva00538133VBase();
};

class Rva00538133 : public Rva00538133Base, public Rva00538133Holder, virtual Rva00538133VBase
{
public:
	virtual ~Rva00538133();
private:
	_STL::_List_base<int, _STL::allocator<int> > m_1C;
	AsciiString m_20;
	AsciiString m_24;
};

// ??1Rva00537F56List@@QAE@XZ present-unmatched
inline Rva00537F56List::~Rva00537F56List()
{
	if (m_begin)
		free(m_begin);
}

// ??1Rva00538133Base@@UAE@XZ present-unmatched
inline Rva00538133Base::~Rva00538133Base()
{
}

// ??1Rva00538133Holder@@QAE@XZ present-unmatched
inline Rva00538133Holder::~Rva00538133Holder()
{
}

// ??1Rva00538133VBase@@UAE@XZ present-unmatched
inline Rva00538133VBase::~Rva00538133VBase()
{
}

// ??1Rva00538133@@UAE@XZ present-unmatched
Rva00538133::~Rva00538133()
{
	m_list.forEach(&Rva0053805DListener::notify00, (Rva0053805DBase *)this);
}
