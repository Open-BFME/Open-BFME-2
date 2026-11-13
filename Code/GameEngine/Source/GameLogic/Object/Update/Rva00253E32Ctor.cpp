// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva00253E32@@QAE@XZ, retail 0x00253E32, 50 bytes.
//
// Evidence (retail body only; names are address-derived):
//  253e32: mov eax, FuncInfo / call __EH_prolog
//          vtable 0x00C4ED70 stored at +0, then the 16-byte record member at
//          +8 constructed through the rowed 0x004CE6BA (two words of
//          2*BfmeLogicFramesPerSecond and two -1.0f floats). The only caller is 0x253D58
//          inside the module-data factory 0x00253D37, so this is the ctor of
//          one of its update-module-data classes; the original class name is
//          not established, so the view keeps the address name.
//
// The base is trivial-constructible but destructible, which is what makes the
// EH prolog and trylevel 0 real: the member ctor call can throw and the base
// subobject needs unwinding. No base ctor call appears in retail, so the base
// ctor is inlined-empty here.

#include "../../../../Include/Common/Rva004CE6BA.h"

class Rva00253E32Base
{
public:
	Rva00253E32Base() {}
	// Empty: the derived destructor 0x0049B47C calls no base destructor.
	virtual ~Rva00253E32Base() {}

private:
	void *m_base4; // base subobject is eight bytes, so the member is at +8
};

class Rva00253E32 : public Rva00253E32Base
{
public:
	Rva00253E32();
	// Empty: vtable 0x0084ED70 slot 0 0x004A10FD calls 0x0049B47C, one vtable store and ret.
	virtual ~Rva00253E32() {}

private:
	Rva004CE6BA m_8; // +0x08, sixteen bytes
};

Rva00253E32::Rva00253E32()
{
}
