// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target 0x000693AE..0x000694A3, RET 0 (245 bytes). Zero Hour's
// BaseHeightMapRenderObjClass::drawScorches (BaseHeightMap.cpp) in its BFME2
// form: updateScorches (0x000678BB, pinned) first, then nothing when no
// scorch index is staged; otherwise the alpha shader (with hardware fog when
// the wrapper's fog flag is on), the scorch index/vertex buffers and texture,
// a depth bias of 1, the render-state flush and two direct texture-stage-0
// writes (state 1 and 2, value 3) before the draw, and the bias back to 0.
// Is_Hidden is vtable slot 100 (+0x190); the draw is skipped while hidden.

class IndexBufferClass;
class VertexBufferClass;
class TextureBaseClass;

struct IDirect3DDevice8
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void d55();
	virtual void d56();
	virtual void d57();
	virtual void d58();
	virtual void d59();
	virtual void d60();
	virtual void d61();
	virtual void d62();
	virtual void d63();
	virtual void d64();
	virtual void d65();
	virtual void d66();
	virtual void d67();
	virtual void d68();
	virtual long __stdcall SetTextureStageState(unsigned stage, unsigned long state, unsigned value);
};

extern unsigned number_of_DX8_calls;

class ShaderClass
{
public:
	unsigned bits;
	void Enable_Fog(const char *source);
	static ShaderClass _PresetAlphaShader;
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
	TextureBaseClass *p;
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
	DX8Wrapper::D3DDevice->SetTextureStageState(0, 1, 3);
	++number_of_DX8_calls;
	++DX8Wrapper::texture_stage_state_changes;
	DX8Wrapper::D3DDevice->SetTextureStageState(0, 2, 3);
	++number_of_DX8_calls;
	++DX8Wrapper::texture_stage_state_changes;
	DX8Wrapper::Draw_Triangles(0, m_curNumScorchIndices / 3, 0, m_curNumScorchVertices);
	bfmeSetProjectionDepthBias(0.0f);
}
