// cl: /O1 /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BFME2 terrain texture-class loading. Retail builds this family with /O1
// (frame-pointer prologue, push/pop materialization); the ZH-port sibling TU
// (WorldHeightMap.cpp) builds /G7, so the /O1 bodies live here.
//
// Layouts are retail-owned: TerrainType carries its name at +0x04 and its
// texture name at +0x08 with the next link at +0x20 (proven by the rowed
// TerrainTypeCollection::findTerrain in TerrainTypes_findTerrain.cpp, whose
// comment records the two by-value getters copying +0x08). TXTextureClass is
// the ZH struct (globalTextureClass, firstTile, numTiles, width,
// isBlendEdgeTile, name at +0x14, positionInTexture).

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString() throw();
	const char *str() const { return m_data ? m_data + 8 : ""; }
private:
	char *m_data;
};

class TerrainType
{
	friend class TerrainTypeCollection;
public:
	AsciiString getTexture() const;
	AsciiString getNrmTexture() const;
private:
	char m_pad0[4];
	AsciiString m_name; // +0x04
	AsciiString m_texture; // +0x08
};

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
};

extern TerrainTypeCollection *TheTerrainTypes;

// ?makeNrmTextureName@@ present-unmatched
AsciiString makeNrmTextureName(const AsciiString &in);

AsciiString TerrainType::getNrmTexture() const
{
	return makeNrmTextureName(m_texture);
}
