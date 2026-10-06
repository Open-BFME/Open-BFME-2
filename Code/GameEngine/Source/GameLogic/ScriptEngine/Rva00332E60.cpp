// cl: /DNDEBUG /MD
// ?rva00332E60@Rva00332E60@@QAEPAXH@Z @0x00332E60 35B
// retail 0x00332E60 35 bytes unlock search 17-entry table at +0x14 each 8 bytes
// compares first dword to arg returns entry pointer or null caller 0x00333918
// neighbours prev 0x00332C7A ScriptEventFlags and next 0x00332E9D Object156Copy

struct Rva00332E60Entry
{
	unsigned int key;
	unsigned int value;
};

struct Rva00333261Entry
{
	int key;
	unsigned char pad[0x20];
};

struct Rva0033323DEntry
{
	int key;
	unsigned char pad[0x98];
};

class Rva00332E60
{
public:
	void *rva00332E60(int key);
	void *rva0033321B(int key);
	void *rva00333261(int key);
	void *rva0033323D(int key);
	void *rva00333918(int key);

private:
	unsigned char m_pad[20];
	Rva00332E60Entry m_entries[17];
	unsigned char m_pad2[4];
	int *m_a0Begin;
	int *m_a0End;
	unsigned char m_pad3[0x14];
	Rva0033323DEntry *m_bcBegin;
	Rva0033323DEntry *m_bcEnd;
	unsigned char m_pad4[4];
	Rva00333261Entry *m_c8Begin;
	Rva00333261Entry *m_c8End;
};

void *Rva00332E60::rva00332E60(int key)
{
	for (int i = 0; i < 17; ++i)
	{
		if (m_entries[i].key == (unsigned int)key)
			return &m_entries[i];
	}
	return 0;
}

void *Rva00332E60::rva0033321B(int key)
{
	int *begin = m_a0Begin;
	int *end = m_a0End;
	for (; begin != end; ++begin)
	{
		if (*begin == key)
			return begin;
	}
	return 0;
}

void *Rva00332E60::rva00333261(int key)
{
	Rva00333261Entry *begin = m_c8Begin;
	Rva00333261Entry *end = m_c8End;
	for (; begin != end; ++begin)
	{
		if (begin->key == key)
			return begin;
	}
	return 0;
}

void *Rva00332E60::rva0033323D(int key)
{
	Rva0033323DEntry *begin = m_bcBegin;
	Rva0033323DEntry *end = m_bcEnd;
	for (; begin != end; ++begin)
	{
		if (begin->key == key)
			return begin;
	}
	return 0;
}

void *Rva00332E60::rva00333918(int key)
{
	void *found = rva00332E60(key);
	if (found != 0)
		return found;
	found = rva0033321B(key);
	if (found != 0)
		return found;
	found = rva0033323D(key);
	if (found != 0)
		return found;
	return rva00333261(key);
}
