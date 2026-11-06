// cl: /DNDEBUG /MD
//
// ?rva001F4D06@Rva001F4D06@@QAE@PAX0@Z @0x001F4D06 28B.
// Derived constructor: forwards two opaque words to the unrowed base ctor
// at 0x001F4B63 (pinned from the emitted spelling; the banked 0x001F4B63
// stash names it as a SmartPtr/chain ctor, unlanded, so params stay void*),
// installs vtable 0x00BE174C and returns this. No virtuals are defined in
// this TU so the vtable stays an extern patched from retail (Rva001F092A
// ctor precedent); base carries the virtuals conceptually via its undefined
// virtual dtor. Strict param/base types unproven.
class Rva001F4D06Base
{
public:
	virtual ~Rva001F4D06Base();
	Rva001F4D06Base(void *a, void *b);
};

class Rva001F4D06 : public Rva001F4D06Base
{
public:
	Rva001F4D06(void *a, void *b);
	// Retail 0x001F4D22, defined in ParticleSys.cpp; declaring it keeps this unit
	// from emitting a second, implicit copy.
	virtual ~Rva001F4D06();
};

Rva001F4D06::Rva001F4D06(void *a, void *b) : Rva001F4D06Base(a, b)
{
}

// The base constructor is the body at 0x001F4B63 that this constructor calls. The base destructor,
// 0x001F4C67, is reached through the destructor 0x001F4D22 that ParticleSys.cpp defines.
#pragma comment(linker, "/alternatename:??0Rva001F4D06Base@@QAE@PAX0@Z=??0Rva001F4C67@@QAE@ABVRvaSmartPtr12@@ABVRva001F376E@@@Z")
