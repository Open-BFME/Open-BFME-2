// cl: /O2 /DNDEBUG /MD
//
// Scalar deleting destructors of classes whose destructor is empty and
// inline, batch C03: the 29-byte wrapper stores the class's own vtable,
// then frees through operator delete (0x0002FD60) when bit 0 of the flags is
// set and returns this (ret 4). Each class is named after the ledger name its
// vtable already carries, else after the wrapper's address; the dummy tag
// constructors (no retail counterpart) only make this TU emit each vtable and
// with it the deleting destructor. No layout or identity beyond that is
// modelled.
//
//   wrapper     vtable
//   0x000382F0  0x00BBE7EC  DebugCmdInterface
//   0x0012D780  0x00BD23B4  Rva0012D780
//   0x00140C00  0x00BD3338  Rva00140C00
//   0x00176940  0x00BD4E24  StaticSortListClass
//   0x00191120  0x00BD5E38  Rva00191120

struct EmitVtableTag;

class DebugCmdInterface
{
public:
	DebugCmdInterface(EmitVtableTag *);
	virtual ~DebugCmdInterface() {}
};

// ?<DebugCmdInterface::DebugCmdInterface> absent-from-retail
DebugCmdInterface::DebugCmdInterface(EmitVtableTag *)
{
}

class Rva0012D780
{
public:
	Rva0012D780(EmitVtableTag *);
	virtual ~Rva0012D780() {}
};

// ?<Rva0012D780::Rva0012D780> absent-from-retail
Rva0012D780::Rva0012D780(EmitVtableTag *)
{
}

class Rva00140C00
{
public:
	Rva00140C00(EmitVtableTag *);
	virtual ~Rva00140C00();
};

// ?<Rva00140C00::Rva00140C00> absent-from-retail
Rva00140C00::Rva00140C00(EmitVtableTag *)
{
}

// ??1Rva00140C00@@UAE@XZ @0x00141C30 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva00140C00::~Rva00140C00()
{
}

class StaticSortListClass
{
public:
	StaticSortListClass(EmitVtableTag *);
	virtual ~StaticSortListClass() {}
};

// ?<StaticSortListClass::StaticSortListClass> absent-from-retail
StaticSortListClass::StaticSortListClass(EmitVtableTag *)
{
}

class Rva00191120
{
public:
	Rva00191120(EmitVtableTag *);
	virtual ~Rva00191120() {}
};

// ?<Rva00191120::Rva00191120> absent-from-retail
Rva00191120::Rva00191120(EmitVtableTag *)
{
}
