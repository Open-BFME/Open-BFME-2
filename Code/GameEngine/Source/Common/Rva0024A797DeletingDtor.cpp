// cl: /MD
//
// ??_GRva0024A797@@UAEPAXI@Z at retail 0x002533E0 (28B): emitted scalar
// deleting destructor for the opaque MI middle UpdateModule (25B order-B body
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

#include "../../Include/Common/MiBase1.h"

// Per-TU PrimaryP (named to avoid colliding with the sibling TU's shared
// one): user empty dtor shares P's vptrs for retail order; inlines away so
// the middle still tail-calls the fold.
class PrimaryP24A797 : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP24A797() {}
};

template <int N> class BitFlags;
enum UpdateSleepTime;

// The update interface: retail 0x00BFBCE4 holds UpdateModule's getDisabledTypesToProcess
// and its rowed rva0044DF8D (0x0044DF8D) after the pure update.
class Rva0024A797_B2
{
public:
	virtual void update() = 0;
	virtual BitFlags<11> getDisabledTypesToProcess() const = 0;
	virtual void rva0044DF8D(UpdateSleepTime wakeDelay) = 0;

private:
	char m_pad08[12];
};

class UpdateModule : public PrimaryP24A797, public Rva0024A797_B2
{
public:
	virtual ~UpdateModule();
	virtual BitFlags<11> getDisabledTypesToProcess() const;
	virtual void rva0044DF8D(UpdateSleepTime wakeDelay);
};

UpdateModule::~UpdateModule()
{
}

#include <new>

class __declspec(novtable) Rva0024A797_Concrete : public UpdateModule
{
public:
	__forceinline Rva0024A797_Concrete() {}
	virtual void update();
};

void Rva0024A797_Anchor()
{
	new Rva0024A797_Concrete;
}

// UpdateModule::~UpdateModule is this body (symbols.csv pins ??1UpdateModule@@UAE@XZ here: the rowed
// BoredUpdate dtor tail-jumps to it). Shapes that declare it non-virtual reference the QAE spelling.
#pragma comment(linker, "/alternatename:??1UpdateModule@@QAE@XZ=??1UpdateModule@@UAE@XZ")
