// cl: /DNDEBUG /MD /EHsc
// ??1Rva002B82D5@@QAE@XZ @0x002B82D5 53B.
// Family dtor: member Rva002B57D5 at +0xC through the rowed 0x002B62A6,
// then base Rva002B57AC at +0 through the rowed 0x002B626E, with the
// __EH_prolog frame and state 0/-1 stores around the member call. Both
// subobject layouts come from the sibling dtor TUs (each 8 bytes:
// handle plus count); +8 is an untouched trivial member. Owner unknown,
// non-virtual like both callees. Callers across 0x00500xxx/0x00502xxx/
// 0x0059xxxx plus del-dtor-style jmps; unblocks 7 functions.

class Rva002B57AC
{
public:
	~Rva002B57AC();
private:
	char m_pad[8];
};

class Rva002B57D5
{
public:
	~Rva002B57D5();
private:
	char m_pad[8];
};

class Rva002B82D5 : public Rva002B57AC
{
public:
	~Rva002B82D5();
private:
	char m_pad8[4];
	Rva002B57D5 m_xC;
};

Rva002B82D5::~Rva002B82D5()
{
}

// ??1Rva002B923F@@QAE@XZ @0x002B923F 8B.
// Trivial dtor over member Rva002B82D5 at +4; empty body tail-jumps.
// Evidence: chain lane; callee rowed 0x002B82D5; callers at 0x002BADF6
// plus 0x002BBC04; unblocks 0x002BADF3 plus 0x002BBBE7; same add-4-jmp
// shape as rowed Rva004BA1C8 dtor at 0x004BA1C8.
class Rva002B923F
{
public:
	~Rva002B923F();
private:
	int m_00;
	Rva002B82D5 m_04;
};

Rva002B923F::~Rva002B923F()
{
}

void *operator new(unsigned int size);
void operator delete(void *p);

// Anchor: new/delete calls the scalar deleting dtor directly (non-virtual,
// so devirtualization is a direct ??_G call), emitting the COMDAT for
// ??_GRva002B923F@@QAEPAXI@Z at 0x002BADF3. Operator new/delete resolve to
// their rows at 0x0002FDA0/0x0002FD60.
void Rva002B923F_Anchor()
{
	Rva002B923F *p = new Rva002B923F;
	delete p;
}
