// cl: /O1 /DNDEBUG /MD
//
// ??1Rva005C47A3@@UAE@XZ retail 0x005C47A3 5 bytes: a jmp to 0x0052B588 with
// `this` unchanged and no vptr store of its own.
// Target evidence: the slot-0 deleting wrapper 0x005C43E7 of vtables
// 0x00C63398/0x00C745A0/0x00C74698/0x00C7475C (rowed
// ??_GRva005C47A3@@UAEPAXI@Z) and the global lifetime thunks 0x007B9035,
// 0x007B96EE, 0x007B96F8 and 0x007B9702 call it as a virtual destructor.
// 0x0052B588 is rowed as Rva00052B588DwordImmSetter::apply, the seven-byte
// store of vtable 0x00C686BC into the dword at `this`; it is called here
// under that name. That it is a base class's empty destructor is the likely
// reading, but the base's identity is not established, so no inheritance is
// declared. novtable keeps cl from storing this class's own vptr first,
// which retail does not do. Owner identity unrecovered (address name).

class Rva00052B588DwordImmSetter
{
public:
	void apply();	// 0x0052B588
};

class __declspec(novtable) Rva005C47A3
{
public:
	virtual ~Rva005C47A3();
};

Rva005C47A3::~Rva005C47A3()
{
	((Rva00052B588DwordImmSetter *)this)->apply();
}
