// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
// partial score=0.9 date=2026-09-25
// cl: /O1 /MD /DNDEBUG
// RefCountPtr<TextureClass>::Get_Texture_Memory_Usage (retail 0x00132B83, 79B).
// Null-guarded smart-pointer query: checks virtual Is_Initialized at slot 0x28,
// then computes bits-per-pixel via rowed Get_Bits_Per_Pixel 0x00131A9D times
// dimensions over 8, times 6 for type 2, times 4/3 unless single mipmap.

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0,
};

unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);

struct TextureSurfaceInfo
{
	int m_pad00[3]; // +0x00..0x0B
	int m_type0C; // +0x0C
	int m_pad10[6]; // +0x10..0x27
	int m_dim28; // +0x28
	int m_dim2C; // +0x2C
	int m_dim30; // +0x30
	int m_pad34[4]; // +0x34..0x43
	int m_mip44; // +0x44
	int m_pad48; // +0x48..0x4B
	int m_format4C; // +0x4C
};

class TextureClass
{
public:
	virtual ~TextureClass();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual bool Is_Initialized();

	char m_pad04[16]; // +0x04..0x13
	TextureSurfaceInfo *m_surface; // +0x14
};

template <class T>
class RefCountPtr
{
public:
	unsigned Get_Texture_Memory_Usage() const;

private:
	T *m_ptr; // +0x00
};

// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
template <>
unsigned RefCountPtr<TextureClass>::Get_Texture_Memory_Usage() const
{
	TextureClass *tex = m_ptr;
	if (tex == 0)
		return 0;
	if (!tex->Is_Initialized())
		return 0;
	TextureSurfaceInfo *ediInfo = tex->m_surface;
	unsigned fmt = ediInfo->m_format4C;
	TextureSurfaceInfo *esiInfo = tex->m_surface;
	unsigned mem = Get_Bits_Per_Pixel((WW3DFormat)fmt);
	mem = mem * esiInfo->m_dim30 * esiInfo->m_dim2C * esiInfo->m_dim28 >> 3;
	if (esiInfo->m_type0C == 2)
		mem = mem * 6;
	if (ediInfo->m_mip44 != 1)
		mem = mem * 4 / 3;
	return mem;
}
