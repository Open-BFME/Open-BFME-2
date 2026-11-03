// cl: /Ireference/shims/bfmerendobj /DNDEBUG /D_WINDOWS /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Three empty derived ctors of the ??0Rva006166B0List@@QAE@XZ shape (18 B):
// call the base ctor then install the derived vtable. Each base is an opaque
// address-derived model: the base ctor is only declared, so the compiler must
// emit the call and the byte gate resolves it through the pin. The derived
// vtable is pinned to the address the retail body stores.
//
//   0x00180E40  base ctor 0x0061ED40  (installs 0x00C7C584)  vtable 0x00BD5090
//   0x006892D0  base ctor 0x001B4E63  (SubsystemInterface)   vtable 0x00CE48A0
//   0x006F7140  base ctor 0x006ED060                          vtable 0x00CED2F0

// The base ctor 0x0061ED40 is rowed as GenBase009EB7D0 (GenBase009EB7D0Ctor.cpp).
// Neither class has a destructor in a vftable slot (base vftable 0x00C7C584,
// derived 0x00BD5090: slot 0 is not a deleting dtor), so this view declares
// none; one pure slot keeps the shared vptr at +0.
class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual void handle() = 0;
};

class Rva00180E40Derived : public GenBase009EB7D0
{
public:
	Rva00180E40Derived();
};

Rva00180E40Derived::Rva00180E40Derived()
{
}

#include "../../subsystem/SubsystemInterface.h"

class Rva006892D0Derived : public SubsystemInterface
{
public:
	Rva006892D0Derived();
};

Rva006892D0Derived::Rva006892D0Derived()
{
}

class Rva006ED150
{
public:
	Rva006ED150();
	virtual ~Rva006ED150();
	char m_remaining[0x30 - 4];
};

#include "../../../../GameEngine/Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;

class Rva006F7140Derived : public Rva006ED150
{
public:
	Rva006F7140Derived();
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocator->freeBlock(p, size); }
};

Rva006F7140Derived::Rva006F7140Derived()
{
}
