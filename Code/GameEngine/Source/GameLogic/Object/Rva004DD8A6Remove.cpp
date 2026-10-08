// cl: /O1 /Oy- /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004DD8A6, 84 bytes, cdecl. For each of count 16-byte records whose
// bucket pointer is non-null, scan the five link slots at bucket +0x14..+0x24
// and unlink the first node whose key matches, freeing it through rowed
// 0x004DD890. The node link is at +0 and the key at +8.
struct Rva004DD8A6Node
{
	Rva004DD8A6Node *next;
	char m_pad[4];
	unsigned int key;		// +0x8
};

struct Rva004DD8A6Bucket
{
	char m_pad[0x14];
	Rva004DD8A6Node *m_slots[5];	// +0x14..+0x24
};

struct Rva004DD8A6Rec
{
	Rva004DD8A6Bucket *m_bucket;	// +0x0
	char m_pad[0xC];
};

void __cdecl rva004DD890(void *node);

void __cdecl rva004DD8A6(unsigned int key, Rva004DD8A6Rec *rec, int count)
{
	for (; count > 0; --count, ++rec)
	{
		if (rec->m_bucket)
		{
			for (int off = 0x14; off < 0x28; off += 4)
			{
				Rva004DD8A6Node **link = (Rva004DD8A6Node **)((char *)rec->m_bucket + off);
				for (; *link; link = (Rva004DD8A6Node **)*link)
				{
					if ((*link)->key == key)
					{
						Rva004DD8A6Node *node = *link;
						*link = node->next;
						rva004DD890(node);
						break;
					}
				}
			}
		}
	}
}
