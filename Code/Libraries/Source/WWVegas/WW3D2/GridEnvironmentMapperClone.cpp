// cl: /O2 /MD /EHsc
//
// ?Clone@GridEnvironmentMapperClass@@UBEPAVTextureMapperClass@@XZ @ 0x0013D390 (85B).
// Dedicated TU: vertmaterial.cpp cannot take another row. Layout mirrors the
// landed GridTextureMapperClass copy-ctor TU (base is 0x34, the derived class
// adds no members, so the implicit copy ctor calls the matched base copy
// @0x00184420 then installs the derived vtable 0x007D3260). BFME2 retail uses
// plain global operator new (rowed @0x2FDA0), so ::new here. Sibling of the
// rowed GridClassicEnvironmentMapper Clone at 0x0013D330; donor is BFME1
// GridEnvironmentMapperClass::Clone returning NEW_REF GridEnvironment.

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int NumRefs;
};

class TextureMapperClass : public RefCountClass
{
public:
	TextureMapperClass(const TextureMapperClass &src);
	virtual ~TextureMapperClass();
	unsigned Stage;
};

class GridTextureMapperClass : public TextureMapperClass
{
public:
	GridTextureMapperClass(const GridTextureMapperClass &src);
	virtual ~GridTextureMapperClass();
	virtual void Reset();

	int Unk;
	int Sign;
	unsigned MSPerFrame;
	float OOGridWidth;
	unsigned GridWidthLog2;
	unsigned LastFrame;
	unsigned Offset;
	unsigned Remainder;
	unsigned CurrentFrame;
	unsigned LastUsedSyncTime;
};

class GridEnvironmentMapperClass : public GridTextureMapperClass
{
public:
	virtual TextureMapperClass *Clone() const;
};

TextureMapperClass *GridEnvironmentMapperClass::Clone() const
{
	return ::new GridEnvironmentMapperClass(*this);
}
