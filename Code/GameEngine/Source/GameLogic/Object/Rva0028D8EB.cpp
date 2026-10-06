// cl: /DNDEBUG /MD

// ?rva0028D8EB@Rva0028D8EB@@QAEHH@Z, RVA 0x0028D8EB, 21B. Unlock lane:
// const forward to rowed ?Rva001E4426Test@@YAHPAIH@Z at 0x001E4426 with
// (this+0x3A4, bit); int passthrough, ret 4, pops. Owner unknown so honest
// address-derived class and method names; the callee takes a non-const word
// pointer so the method is QAE. Unblocks 5 callers incl 0x0039E968. Flags copy the next neighbour
// ObjectRva0028D9E5.cpp.
int Rva001E4426Test(unsigned int *words, int bit);

class Rva0028D8EB
{
public:
	int rva0028D8EB(int bit);
private:
	unsigned char m_pre[0x3A4];
	unsigned int m_bits[1];
};

int Rva0028D8EB::rva0028D8EB(int bit)
{
	return Rva001E4426Test(m_bits, bit);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?hasSpecialPower@Object@@QBE_NW4SpecialPowerType@@@Z=?rva0028D8EB@Rva0028D8EB@@QAEHH@Z")
