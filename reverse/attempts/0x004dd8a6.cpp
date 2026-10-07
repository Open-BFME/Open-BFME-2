// ?rva004DD8A6@@YAXHPAURva004DD8A6Entry@@H@Z
// partial score=0.96 date=2026-10-07
// cl: /Oy-
//
// Target boundary 0x004DD8A6 (84B). Retail reads a cdecl key, an array whose
// entries advance by 0x10, and a count. For each non-null pointer at entry+0,
// it visits five list heads at pointed-object+0x14..+0x24; node links are at
// +0 and the compared dword is at +8. These offsets and loop bounds come from
// target bytes. The owner and node type identities are not established.
struct Rva004DD8A6Node
{
	Rva004DD8A6Node *m_next;
	int m_04;
	int m_key;
};

struct Rva004DD8A6Table
{
	char m_pad00[0x14];
	Rva004DD8A6Node *m_buckets[5];
};

struct Rva004DD8A6Entry
{
	Rva004DD8A6Table * volatile m_table;
	char m_pad04[0x0c];
};

void __cdecl rva004DD890(void *node);

void __cdecl rva004DD8A6(volatile int key, Rva004DD8A6Entry *entries, int count)
{
	if (count <= 0)
		return;
	int remaining = count;

	do {
		if (entries->m_table != 0) {
			for (int offset = 0x14; offset < 0x28; offset += 4) {
				Rva004DD8A6Node * volatile *link =
					(Rva004DD8A6Node * volatile *)((char *)entries->m_table + offset);
				Rva004DD8A6Node *node;
				while (*link != 0) {
					node = *link;
					int nodeKey = node->m_key;
					if (nodeKey == key) {
						Rva004DD8A6Node *removed = *link;
						*link = removed->m_next;
						rva004DD890(removed);
						break;
					}
					link = (Rva004DD8A6Node * volatile *)node;
				}
			}
		}
		entries = (Rva004DD8A6Entry *)((char *)entries + 0x10);
	} while (--remaining != 0);
}
