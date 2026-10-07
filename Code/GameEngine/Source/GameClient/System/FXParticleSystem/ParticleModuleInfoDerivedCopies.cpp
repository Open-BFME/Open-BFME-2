// cl: /O2 /Os /DNDEBUG /MD /EHs-c-
// Particle module-info derived copy ctor (retail 0x003AF89A, 45B). Same
// recipe as ParticleModuleInfoCopyCtors.cpp: the derived class
// calls its intermediate base copy (pinned, declared-only) then installs its
// own 4 vptrs. The intermediates are not rowed, so this unit declares their
// vptr lattice as size-only views: the sparse +0/+0x14/+0x18/+0x20 (+0x1c)
// stores prove one vptr per base with data between them, and every vftable
// dword is a DIR32 site the gate takes from the target. No base layout
// beyond the vptr offsets is claimed.
class Rva003AF8C7B00
{
public:
	virtual ~Rva003AF8C7B00();

private:
	char m_pad[0x10];
};

class Rva003AF8C7B14
{
public:
	virtual ~Rva003AF8C7B14();
};

class Rva003AF8C7B18
{
public:
	virtual ~Rva003AF8C7B18();
};

class Rva003AF8C7B1C
{
public:
	Rva003AF8C7B1C(const Rva003AF8C7B1C &other);
	virtual ~Rva003AF8C7B1C();
};

class Rva003AF8C7 : public Rva003AF8C7B00, public Rva003AF8C7B14,
	public Rva003AF8C7B18, public Rva003AF8C7B1C
{
public:
	Rva003AF8C7(const Rva003AF8C7 &other);
	virtual ~Rva003AF8C7();
};

class Rva003AF89A : public Rva003AF8C7
{
public:
	Rva003AF89A(const Rva003AF89A &other);
	virtual ~Rva003AF89A();
};

// ??0Rva003AF89A@@QAE@ABV0@@Z @0x003AF89A 45B: calls intermediate 0x003AF8C7
// then stores vptrs at +0/+0x14/+0x18/+0x1c DIR32.
Rva003AF89A::Rva003AF89A(const Rva003AF89A &other)
	: Rva003AF8C7(other)
{
}
