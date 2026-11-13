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

// The established owning-handle copy at424BB is a 21-byte twin of the
// Native=AssetReference constructor emitted by MaterialInfoTextureHandles.
class AssetReference { public: void *m_object; };
template <class T> class RefCountPtr
{
public:
    AssetReference m_native;
    RefCountPtr();
    RefCountPtr(const RefCountPtr<T> &rhs);
    template<class Native> __declspec(noinline) RefCountPtr(const Native &other)
    {
        m_native.m_object = other.m_object;
        if (m_native.m_object)
            ++*(unsigned short *)((char *)m_native.m_object + 4);
    }
    ~RefCountPtr()
    {
        T *referencedObject = (T *)m_native.m_object;
        if (referencedObject) referencedObject->Release_Ref();
    }
    const RefCountPtr<T> &operator=(const RefCountPtr<T> &rhs);
};
class RvaTextureHandleView : public RefCountPtr<TextureClass>
{
public:
    __forceinline RvaTextureHandleView(const AssetReference &rhs)
        : RefCountPtr<TextureClass>(rhs) {}
};

// Surface lock/unlock under their ledger names (0x00116680 returns the bits
// and the pitch; 0x00116760 unlocks).
#include "../../../../Libraries/Source/WWVegas/WW3D2/Rva00116680.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/Member0C00739C70.h"

class Rva00072B3A
{
public:
	RvaTextureHandleView getShroudTexture() const;
	void fillShroudData(unsigned char level);
	void rva00072E84(unsigned char level, Rva00116680 *surface);
private:
	int m_numCellsX;         // +0x00
	int m_numCellsY;         // +0x04
	char m_pad08[0x10];
	unsigned short *m_shroudData;  // +0x18
	RvaTextureHandleView m_texture;
	int m_dstTextureWidth;   // +0x20 (Zero Hour's name for the border fill extent)
	int m_dstTextureHeight;  // +0x24
	char m_pad28[0x10];
	unsigned char *m_finalFogData;  // +0x38
};

RvaTextureHandleView Rva00072B3A::getShroudTexture() const
{
	return RvaTextureHandleView(m_texture.m_native);
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

};

// Native DE1F8C..DE1FAB holds eight four-byte nullable texture slots.
// The indexed F5D1B getter and the 76790 eight-slot reset prove the layout.
// This raw pointer array has no startup constructor or exit destructor;
// assignment and release are performed through the established handle view.
RefCountPtr<TextureClass> g_shaderTextureSlots[8];
typedef char ShaderTextureHandleWidth[sizeof(RefCountPtr<TextureClass>) == sizeof(void *) ? 1 : -1];

// ?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ @0x00072EEB
void W3DShroudMaterialPassClass::Install_Materials() const
{
	if (TheTerrainRenderObject->getShroud())
	{
		reinterpret_cast<RefCountPtr<TextureClass> *>(g_shaderTextureSlots)[0] = TheTerrainRenderObject->getShroud()->getShroudTexture();
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

#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

void W3DShaderManager::setTexture(int stage, const TextureHandle &texture)
{
	reinterpret_cast<RefCountPtr<TextureClass> *>(g_shaderTextureSlots)[stage] = texture;
}

// TheGlobalData view: the shroud colour as red/green/blue floats at
// +0xBDC/+0xBE0/+0xBE4 and the minimum shroud level byte at +0xBEA.
#include "../../../../GameEngine/Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

// Reference-returning clamps; retail's min tests a < b (not STLport's
// b < a), as its select order shows.
template <class T> inline const T &ShroudMax(const T &left, const T &right) { return left < right ? right : left; }
template <class T> inline const T &ShroudMin(const T &left, const T &right) { return left < right ? left : right; }

// Native 00072D5D..00072E10, cdecl. Converts a shroud level to the shroud
// texture's 4444 pixel: each colour channel is the level scaled by the
// shroud colour, alpha ramps from level 4 to 50, and a fully visible level
// (255) is opaque white. Zero Hour inlines the colour part in each fill.
unsigned short __cdecl Rva00072D5DShroudPixel(unsigned char level)
{
	int value = level;
	unsigned int blue = (unsigned int)(value * TheGlobalData->m_shroudColor.blue);
	unsigned int green = (unsigned int)(value * TheGlobalData->m_shroudColor.green);
	unsigned int red = (unsigned int)(value * TheGlobalData->m_shroudColor.red);
	int alpha = ShroudMin((ShroudMax(0, value - 4) * 255) / 46, 255);
	if (level == 255) {
		red = 255;
		green = 255;
		blue = 255;
		alpha = 255;
	}
	return (unsigned short)(((alpha & 0xf0) << 8) | ((red & 0xf0) << 4) | (green & 0xf0) | ((blue >> 4) & 0xf));
}

// Native 00072E10..00072E82 RET4. BFME 1's W3DShroud::fillShroudData
// (donor W3DShroud_fillShroudData.cpp, BFME 1 retail 0x0071A520): the level
// is raised to the global minimum, every shroud pixel (+0x18) gets its packed
// value and the logical levels (+0x38) get the level. The second loop
// rewrites the first row only, as the donor does.
void Rva00072B3A::fillShroudData(unsigned char level)
{
	int column;
	int row;
	unsigned short pixel;
	unsigned short *shroud;
	unsigned char *fog;

	if (level < TheGlobalData->m_shroudAlpha)
		level = TheGlobalData->m_shroudAlpha;

	pixel = Rva00072D5DShroudPixel(level);
	shroud = m_shroudData;
	for (row = 0; row < m_numCellsY; ++row)
	{
		for (column = 0; column < m_numCellsX; )
		{
			*shroud = pixel;
			++column;
			++shroud;
		}
	}

	fog = m_finalFogData;
	for (row = 0; row < m_numCellsY; ++row)
	{
		for (column = 0; column < m_numCellsX; ++column)
		{
			fog[column] = level;
		}
	}
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
	for (int row = 0; row < m_dstTextureHeight; row++) {
		for (int column = 0; column < m_dstTextureWidth; column++)
			ptr[column] = pixel;
		ptr = (unsigned short *)((char *)ptr + pitch);
	}
	reinterpret_cast<Member0C00739C70 *>(surface)->clear();
}
