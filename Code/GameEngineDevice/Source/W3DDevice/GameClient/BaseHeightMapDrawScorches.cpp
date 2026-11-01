// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// Target 0x000693AE..0x000694A3, RET 0 (245 bytes). Zero Hour's
// BaseHeightMapRenderObjClass::drawScorches (BaseHeightMap.cpp) in its BFME2
// form: updateScorches (0x000678BB, pinned) first, then nothing when no
// scorch index is staged; otherwise the alpha shader (with hardware fog when
// the wrapper's fog flag is on), the scorch index/vertex buffers and texture,
// a depth bias of 1, the render-state flush and two direct sampler-0 writes
// (IDirect3DDevice9::SetSamplerState, slot 69: ADDRESSU / ADDRESSV clamp,
// counted as texture-stage changes) before the draw, and the bias back to 0.
// Is_Hidden is vtable slot 100 (+0x190); the draw is skipped while hidden.

#include <d3d9.h>

class IndexBufferClass;
class VertexBufferClass;
class TextureBaseClass;

// The device keeps its D3D8 type name but is a Direct3D 9 device.
struct IDirect3DDevice8;

extern unsigned number_of_DX8_calls;

class DX8Wrapper;
class ShaderClass
{
protected:
	friend class DX8Wrapper;
public:
	static ShaderClass _PresetAlphaShader;
	static ShaderClass _PresetMultiplicativeShader;
protected:
	static bool ShaderDirty;
public:
	void Enable_Fog(const char *source);
	unsigned bits; // +0x00
};

class DX8Wrapper
{
	friend class BaseHeightMapRenderObjClass;
public:
	static void Set_Shader(const ShaderClass &shader);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Apply_Render_State_Changes();
	static void Draw_Triangles(unsigned buffer_type, unsigned start_index, unsigned min_vertex_index, unsigned vertex_count);
protected:
	static bool FogEnable;
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_stage_state_changes;
};

struct BFME2TextureRef
{
public:
	TextureBaseClass *p; // +0x00
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);
void bfmeSetProjectionDepthBias(float bias);

class BaseHeightMapRenderObjClass
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual int Is_Hidden();
	void updateScorches();
	void drawScorches();

private:
	char m_pad04[0xCC - 4];
	VertexBufferClass *m_vertexScorch;	// +0xCC
	IndexBufferClass *m_indexScorch;	// +0xD0
	BFME2TextureRef m_scorchTexture;	// +0xD4
	int m_curNumScorchVertices;	// +0xD8
	int m_curNumScorchIndices;	// +0xDC
};

void BaseHeightMapRenderObjClass::drawScorches()
{
	updateScorches();
	if (m_curNumScorchIndices == 0)
		return;
	if (Is_Hidden() != 0)
		return;

	ShaderClass shader = ShaderClass::_PresetAlphaShader;
	if (DX8Wrapper::FogEnable)
		shader.Enable_Fog("HardwareFog");
	DX8Wrapper::Set_Shader(shader);
	DX8Wrapper::Set_Index_Buffer(m_indexScorch, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexScorch, 0);
	BFME2Set_Texture(0, m_scorchTexture);
	bfmeSetProjectionDepthBias(1.0f);
	DX8Wrapper::Apply_Render_State_Changes();
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	++number_of_DX8_calls;
	++DX8Wrapper::texture_stage_state_changes;
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	++number_of_DX8_calls;
	++DX8Wrapper::texture_stage_state_changes;
	DX8Wrapper::Draw_Triangles(0, m_curNumScorchIndices / 3, 0, m_curNumScorchVertices);
	bfmeSetProjectionDepthBias(0.0f);
}
