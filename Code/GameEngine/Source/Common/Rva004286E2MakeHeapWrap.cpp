// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva004286E2Wrap@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z RVA 0x004286E2 size 25 evidence make_heap forwarding wrapper pushing two trailing zeros into rowed worker 0x004285F3 caller 0x00428832 same pattern as Rva002C531BWrap and Rva00207BAAWrap
struct VersionBlockEntry
{
	char m_data[24];
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
void __cdecl Rva004285F3MakeHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp);
void __cdecl Rva004286E2Wrap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp)
{
	typedef void (__cdecl *MakeHeap5)(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare, int, int);
	((MakeHeap5)Rva004285F3MakeHeap)(first, last, comp, 0, 0);
}
