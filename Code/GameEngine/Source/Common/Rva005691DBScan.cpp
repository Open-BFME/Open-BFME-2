// cl: /MD /Ireference/shims/bfme2_ascii
//
// ?removePointersToGridCellsInDuckingTarget@LargeGroupAudioSoundKeyPair@@QAEXPAVBitRange@@PAX@Z @0x005691DB 145B.
// Clear-on-match scan: notify the 4 slots at +0x2C via pinned 0x005C834A,
// then walk elements [m_begin,m_end) at +0x14/+0x18 stride 0x14; the first
// element whose StringBase at +0 compares 0 against the +0x3C key's +0x18
// StringBase AND whose +4 compares 0 against a BitRange::rva00568BE2 temp
// (0x00568BE2, temp torn down via releaseBuffer 0x00036410) gets its +0x10
// byte cleared and the scan returns. Twin of 0x0056913D, which also erases
// via rowed 0x00568F04 and clears +0xC. Honest address-derived names;
// element halves reuse the Rva005686F5Elem adjacency (+0/+4 strings).
// The && short-circuit is load-bearing: the rva00568BE2 hidden temp is a
// statement-scoped temporary constructed only when the first compare is 0,
// so its flag-guarded teardown sits at the if/else join reached by both
// paths; a named inner-scope temp lets MSVC prove post-domination and drop
// the flag (124B). Nested call keeps `push eax` for the compare argument.
//
// Codegen: the strings are the shared AsciiString, whose destructor calls
// releaseBuffer directly, and rva00568BE2 returns one (the row's own spelling,
// Rva003ED498Count.cpp). Retail has no EH frame (no __EH_prolog, no fs chain),
// only the plain [ebp-4] alive-flag, so compare and releaseBuffer are declared
// non-throwing below; the shared header declares them potentially-throwing,
// which emits a frame.

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

class BitRange
{
public:
	AsciiString rva00568BE2() throw();
};

struct Rva005691DBKeyRef
{
	char m_pad[0x18];
	AsciiString m_key; // +0x18
};

struct Rva005691DBElem
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
	void removePointersToGridCellsInDuckingTarget(BitRange *host, void *tag);
private:
	char m_pad[0x14];
	Rva005691DBElem *m_begin;	// +0x14
	Rva005691DBElem *m_end;	// +0x18
	char m_pad2[0x10];
	Rva005C834A *m_slots[4];	// +0x2C
};

void LargeGroupAudioSoundKeyPair::removePointersToGridCellsInDuckingTarget(BitRange *host, void *tag)
{
	Rva005C834A **slot = m_slots;
	int left = 4;
	do {
		if (*slot != 0)
			((HostClass005C815B *)*slot)->method_005C834A((int)host, (int)tag);
		++slot;
	} while (--left != 0);
	for (Rva005691DBElem *e = m_begin; e != m_end; ++e) {
		Rva005691DBKeyRef *keyRef = (Rva005691DBKeyRef *)*(void **)((char *)host + 0x3C);
		bool hit;
		if (asBase(e->m_a).compare(asBase(keyRef->m_key)) == 0 && asBase(e->m_b).compare(asBase(host->rva00568BE2())) == 0)
			hit = true;
		else
			hit = false;
		if (hit) {
			e->m_active = 0;
			return;
		}
	}
}
