// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// Wave-3 F78 shape family: throwing-new plus final. Each body allocates its
// POD helper with operator new, constructs it in place with (member, arg)
// (the null-checked call some shapes mistake for a cond call), then passes
// the helper (or null when allocation failed) to a thiscall final on the
// member's +0x1C subobject. The throwing new plus the in-place ctor is what
// requires the EH prologue and its 0/-1 state transitions. Callees pinned
// under their addresses; identities unproven.
//

struct Rva005CF22CBig;

class Rva00575674Sub
{
public:
	void rva00575674(void *h);
};

struct Rva005CF22CBig
{
	char m_pad[0x1C];
	Rva00575674Sub m_sub;
};

class Rva005CF07EHelper
{
public:
	Rva005CF07EHelper(Rva005CF22CBig *b, int x);
	unsigned char m_data[0x14];
};

class Rva005CF22COwner
{
public:
	void rva005CF22C(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF22COwner::rva005CF22C(int x)
{
	Rva005CF07EHelper *h = new Rva005CF07EHelper(m_a, x);
	m_a->m_sub.rva00575674(h);
}

class Rva005CF37DHelper
{
public:
	Rva005CF37DHelper(Rva005CF22CBig *b, int x);
	unsigned char m_data[0x10];
};

class Rva005CF6B5Owner
{
public:
	void rva005CF6B5(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF6B5Owner::rva005CF6B5(int x)
{
	Rva005CF37DHelper *h = new Rva005CF37DHelper(m_a, x);
	m_a->m_sub.rva00575674(h);
}

class Rva005CF4A8Helper
{
public:
	Rva005CF4A8Helper(Rva005CF22CBig *b, int x);
	unsigned char m_data[0x14];
};

class Rva005CF703Owner
{
public:
	void rva005CF703(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF703Owner::rva005CF703(int x)
{
	Rva005CF4A8Helper *h = new Rva005CF4A8Helper(m_a, x);
	m_a->m_sub.rva00575674(h);
}
