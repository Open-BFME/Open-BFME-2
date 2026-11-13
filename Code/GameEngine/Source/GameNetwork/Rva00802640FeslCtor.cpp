// cl: /GX-
// Rva00802680Owner ctor: vtable, V2ZeroInt field8, zero-pair block at +0x20,
// two Gen_dtor_007f6d20 members at +0x28/+0x30, then field4/C/8 in body.
// The inline cleanup and explicit base-view teardown preserve the native
// deleting wrapper; the flat constructor view preserves member initialization.

#include "../../Include/Common/V2ZeroInt.h"

struct V2ZeroPair
{
	__forceinline V2ZeroPair() : m_a(0), m_b(0) {}
	int m_a;
	int m_b;
};

class Gen_dtor_007f6d20
{
public:
	Gen_dtor_007f6d20();

	void *m_ptr;
	int m_size;
};

// Private ABI views shared with the verified destructor owner. The complete
// inheritance/lifetime model and original class identities remain unrecovered.
class Rva00800290Buffer
{
public:
    void reset();
    char *m_ptr;
    int m_size;
};

class Rva007F78E0Block
{
public:
    void clear();
    Gen_dtor_007f6d20 *m_data;
    int m_count;
};

class Rva00802680Base
{
public:
    virtual ~Rva00802680Base() {}
    // Neutral declarations encode native pure-slot count; signatures are unknown.
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    int m_field4;
    int m_field8;
    int m_fieldC;
};

class Rva00802680Owner
{
public:
	__declspec(noinline) Rva00802680Owner();
	virtual __forceinline ~Rva00802680Owner()
	{
		m_field4 = 0;
		m_fieldC = 0;
		m_field8.m_value = 0;
		reinterpret_cast<Rva00800290Buffer *>(&m_c)->reset();
		reinterpret_cast<Rva00800290Buffer *>(&m_b)->reset();
		reinterpret_cast<Rva007F78E0Block *>(&m_block)->clear();
		reinterpret_cast<Rva00802680Base *>(this)->Rva00802680Base::~Rva00802680Base();
	}

	int m_field4;
	V2ZeroInt m_field8;
	int m_fieldC;
	char m_pad010[0x10];
	V2ZeroPair m_block;
	Gen_dtor_007f6d20 m_b;
	Gen_dtor_007f6d20 m_c;
};

Rva00802680Owner::Rva00802680Owner()
{
	m_field4 = 0;
	m_fieldC = 0;
	m_field8.m_value = 0;
}
