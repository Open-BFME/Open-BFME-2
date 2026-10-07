// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// Donor: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// Drawable/Draw/Rva0075C690CountSharedEdges.cpp. Original target helper name
// is unknown; native three-ushort entries and remap loads prove the operation.
// Address-qualified reconstruction of retail RVA 0x000B36CE.
// Each packed entry names three vertices. The helper counts entries containing
// both requested vertices after translating the packed indices through the
// caller's vertex-remap table.

typedef unsigned short UnsignedShort;

struct Rva000B36CEPackedEntry
{
	UnsignedShort vertex[3];
};

static __declspec(noinline) int Rva000B36CECountSharedEdges(
	int entryCount, const Rva000B36CEPackedEntry *entries,
	const int *vertexRemap, int firstVertex, int secondVertex)
{
	int sharedCount = 0;
	for (int i = 0; i < entryCount; ++i)
	{
		bool hasFirst =
			firstVertex == vertexRemap[entries[i].vertex[0]] ||
			firstVertex == vertexRemap[entries[i].vertex[1]] ||
			firstVertex == vertexRemap[entries[i].vertex[2]];
		bool hasSecond =
			secondVertex == vertexRemap[entries[i].vertex[0]] ||
			secondVertex == vertexRemap[entries[i].vertex[1]] ||
			secondVertex == vertexRemap[entries[i].vertex[2]];
		if (hasFirst && hasSecond)
			++sharedCount;
	}
	return sharedCount;
}

// Native Ghidra boundary B36CE/111, ending with RET at B373C. Two native
// callers at B8440 and B89E9 each call this helper three times. At B8723,
// EAX=count ECX=packed entries EDX=remap EDI=first vertex and a pushed
// second vertex establish the private register ABI. Preserve TU-local linkage.
// The context below is compiler support, not a recovered retail caller.
// ?Rva000B36CECallPattern absent-from-retail
int Rva000B36CECallPattern(int count,
	const Rva000B36CEPackedEntry *entries, const int *remap,
	int a, int b, int c)
{
	return Rva000B36CECountSharedEdges(count, entries, remap, a, b)
		+ Rva000B36CECountSharedEdges(count, entries, remap, b, c)
		+ Rva000B36CECountSharedEdges(count, entries, remap, c, a);
}
