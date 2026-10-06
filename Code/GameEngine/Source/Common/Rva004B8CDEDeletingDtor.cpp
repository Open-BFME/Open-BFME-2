// cl: /MD
//
// ??_GRva004B8CDE@@UAEPAXI@Z at retail 0x004B8D32 (28B): emitted scalar
// deleting destructor for the opaque MI middle Rva004B8CDE (25B order-B body
// tail-jumping the 0x49B47C fold). The middle uses the per-TU PrimaryP model
// (order +0x10/+0/+0xC, own B2, tail-jump to the pinned fold;
// Rva0049B47C throw() is truthful and mangle-safe). The dtor call resolves
// via the row once the pin upgrades; operator delete via its pin. The anchor
// new/deletes (devirtualized direct ??_G call) to emit the COMDAT.

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

// Per-TU PrimaryP (named to avoid colliding with the sibling TU's shared
// one): user empty dtor shares P's vptrs for retail order; inlines away so
// the middle still tail-calls the fold.
class PrimaryP4B8CDE : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP4B8CDE() {}
};

class Rva004B8CDE_B2
{
public:
	virtual void f2();
};

class Rva004B8CDE : public PrimaryP4B8CDE, public Rva004B8CDE_B2
{
public:
	virtual ~Rva004B8CDE();
};

Rva004B8CDE::~Rva004B8CDE()
{
}

void *operator new(unsigned int size);
void operator delete(void *p);

// Anchor: new/delete devirtualizes to a direct ??_G call, emitting the COMDAT.
void Rva004B8CDE_Anchor()
{
	Rva004B8CDE *p = new Rva004B8CDE;
	delete p;
}
