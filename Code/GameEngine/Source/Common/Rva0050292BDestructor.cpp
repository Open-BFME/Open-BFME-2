// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_CRTIMP=

#include <stdlib.h>

class Rva00500D30
{
public:
	~Rva00500D30();

private:
	char m_data[8];
};

class Rva005026B6
{
public:
	~Rva005026B6();

private:
	char m_data[8];
};

// Retail EH calls the5B destructor wrapper502926, while the containing
// destructor inlines it to the56B base destructor5026B6.
// Address-derived view; original class and payload identities stay unknown.
class Rva00502926 : public Rva005026B6
{
public:
    ~Rva00502926() {}
};

class Rva0050292BFree
{
public:
	__forceinline ~Rva0050292BFree()
	{
		if (m_pointer)
			free(m_pointer);
	}

private:
	void *m_pointer;
};

// LivingWorldAI's +0x18 member is constructed by502C80 and destroyed by
//50292B on both ordinary and exceptional paths. Use the constructor's
// existing address-derived owner for this destructor as well. The0x50-byte
// span is fixed by the next parent member at+0x68; payload types stay opaque.
class Rva00502C80
{
public:
	~Rva00502C80();

private:
	char m_pad00[0x10];
	Rva0050292BFree m_free10;
	char m_pad14[0x10];
	Rva0050292BFree m_free24;
	char m_pad28[0x10];
	Rva00502926 m_tree38;
	char m_pad40[4];
	Rva00500D30 m_tree44;
	char m_pad4C[4];
};

// 0x0050292B 93B: extent and EH state transitions come from Ghidra and the
// target call graph; class/member owners remain address-derived.
Rva00502C80::~Rva00502C80()
{
}
