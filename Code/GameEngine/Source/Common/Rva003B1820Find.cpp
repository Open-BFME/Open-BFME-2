// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva003B1820@Rva003B1820@@QAEPAXABV?$StringBase@D@@@Z @0x003B1820 (51B):
// Fixed 6-entry name-table lookup. Each entry is 0x14 bytes starting with a
// StringBase<char> at +0x00, table at +0x0C. Compares each entry name
// case-insensitively via the rowed StringBase compareNoCase at 0x00006A00
// and returns the entry address or null. Shape matches the retail loop with
// index in esi, base in ebx and imul recompute on hit.
// Evidence: unlock lane, sole callee rowed, caller 0x00200B20.
template <typename T>
class StringBase
{
public:
	int compareNoCase(const StringBase &other) const;
private:
	T *m_data;
};

struct Rva003B1820Entry
{
	StringBase<char> m_name; // +0x00
	char m_rest[0x10]; // +0x04..+0x13
};

class Rva003B1820
{
public:
	void *rva003B1820(const StringBase<char> &name);
private:
	char m_pad[0x0C]; // +0x00..+0x0B
	Rva003B1820Entry m_entries[6]; // +0x0C
};

void *Rva003B1820::rva003B1820(const StringBase<char> &name)
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_entries[i].m_name.compareNoCase(name) == 0)
			return &m_entries[i];
	}
	return 0;
}
