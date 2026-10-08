// cl: /MD
//
// ?removeDuckingTarget@LargeGroupAudioSoundKeyPair@@QAEXPAVBitRange@@PAX@Z @0x0056913D 158B.
// Twin of 0x005691DB (see Rva005691DBScan.cpp for the recipe): same slot
// notify via pinned 0x005C834A and same && short-circuit statement-temp
// element scan, plus a rowed 0x00568F04 find-erase of this from the host
// vector before the scan and a +0xC clear beside the +0x10 clear on match.
// Honest address-derived names.
// class-gate: allow StringBase nothrow TU-local codegen view, shim decls throw and emit an EH frame retail lacks

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &str) const throw();
	~StringBase();
private:
	void *m_data;
};

#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

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
	StringBase<char> rva00568BE2() throw();
};

struct Rva0056913DKeyRef
{
	char m_pad[0x18];
	StringBase<char> m_key; // +0x18
};

struct Rva0056913DElem
{
	StringBase<char> m_a;	// +0x0
	StringBase<char> m_b;	// +0x4
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
		if (e->m_a.compare(keyRef->m_key) == 0 && e->m_b.compare(host->rva00568BE2()) == 0)
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
