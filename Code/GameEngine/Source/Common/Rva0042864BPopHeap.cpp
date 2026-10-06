// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0042864BPopHeap@@YAXPAUVersionBlockEntry@@0HVVersionBlockKeyCompare@@@Z RVA 0x0042864B size 45 evidence chain linkbody callers 0x00428724 callees narrow-copy 0x00427F75 pop-heap 0x00428594
struct BfmeNarrowRecord00427F75
{
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
	char m_data[24];
};
struct VersionBlockEntry
{
	const char *m_key; // +0
	char m_padAfterKey[8]; // +4
	const char *m_value; // +0xC
	char m_padTail[8]; // +0x10
	~VersionBlockEntry();
};
class ProductionPrerequisite
{
public:
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
struct Pivot24
{
	Pivot24(const Pivot24 &other);
	~Pivot24();
	BfmeNarrowRecord00427F75 narrow;
};
void __cdecl Rva00428594PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *result, Pivot24 val, VersionBlockKeyCompare comp, int extra);
void __cdecl Rva0042864BPopHeap(VersionBlockEntry *first, VersionBlockEntry *last, int unused, VersionBlockKeyCompare comp)
{
	Rva00428594PopHeap(first, last - 1, last - 1, *(Pivot24 *)(last - 1), comp, 0);
}
