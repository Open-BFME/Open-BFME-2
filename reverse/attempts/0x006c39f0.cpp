// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// partial score=0.88 date=2026-10-04
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// cl: /O2 /DNDEBUG /MD
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z @ 0x006C39F0 (191B)
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
	void *rva006C3940Alloc(unsigned int size);
	void rva006C1A50Free(void *run);

	bool rva006C39F0(unsigned int key, unsigned int altLen, unsigned int allocSize, void *buffer);

	unsigned char m_unaccessed[0x680];
	unsigned char m_tracking;
	unsigned char m_pad681[3];
	Rva006C17B0 m_table;
};

bool Rva006C39F0Owner::rva006C39F0(unsigned int key, unsigned int altLen,
                                  unsigned int allocSize, void *buffer)
{
	if (!m_tracking)
		return true;

	Rva006C17B0 *table = &m_table;
	Rva006C17B0Node *node = table->m_array
		? table->m_array[(key >> 3) % table->m_prime] : 0;

	while (node) {
		if (node->m_key == key)
			return true;
		node = node->m_next;
	}

	unsigned char *run = (unsigned char *)buffer;
	bool allocated = false;

	if (!buffer) {
		if (!allocSize)
			return false;

		run = (unsigned char *)rva006C3940Alloc(allocSize);
		if (!run)
			return false;

		*(unsigned short *)run = (unsigned short)allocSize;
		*(unsigned short *)(run + allocSize - 2) = 0;
		allocated = true;
	}

	if (!table->rva006C21C0(altLen, run))
		return false;

	if (allocated) {
		rva006C1A50Free(run);
		return false;
	}

	return true;
}