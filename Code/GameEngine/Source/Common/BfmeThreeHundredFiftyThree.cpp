extern "C" unsigned char bfmeVftUB[];

void bfmeFreeUB(void *what);

class BfmeThingUB
{
public:
	__declspec(noinline) void bfmeResetUB();
	void rva00135E35();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

void BfmeThingUB::bfmeResetUB()
{
	m_bfmeVft = bfmeVftUB;
	bfmeFreeUB(m_bfmeWhat);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva0061ED80@@UAE@XZ=?bfmeResetUB@BfmeThingUB@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva009EB810TailBase@@UAE@XZ=?bfmeResetUB@BfmeThingUB@@QAEXXZ")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_bfmeVftUB=??_7ShdDefFactoryClass@@6B@")

// Native135E35..135E3A five-byte JMP61ED80. The established opaque
// donor receiver and no-argument ABI are preserved; this wrapper has no
// independently recovered application name or parent lifetime identity.
void BfmeThingUB::rva00135E35() { bfmeResetUB(); }
