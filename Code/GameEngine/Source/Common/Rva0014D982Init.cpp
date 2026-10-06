// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
// ?rva0014D982@Rva0014D982This@@QAEXPAUID3DXEffect@@PBD@Z retail 0x0014D982 113 bytes. Texture effect callback with WhiteTexture fallback. Evidence: bracket contiguity prev 0x0014D722 next 0x0014D9F3 same // cl: plus EHsc for RefCountPtr temp; this+0x48 TextureBaseClass member null-checked like sibling Rva0014D9F3This; callees rowed Peek 0x0013270C Release 0x0061ED10 plus pinned WhiteTexture 0x00132E76; virtual SetTexture slot 52 (+0xD0) same as W3DTerrainTexturePtrGetters; REF constant at 0x0014FFB4 callback.
struct IDirect3DBaseTexture8;

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class TextureClass
{
public:
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const
	{
		return ((const TextureBaseClass *)this)->Peek_D3D_Base_Texture();
	}
private:
	T *m_ptr;
};

typedef const char *D3DXHANDLE;

struct ID3DXEffect
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual long __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture);
};

RefCountPtr<TextureClass> Rva00132E76WhiteTexture();

class Rva0014D982This
{
public:
	void rva0014D982(ID3DXEffect *effect, D3DXHANDLE handle);
private:
	char m_pad00[0x48];
	TextureBaseClass m_tex48;
};

void Rva0014D982This::rva0014D982(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (*(void **)&m_tex48 != 0)
		effect->SetTexture(handle, m_tex48.Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}
