// cl: /MD
// ?rva000B4BED@Rva000B4BED@@QAEPAXPBX@Z @0x000B4BED 176B.
// Finds first entry whose WeaponTemplateSetHead is a subset of the query
// ((entry & query) == entry, skipping empty heads), else first empty head,
// else null. Entries stride 0xF8 with head at +4; table begin/end at +0x24/+0x28.
// Evidence: three copy-ctor calls to ??0WeaponTemplateSetHead@@QAE@ABV0@@Z,
// memcmp wrapper ?Rva00045473Equal@@YA_NPBX0@Z, callers at 0x000BFCD9 etc.

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	unsigned m_bits[19];
};

extern bool __cdecl Rva00045473Equal(const void *a, const void *b);

struct Rva000B4BEDEntry
{
	char _pad[4];
	WeaponTemplateSetHead head;
	char _rest[0xF4 - 4 - 0x4C];
	unsigned char m_00F4;
	char _tail[0xF8 - 0xF4 - 1];
};

class Rva000B4BED
{
	char _pad[0x24];
	Rva000B4BEDEntry *m_begin;
	Rva000B4BEDEntry *m_end;
public:
	void *rva000B4BED(const void *query);
	void *rva000B4C9D(const void *entry);
	void *rva000B4CBE(const void *entry);
	void rva000B4AE4();
};

void *Rva000B4BED::rva000B4BED(const void *query)
{
	WeaponTemplateSetHead tmpQuery(*(const WeaponTemplateSetHead *)query);
	Rva000B4BEDEntry *p = m_begin;
	if (p != m_end)
	{
		do
		{
			WeaponTemplateSetHead tmp(p->head);
			unsigned i = 0;
			do
			{
				if (((const unsigned *)&tmp)[i] != 0)
					goto hasBits;
				++i;
			} while (i < 19);
			goto nextEntry;
		hasBits:
			for (unsigned b = 0; b < 0x4C; b += 4)
				*(unsigned *)((char *)&tmp + b) &= *(const unsigned *)((const char *)&tmpQuery + b);
			if (Rva00045473Equal(&tmp, &p->head))
				return p;
		nextEntry:
			++p;
		} while (p != m_end);
	}
	for (p = m_begin; p != m_end; ++p)
	{
		WeaponTemplateSetHead tmp(p->head);
		unsigned i = 0;
		do
		{
			if (((const unsigned *)&tmp)[i] != 0)
				goto nonEmpty;
			++i;
		} while (i < 19);
	return p;
nonEmpty:;
	}
	return 0;
}

// ?rva000B4C9D@Rva000B4BED@@QAEPAXPBX@Z @0x000B4C9D 33B. Returns entry before
// the given one, or null when given is first or not found. Same table
// begin/end at +0x24/+0x28, stride 0xF8. Evidence: neighbours 0x000B4BED
// and 0x000B6253, caller at 0x000BFD80.
void *Rva000B4BED::rva000B4C9D(const void *entry)
{
	Rva000B4BEDEntry *prev = 0;
	for (Rva000B4BEDEntry *p = m_begin; p != m_end; ++p)
	{
		if (p == entry)
			return prev;
		prev = p;
	}
	return 0;
}

void *Rva000B4BED::rva000B4CBE(const void *entry)
{
	bool found = false;
	for (Rva000B4BEDEntry *p = m_begin; p != m_end; ++p)
	{
		if (found)
			return p;
		if (p == entry)
			found = true;
	}
	return 0;
}

// ?rva000B4AE4@Rva000B4BED@@QAEXXZ @0x000B4AE4 23B. Clears the byte at
// entry+0xF4 for every entry in the same +0x24/+0x28 table, stride 0xF8.
// Evidence: caller at 0x002D0667, neighbours 0x000B4AB5/0x000B4BED.
void Rva000B4BED::rva000B4AE4()
{
	for (Rva000B4BEDEntry *p = m_begin; p != m_end; ++p)
		p->m_00F4 = 0;
}
