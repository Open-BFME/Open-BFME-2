// cl: /DNDEBUG /MD /EHs-c-
// ??4Rva002CF5D4@@QAEAAU0@ABU0@@Z @0x002CF5D4 43B.
// Assignment for a 448-byte record holding 56 Rva002C99FB at +0: loops 0x38
// times assigning via the rowed 0x002C99FB, returns this in eax with ret 4.
// Caller at 0x002D128C unblocks 0x002D1101.
struct OpaqueRefElement4 {
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
struct Rva002C99FB {
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

struct Rva002CF5D4
{
	Rva002C99FB m_items[56];
	Rva002CF5D4 &operator=(const Rva002CF5D4 &other);
};

Rva002CF5D4 &Rva002CF5D4::operator=(const Rva002CF5D4 &other)
{
	for (int i = 0; i < 0x38; i++)
		m_items[i] = other.m_items[i];
	return *this;
}
