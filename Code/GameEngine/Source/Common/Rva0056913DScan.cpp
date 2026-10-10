// cl: /MD /Ireference/shims/bfme2_ascii
//
// ?removeDuckingTarget@LargeGroupAudioSoundKeyPair@@QAEXPAVBitRange@@PAX@Z @0x0056913D 158B.
// Twin of 0x005691DB (see Rva005691DBScan.cpp for the recipe): same slot
// notify via pinned 0x005C834A and same && short-circuit statement-temp
// element scan, plus a rowed 0x00568F04 find-erase of this from the host
// vector before the scan and a +0xC clear beside the +0x10 clear on match.
// Honest address-derived names.

#include "ascii_string.h"

// Retail has no EH frame here (no __EH_prolog, only the [ebp-4] alive flag of
// the rva00568BE2 temporary): it compiled compare and the temporary's
// releaseBuffer teardown as non-throwing.
template <> int StringBase<char>::compare(const StringBase<char> &str) const throw();
template <> void StringBase<char>::releaseBuffer() throw();

// The element strings compare through StringBase<char>::compare, as retail calls it.
static inline const StringBase<char> &asBase(const AsciiString &s)
{
	return *(const StringBase<char> *)&s;
}

// The ledger row at 0x005C834A is HostClass005C815B::method_005C834A.
class HostClass005C815B
{
public:
	void method_005C834A(int a, int b) throw();
};

class Rva005C834A
{
public:
};

class Rva00568F04
{
public:
	void rva00568F04(void *item) throw();
};

class BitRange
{
public:
	AsciiString rva00568BE2() throw();
};

struct Rva0056913DKeyRef
{
	char m_pad[0x18];
	AsciiString m_key; // +0x18
};

struct Rva0056913DElem
{
	AsciiString m_a;	// +0x0
	AsciiString m_b;	// +0x4
	char m_pad08[4];	// +0x8
	unsigned m_flags;	// +0xC
	unsigned char m_active; // +0x10
	char m_pad11[3];
};

class LargeGroupAudioSoundKeyPair
{
public:
	void removeDuckingTarget(BitRange *host, void *tag);
private:
	char m_pad[0x14];
	Rva0056913DElem *m_begin;	// +0x14
	Rva0056913DElem *m_end;	// +0x18
	char m_pad2[0x10];
	Rva005C834A *m_slots[4];	// +0x2C
};

void LargeGroupAudioSoundKeyPair::removeDuckingTarget(BitRange *host, void *tag)
{
	Rva005C834A **slot = m_slots;
	int left = 4;
	do {
		if (*slot != 0)
			((HostClass005C815B *)*slot)->method_005C834A((int)host, (int)tag);
		++slot;
	} while (--left != 0);
	((Rva00568F04 *)host)->rva00568F04(this);
	for (Rva0056913DElem *e = m_begin; e != m_end; ++e) {
		Rva0056913DKeyRef *keyRef = (Rva0056913DKeyRef *)*(void **)((char *)host + 0x3C);
		bool hit;
		if (asBase(e->m_a).compare(asBase(keyRef->m_key)) == 0 && asBase(e->m_b).compare(asBase(host->rva00568BE2())) == 0)
			hit = true;
		else
			hit = false;
		if (hit) {
			e->m_flags = 0;
			e->m_active = 0;
			return;
		}
	}
}
