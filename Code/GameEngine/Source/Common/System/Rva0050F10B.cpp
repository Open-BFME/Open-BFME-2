// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc
// ?rva0050F10B@Rva0050F10B@@QAEXPBD@Z 119B @0x0050F10B: index-param clear of entry holder via rowed GetParam and clear. Evidence: REF constant at 0x0051076D in FUN_0091066a plus rowed callees 0x004128F0 0x000AD6F4 0x00036410 plus IAT atoi plus neighbours Rva0050F0AB and FamilyDeletingDtors.
#include "ascii_string.h"

class Rva000AD6F4
{
public:
	void clear();
private:
	void *m_ptr;
};

bool __cdecl Rva004128F0GetParam(const char *a, const char *b, AsciiString &c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

class Rva0050F10B
{
public:
	void rva0050F10B(const char *p);
private:
	char m_pad00[0x20];
	int m_count;
	struct Entry
	{
		int m_00;
		Rva000AD6F4 m_holder;
	};
	Entry m_entries[1];
};

void Rva0050F10B::rva0050F10B(const char *p)
{
	AsciiString tmp;
	if (!Rva004128F0GetParam(p, "index", tmp))
		return;
	int idx = atoi(tmp.str());
	if (idx < 0 || idx > m_count)
		return;
	Entry &slot = m_entries[idx];
	slot.m_holder.clear();
}
