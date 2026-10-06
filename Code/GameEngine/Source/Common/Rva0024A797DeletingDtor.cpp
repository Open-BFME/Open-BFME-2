// cl: /MD
//
// ??_GRva0024A797@@UAEPAXI@Z at retail 0x002533E0 (28B): emitted scalar
// deleting destructor for the opaque MI middle Rva0024A797 (25B order-B body
// tail-jumping the 0x49B47C fold). The middle uses the shared-PrimaryP model
// (order +0x10/+0/+0xC, per-middle B2, tail-jump to the pinned fold;
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
class PrimaryP24A797 : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP24A797() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0024A797 : public PrimaryP24A797, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

Rva0024A797::~Rva0024A797()
{
}

void *operator new(unsigned int size);
void operator delete(void *p);

// Anchor: new/delete devirtualizes to a direct ??_G call, emitting the COMDAT.
void Rva0024A797_Anchor()
{
	Rva0024A797 *p = new Rva0024A797;
	delete p;
}

// UpdateModule::~UpdateModule is this body (symbols.csv pins ??1UpdateModule@@UAE@XZ here: the rowed
// BoredUpdate dtor tail-jumps to it). Shapes that declare it non-virtual reference the QAE spelling.
#pragma comment(linker, "/alternatename:??1UpdateModule@@QAE@XZ=??1Rva0024A797@@UAE@XZ")
