// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??0Rva00437E72@@QAE@XZ @0x00437F0A 87B. Constructs the base message object
// with type 13 and the target string "MessageBox", then publishes this at the
// global slot used by the two prompt forwarders.
// ??1Rva00437E72@@UAE@XZ @0x00437E72 18B stores vtable g_00C3D294 clears g_Va00E032FC then tail-jmps to base dtor 0x0054D2CF.
// ??_GRva00437E72@@UAEPAXI@Z @0x00437EEE 28B deleting dtor calls ??1 then operator delete on flag.
// Evidence: packet disassembly pair; base dtor pin ??1Rva0054D2CF@@UAE@XZ; vtable g_00C3D294; global g_Va00E032FC.
#include "ascii_string.h"

class Rva0054D2CF
{
public:
	Rva0054D2CF(int type, const AsciiString &label);
	virtual ~Rva0054D2CF();
};

extern const void *const g_00C3D294[];
extern int g_Va00E032FC;

class Rva00437E72 : public Rva0054D2CF
{
public:
	Rva00437E72();
	virtual ~Rva00437E72();
};

Rva00437E72::Rva00437E72()
	: Rva0054D2CF(13, AsciiString("MessageBox"))
{
	g_Va00E032FC = (int)this;
}

Rva00437E72::~Rva00437E72()
{
	g_Va00E032FC = 0;
}
