// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00428716PopHeap@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z RVA 0x00428716 size 23 evidence pop_heap wrapper calling rowed aux 0x0042864B with dummy 0 caller 0x004287C9 shape matches int precedent 0x00424637
struct VersionBlockEntry
{
	char m_data[24];
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
void __cdecl Rva0042864BPopHeap(VersionBlockEntry *first, VersionBlockEntry *last, int unused, VersionBlockKeyCompare comp);
void __cdecl Rva00428716PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp)
{
	Rva0042864BPopHeap(first, last, 0, comp);
}
