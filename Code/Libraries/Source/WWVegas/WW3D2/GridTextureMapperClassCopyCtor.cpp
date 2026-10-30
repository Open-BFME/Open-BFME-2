// cl: /O2 /G7 /MD
//
// GridTextureMapperClass copy constructor, retail 0x00184420, 127 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies. Reset is inlined.

class WW3D
{
public:
private:
	static unsigned int SyncTime;
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
};

// WW3D::SyncTime is owned by ww3d.cpp (private static ?SyncTime@WW3D@@0IA
// at VA 0x00DEC3CC); this unit merely declares it via the class above.

class RefCountClass
{
public:
	// Match the retail base constructor and donor virtual order. Its inline
	// copies initialize one reference; Delete_This occupies slot zero.
	__declspec(dllimport) __forceinline RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass();
private:
	int NumRefs;
};

class Matrix4;

class TextureMapperClass : public RefCountClass
{
public:
	// ??0TextureMapperClass@@QAE@ABV0@@Z is owned by mapper.cpp; its strong copy wins at link time.
	// This inline body lets Grid's copy constructor inline the base initialization.
	TextureMapperClass(const TextureMapperClass &src)
	{
		Stage = src.Stage;
	}
	virtual ~TextureMapperClass();
	virtual int Mapper_ID() const;
	virtual TextureMapperClass *Clone() const = 0;
	virtual bool Is_Time_Variant();
	virtual void Apply(int) = 0;
	virtual void Reset();
	virtual bool Needs_Normals();
	virtual void Calculate_Texture_Matrix(Matrix4 &) = 0;
	unsigned Stage;
};

class GridTextureMapperClass : public TextureMapperClass
{
public:
	GridTextureMapperClass(const GridTextureMapperClass &src)
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
	virtual ~GridTextureMapperClass();
	virtual int Mapper_ID() const;
	virtual TextureMapperClass *Clone() const;
	virtual bool Is_Time_Variant();
	virtual void Apply(int);
	virtual void Reset()
	{
		Remainder = 0;
		if (Sign >= 0)
			CurrentFrame = Offset;
		else
			CurrentFrame = (LastFrame - 1) - Offset;
		LastUsedSyncTime = WW3D::Get_Sync_Time();
	}
	virtual void Calculate_Texture_Matrix(Matrix4 &);

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

// The copy constructor is a header inline in mapper.cpp. This anchor retains
// its matched row body here, but the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeGridTextureMapperInlineAnchor@@YAXPAVGridTextureMapperClass@@@Z absent-from-retail
void _bfmeGridTextureMapperInlineAnchor(GridTextureMapperClass *mapper)
{
	mapper->GridTextureMapperClass::GridTextureMapperClass(*mapper);
	mapper->GridTextureMapperClass::Reset();
}
#pragma inline_depth()
