// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// partial score=0.85 date=2026-10-04
// cl: /O2 /DNDEBUG /MD
// Address-derived recovery of 0x006C39F0 (191 bytes), the delayed-free hash
// insert of the debug allocator. Structure, hash shape and flags come from the
// near file Rva006C21C0.cpp, whose rowed body this one calls at 0x006C21C0.
//
// Retail returns true immediately unless the tracking byte at this+0x680 is set.
// The table at this+0x684 holds the bucket array at +0 and the bucket count at
// +8; the search hashes the key with (key >> 3) % count, walks the chain
// comparing the stored key at node+0 and following m_next at node+8, and
// returns true on a hit. On a miss the run is either the caller's buffer (a4)
// or a fresh allocation of a3 bytes from 0x006C3940, in which case the trailing
// two-byte length word is written at both ends exactly as the sibling reader
// Rva006C1FE0 expects. The insert length differs between the two paths: a1 on
// the direct path, a2 on the allocated path. A failed insert releases the run
// through 0x006C1A50 only when this body allocated it.
//
// The class view is deliberately partial: only the fields these two bodies
// touch are named, and the allocator object is known to exceed 0x684 bytes.

struct Rva006C17B0Node
{
	unsigned int m_key;
	unsigned char m_unaccessed4[4];
	Rva006C17B0Node *m_next;
};

// Retail reads the bucket array at table+0 and divides by table+8, so only
// those two leading fields are named here; the rowed insert body at 0x006C21C0
// proves the rest of the object independently and is not re-declared.
class Rva006C17B0
{
public:
	Rva006C17B0Node **m_array;
	unsigned char m_pad4[4];
	unsigned int m_prime;

	bool rva006C21C0(unsigned int len, void *buf);
};

class Rva006C39F0Owner
{
public:
	// 0x006C3940: thiscall, ret 4, returns the run base or null.
	void *rva006C3940Alloc(unsigned int size);
	// 0x006C1A50: thiscall, ret 4, releases a run.
	void rva006C1A50Free(void *run);

	bool rva006C39F0(unsigned int key, unsigned int altLen, unsigned int allocSize, void *buffer);

	unsigned char m_unaccessed[0x680];
	unsigned char m_tracking;
	unsigned char m_pad681[3];
	Rva006C17B0 m_table; // +0x684, embedded by value
};

// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z @ 0x006C39F0 (191B)
// Retail holds `this` in a local (spilled to [esp+4]) because the allocator and
// release calls clobber ecx, and it carries two byte flags: bl starts 1 so the
// not-tracking and chain-hit paths share the `al = bl` epilogue and return true,
// is cleared before the miss work, and is set again once an allocation succeeds
// so only a genuinely self-allocated run is released when the insert rejects it.
bool Rva006C39F0Owner::rva006C39F0(unsigned int key, unsigned int altLen,
                                  unsigned int allocSize, void *buffer)
{
	Rva006C39F0Owner *self = this;
	bool result = true;

	if (self->m_tracking) {
		Rva006C17B0 *table = &self->m_table;
		Rva006C17B0Node *node = table->m_array
			? table->m_array[(key >> 3) % table->m_prime] : 0;

		while (node) {
			if (node->m_key == key)
				return result;
			node = node->m_next;
		}

		result = false;
		unsigned char *run = (unsigned char *)buffer;
		bool allocated = false;

		if (buffer) {
			if (table->rva006C21C0(key, run))
				return true;
		} else if (allocSize) {
			run = (unsigned char *)self->rva006C3940Alloc(allocSize);
			if (run) {
				*(unsigned short *)run = (unsigned short)allocSize;
				*(unsigned short *)(run + allocSize - 2) = 0;
				allocated = true;
				result = true;
				if (table->rva006C21C0(altLen, run))
					return true;
			}
			if (allocated)
				self->rva006C1A50Free(run);
		}
	}

	return result;
}