// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
// partial score=0.97 date=2026-09-25
// VH shape for ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
// @0x132B83 (80/79B): /O1 /G7 temp-chain (bpp-first, imul-6) plus post-call
// reload dual-reg (tex stays alive for b = tex->m_surface after the call).
// Remaining: reload mov edi,[edi+0x14] (3B) vs retail copy mov esi,edi (2B)
// pre-call, plus tex in edi vs retail esi. Pre-call b = a copies always merge
// under /O1 (with and without /G7); __forceinline boundary merges too.
enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0,
};

unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);

struct TextureSurfaceInfo
{
	int m_pad00[3];
	int m_type0C;
	int m_pad10[6];
	int m_dim28;
	int m_dim2C;
	int m_dim30;
	int m_pad34[4];
	int m_mip44;
	int m_pad48;
	int m_format4C;
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

	char m_pad04[16];
	TextureSurfaceInfo *m_surface;
};

struct Holder
{
	TextureClass *m_ptr;
	unsigned Get_Texture_Memory_Usage() const;
};

unsigned Holder::Get_Texture_Memory_Usage() const
{
	TextureClass *tex = m_ptr;
	if (tex == 0)
		return 0;
	if (!tex->Is_Initialized())
		return 0;
	TextureSurfaceInfo *a = tex->m_surface;
	unsigned mem = Get_Bits_Per_Pixel((WW3DFormat)a->m_format4C)
		* a->m_dim30 * a->m_dim2C * a->m_dim28 >> 3;
	TextureSurfaceInfo *b = tex->m_surface;
	if (b->m_type0C == 2)
		mem *= 6;
	if (b->m_mip44 != 1)
		mem = mem * 4 / 3;
	return mem;
}
