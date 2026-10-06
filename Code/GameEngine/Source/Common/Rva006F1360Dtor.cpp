// cl: /MD
//
// Opaque destructor with member clears tail-calling Rva006D6470::~
// Rva006D6470 at 0x006D6470 (pinned opaque SEH base dtor; identity unproven).
// The class below stores its own vtable (0xCECCF8, DIR32 auto-patch), clears
// its two pointer members at +0x20/+0x24 via xor-eax plus mov stores, and
// tail-jumps to the base destructor; the base itself is only declared here
// (defined nowhere -- it resolves via the pin), because a same-TU definition
// would capture the call locally instead of at the ledger address.
// Dedicated speed-flags TU (like Rva00711330Dtor): /O1 compacts member
// clears. Owner identity is unproven (opaque Rva name).

class Rva006D6470
{
public:
	virtual ~Rva006D6470();
};

class Rva006F1360 : public Rva006D6470
{
public:
	virtual ~Rva006F1360();

private:
	char m_pad04[0x20 - 4];
	void *m_ptr20;
	void *m_ptr24;
};

Rva006F1360::~Rva006F1360()
{
	m_ptr20 = 0;
	m_ptr24 = 0;
}
