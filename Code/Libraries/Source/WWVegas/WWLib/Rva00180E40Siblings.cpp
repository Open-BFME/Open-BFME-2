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

class Rva0061ED40Base
{
public:
	Rva0061ED40Base();
	virtual ~Rva0061ED40Base();
};

class Rva00180E40Derived : public Rva0061ED40Base
{
public:
	Rva00180E40Derived();
};

Rva00180E40Derived::Rva00180E40Derived()
{
}

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
};

class Rva006892D0Derived : public SubsystemInterface
{
public:
	Rva006892D0Derived();
};

Rva006892D0Derived::Rva006892D0Derived()
{
}

class Rva006ED060Base
{
public:
	Rva006ED060Base();
	virtual ~Rva006ED060Base();
};

class Rva006F7140Derived : public Rva006ED060Base
{
public:
	Rva006F7140Derived();
};

Rva006F7140Derived::Rva006F7140Derived()
{
}
