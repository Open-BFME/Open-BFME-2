// cl: /O2 /MD /EHsc
//
// ?Clone@ScreenMapperClass@@UBEPAVTextureMapperClass@@XZ @ 0x0013DA80 (85B).
// Dedicated TU: vertmaterial.cpp cannot take another row. Layout mirrors the
// BFME1 mapper.h donor (ScreenMapper adds no members over LinearOffset, total
// 0x34, so the implicit copy ctor calls the matched LinearOffset base copy
// @0x00184270 then installs the derived vtable 0x007D32D0). BFME2 retail uses
// plain global operator new (rowed @0x2FDA0), so ::new here. Slot 3 of vtable
// 0x007D32D0 (same primary as ScreenMapper ctor); donor is BFME1
// ScreenMapperClass::Clone returning NEW_REF ScreenMapper.

class Vector2
{
public:
	float X;
	float Y;
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

class ScaleTextureMapperClass : public TextureMapperClass
{
public:
	ScaleTextureMapperClass(const ScaleTextureMapperClass &src);

protected:
	Vector2 Scale;
};

class LinearOffsetTextureMapperClass : public ScaleTextureMapperClass
{
public:
	LinearOffsetTextureMapperClass(const LinearOffsetTextureMapperClass &src);

protected:
	Vector2 CurrentUVOffset;
	Vector2 UVOffsetDeltaPerMS;
	unsigned int LastUsedSyncTime;
	Vector2 StartingUVOffset;
	bool ClampFix;
};

class ScreenMapperClass : public LinearOffsetTextureMapperClass
{
public:
	virtual TextureMapperClass *Clone() const;
};

TextureMapperClass *ScreenMapperClass::Clone() const
{
	return ::new ScreenMapperClass(*this);
}
