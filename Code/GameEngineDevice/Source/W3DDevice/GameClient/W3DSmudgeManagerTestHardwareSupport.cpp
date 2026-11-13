// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
//
// W3DSmudgeManager::testHardwareSupport, retail 0x000A648C, 930 bytes.
// Ported from Open-BFME-1's
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudgeManagerTestHardwareSupport.cpp
// (donor revision d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c, BFME 1 retail
// 0x00722640), itself the GeneralsMD W3DSmudge.cpp probe on BFME's D3D9
// device slots. /O1 /arch:SSE /G7 as the sibling W3DSmudge donor units.
//
// Target evidence (BFME 2 bytes): the body sits in W3DSmudge's run between
// copyRect 0x000A6270 and render 0x000A6E08, calls copyRect twice with the
// 8x8 block, and tests and writes the support status at +4 with the GeneralsMD
// values (0 unknown, 1 no, 2 yes). BFME 2 deltas from the donor, each read
// from the bytes:
//  - W3DShaderManager::getRenderTexture is the out-of-line getter 0x00075E36
//    (reads the render texture static at VA 0x00DE1F68);
//  - Display::getWidth/getHeight sit at vtable +0x40/+0x44;
//  - the FVF is set through DX8Wrapper (the call is counted in
//    number_of_DX8_calls), the draws go straight to the device;
//  - the vertex array takes no constructor call.

#include <string.h>

typedef int Int;
typedef int Bool;
typedef float Real;
#include <d3d9.h>

#define UNIQUE_COLOR (0x12345678)
#define BLOCK_SIZE (8)

// vector4.h gives Vector4 a user-defined default constructor.  That matters:
// with /EHsc the four-element vertex array then uses the retail vector
// constructor iterator at the same point in the frame.
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../GameEngine/Include/Common/IDirect3DBaseTexture8.h"

struct IDirect3DTexture8 : public IDirect3DBaseTexture8
{
};

// The device and textures keep their D3D8 type names (DX8Wrapper's static
// decorations) but are Direct3D 9 objects: SetTexture is slot 65,
// DrawPrimitiveUP slot 83, and the FVF setter ZH spells Set_Vertex_Shader is
// SetFVF, slot 89; texture AddRef / Release are slots 1 / 2.
struct IDirect3DDevice8;

#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"

#include "../../../../GameEngine/Include/Common/W3DMPO.h"



#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"


// This TU already mirrors TextureBaseClass by name; the release declaration
// below is the same member signature the shared header declares
// (game/Libraries/Source/WWVegas/WW3D2/texture.h:78), so the call spells
// ?Release_Ref@TextureBaseClass@@QAEXXZ (retail 0x9EB7A0). texture.h itself
// cannot be included here: it pulls refcount.h/wwstring.h, which redefine the
// W3DMPO/RefCountClass/StringClass mirrors this probe depends on.
class TextureBaseClass
{
public:
	void Release_Ref(void);
};

// The stage reference releases through TextureClass::Release_Ref, the ICF
// alias of the same retail body (0x0061ED10), as BfmeConv1137Uninstall.cpp's
// view does, so both units emit one destructor.
class TextureClass : public TextureBaseClass
{
public:
	void Release_Ref(void);
};

// Reuse the rowed four-byte RefCountPtr<TextureClass> lifetime view.
// Native EH cleanup760A55 calls its complete12B destructor17098D, whose
// release call61ED10 already has the TextureClass provider. The null
// constructor and base-pointer reference conversion preserve the donor ABI;
// this does not establish the original target wrapper spelling.
template<class T>
class RefCountPtr
{
	T *Texture;

public:
	RefCountPtr(void) : Texture(NULL) {}
	~RefCountPtr(void)
	{
		if (Texture)
			Texture->Release_Ref();
	}
	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&Texture;
	}
};

extern void BoxSetTexture(unsigned index, TextureBaseClass *&texture);
extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
protected:
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static IDirect3DBaseTexture8 *Textures[8];
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_changes;

public:
	static void Apply_Render_State_Changes(void);
	static IDirect3DDevice8 *_Get_D3D_Device8(void)
	{
		return D3DDevice;
	}

	static __forceinline void Set_Vertex_Shader(DWORD vertex_shader)
	{
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetFVF(vertex_shader);
		++number_of_DX8_calls;
	}

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		if (material)
			const_cast<VertexMaterialClass *>(material)->Add_Ref();
		if (render_state.material)
			render_state.material->Release_Ref();
		render_state.material = const_cast<VertexMaterialClass *>(material);
		render_state_changed |= 0x4000;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty &&
			shader.ShaderBits == render_state.shader.ShaderBits)
			return;

		render_state.shader = shader;
		render_state_changed |= 0x8000;
		StringClass str;
	}

	static __declspec(dllimport) __forceinline void Set_DX8_Texture(unsigned int stage,
		IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 8)
		{
			IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8());
			device->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
			++number_of_DX8_calls;
			return;
		}

		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->Release();
		Textures[stage] = texture;
		if (texture)
			reinterpret_cast<IDirect3DBaseTexture9 *>(texture)->AddRef();
		IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(_Get_D3D_Device8());
		device->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
		++number_of_DX8_calls;
		++texture_changes;
	}
};

class SmudgeManager
{
public:
	virtual ~SmudgeManager(void);
	virtual void init(void);
	virtual void reset(void);
	virtual void ReleaseResources(void);
	virtual void ReAcquireResources(void);

	enum HardwareSmudgeSupport
	{
		SMUDGE_SUPPORT_UNKNOWN = 0,
		SMUDGE_SUPPORT_NO = 1,
		SMUDGE_SUPPORT_YES = 2
	};

	HardwareSmudgeSupport m_hardwareSupportStatus;
	char m_pad[0x1C];
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	bool testHardwareSupport(void);
};

#include "../../../../GameEngine/Include/GameClient/Display.h"

extern Display *TheDisplay;

extern Int copyRect(unsigned char *buffer, Int buffer_size, int origin_x,
	int origin_y, int width, int height);

bool W3DSmudgeManager::testHardwareSupport(void)
{
	if (m_hardwareSupportStatus == SMUDGE_SUPPORT_UNKNOWN)
	{
		IDirect3DTexture8 *backTexture = W3DShaderManager::getRenderTexture();
		if (!backTexture)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		if (!W3DShaderManager::isRenderingToTexture())
			return false;

		VertexMaterialClass *vmat =
			VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		if (vmat)
			vmat->Release_Ref();

		ShaderClass shader = ShaderClass::_PresetOpaqueShader;
		shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
		shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
		DX8Wrapper::Set_Shader(shader);
		{
			RefCountPtr<TextureClass> texture;
			BoxSetTexture(0, texture);
		}
		DX8Wrapper::Apply_Render_State_Changes();

		struct _TRANS_LIT_TEX_VERTEX
		{
			Vector4 p;
			DWORD color;
			float u;
			float v;
		} v[4];

		v[0].p = Vector4(BLOCK_SIZE - 0.5f, BLOCK_SIZE - 0.5f, 0.0f, 1.0f);
		v[0].u = BLOCK_SIZE / (Real)TheDisplay->getWidth();
		v[0].v = BLOCK_SIZE / (Real)TheDisplay->getHeight();
		v[1].p = Vector4(BLOCK_SIZE - 0.5f, 0 - 0.5f, 0.0f, 1.0f);
		v[1].u = BLOCK_SIZE / (Real)TheDisplay->getWidth();
		v[1].v = 0;
		v[2].p = Vector4(0 - 0.5f, BLOCK_SIZE - 0.5f, 0.0f, 1.0f);
		v[2].u = 0;
		v[2].v = BLOCK_SIZE / (Real)TheDisplay->getHeight();
		v[3].p = Vector4(0 - 0.5f, 0 - 0.5f, 0.0f, 1.0f);
		v[3].u = 0;
		v[3].v = 0;

		v[0].color = UNIQUE_COLOR;
		v[1].color = UNIQUE_COLOR;
		v[2].color = UNIQUE_COLOR;
		v[3].color = UNIQUE_COLOR;

		IDirect3DDevice9 *pDev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
		DX8Wrapper::Set_Vertex_Shader(0x144);
		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

		DWORD refData[BLOCK_SIZE * BLOCK_SIZE];
		memset(refData, 0, sizeof(refData));
		Int bufSize = copyRect((unsigned char *)refData, sizeof(refData),
			0, 0, BLOCK_SIZE, BLOCK_SIZE);
		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		DX8Wrapper::Set_DX8_Texture(0, backTexture);

		DWORD testData[BLOCK_SIZE * BLOCK_SIZE];
		memset(testData, 0xff, sizeof(testData));

		v[0].color = 0xffffffff;
		v[1].color = 0xffffffff;
		v[2].color = 0xffffffff;
		v[3].color = 0xffffffff;

		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
		bufSize = copyRect((unsigned char *)testData, sizeof(testData),
			0, 0, BLOCK_SIZE, BLOCK_SIZE);
		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		if (memcmp(testData, refData, (unsigned)bufSize) == 0)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_YES;
			return true;
		}
		m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
	}

	return m_hardwareSupportStatus == SMUDGE_SUPPORT_YES;
}
