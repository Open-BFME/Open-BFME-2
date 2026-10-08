// ?drainChain@Rva006CEAD0@@QAEXXZ, retail 0x006CEAD0, 57 bytes.
//
// Drains the 8-byte-block chain rooted at ModuleInfo::Nugget+0. The landed
// Nugget dtor (ModuleInfoNuggetDestructor.cpp) calls this address as its +0
// member teardown and spells that member AsciiString, but the plain
// AsciiString dtor already lives at 0x0048BA39 as a 5-byte releaseBuffer
// tail-jump, so this 57-byte walker takes an opaque, address-derived
// identity instead of a second claim on the AsciiString name.
//
// Retail walks [this] as the head of an intrusive list whose link sits at
// +4: each live node is detached through 0x006CD530 (thiscall, no args),
// released through the sized deallocator at 0x006DB270 (this = allocator
// object at 0x00E176E8, args (block, 8)), and the head advances to the
// saved next pointer until it runs null. Both callees resolve via pins;
// the allocator global is a TU-local extern (DIR32 auto-patches).
// No // cl: line: the defaults (-O2, -EHsc-) already match this EH-free
// loop body (the lea-ebx alignment nop is plain /O2 loop alignment).
class Rva006CD530
{
public:
	void detach();

	int m_linkHead; // +0, consumed inside detach, untouched here
	Rva006CD530 *m_next; // +4, chain link advanced below
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006CEAD0
{
public:
	void drainChain();

private:
	// Volatile: the loop must re-read the head from memory top and bottom
	// (retail is cmp [this],0 at both ends, never a test on the saved
	// next pointer); without it MSVC forwards the stored next pointer
	// into the loop check and the bottom compare vanishes.
	Rva006CD530 *volatile m_chainHead;
};

// ?drainChain@Rva006CEAD0@@QAEXXZ
void Rva006CEAD0::drainChain()
{
	if (m_chainHead == 0)
		return;
	Rva006CD530 *current;
	Rva006CD530 *next;
	do {
		current = m_chainHead;
		if (current != 0) {
			next = current->m_next;
			current->detach();
			g_pChainBlockAllocator->freeBlock(current, 8);
			m_chainHead = next;
		}
	} while (m_chainHead != 0);
}

