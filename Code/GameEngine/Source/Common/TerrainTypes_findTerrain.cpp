// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BFME2 terrain-type collection lookup. Layout is retail-owned: the list
// head lives at this+0x0C, TerrainType carries its name at +0x04 and its
// next link at +0x20 (the +0x00..+0x03 and +0x0C..+0x1F ranges are still
// unproven; m_texture sits at +0x08 per the two by-value getters that copy
// it). The name comparison calls out to AsciiString::compare (rowed at
// 0x0069D6) instead of inlining it the way the BFME1 donor does.
//
// Codegen notes (all load-bearing, verified byte-exact at 0x000317D18):
// the key travels by value (caller constructs, callee destroys through the
// pinned ~AsciiString at 0x00036410) and compare is declared throw() -
// without it MSVC spends an EH state around the loop (and [ebp-4],0) that
// retail does not have.

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();
	Int compare(const AsciiString &other) const throw();
private:
	void *m_data;
};

class TerrainType
{
	friend class TerrainTypeCollection;
public:
// ?friend_getNext@TerrainType@@ present-unmatched
	TerrainType *friend_getNext(void) { return m_next; }
private:
	char m_pad0[4];
	AsciiString m_name;
	AsciiString m_texture;
	char m_pad1[0x14];
	TerrainType *m_next;
};

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
private:
	char m_pad[0x0c];
	TerrainType *m_terrainList;
};

TerrainType *TerrainTypeCollection::findTerrain(AsciiString name)
{
	TerrainType *terrain;

	for (terrain = m_terrainList; terrain; terrain = terrain->friend_getNext()) {
		if (terrain->m_name.compare(name) == 0)
			return terrain;
	}

	return 0;
}
