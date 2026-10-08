// cl: /MD /EHsc /DNDEBUG
//
// ?UnInstall_Materials@W3DShroudMaterialPassClass@@UBEXXZ, retail 0x000729EB, 9 bytes.
// Slot 3 of ??_7W3DShroudMaterialPassClass 0x00BC6244 (WW3D MaterialPassClass
// order: Delete_This, ??_G, Install_Materials, UnInstall_Materials). Donor ZH
// W3DShroud.cpp: W3DShaderManager::resetShader(ST_SHROUD_TEXTURE); retail
// pushes 1 to the rowed static at 0x00075695, rowed here under its address
// name Rva00075695Notify.
//
// ?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ, retail 0x00072EEB, 94 bytes.
// Slot 2. Donor ZH W3DShroud.cpp: if the terrain has a shroud, bind its texture
// to shader stage 0 and set ST_SHROUD_TEXTURE. BFME2 drops the terrain null
// test, reads the shroud twice (as the donor's getShroud() calls do), and the
// texture getter returns a ref-counted handle by value. Callees are the pinned
// address views 0x00072B3A (shroud texture), 0x000424D0 (RefCountPtr assign)
// and 0x00075655 (setShader); the stage-0 slot is the array at 0x00DE1F8C.

void __cdecl Rva00075695Notify(int index);

class W3DShroudMaterialPassClass
{
public:
	virtual void Delete_This();
	virtual ~W3DShroudMaterialPassClass();
	virtual void Install_Materials() const;
	virtual void UnInstall_Materials() const;
};

// ?UnInstall_Materials@W3DShroudMaterialPassClass@@UBEXXZ @0x000729EB
void W3DShroudMaterialPassClass::UnInstall_Materials() const
{
	Rva00075695Notify(1); // W3DShaderManager::ST_SHROUD_TEXTURE
}

class TextureClass
{
public:
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr<T> &rhs);
	~RefCountPtr()
	{
		if (m_ref)
		{
			m_ref->Release_Ref();
		}
	}
	const RefCountPtr<T> &operator=(const RefCountPtr<T> &rhs);

private:
	T *m_ref;
};

class RvaTextureHandleView : public RefCountPtr<TextureClass>
{
};

class Rva00072B3A
{
public:
	RvaTextureHandleView rva00072B3A() const;
private:
	char m_pad[0x1c];
	RvaTextureHandleView m_texture;
};

RvaTextureHandleView Rva00072B3A::rva00072B3A() const
{
	return m_texture;
}

class BaseHeightMapRenderObjClass
{
public:
	Rva00072B3A *getShroud() { return m_shroud; }

private:
	char m_pad[0x3878];
	Rva00072B3A *m_shroud;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class Rva00075655
{
public:
	static int setShader(int shader, int pass);
	static RefCountPtr<TextureClass> m_Textures[];
};

// ?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ @0x00072EEB
void W3DShroudMaterialPassClass::Install_Materials() const
{
	if (TheTerrainRenderObject->getShroud())
	{
		Rva00075655::m_Textures[0] = TheTerrainRenderObject->getShroud()->rva00072B3A();
		// W3DShaderManager::ST_SHROUD_TEXTURE, pass 0
		Rva00075655::setShader(1, 0);
	}
}

// ?setTexture@W3DShaderManager@@SAXHABVTextureHandle@@@Z, retail 0x00072B25,
// 21 bytes: Zero Hour's inline W3DShaderManager::setTexture, emitted out of
// line. It assigns into the stage slot of the same 0x00DE1F8C array through
// the rowed RefCountPtr assignment 0x000424D0. Placed by compiling the
// Open-BFME-1 donor W3DShroudMaterialPassClass_Install_Materials.cpp at /O1.
class TextureHandle : public RefCountPtr<TextureClass>
{
};

class W3DShaderManager
{
public:
	static void setTexture(int stage, const TextureHandle &texture);
};

void W3DShaderManager::setTexture(int stage, const TextureHandle &texture)
{
	Rva00075655::m_Textures[stage] = texture;
}
