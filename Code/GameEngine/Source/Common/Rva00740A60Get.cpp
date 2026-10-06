// cl: /MD
// ?Rva00740A60Get@@YAHABV?$StringBase@D@@@Z, retail 0x00740A60, 54 bytes.
// Table walk with compareNoCase returning index else 0.
// Evidence: caller at 0x00740E49 pushes dword; callee rowed compareNoCase 0x00037980; global table data 0x009DDF68.
template <typename T>
struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};
template <typename T>
class StringBase
{
public:
	int compareNoCase(const char *other) const;
private:
	BfmeStringData<T> *m_data;
};
const char *g_Rva00740A60Table[] = { "A", "B", 0 };
int __cdecl Rva00740A60Get(const StringBase<char> &name)
{
	for (int i = 0; g_Rva00740A60Table[i]; ++i)
	{
		if (name.compareNoCase(g_Rva00740A60Table[i]) == 0)
			return i;
	}
	return 0;
}
