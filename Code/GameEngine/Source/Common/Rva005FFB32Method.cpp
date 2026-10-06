// cl: /MD
//
// ?rva005FFB32@Rva005FFB32@@QAEXXZ @ 0x005FFB32 (51B).
// Reset notifier if present then reset each entry whose head pointer is set.
// Evidence: method twin pin 0x005CB260 via ecx-this call sites; count at +0x48;
// array at +0x28 stride 0xC; head pointers at +0x20 and entry +0x0;
// caller 0x005FFB81 8B jmp; free pin ?Rva005CB260@@YAXXZ shares address.
class Rva005CB260
{
public:
	void rva005CB260();
};

struct Rva005FFB32Elem
{
	Rva005CB260 *m_head;
	char m_pad[8];
};

class Rva005FFB32
{
public:
	void rva005FFB32();
private:
	char m_pad0[0x20];
	Rva005CB260 *m_p20;
	char m_pad1[0x4];
	Rva005FFB32Elem m_elems[2];
	char m_pad2[0x48 - (0x28 + 2 * 0xC)];
	int m_count;
};

void Rva005FFB32::rva005FFB32()
{
	if (m_p20)
		m_p20->rva005CB260();
	for (int i = 0; i < m_count; ++i) {
		if (m_elems[i].m_head)
			m_elems[i].m_head->rva005CB260();
	}
}
