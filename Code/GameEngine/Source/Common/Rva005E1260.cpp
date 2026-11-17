// cl: /DNDEBUG /MD
// ?rva005E1260@Rva005E1260@@QAEAAV1@PBUInit005E1260@@@Z @0x005E1260 59B unlock ref-holder alloc via rowed operator new.
// Evidence: retail push 0x10 call rowed ??2@YAPAXI@Z 0x0002FDA0 then vtable 0x00877990 refcount at +4 payload copy +8 +0xC store to [this] inc ref return this; callers 0x005C7D3F 0x005C7F0A 0x005E15EB.
struct Init005E1260
{
	int m_a;
	int m_b;
};

// Native 0x005E1222 slot 1 body: invoke the member callback stored at +0xC on
// the target object stored at +0x8, returning the eight-byte handle through the
// caller's output pointer. Same declaration family as Code/GameEngine/Source/
// Common/Rva005E1222.cpp, which owns the rowed 36-byte body.
struct Rva005E1222Value
{
	void *first;
	void *second;
	Rva005E1222Value();
	Rva005E1222Value(const Rva005E1222Value &v) : first(v.first), second(v.second) {}
	~Rva005E1222Value() {}
};

class Rva005E1222Target {};

#include "../../Include/Common/Rva0007DF07.h"

class Rva005E1260Body : public Rva0007DF07
{
public:
	virtual ~Rva005E1260Body() {}
	union
	{
		struct
		{
			int m_a;
			int m_b;
		};
		struct
		{
			Rva005E1222Target *m_object;
			Rva005E1222Value (Rva005E1222Target::*m_method)();
		};
	};
	Rva005E1260Body(const Init005E1260 *p)
	{
		m_a = p->m_a;
		m_b = p->m_b;
	}
	virtual Rva005E1222Value invoke();
};

Rva005E1222Value Rva005E1260Body::invoke()
{
	return (m_object->*m_method)();
}

class Rva005E1260
{
	Rva005E1260Body *m_ptr;
public:
	Rva005E1260 &rva005E1260(const Init005E1260 *p);
	Rva005E1260(Init005E1260 init);
};

// Native 0x005C7D37..0x005C7D4A (19B): forwards the two-word by-value
// payload to the existing timer binder and returns this. The binder's
// reference return is ignored; the wrapper owns the constructor return.
Rva005E1260::Rva005E1260(Init005E1260 init)
{
	rva005E1260(&init);
}

Rva005E1260 &Rva005E1260::rva005E1260(const Init005E1260 *p)
{
	Rva005E1260Body *q = new Rva005E1260Body(p);
	m_ptr = q;
	if (q)
		++q->m_04;
	return *this;
}
