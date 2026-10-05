// cl: /O1 /DNDEBUG /MD
//
// ?rva002D2E30@Rva002D2E30@@QAEXH@Z @0x002D2E30 39B: guarded callback fire.
// Retail reads a cdecl callback pointer at +0x14C; if non-null it materializes
// (flag byte at +0x150 != 0) as int, pushes it, calls the pointer, zeroes the
// slot, and pops the argument (caller-cleaned cdecl). The single stack arg is
// dead (frameless this-use only) but required for the ret-4 shape. Member
// bytes before +0x14C are unclaimed pad; the callback target and flag
// semantics are unproven beyond the observed call/zero. Boundary abuts the
// next body at 0x002D2E57. Honest address-derived names.

class Rva002D2E30
{
public:
	void rva002D2E30(int unused);
private:
	unsigned char m_pad00[0x14C]; // +0x00..+0x14C unclaimed
	void (__cdecl *m_cb)(int); // +0x14C
	unsigned char m_flag; // +0x150
};

// ?rva002D2E30@Rva002D2E30@@QAEXH@Z
void Rva002D2E30::rva002D2E30(int)
{
	void (__cdecl *cb)(int) = m_cb;
	if (cb)
	{
		cb(m_flag ? 1 : 0);
		m_cb = 0;
	}
}
