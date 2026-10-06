// cl: /MD
//
// Opaque destructor with a member clear tail-calling
// Rva006D6470Owner::~Rva006D6470Owner at 0x006D6470.
// The class below stores its own vtable (0xCEFB40, DIR32 auto-patch), clears
// its pointer member at +0x20, and tail-jumps to the base destructor; the
// base itself is only declared here (defined nowhere), because a same-TU
// definition would capture the call locally instead of at the ledger address.
// Dedicated speed-flags TU: the /O1 shared TU
// compacts the member clear to and-form ahead of the vptr store, while
// retail uses the speed-form mov after it. The opaque derived identity remains
// unresolved.

class Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
};

class Rva00711330 : public Rva006D6470Owner
{
public:
	virtual ~Rva00711330();

private:
	char m_pad04[0x20 - 4];
	void *m_ptr20;
};

Rva00711330::~Rva00711330()
{
	m_ptr20 = 0;
}
