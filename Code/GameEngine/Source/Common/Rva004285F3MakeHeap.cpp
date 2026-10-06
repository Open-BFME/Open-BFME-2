// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva004285F3MakeHeap@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z RVA 0x004285F3 size 88 evidence chain linkbody callers 0x004286F2 callees narrow-copy 0x00427F75 adjust-heap 0x00428372
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
void __cdecl Rva00428372AdjustHeap(VersionBlockEntry *first, int holeIndex, int len, Pivot24 val, VersionBlockKeyCompare comp);
void __cdecl Rva004285F3MakeHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp)
{
	int len = last - first;
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	while (1)
	{
		Rva00428372AdjustHeap(first, parent, len, *(Pivot24 *)(first + parent), comp);
		if (parent == 0)
			break;
		--parent;
	}
}
