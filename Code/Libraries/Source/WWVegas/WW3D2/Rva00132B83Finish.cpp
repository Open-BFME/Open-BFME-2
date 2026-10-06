// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
// partial score=0.98 date=2026-10-03
// ?Get_Texture_Memory_Usage@?$RefCountPtr@VTextureClass@@@@QBEIXZ
// cl: /MD
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);
struct TextureSurfaceInfo {
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
class TextureBaseClass { public: void Add_Ref(); void Release_Ref(); };
class TextureClass : public TextureBaseClass {
public:
	virtual ~TextureClass();
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual bool Is_Initialized() const;
	char m_pad04[16];
	TextureSurfaceInfo *m_surface;
	__forceinline unsigned Get_Memory_Size() const
	{
		if (!Is_Initialized())
			return 0;
		TextureSurfaceInfo *surface = m_surface;
		unsigned mem = Get_Bits_Per_Pixel((WW3DFormat)m_surface->m_format4C)
			* m_surface->m_dim30 * m_surface->m_dim2C * m_surface->m_dim28 >> 3;
		if (m_surface->m_type0C == 2)
			mem *= 6;
		if (surface->m_mip44 != 1)
			mem = mem * 4 / 3;
		return mem;
	}
};
template<class T>
class RefCountPtr {
public:
	T *Referent;
	unsigned Get_Texture_Memory_Usage() const
	{
		if (Referent == 0)
			return 0;
		return Referent->Get_Memory_Size();
	}
};
template class RefCountPtr<TextureClass>;
