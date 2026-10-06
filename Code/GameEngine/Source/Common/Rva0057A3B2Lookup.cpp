// cl: /MD
// ?Rva0057A3B2Get@@YAHH@Z @0x0057A3B2 33B
// Linear search of 6-entry key/value table at 0x00C6EF40; returns value or -1.
// Evidence: callers at 0x0057AB2B 0x0057AB36 pass int and use signed result.
struct Rva0057A3B2Entry
{
	int m_key;
	int m_value;
};
extern Rva0057A3B2Entry g_00C6EF40[6];
// The matched search indexes exactly six 8-byte entries; retail's table at
// VA 0x00C6EF40 ends at 0x00C6EF70, before the adjacent APT token text.
#pragma data_seg(".rdata")
Rva0057A3B2Entry g_00C6EF40[6] = {
	{ 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 4 },
};
#pragma data_seg()
int __cdecl Rva0057A3B2Get(int val)
{
	for (unsigned int i = 0; i < 6; ++i)
	{
		if (val == g_00C6EF40[i].m_key)
			return g_00C6EF40[i].m_value;
	}
	return -1;
}
