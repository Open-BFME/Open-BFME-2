// cl: /MD
//
// FirewallHelperClass's virtual destructor and the scalar deleting destructor
// that fills the only slot of its one-slot vftable 0x00C70A2C (VA; installed
// at +0 by the constructor 0x00594CDD). ZH FirewallHelper.h declares
// virtual ~FirewallHelperClass() as the class's only virtual, and ZH
// FirewallHelper.cpp defines it as { reset(); }.
//
// ??1FirewallHelperClass@@UAE@XZ @0x00595390 10B: restores the vtable and
// tail-jumps to reset (rowed at 0x0059515C under its address name). Retail
// keeps this out-of-line copy although no code calls it.
// ??_GFirewallHelperClass@@UAEPAXI@Z @0x00595D0B 34B: the compiler-generated
// scalar deleting destructor with the destructor expanded inline (vtable
// store, reset), then operator delete (0x0002FD60) when bit 0 of the flags
// is set; returns this (ret 4). Only the vftable reaches it.
//
// Evidence for reset: 0x0059515C calls 0x0059510D (closeAllSpareSockets in
// the ZH order), zeroes the state at +0x17C and clears the eight message
// lengths (stride 0x1E from +0x9E), which is ZH reset() on this layout.

class Rva0059515C
{
public:
	void rva0059515C();
};

class FirewallHelperClass
{
public:
	virtual ~FirewallHelperClass();
};

FirewallHelperClass::~FirewallHelperClass()
{
	// FirewallHelperClass::reset(), rowed under its address name.
	((Rva0059515C *)this)->rva0059515C();
}
