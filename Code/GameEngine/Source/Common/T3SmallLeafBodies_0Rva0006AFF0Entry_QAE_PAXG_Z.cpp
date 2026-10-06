// cl: -DNDEBUG -MD -EHs-c- -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME-1: leaf bodies out of d_0005b6c0.asm that carry no relocation at
// all, so every byte of them is proof.
//
// 0x6AFF0 is one of the remaining constructors. It takes a pointer and a 16-bit
// tag and stores one at +0x00, the other at +0x04; the whole body is two stores
// and no relocation, so every byte of it is proof.
//
// Identity here is address-derived: it touches no named global and calls nothing.
//
// Dedicated TU: only the placed body is defined; the donor's other seven
// definitions are omitted.

typedef int Int;

// a two-field record: pointer then a 16-bit tag
class Rva0006AFF0Entry
{
public:
	Rva0006AFF0Entry(void *item, unsigned short tag);

private:
	void *m_item;										///< retail this+0x00
	unsigned short m_tag;								///< retail this+0x04
};

// ??0Rva0006AFF0Entry@@QAE@PAXG@Z
Rva0006AFF0Entry::Rva0006AFF0Entry(void *item, unsigned short tag)
{
	m_item = item;
	m_tag = tag;
}