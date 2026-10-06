// cl: /MD
// ?rva00447773@Rva00447773@@QAEPAXH@Z, retail 0x00447773, 33 bytes.
// Bounds-checked indexer returning &m_items[index] for 8 x 0x1D0 records at
// +0xDC else null. Evidence: unlock lane; __thiscall ret 4; callers at
// 0x00248DF1 0x00249950 0x004477A7 0x004483DA 0x004492E4; unblocks 0x00447794.
struct Rva00447773Elem { char data[0x1D0]; };
class Rva00447773 {
	char m_pad[0xDC];
	Rva00447773Elem m_items[8];
public:
	void *rva00447773(int index);
};
void *Rva00447773::rva00447773(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return &m_items[index];
}
