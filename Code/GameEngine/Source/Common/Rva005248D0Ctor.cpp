// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ??0Rva005248D0@@QAE@XZ @0x002D2C34 106B.
//
// The 0x58-byte Apt callback registry base whose vtable is 0x00C02A80 and whose
// virtual destructor is rowed at 0x005248D0 (target evidence: the ctor stores
// 0x00C02A80 at [this] last, and the dtor at 0x005248D0 stores the same table
// first). Its six register holders are BASE CLASSES, not members: retail stores
// the vptr AFTER all six constructor calls, which is what MSVC emits for bases
// (a member list stores the vptr before the member ctors). Member spelling was
// the old bank's sole residue (nd 2); the base spelling is raw-instruction
// exact, 106/106.
//
// The holder classes are named from the ledger's own rows:
//   +0x04 AptCommandMapAdder (12B; ctor 0x001F81BF folded, dtor 0x0052413E)
//   +0x10 Rva005241B0        (12B; ctor 0x001F81BF folded, dtor 0x005241B0)
//   +0x1C Rva00524415        (24B; ctor 0x00524415, dtor 0x00524436)
//   +0x34 Rva00524265        (12B; ctor 0x001F81BF folded, dtor 0x00524265)
//   +0x40 Rva005242D7        (12B; ctor 0x001F81BF folded, dtor 0x005242D7)
//   +0x4C AptTimerAdder      (12B; ctor 0x001F81BF folded, dtor 0x00524349)
// Every ctor folds to 0x001F81BF and every dtor sits at its own address, so the
// classes are distinguished by their dtors. The five 12B holders are mutually
// interchangeable in the REL32-masked comparison (their ctors fold); the order
// above follows the declared class order in the matched views
// (AptPalantirConstructor.cpp: command maps +0x04, extern handlers +0x10,
// over-button +0x1C, custom renders +0x34). The 24B +0x1C holder is the
// stlport dual-vector object the 0x00524415 ctor row owns.
//
// Most consumer units call this constructor by name; the address-derived
// pin ?rva002D2C34@Rva002D2C34@@QAEXXZ stays for the callers still spelling
// it (AptRowListCallbacks.cpp, AptPalantirUpdate.cpp).

#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

class Rva005241B0
{
public:
	Rva005241B0();
	~Rva005241B0();

private:
	char m_pad[12];
};

class Rva00524415
{
public:
	Rva00524415();
	~Rva00524415();

private:
	char m_pad[24];
};

class Rva00524265
{
public:
	Rva00524265();
	~Rva00524265();

private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	Rva005242D7();
	~Rva005242D7();

private:
	char m_pad[12];
};

class AptTimerAdder
{
public:
	AptTimerAdder();
	~AptTimerAdder();

private:
	char m_pad[12];
};

class Rva005248D0 : public AptCommandMapAdder, public Rva005241B0, public Rva00524415,
                    public Rva00524265, public Rva005242D7, public AptTimerAdder
{
public:
	virtual ~Rva005248D0();
	Rva005248D0();
};

Rva005248D0::Rva005248D0()
{
}
