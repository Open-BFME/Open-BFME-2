// ?rva004FAC80@Rva004FAC80@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004FAC80, 25 bytes: thiscall that frees the pointer stored at
// +4 when it is non-null (free = retail 0x00030830, ledger _free). The
// member is read through a null-guarded address, which MSVC emits as a
// neg/sbb mask over this.
extern "C" void __cdecl free(void *block);

class Rva004FAC80
{
public:
	void rva004FAC80();

	char m_pad[4];
	void *m_ptr;		// +0x4
};

void Rva004FAC80::rva004FAC80()
{
	unsigned int base = (unsigned int)this;
	void *p = *(void **)(base ? base + 4 : 0);
	if (p)
		free(p);
}
