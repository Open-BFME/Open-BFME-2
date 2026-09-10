// cl: /O2 /G7 /MD
//
// GridTextureMapperClass copy constructor, retail 0x00184420, 127 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies. Reset is inlined.

class WW3D
{
public:
	static unsigned int SyncTime;
	static unsigned int Get_Sync_Time() { return SyncTime; }
};

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

TextureMapperClass::TextureMapperClass(const TextureMapperClass &src)
{
	NumRefs = 1;
	Stage = src.Stage;
}

void GridTextureMapperClass::Reset()
{
	Remainder = 0;
	if (Sign >= 0)
		CurrentFrame = Offset;
	else
		CurrentFrame = (LastFrame - 1) - Offset;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}

GridTextureMapperClass::GridTextureMapperClass(const GridTextureMapperClass &src)
	: TextureMapperClass(src)
{
	Unk = src.Unk;
	Sign = src.Sign;
	MSPerFrame = src.MSPerFrame;
	OOGridWidth = src.OOGridWidth;
	GridWidthLog2 = src.GridWidthLog2;
	LastFrame = src.LastFrame;
	Offset = src.Offset;
	Reset();
}
