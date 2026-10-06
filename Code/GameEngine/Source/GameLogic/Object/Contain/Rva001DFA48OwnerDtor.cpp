// cl: /Ob2 /DNDEBUG /MD /EHsc
// ??1Rva001DFA48Owner@@UAE@XZ @0x1DFA48 (60B): virtual destructor.
// Formerly spelled ~TransportContainModuleData; that identity belongs to
// 0x004684F1 (slot 0 of TransportContainModuleData vtable 0x00C442F8, installed
// by ctor 0x00468301, calls it via ??_G 0x004684D5). This body installs a
// different vtable (0x7DC940), so its owner class is unrecovered.
// Installs vtable 0x7DC940 then destroys the two pool-aware members at +0xC
// and +0x8 (reverse order) through the 13B forwarder at 0x360D26.
// Identity: vtable install and the ??_G scalar-deleting
// destructor at 0x1DFA87 tail-calling here. The member type is unrecovered
// (not a string: strings route to releaseBuffer, this forwards to a pool op),
// so it keeps an address-derived name with an opaque pin.
// No base call is emitted (trivial base).

// The pool-aware member at +0x8/+0xC; only its address and non-virtual dtor
// are proven. It occupies four bytes (the two call sites are four apart).
class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class Rva001DFA48Owner
{
public:
	virtual ~Rva001DFA48Owner();

private:
	unsigned m_04;				// +0x04 (unrecovered; pads the members to retail offsets)
	Rva00360D26Member m_08;			// +0x08
	Rva00360D26Member m_0C;			// +0x0C
};

// ??1Rva001DFA48Owner@@UAE@XZ
Rva001DFA48Owner::~Rva001DFA48Owner()
{
}
