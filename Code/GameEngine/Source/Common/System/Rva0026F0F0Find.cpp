// cl: /DNDEBUG /MD
// ?rva0026F0F0@Rva0026F0F0@@QAEPAXPBX@Z @0x0026F0F0 42B
// Find over +0xc list: return first node whose +0x38 bit is set in the
// caller mask array, following +0x64 links. Unlocks 8 callers.
// Evidence: and 0x1f shl shr-5 test [mask+word*4] bit pattern ret 4.
struct Rva0026F0F0Node
{
	char m_pad00[0x38];
	int m_bit;
	char m_pad3c[0x28];
	Rva0026F0F0Node *m_next;
};
struct Rva0026F0F0
{
	char m_pad00[0x0c];
	Rva0026F0F0Node *m_head;
	void *rva0026F0F0(const void *mask);
};
void *Rva0026F0F0::rva0026F0F0(const void *mask)
{
	const unsigned int *bits = (const unsigned int *)mask;
	for (Rva0026F0F0Node *node = m_head; node; node = node->m_next) {
		unsigned int bit = (unsigned int)node->m_bit;
		if (bits[bit >> 5] & (1u << (bit & 0x1f)))
			return node;
	}
	return 0;
}
