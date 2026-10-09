// cl: /EHsc /MD
//
// ??_GRva0042CBB6@@UAEPAXI@Z, retail 0x004296EE, 28 bytes: the scalar
// deleting destructor in slot 1 of vftable 0x00C3C6F4, which the class's
// constructor 0x0042CBB6 installs at +0 (slot 0 is the message handler
// 0x0042CC7B). It calls the class destructor, frees through operator delete
// (0x0002FD60) when bit 0 of the flags is set and returns this (ret 4).
// Retail never calls it directly. ICF folded it with the deleting
// destructors of the other translators whose tables have the same shape:
// 0x004296EE is slot 1 of eleven two-slot tables, among them
// MetaEventTranslator's 0x00BDBAB4 (slot 0 its rowed translateGameMessage
// 0x001DB0B5).
//
// ??1Rva0042CBB6@@UAE@XZ, retail 0x00429191, 7 bytes: the destructor the
// wrapper calls. With the base's empty inline destructor expanded, the
// store of this class's own vtable is dead and only the base vtable store
// 0x00BDBA74 remains (mov [ecx], imm32 / ret); the translators' destructors
// fold to this one copy. That the wrapper calls this address is the
// evidence: MSVC's ??_G calls its own class's ??1.
//
// The base's vftable 0x00BDBA74 is [__purecall, ??_GRva001DB080], the shape
// of ZH's GameMessageTranslator (a pure translateGameMessage, then an empty
// inline virtual destructor); the ledger names that class Rva001DB080. No
// other layout is modelled. The dummy tag constructor (no retail
// counterpart) only makes this TU emit the vftable and with it the deleting
// destructor.

struct EmitVtableTag;

class Rva001DB080
{
public:
	virtual int translateGameMessage(const void *msg) = 0;
	virtual ~Rva001DB080() {}
};

class Rva0042CBB6 : public Rva001DB080
{
public:
	Rva0042CBB6(EmitVtableTag *);
	virtual int translateGameMessage(const void *msg);
};

// ?<Rva0042CBB6::Rva0042CBB6> absent-from-retail
Rva0042CBB6::Rva0042CBB6(EmitVtableTag *)
{
}
