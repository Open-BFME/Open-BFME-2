// cl: /MD
// ?Rva00586B92Destroy@@YAXPAVRva00585B16@@0@Z @0x00586B92 25B.
// Destroy range [first,last) elem 0x54 via rowed ??1Rva00585B16 0x585B16. Callers 0x586BB3 0x586C31 0x586EA5. Unlocks 3.
class Rva00585B16 {
public: ~Rva00585B16();
private: char m_pad[0x54];
};
void __cdecl Rva00586B92Destroy(Rva00585B16 *first, Rva00585B16 *last)
{
	for (; first != last; ++first)
		first->~Rva00585B16();
}
