// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva000FDD1C@Rva000FDD1C@@QAE_NHHHH@Z @0x000FDD1C 147B: stored function pointer at table slot 3 near GameFileClass::Create and RenderObjClass::_bfme_ro_v50; renderer behavior follows the table role and retail call sequence, while class identity remains unproven.

struct IDirect3DBaseTexture8
{
	void **m_vtable;
};

struct IDirect3DTexture8 : IDirect3DBaseTexture8
{
};

struct IDirect3DDevice8
{
	void **m_vtable;
};

typedef unsigned long (__stdcall *TextureReferenceFunction)(IDirect3DBaseTexture8 *);
typedef long (__stdcall *SetTextureFunction)(IDirect3DDevice8 *, unsigned long, IDirect3DBaseTexture8 *);

struct Vector2
{
	float x;
	float y;
};

struct W3DShaderManager
{
	static IDirect3DTexture8 *endRenderToTexture();
	static void drawViewport(int color, bool flip, const Vector2 *uv);
};

struct Rva000FDD1C;

struct DX8Wrapper
{
	friend struct Rva000FDD1C;
	private:
	static IDirect3DBaseTexture8 *Textures[1];
	static int texture_changes;
	static IDirect3DDevice8 *D3DDevice;
};
extern int number_of_DX8_calls;

struct Rva000FDD1C
{
	virtual void f00() = 0;
	virtual void f01() = 0;
	virtual void f02() = 0;
	virtual void f03() = 0;
	virtual void f04() = 0;
	virtual int rva000FDD1CFirst(int arg);
	virtual void rva000FDD1CNext();
	bool rva000FDD1C(int arg1, int arg2, int arg3, int arg4);
};

bool Rva000FDD1C::rva000FDD1C(int arg1, int arg2, int arg3, int arg4)
{
	IDirect3DTexture8 *texture = W3DShaderManager::endRenderToTexture();
	if (!texture)
		return false;
	if (!rva000FDD1CFirst(arg1))
		return false;
	{
		if (DX8Wrapper::Textures[0] != texture)
		{
			if (DX8Wrapper::Textures[0])
				((TextureReferenceFunction)DX8Wrapper::Textures[0]->m_vtable[2])(DX8Wrapper::Textures[0]);
			DX8Wrapper::Textures[0] = texture;
			((TextureReferenceFunction)texture->m_vtable[1])((IDirect3DBaseTexture8 *)texture);
			((SetTextureFunction)DX8Wrapper::D3DDevice->m_vtable[65])(DX8Wrapper::D3DDevice, 0, texture);
			++number_of_DX8_calls;
			++DX8Wrapper::texture_changes;
		}
		Vector2 uv;
		uv.x = 1.0f;
		uv.y = 1.0f;
		W3DShaderManager::drawViewport(-1, false, &uv);
		rva000FDD1CNext();
		return true;
	}
	return false;
}
