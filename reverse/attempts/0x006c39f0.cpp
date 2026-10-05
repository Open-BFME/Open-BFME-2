// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// partial score=0.95 date=2026-10-05
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// partial score=0.92 date=2026-10-05
// cl: /O2 /DNDEBUG /MD
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z @ 0x006C39F0 (191B)
//
// Delayed-free hash insert of the debug allocator, continued from the banked
// attempt at reverse/attempts/0x006c39f0.cpp.
//
// Retail returns true immediately unless the tracking byte at this+0x680 is
// set. The table at this+0x684 holds the bucket array at +0 and the bucket
// count at +8; the search hashes the key with (key >> 3) % count, walks the
// chain comparing the stored key at node+0 and following m_next at node+8,
// and returns true on a hit. On a miss the run is either the caller's buffer
// or a fresh allocation from 0x006C3940, in which case the trailing two-byte
// length word is written at both ends. The insert length differs between the
// two paths: the second argument on the direct path, the third on the
// allocated path. A failed insert releases the run through 0x006C1A50 only
// when this body allocated it.
//
// Register shape (retail): bl is a persistent byte that is preset to 1 at
// entry, doubles as the true-return constant for the tracking-off and
// key-found exits, and is the "allocated" flag (cleared on the direct path).
// Keeping `owned` as a bool that spans the whole function is what reproduces
// bl; declaring it after the tracking check does not.
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

// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z present-unmatched
bool Rva006C39F0Owner::rva006C39F0(unsigned int key, unsigned int altLen,
                                  unsigned int allocSize, void *buffer)
{
	bool owned = true;
	if (!m_tracking)
		return owned;

	Rva006C17B0 *table = &m_table;
	Rva006C17B0Node *node = table->m_array
		? table->m_array[(key >> 3) % table->m_prime] : 0;

	while (node)
	{
		if (node->m_key == key)
			return owned;
		node = node->m_next;
	}

	void *run = buffer;
	owned = run == 0;
	if (!run)
	{
		if (!allocSize)
			return false;

		run = rva006C3940Alloc(allocSize);
		if (!run)
			return false;

		*(unsigned short *)run = (unsigned short)allocSize;
		*(unsigned short *)((unsigned char *)run + allocSize - 2) = 0;
		altLen = allocSize;
	}

	if (table->rva006C21C0(altLen, run))
		return true;

	if (owned)
		rva006C1A50Free(run);
	return false;
}