// cl: /MD
//
// ??_GRva0030B0E3@@UAEPAXI@Z, retail 0x0030B119, 28 bytes: the scalar
// deleting destructor in slot 0 of vftable 0x00C08830, which the class's
// constructor 0x0030B0E3 installs at +0. It calls the class destructor,
// frees through operator delete (0x0002FD60) when bit 0 of the flags is set
// and returns this (ret 4). Retail never calls it directly.
//
// ??1Rva0030B0E3@@UAE@XZ, retail 0x0007461F, 7 bytes: the destructor the
// wrapper calls. With the base's empty inline destructor expanded, the
// store of this class's own vtable is dead and only the base vtable store
// 0x00BC65A8 remains, the same bytes as ??1Rva00074626 (rowed at that
// address), so ICF folded the two. That the wrapper calls this address is
// the evidence for the base: MSVC's ??_G calls its own class's ??1.
//
// No other layout is modelled. The dummy tag constructor (no retail
// counterpart) only makes this TU emit the vftable and with it the deleting
// destructor.

struct EmitVtableTag;

class Rva00074626
{
public:
	Rva00074626();
	virtual ~Rva00074626() {}
};
// ??0Rva00074626@@QAE@XZ @0x0030B04C 9B: the default constructor, storing the
// class's own vtable (VA 0x00BC65A8) and returning this.
Rva00074626::Rva00074626()
{
}

class Rva0030B0E3 : public Rva00074626
{
public:
	Rva0030B0E3(EmitVtableTag *);
};

// ?<Rva0030B0E3::Rva0030B0E3> absent-from-retail
Rva0030B0E3::Rva0030B0E3(EmitVtableTag *)
{
}
