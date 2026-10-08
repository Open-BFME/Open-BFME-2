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

// Surface lock/unlock under their ledger names (0x00116680 returns the bits
// and the pitch; 0x00116760 unlocks).
class Rva00116680
{
public:
	void *rva00116680(int *pitch, bool discard);
};

class Member0C00739C70
{
public:
	void clear();
};

class Rva00072B3A
{
public:
	RvaTextureHandleView rva00072B3A() const;
	void rva00072E84(unsigned char level, Rva00116680 *surface);
private:
	char m_pad[0x1c];
	RvaTextureHandleView m_texture;
	int m_dstTextureWidth;   // +0x20 (Zero Hour's name for the border fill extent)
	int m_dstTextureHeight;  // +0x24
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

// TheGlobalData view: the shroud colour as red/green/blue floats at
// +0xBDC/+0xBE0/+0xBE4 and the minimum shroud level byte at +0xBEA.
class GlobalData
{
public:
	char m_pad[0xBDC];
	float m_shroudRed;
	float m_shroudGreen;
	float m_shroudBlue;
	char m_padBE8[0xBEA - 0xBE8];
	unsigned char m_shroudAlpha;
};

extern GlobalData *TheGlobalData;

// Reference-returning clamps; retail's min tests a < b (not STLport's
// b < a), as its select order shows.
template <class T> inline const T &ShroudMax(const T &a, const T &b) { return a < b ? b : a; }
template <class T> inline const T &ShroudMin(const T &a, const T &b) { return a < b ? a : b; }

// Native 00072D5D..00072E10, cdecl. Converts a shroud level to the shroud
// texture's 4444 pixel: each colour channel is the level scaled by the
// shroud colour, alpha ramps from level 4 to 50, and a fully visible level
// (255) is opaque white. Zero Hour inlines the colour part in each fill.
unsigned short __cdecl Rva00072D5DShroudPixel(unsigned char level)
{
	int value = level;
	unsigned int blue = (unsigned int)(value * TheGlobalData->m_shroudBlue);
	unsigned int green = (unsigned int)(value * TheGlobalData->m_shroudGreen);
	unsigned int red = (unsigned int)(value * TheGlobalData->m_shroudRed);
	int alpha = ShroudMin((ShroudMax(0, value - 4) * 255) / 46, 255);
	if (level == 255) {
		red = 255;
		green = 255;
		blue = 255;
		alpha = 255;
	}
	return (unsigned short)(((alpha & 0xf0) << 8) | ((red & 0xf0) << 4) | (green & 0xf0) | ((blue >> 4) & 0xf));
}

// Native 00072E84..00072EEB. Zero Hour's fillBorderShroudData destination
// fill: the level is raised to the global minimum, converted once, and
// written to every texel of the locked surface.
void Rva00072B3A::rva00072E84(unsigned char level, Rva00116680 *surface)
{
	if (level < TheGlobalData->m_shroudAlpha)
		level = TheGlobalData->m_shroudAlpha;
	unsigned short pixel = Rva00072D5DShroudPixel(level);
	int pitch;
	unsigned short *ptr = (unsigned short *)surface->rva00116680(&pitch, false);
	for (int y = 0; y < m_dstTextureHeight; y++) {
		for (int x = 0; x < m_dstTextureWidth; x++)
			ptr[x] = pixel;
		ptr = (unsigned short *)((char *)ptr + pitch);
	}
	reinterpret_cast<Member0C00739C70 *>(surface)->clear();
}
